#include "console_utils.hpp"
#include <iostream>

#ifdef _WIN32
    #define CLEAR_COMMAND "cls"
#else
    #define CLEAR_COMMAND "clear"
#endif

/**
 * @brief Limpia la consola dependiendo del sistema operativo.
 */
void clearConsole() 
{
    system(CLEAR_COMMAND);
}

/**
 * @brief Pausa la consola esperando una tecla del usuario.
 */
void pauseConsole() 
{
    std::cout << "Presione una tecla para continuar...\n";
    std::cin.ignore();
    std::cin.get();
}