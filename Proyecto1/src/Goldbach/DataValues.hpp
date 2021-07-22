// Copyright 2021 Wilmer Araya-Sebastian Chaves <wilmer.araya@ucr.ac.cr> CC-BY-4
#ifndef DATAVALUES_HPP
#define DATAVALUES_HPP
#include <stdint.h>
#include <string>


class DataValues {

     public:
      int64_t valor;
      int64_t posicion;
      std::string identificador;
      std::string sumas;
   

    /// Constructor
    DataValues(int64_t valor, int64_t posicion, std::string identificador);

    /// Destructor
    ~DataValues();

    std::string get_ID();
    int64_t get_number();
    int64_t get_position();
    void set_sumas(std::string sumas);

  };
#endif // DATAVALUES_HPP
