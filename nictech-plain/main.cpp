// nictech_doxygenado.cpp

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

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

const int MAX_CUSTOMERS = 100;

struct Customer 
{
    int code;
    std::string name;
    std::string surname;
    std::string address;
};

struct CustomersRepository 
{
    Customer customers[MAX_CUSTOMERS];
    int length;
};

/**
 * @brief Carga los datos de clientes desde un archivo CSV.
 * 
 * @param repo Referencia al repositorio de clientes.
 * @param filename Nombre del archivo CSV.
 */
void customers_loadFromFile(CustomersRepository& repo, const std::string& filename) 
{
    repo.length = 0;
    std::ifstream file(filename);
    if (!file.is_open()) return;

    std::string line;
    while (std::getline(file, line) && repo.length < MAX_CUSTOMERS) 
    {
        std::stringstream ss(line);
        std::string field;
        Customer c;

        std::getline(ss, field, ',');
        c.code = std::stoi(field);
        std::getline(ss, c.name, ',');
        std::getline(ss, c.surname, ',');
        std::getline(ss, c.address, ',');

        repo.customers[repo.length++] = c;
    }

    file.close();
}

/**
 * @brief Guarda los datos de los clientes en un archivo CSV.
 * 
 * @param repo Referencia constante al repositorio de clientes.
 * @param filename Nombre del archivo CSV.
 */
void customers_saveToFile(const CustomersRepository& repo, const std::string& filename) 
{
    std::ofstream file(filename);
    for (int i = 0; i < repo.length; ++i) 
    {
        if (repo.customers[i].code == -1) continue;

        file << repo.customers[i].code << ","
             << repo.customers[i].name << ","
             << repo.customers[i].surname << ","
             << repo.customers[i].address << "\n";
    }

    file.close();
}

/**
 * @brief Crea un nuevo cliente y lo agrega al repositorio.
 * 
 * @param repo Referencia al repositorio de clientes.
 */
void customers_create(CustomersRepository& repo) 
{
    clearConsole();

    if (repo.length >= MAX_CUSTOMERS) 
    {
        std::cout << "No se pueden agregar más clientes.\n";
        return;
    }

    Customer c;
    c.code = (repo.length > 0) ? repo.customers[repo.length - 1].code + 1 : 100;

    std::cout << "Nombre: ";
    std::cin >> c.name;
    std::cout << "Apellido: ";
    std::cin >> c.surname;
    std::cout << "Dirección: ";
    std::cin.ignore();
    std::getline(std::cin, c.address);

    repo.customers[repo.length++] = c;

    std::cout << "Cliente agregado correctamente.\n";
}

/**
 * @brief Muestra la lista de clientes en consola.
 * 
 * @param repo Referencia constante al repositorio de clientes.
 */
void customers_list(const CustomersRepository& repo) 
{
    clearConsole();
    std::cout << "Listado de clientes:\n";

    for (int i = 0; i < repo.length; ++i) 
    {
        const Customer& c = repo.customers[i];
        if (c.code == -1) continue;

        std::cout << "Código: " << c.code << "\n"
                  << "Nombre: " << c.name << "\n"
                  << "Apellido: " << c.surname << "\n"
                  << "Dirección: " << c.address << "\n\n";
    }
}

/**
 * @brief Elimina un cliente estableciendo su código en -1.
 * 
 * @param repo Referencia al repositorio.
 * @param code Código del cliente a eliminar.
 */
void customers_removeByCode(CustomersRepository& repo, int code) 
{
    for (int i = 0; i < repo.length; ++i) 
    {
        if (repo.customers[i].code == code) 
        {
            repo.customers[i].code = -1;
            std::cout << "Cliente eliminado.\n";
            return;
        }
    }

    std::cout << "Cliente no encontrado.\n";
}

/**
 * @brief Modifica los datos de un cliente por su código.
 * 
 * @param repo Referencia al repositorio.
 * @param code Código del cliente a modificar.
 */
void customers_modifyByCode(CustomersRepository& repo, int code) 
{
    for (int i = 0; i < repo.length; ++i) 
    {
        if (repo.customers[i].code == code) 
        {
            std::cout << "Nuevo nombre: ";
            std::cin >> repo.customers[i].name;
            std::cout << "Nuevo apellido: ";
            std::cin >> repo.customers[i].surname;
            std::cout << "Nueva dirección: ";
            std::cin.ignore();
            std::getline(std::cin, repo.customers[i].address);
            std::cout << "Cliente modificado.\n";
            return;
        }
    }

    std::cout << "Cliente no encontrado.\n";
}

/**
 * @brief Busca y muestra un cliente por su código.
 * 
 * @param repo Referencia constante al repositorio.
 * @param code Código del cliente a buscar.
 */
void customers_findByCode(const CustomersRepository& repo, int code) 
{
    for (int i = 0; i < repo.length; ++i) 
    {
        const Customer& c = repo.customers[i];
        if (c.code == code) 
        {
            std::cout << "Código: " << c.code << "\n"
                      << "Nombre: " << c.name << "\n"
                      << "Apellido: " << c.surname << "\n"
                      << "Dirección: " << c.address << "\n";
            return;
        }
    }

    std::cout << "Cliente no encontrado.\n";
}

/**
 * @brief Muestra el menú principal.
 */
void showMenu() 
{
    std::cout << "----- MENÚ -----\n"
              << "1. Alta\n"
              << "2. Baja\n"
              << "3. Modificar\n"
              << "4. Listar\n"
              << "5. Buscar por código\n"
              << "6. Salir\n"
              << "Opción: ";
}

/**
 * @brief Ejecuta la aplicación principal.
 */
void runApp() 
{
    CustomersRepository repo;
    customers_loadFromFile(repo, "customers.csv");

    int option;

    do 
    {
        showMenu();
        std::cin >> option;

        switch (option) 
        {
            case 1:
                customers_create(repo);
                break;
            case 2:
            {
                int code;
                std::cout << "Código del cliente: ";
                std::cin >> code;
                customers_removeByCode(repo, code);
                break;
            }
            case 3:
            {
                int code;
                std::cout << "Código del cliente: ";
                std::cin >> code;
                customers_modifyByCode(repo, code);
                break;
            }
            case 4:
                customers_list(repo);
                break;
            case 5:
            {
                int code;
                std::cout << "Código del cliente: ";
                std::cin >> code;
                customers_findByCode(repo, code);
                break;
            }
            case 6:
                customers_saveToFile(repo, "customers.csv");
                std::cout << "Saliendo...\n";
                break;
            default:
                std::cout << "Opción no válida.\n";
        }

        pauseConsole();
        clearConsole();

    } while (option != 6);
}

/**
 * @brief Punto de entrada del programa.
 * @return int Código de retorno.
 */
int main() 
{
    runApp();
    return 0;
}