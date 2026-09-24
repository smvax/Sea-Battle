#include "sea.h"
#include "game.h"

int main() {
    std::setlocale(LC_ALL, "rus");

    try {
        Game sea_battle;
        sea_battle.start();
    }
    catch (const std::exception& ex) {
        std::cerr << std::endl << "CRITICAL ERROR: " << ex.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cerr << std::endl << "UNEXPECTED CRITICAL ERROR!!!" << std::endl;
        return 1;
    }

    return 0;
}
