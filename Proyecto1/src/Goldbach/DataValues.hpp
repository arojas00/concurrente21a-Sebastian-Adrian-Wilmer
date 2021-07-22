// Copyright 2021 Wilmer Araya-Sebastian Chaves <wilmer.araya@ucr.ac.cr> CC-BY-4
#ifndef DATAVALUES_HPP
#define DATAVALUES_HPP
#include <stdint.h>
#include <string>


class DataValues {

    private:
      int64_t valor;
      int64_t posicion;
      std::string identificador;
      std::string sumas;
   
    public:
    /// Constructor
    DataValues(int64_t valor = 0, int64_t posicion = -1, std::string identificador = "");

    /// Destructor
    ~DataValues();

    std::string get_ID() const;
    int64_t get_number() const;
    int64_t get_position() const;
    void set_sumas(std::string sumas);
    bool operator==(const DataValues& other) const;
    

  };
#endif // DATAVALUES_HPP
