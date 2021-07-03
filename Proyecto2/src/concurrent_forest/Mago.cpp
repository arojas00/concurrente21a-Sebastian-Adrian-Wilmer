/// @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Sebastian-Adrian-Wilmer

#include <errno.h>
#include "Mago.hpp"

Mago::Mago() {
  this->nights = 0;
}

Mago::~Mago() {

}

int Mago::start(int argc, char* argv[]) {
  int error = EXIT_SUCCESS;

  if (argc >= 2) {
    std::string job_name = argv[1];
    this->path = argv[2];
    std::string job_dir = path + job_name;
    FILE* job_file = fopen(job_dir.c_str(),"r+");
    read_job(job_file);

  } else {
    error = EXIT_FAILURE;
  }

  return error;
}
void Mago::read_job(FILE* job) {

  char map[64];
  int night = 0;

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
    FILE* input = fopen(map_dir.c_str(),"r+");
    /// Se saca del arreglo la cantidad de noches para el mapa
    this->nights = nights_array[i];

    fscanf(input, "%d", &rows);
    fscanf(input, "%d", &cols);

    this->map_original = new Map(rows, cols);

    fscanf(input, "\n");

    bosqueDelMago = new Bosque(rows,cols,nights);
    map_original->fillMatrix(input);
    map_copy = new Map(rows, cols);
    map_original->copyMatrix(map_copy->getMatrix());

    run_nights(i);
    delete this->map_original;
    delete bosqueDelMago;
    delete map_copy;
    fclose(input);
  }
}
  
void Mago :: run_nights(int map_index) {
  std::string night_number;
  std::string forest_name;

  if (nights > 0) {
    for (int j = 1; j <= nights; j++) {
      night_number = std::to_string(j);
      forest_name = "output/" + maps_array[map_index] + "-" + night_number;
      bosqueDelMago->changeForest(map_original->getRows(), map_original->getCols()
        , map_original->getMatrix(), map_copy->getMatrix());
      map_copy->createTextFile(forest_name);
      map_copy->copyMatrix(map_original->getMatrix());
    }
  } else {
    for (int i = 0; i > nights; i--) {
      bosqueDelMago->changeForest(map_original->getRows(), map_original->getCols()
        , map_original->getMatrix(), map_copy->getMatrix());
      map_copy->copyMatrix(map_original->getMatrix());
    }
    forest_name = "output/" + maps_array[map_index] + std::to_string(nights);
    map_original->createTextFile(forest_name);
  } 
}