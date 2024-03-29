#include "game.h"
#include <iostream>

int main() {
    try {
        Game game;
        game.run();
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return -1;
    }
    return 0;
}
