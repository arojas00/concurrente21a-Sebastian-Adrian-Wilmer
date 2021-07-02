/// @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Sebastian-Adrian-Wilmer

#include <errno.h>
#include "Mago.hpp"
#include "matrix.hpp"

/*
/Funciones seriales del mago:
/(Wil)Leer mapa de entrada estandar y guardarlo en el arbol de memoria compartida y en la variable para serial y leer
/ la cantidad de noches(ciclos) y el tamano desde el txt
/(Adrian)Hacer funcionar las funciones del bosque con una matriz de ejemplo para generar un nuevo bosque(Mientras se completan las cosas de arriba)
/(Sebas)Despues de que se completa el nuevo bosque generar un archivo txt con el numero de noche(ciclo) en la carpeta bosques

/Guardar el nuevo bosque donde estaba el primero para recibirlo como parametro en el siguiente ciclo
/
/Funciones concurrentes del mago:
/Leer la cantidad de hilos que se quieren usar o usar la cantidad que tenga la maquina
/Guardar los arboles en memoria compartida
/Es posible que sea al mago que crea los hilos
*/
typedef struct
{
   size_t thread_count;
    Bosque bosque_original;
    Bosque bosque_nuevo;
} shared_data_t;

typedef struct
{
    size_t thread_number;
    shared_data_t *shared_data;
} private_data_t;

Mago::Mago() {
  
}

Mago::~Mago() {
}

int Mago::start(int argc, char* argv[]) {

  int rows, cols, nights, num = 0;

  std::string job_name = argv[1];
  std::string path = argv[2];
  std::string job_dir = path + job_name;

  //FILE* job = stdin;
  FILE* job_file = fopen(job_dir.c_str(),"r+");

  std::vector<std::string> maps_array;
  std::vector<int> nights_array;

  readJob(job_file, maps_array, nights_array);

  for (long unsigned int i = 0; i < nights_array.size(); i++) {

    std::cout << maps_array[i] << std::endl;
    std::string map_name = "tests/test_set_1/input/" + maps_array[i];
    FILE* input = fopen(map_name.c_str(),"r+");

    //FILE* input = stdin;
    nights = nights_array[i];

    fscanf(input, "%d", &rows);
    fscanf(input, "%d", &cols);

    fscanf(input, "\n");

    bosqueDelMago = new Bosque(rows,cols,nights);
    char **forest = create_matrix(rows, cols);
    fillMatrix(input, rows, cols, forest);
    char **newForest = create_matrix(rows, cols);
    copyMatrix(rows, cols, forest, newForest);

    std::string night_number;
    std::string forest_name;
    if (nights > 0) {
      for (int j = 0; j <= nights; j++)
      {
        //printf("%i:\n", i);
        //printMatrix(rows, cols, forest);
        night_number = std::to_string(j);
        forest_name = "bosques/" + maps_array[i] + "-" + night_number;
        createTextFile(rows, cols, forest, forest_name);
        bosqueDelMago->changeForest(rows, cols, forest, newForest);
        copyMatrix(rows, cols, newForest, forest);
        //printf("\n");
      }
    } else {
      num = 0;
      forest_name = "bosques/" + maps_array[i] + std::to_string(0);
      //printf("%i:\n", num);
      //printMatrix(rows, cols, forest);
      createTextFile(rows, cols, forest, forest_name);
      for (int i = 0; i > nights; i--)
      {
        bosqueDelMago->changeForest(rows, cols, forest, newForest);
        copyMatrix(rows, cols, newForest, forest);
        num++;
      }
     // printf("\n%i:\n", num);
      forest_name = "bosques/" + maps_array[i] + std::to_string(nights);
      createTextFile(rows, cols, forest, forest_name);
    }
    fclose(input);
  }
  return EXIT_SUCCESS;
}

void Mago::readJob(FILE* job, std::vector<std::string> &maps_array, std::vector<int> &nights_array) {

  //std::string map_str;

  char map[64];
  int night = 0;

  while ( ! feof (job) ) {
    fscanf(job, "%s", &map);
    std::string map_str(map);
    maps_array.push_back(map_str);
    fscanf(job, "%d", &night);
    nights_array.push_back(night);
    fscanf(job, "\n");
  }
  fclose (job);

}