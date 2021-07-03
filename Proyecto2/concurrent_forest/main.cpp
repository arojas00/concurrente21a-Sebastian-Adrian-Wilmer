/// @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Sebastian-Adrian-Wilmer

#include "Mago.hpp"

int main(int argc, char* argv[]) {
  return Mago().start(argc, argv);
}

/*
main(){
    controlador.start();

}

Shared_data{
    Bosque original
    NuevoBosque
}

controlador(char[][] mapa){
    for(noches){
        actualizarbosque(SharedData);
    }
    filecreate(NuevoBosque);
    shared_data->BosqueOriginal = NuevoBosque;
}

bosque(){
    actualizarbosque(){
        createthreads(actualizarCelda, Bosqueoriginal)
    }

    actualizarCelda(void * data){
        AplicarReglas();
        nuevoBosque[0][0] = 'a';
    }
}*/