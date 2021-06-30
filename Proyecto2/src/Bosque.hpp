/// @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Sebastian-Adrian-Wilmer

#ifndef BOSQUE_HPP
#define BOSQUE_HPP


/**
 * @brief 
 */
class Bosque{
  
 protected:
  
 private:
 int filas,columnas,noches;

 public:
 char** matriz_bosque;

 private:
 bool checkInundation(int fila, int columna, char **matriz_bosque, int numero_filas, int numero_columnas);
 bool checkOvercrowding(int fila, int columna, char **matriz_bosque, int numero_filas, int numero_columnas);
 bool checkDrought(int fila, int columna, char **matriz_bosque, int numero_filas, int numero_columnas);
 bool checkReforestation(int fila, int columna, char **matriz_bosque, int numero_filas, int numero_columnas);
 bool checkCell(int fila, int columna, int numero_filas, int numero_columnas);

 public:
  Bosque(int filas,int columnas,int noches);
  ~Bosque();
 void changeForest(int fila, int columna, char **matriz_bosque, char **new_matriz_bosque);

};

#endif  // BOSQUE_HPP
