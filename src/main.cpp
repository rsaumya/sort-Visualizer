#include <SFML/Graphics.hpp>

#include "visualizer.h"

int main() 
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
   
    visualizer v;
    v.run();

    return 0;
}
