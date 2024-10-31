#include "QuadTree.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {

    int width = 100, height = 100, max = 4, option;
    QuadTree quadtree(width, height, max);

    std::srand(std::time(0));  

    do {
        std::cout << "---------------------------------------------" << std::endl;
        std::cout << ">>>>>>>>>>>>>   MENU QUADTREE   <<<<<<<<<<<<<" << std::endl;
        std::cout << "---------------------------------------------" << std::endl;
        std::cout << "1. Insertar punto manualmente" << std::endl;
        std::cout << "2. Insertar 50 puntos aleatorios" << std::endl;
        std::cout << "3. Buscar puntos en rango" << std::endl;
        std::cout << "4. Crear estructura del QuadTree" << std::endl;
        std::cout << "5. Salir" << std::endl;
        std::cout << "Seleccione una opción: ";

        std::cin >> option;

        switch (option) {

        case 1: { //generador manual

            int x, y;

            std::cout << "Pos X del punto: ";
            std::cin >> x;
            std::cout << "Pos Y del punto: ";
            std::cin >> y;

            quadtree.insert(Point{ x, y });
            break;
        }

        case 2: { // generador aleatorio

            for (int i = 0; i < 50; ++i) {
                int x = std::rand() % width; 
                int y = std::rand() % height; 
                quadtree.insert(Point{ x, y });
            }

            std::cout << "Se han insertado 50 puntos aleatorios en el QuadTree.\n";
            break;
        }
        case 3: {

            int rangeX, rangeY, range;
            std::cout << "Centro X del rango de búsqueda: ";
            std::cin >> rangeX;
            std::cout << "Centro Y del rango de búsqueda: ";
            std::cin >> rangeY;
            std::cout << "Radio de búsqueda: ";
            std::cin >> range;

            auto found_points = quadtree.rangeSearch(rangeX, rangeY, range);
            std::cout << "Puntos encontrados en el rango:\n";

            for (const auto& p : found_points) {
                std::cout << " - (" << p.x << ", " << p.y << ")\n";
            }
            break;
        }
        case 4:
            quadtree.exportStructure("quadtree_structure.txt");
            std::cout << "Estructura exportada a 'quadtree_structure.txt'\n";
            break;
        case 5:
            std::cout << "Saliendo del programa.\n";
            break;
        default:
            std::cout << "Opción no válida.\n";
        }
    } while (option != 5);

    return 0;
}
