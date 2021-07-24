#include "DataValues.hpp"

    /// Constructor
    DataValues::DataValues(){
        this->valor = 0;
        this->posicion = 0;
        this->identificador = "";
    }

    /// Destructor
    DataValues::~DataValues(){

    }
    std::string DataValues::getID() const{
        return this->identificador;
    }
    int64_t DataValues::getNumber() const{
        return this->valor;
    }
    int64_t DataValues::getPosition() const{
        return this->posicion;
    }
    void DataValues::setSumas(std::string sumas){
        this->sumas = sumas;
    }
    void DataValues::setID(std::string ID){
        this->identificador = ID;
    }
    void DataValues::setNumber(int64_t number){
        this->valor = number;
    }
    void DataValues::setPosition(int64_t position){
        this->posicion = position;
    }

    void DataValues::setData(int64_t number, int64_t position, std::string ID){
        this->valor = number;
        this->posicion = position;
        this->identificador = ID;
    }
    bool DataValues::operator==(const DataValues& other) const {
    return this->identificador
    == other.identificador;
    }
