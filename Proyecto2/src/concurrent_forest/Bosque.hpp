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
    //char** matriz_bosque;

  private:
    /**
     * @brief 
     * @details 
     * @param 
     * @return 
     */
    bool checkInundation(int fila, int columna, char **matriz_bosque, int numero_filas, int numero_columnas);
    /**
     * @brief 
     * @details 
     * @param 
     * @return 
     */
    bool checkOvercrowding(int fila, int columna, char **matriz_bosque, int numero_filas, int numero_columnas);
    /**
     * @brief 
     * @details 
     * @param 
     * @return 
     */
    bool checkDrought(int fila, int columna, char **matriz_bosque, int numero_filas, int numero_columnas);
    /**
     * @brief 
     * @details 
     * @param 
     * @return 
     */
    bool checkReforestation(int fila, int columna, char **matriz_bosque, int numero_filas, int numero_columnas);
    /**
     * @brief 
     * @details 
     * @param 
     * @return 
     */
    bool checkCell(int fila, int columna, int numero_filas, int numero_columnas);

  public:
    /**
     * @brief
     */
    Bosque(int filas,int columnas,int noches);
    /**
     * @brief
     */
    ~Bosque();
    /**
     * @brief 
     * @details 
     * @param 
     * @return 
     */
    void changeForest(int fila, int columna, char **matriz_bosque, char **new_matriz_bosque);

};

#endif  // BOSQUE_HPP
