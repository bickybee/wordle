//
//  main.cpp
//  Wordle
//
//  Created by Vicky on 2024-04-01.
//

#include <iostream>
#include <memory>
#include "Game.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Press enter to start.\n";
    std::cin.get();
    
    Game* Wordle = new Game();
    Wordle->start();
    
    delete Wordle;
}
