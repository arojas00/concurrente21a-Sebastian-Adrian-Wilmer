/// @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Sebastian-Adrian-Wilmer

#include <errno.h>
#include <fstream>

#include "Mago.hpp"

Mago::Mago() {
  this->nights = 0;
  this->thread_count = 0;
}

Mago::~Mago() {

}

int Mago::start(int argc, char* argv[]) {
  int error = EXIT_SUCCESS;
  // Se leen los argumentos para abrir el archivo job
  if (argc >= 2) {
    std::string job_name = argv[1];
    this->path = argv[2];
    std::string job_dir = path + job_name;
    FILE* job_file = fopen(job_dir.c_str(),"r");
    if (argc >= 3) {
      thread_count = atoi(argv[3]);
    }
    read_job(job_file);
  } else {
    error = EXIT_FAILURE;
  }

  return error;
}
void Mago::read_job(FILE* job) {

  char map[64];
  int night = 0;

  // Se leen los mapas del archivo job y se guardan
  // en un arreglo para mapas y otro para noches
  while ( ! feof (job) ) {
    fscanf(job, "%s", map);
    std::string map_str(map);
    this->maps_array.push_back(map_str);
    fscanf(job, "%d", &night);
    this->nights_array.push_back(night);
    fscanf(job, "\n");
  }
  fclose (job);

  run_job();
}
void Mago :: run_job() {
  int rows, cols = 0;

  /// Por cada mapa del job
  for (long unsigned int i = 0; i < nights_array.size(); i++) {
    std::cout << maps_array[i] << std::endl;
    /// Se guarda en un string el directorio del mapa a evaluar
    std::string map_dir = path + maps_array[i];
    /// Se abre el mapa
    FILE* input = fopen(map_dir.c_str(),"r");
    /// Se saca del arreglo la cantidad de noches para el mapa
    this->nights = nights_array[i];

    fscanf(input, "%d", &rows);
    fscanf(input, "%d", &cols);

    this->map_original = new Map(rows, cols);

    fscanf(input, "\n");

    bosqueDelMago = new Bosque(rows,cols);
    map_original->fillMatrix(input);
    map_copy = new Map(rows, cols);
    map_original->copyMatrix(map_copy->getMatrix());

    run_nights(i);
    // Se libera la memoria
    delete this->map_original;
    delete bosqueDelMago;
    delete map_copy;
    // Cerrar el mapa con el que se trabajo
    fclose(input);
  }
}
  
void Mago :: run_nights(int map_index) {
  std::string night_number;
  std::string forest_name;
  std::string map_name;
  std::size_t begin,end;
  if (nights > 0) {
    for (int j = 1; j <= nights; j++) {
      night_number = std::to_string(j);
      // Nombrar el archivo de texto
      begin = maps_array[map_index].find("map");
      end = maps_array[map_index].find(".");
      map_name = maps_array[map_index].substr (begin,end);
      forest_name = "output/" + map_name + "-" + night_number + ".txt";
      // Procesar el mapa noche por noche
      bosqueDelMago->changeForest(map_original, map_copy, thread_count);
      // Crear cada archivo de texto
      createTextFile(forest_name, map_copy->getMatrix());
      map_copy->copyMatrix(map_original->getMatrix());
    }
  } else {
    for (int i = 0; i > nights; i--) {
      // Procesar el mapa noche por noche
      bosqueDelMago->changeForest(map_original, map_copy, thread_count);
      map_copy->copyMatrix(map_original->getMatrix());
    }
    // Nombrar y crear el archivo de texto
    begin = maps_array[map_index].find("map");
    end = maps_array[map_index].find(".");
    map_name = maps_array[map_index].substr (begin,end);
    forest_name = "output/" + map_name + night_number + std::to_string(nights) + ".txt";
    createTextFile(forest_name, map_original->getMatrix());
  } 
}

void Mago :: createTextFile(std::string filename, char** map) {
  std::ofstream fw(filename, std::ofstream::out);
   //check if file was successfully opened for writing
    if (fw.is_open()) {
      //store array contents to text file
      for(int x = 0; x < this->map_original->getRows(); x++) {
        for (int y = 0; y < this->map_original->getCols(); y++) {
        fw << map[x][y];
        }
         fw << "\n";
      }
      fw.close();
    }
    else std::cout << "Problem with opening file";
}