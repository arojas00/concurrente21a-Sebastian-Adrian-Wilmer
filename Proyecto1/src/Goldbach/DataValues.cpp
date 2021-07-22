#include "DataValues.hpp"

    /// Constructor
    DataValues::DataValues(int64_t valor, int64_t posicion, std::string identificador){
        this->valor = valor;
        this->posicion = posicion;
        this->identificador = identificador;
    }

    /// Destructor
    DataValues::~DataValues(){

    }

    std::string DataValues::get_ID() const{
        return this->identificador;
    }
    int64_t DataValues::get_number() const{
        return this->valor;
    }
    int64_t DataValues::get_position() const{
        return this->posicion;
    }
    void DataValues::set_sumas(std::string sumas){
        this->sumas = sumas;
    }

    bool DataValues::operator==(const DataValues& other) const {
    return this->identificador
    == other.identificador;
    }
    /*
    bool Socket::operator==(const Socket& other) const {
    return this->sharedSocket->socketFileDescriptor
    == other.sharedSocket->socketFileDescriptor;
    }
    */