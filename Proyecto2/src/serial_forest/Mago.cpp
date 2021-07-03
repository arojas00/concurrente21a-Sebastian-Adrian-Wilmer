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

  std::string job_name = argv[1];
  this->path = argv[2];
  std::string job_dir = path + job_name;

  FILE* job_file = fopen(job_dir.c_str(),"r+");

  readJob(job_file);
  return EXIT_SUCCESS;
}

void Mago :: run_job() {
  int rows, cols = 0;
  for (long unsigned int i = 0; i < nights_array.size(); i++) {

    std::cout << maps_array[i] << std::endl;
    std::string map_name = path + maps_array[i];
    FILE* input = fopen(map_name.c_str(),"r+");

    this->nights = nights_array[i];

    fscanf(input, "%d", &rows);
    fscanf(input, "%d", &cols);

    this->map = new Map(rows, cols);

    fscanf(input, "\n");

    bosqueDelMago = new Bosque(rows,cols,nights);
    map->fillMatrix(input);
    newForest = new Map(rows, cols);
    map->copyMatrix(newForest->getMatrix());

    run_nights(i);
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
      bosqueDelMago->changeForest(map->getRows(), map->getCols(), map->getMatrix(), newForest->getMatrix());
      newForest->createTextFile(forest_name);
      newForest->copyMatrix(map->getMatrix());
    }
  } else {
    for (int i = 0; i > nights; i--) {
      bosqueDelMago->changeForest(map->getRows(), map->getCols(), map->getMatrix(), newForest->getMatrix());
      newForest->copyMatrix(map->getMatrix());
    }
    forest_name = "output/" + maps_array[map_index] + std::to_string(nights);
    map->createTextFile(forest_name);
  } 
}

void Mago::readJob(FILE* job) {

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