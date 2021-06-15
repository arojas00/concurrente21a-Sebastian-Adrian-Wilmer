// Copyright 2021 Wilmer Araya <wilmer.araya@ucr.ac.cr> CC-BY-4
#include <assert.h>
#include <errno.h>
#include <pthread.h>
#include <queue>
#include <semaphore.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "QueueSums.hpp"

typedef struct values{
  int64_t value; // valor
  queue_t* cola_sumas; // cola para guardar las sumas de cada valor
  bool signo; // Para guardar el signo del numero
  int cant_sumas; // La cantidad de sumas
} values_t;

typedef struct goldbach {
  size_t thread_count; // numero de hilos
  int64_t data_count; // numero de datos en total
  sem_t* can_print; // semaforo para controlar la concurrencia
  queue_t* cola_valores; // cola para almacenar los datos
  values_t* nums; 
  size_t cont_nums;
} goldbach_t;

typedef struct {
  goldbach_t* shared_data; // Los datos compartidos entre hilos
  size_t thread_number;
  values_t* values;
  size_t num_count;
} private_data_t;


/**
 * @brief Evalua si el numero ingresado es par o no
 * @details Si el resto de la division del numero entre 2 
 *          es igual a 0 significa que el numero es par
 * @param Numero a ser evaluado
 * @return Retorna true si el numero es par,
 *         de lo contrario retorna false
 */
bool esPar(int64_t value);
/**
 * @brief Evalua si el numero ingresado es primo o no
 * @details Si la division del numero ingresado da entero
 *          solo cuando se divide por si mismo y 1 significa que es primo.
 * @param Numero a ser evaluado
 * @return Retorna true si el numero es primo,
 *         de lo contrario retorna false
 */
bool esPrimo(int64_t value);
/**
 * @brief Calcula la cantidad de sumas goldbach que tiene cada numero
 * @details Se evaluan todas las posibles combinaciones de numeros primos
 *          mediante ciclos for, si el numero es par guarda los dos
 *          numeros que conforman la suma en el arreglo, si es impar guarda 
 *          los tres numeros que conforman la suma.
 * @param Numero a ser evaluado y el arreglo en el cual se guardan los numeros
 *        que conforman la suma.
 * @return Retorna la cantidad de sumas de goldbach
 */
int calcula_sumas(int64_t value, queue_t* cola_sumas, bool signo);

/**
 * @brief Encuentra un minimo entre dos numeros
 * @details ...
 * @param Numeros a ser evaluados 
 * @return numero menor entre a y b
 */
size_t min(size_t a, size_t b);

/**
 * @brief Calcula los bloques para realizar el mapeo por bloques
 * @details ...
 * @param Numero del hilo, cantidad total de datos, cantidad total de hilos
 * @return EL numero donde empieza cada bloque
 */
size_t start(size_t my_thread_id, size_t data_count, size_t thread_count);

/**
 * @brief Esta subrutina se encarga de crear los hilos e inicializar sus respectivos campos
 * @details ...
 * @param Numero el registro de datos compartidos que en este programa es llamado goldbach_t
 * @return Un numero entero que indica si hubo un error o no
 */
int create_threads(goldbach_t* goldbach);

/**
 * @brief Esta subrutina se encarga de realizar el trabajo conurrentemente
 * @details 
 * @param Numero el registro de datos compartidos que en este programa es llamado goldbach_t
 * @return Un numero entero que indica si hubo un error o no
 */
void* concurrencia(void* data);

goldbach_t* goldbach_create() {
  goldbach_t* goldbach = (goldbach_t*)
    calloc(1, sizeof(goldbach_t));
  if (goldbach) {
    goldbach->thread_count = 0;
    goldbach->data_count = 0;
    goldbach->cont_nums = 0;
  }
  return goldbach;
}

void goldbach_destroy(goldbach_t* goldbach) {
  assert(goldbach); // Se valida la memoria
  sem_destroy(goldbach->can_print);
  queue_destroy(goldbach->cola_valores);
  free(goldbach); // Se libera la memoria del registro goldbach
}

values_t* goldbach_run(goldbach_t* goldbach, std::queue<int64_t> queue_values) {
  assert(goldbach);
  int error = EXIT_SUCCESS;

  goldbach->thread_count = sysconf(_SC_NPROCESSORS_ONLN);
  /*if (argc == 2) {
    if (sscanf(argv[1], "%zu", &goldbach->thread_count) != 1 || errno) {
      fprintf(stderr, "error: invalid thread count\n");
      return EXIT_FAILURE;
    }
  }*/
  
  int64_t value = 0;

   goldbach->cola_valores = (queue_t*)
      calloc(1, sizeof(queue_t)); // Se crea el arreglo que contiene las sumas
  queue_init(goldbach->cola_valores); // Se inicializa el arreglo de sumas
  assert(goldbach->cola_valores);

  goldbach->data_count = queue_values.size();
  for (int i = 0; i < goldbach->data_count; i++) { 
    value = queue_values.front();
    queue_values.pop();
    queue_enqueue(goldbach->cola_valores, value);
  }
  
  goldbach->nums = new values_t[goldbach->data_count];

  if (error == EXIT_SUCCESS) {
    goldbach->can_print = (sem_t*) calloc(goldbach->thread_count
      , sizeof(sem_t));

    if (goldbach->can_print) {
      error = create_threads(goldbach);
      free(goldbach->can_print);
    } else {
      fprintf(stderr, "error: could not allocate semaphores\n");
      error = 3;
    }
  }

  return goldbach->nums;
}


bool esPar(int64_t value) {
  return (value%2) == 0;
}

bool esPrimo(int64_t value) {
  bool primo = false;
  if (value>1) {
    for (int64_t i = 2; i <= value; i++) {
      if (value%i == 0) { // Si el numero es divisible entre si mismo
        if (value == i) {
          primo = true;
        } else { // Si es divisible entre otro numero
          return false;
        }
      }
    }
  }
  return primo;
}

int calcula_sumas(int64_t value, queue_t* cola_sumas, bool signo) {
  int cantSumas = 0;
  for (int64_t i = 2; i < value; i++) { 
    if (esPrimo(i)) { // Busca el primer numero primo
      for (int64_t j = i; j < value; j++) {
        if (esPrimo(j)) { // Busca el segundo numero primo
          if (esPar(value)) { // Si el valor es par entonces la suma es de dos primos
            if ((i + j) == value) { // Si ambos primos sumados son iguales al valor
              cantSumas += 1; // Se incrementa la cantidad de sumas
              if (signo == 0) { // Si el numero es negativo se agregan a la cola de sumas
                queue_enqueue(cola_sumas, i);
                queue_enqueue(cola_sumas, j);
              }
            }
          } else { // Si el valor es impar se necesitan tres numeros primos
            for (int64_t k = j; k < value; k++) {
              if (esPrimo(k)) { // Busca el tercer numero primo
                if ((i + j + k) == value) { // Si los tres primos sumados son igual al valor
                  cantSumas += 1; // Se incrementa la cantidad de sumas
                  if (signo == 0) { // Si el numero es negativo se agregan a la cola de sumas
                    queue_enqueue(cola_sumas, i);
                    queue_enqueue(cola_sumas, j);
                    queue_enqueue(cola_sumas, k);
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  return cantSumas; // retorna la cantidad de sumas
}

size_t min(size_t a, size_t b) {
  size_t result = 0;
  if (a <= b) {
    result = a;
  } else {
    result = b;
  }
  return result;
}

size_t start(size_t my_thread_id, size_t data_count, size_t thread_count) {
  size_t result = my_thread_id * (data_count / thread_count)
    + min(my_thread_id, (data_count % thread_count));
  return result;
}

int create_threads(goldbach_t* goldbach) {
  assert(goldbach); // Validacion de memoria
  int error = EXIT_SUCCESS; 
  pthread_t* threads = (pthread_t*) calloc(goldbach->thread_count
    , sizeof(pthread_t)); // Se crea el arreglo de hilos
  private_data_t* private_data = (private_data_t*) 
    calloc(goldbach->thread_count, sizeof(private_data_t)); // Se crean los datos privados para cada hilo

  if (threads && private_data) {
    for (size_t index = 0; index < goldbach->thread_count; ++index) {
      private_data[index].shared_data = goldbach; // Se asignan los datos compartidos a cada hilo
      private_data[index].thread_number = index; // Se asigna un numero de identifiacion a cada hilo

      size_t inicio = start(index, goldbach->data_count, goldbach->thread_count); // Se calcula el inicio para realizar el mapeo por bloques
      size_t fin = start(index + 1, goldbach->data_count, goldbach->thread_count); // Se calcula donde va terminar cada bloque
      private_data[index].num_count = fin - inicio; // Se asigna a num_count el tamano del bloque

      private_data[index].values = (values_t*) 
        calloc(private_data[index].num_count, sizeof(values_t)); // Se crea el arreglo de valores que tendra cada hilo
      assert(private_data[index].values); // Se valida que se haya creado correctamente

      int64_t valor = 0;
      for (size_t j = 0; j < private_data[index].num_count; j++) {
        queue_dequeue(goldbach->cola_valores, &valor); // Se van sacando los valores de la cola de valores total
        private_data[index].values[j].value = valor; // Se asigna cada valor a un registro de value_t

        private_data[index].values[j].cola_sumas = (queue_t*)
        calloc(1, sizeof(queue_t)); // Se declara el arreglo que contiene las sumas
        queue_init(private_data->values->cola_sumas); // Se inicializa el arreglo de sumas
        assert(private_data->values->cola_sumas); 

        private_data->values->cant_sumas = 0; // Se inicializa cant_sumas
        if (valor < 0) { // Se guarda el signo del valor
          private_data->values->signo = 0;
        }
      }

      error = sem_init(&goldbach->can_print[index], /*pshared*/ 0
        , /*value*/ !index);

      if (pthread_create(&threads[index], /*attr*/ NULL, concurrencia
        , &private_data[index]) == EXIT_SUCCESS) {
      } else {
        fprintf(stderr, "error: could not create thread %zu\n", index);
        error = 21;
        break;
      }
    }

    for (size_t index = 0; index < goldbach->thread_count; ++index) {
      pthread_join(threads[index], /*value_ptr*/ NULL);
    }
    free(threads);
    free(private_data);
  } else {
    fprintf(stderr, "error: could not allocate memory for %zu threads\n"
      , goldbach->thread_count);
    error = 22;
  }
  
  return error;
}

void* concurrencia(void* data) {
  private_data_t* private_data = (private_data_t*)data;
  goldbach_t* shared_data = private_data->shared_data;
  const size_t my_thread_id = private_data->thread_number;
  const size_t thread_count = shared_data->thread_count;
  int64_t value = 0;

  for (size_t i = 0; i < private_data->num_count; i++) { // Desde cero hasta la cantidad de valores que debe analizar cada hilo
    value = private_data->values[i].value; 
    if (value < -5) { // Si el numero es negativo se pasa a positivo para calcular sus sumas con la misma funcion que a los positivos
      value = value * -1;    
    }
    if (value > 5) { // Si es mayor que 5 se calculan sus sumas
      private_data->values[i].cant_sumas = calcula_sumas(value
        , private_data->values[i].cola_sumas, private_data->values[i].signo);
    }
  }

  sem_wait(&shared_data->can_print[my_thread_id]); // Espera a que sea el primer hilo en imprimir
  for (size_t i = 0; i < private_data->num_count; i++) {
    shared_data->nums[shared_data->cont_nums] = private_data->values[i];
    //int num = shared_data->nums[shared_data->cont_nums].value;
    //printf(" %d", num);
    shared_data->cont_nums++;
  }
  sem_post(&shared_data->can_print[(my_thread_id + 1) % thread_count]); // Le da accesso al siguiente hilo para que imprima
  
  return NULL;
}

