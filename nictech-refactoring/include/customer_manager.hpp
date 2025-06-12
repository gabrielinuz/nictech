#ifndef CUSTOMER_MANAGER_HPP
#define CUSTOMER_MANAGER_HPP

#include <string>

const int MAX_CUSTOMERS = 100;

/**
 * @brief Representa un cliente.
 */
struct Customer
{
    int code;
    std::string name;
    std::string surname;
    std::string address;
};

/**
 * @brief Repositorio que almacena clientes en un arreglo estático.
 */
struct CustomersRepository
{
    Customer customers[MAX_CUSTOMERS];
    int length;
};

// Funciones del sistema de clientes
void customers_loadFromFile(CustomersRepository* repo, const std::string& filename);
void customers_saveToFile(const CustomersRepository* repo, const std::string& filename);
void customers_create(CustomersRepository* repo);
void customers_list(const CustomersRepository* repo);
void customers_removeByCode(CustomersRepository* repo, int code);
void customers_modifyByCode(CustomersRepository* repo, int code);
void customers_findByCode(const CustomersRepository* repo, int code);
void runApp();

#endif
