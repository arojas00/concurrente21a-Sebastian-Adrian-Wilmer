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
    DataValues();

    /// Destructor
    ~DataValues();

    /**
   * @return Retorna la identificacion de cada request
   */
    std::string getID() const;
    /**
   * @return Retorna el numero que contiene el objeto
   */
    int64_t getNumber() const;
    /**
   * @return Retorna la posicion en que venia en el request
   */
    int64_t getPosition() const;
    /**
   * @return Retorna la cantidad de sumas
   */
    std::string getSumas() const;
    /**
   * @details Establece la cantidad de sumas
   * @param sumas La cantidad de sumas 
   */
    void setSumas(std::string sumas);
    void setID(std::string ID);
    void setNumber(int64_t number);
    void setPosition(int64_t position);
    void setData(int64_t number, int64_t position, std::string ID);
    bool operator==(const DataValues& other) const;
  };
#endif // DATAVALUES_HPP
