#include <iostream>
#include "pokemon.h"

int main() {
    // *** STARTER SELECTION ***

    int selectedStarter = 0;
    bool starterWasChosen = false;
    std::cout << "Professor Birch is in trouble! Release a Pokemon and rescue him!\n"
                 "Type '1', '2' or '3' to show details about each Pokemon.\n";
    while (!starterWasChosen) {
        std::string input;
        std::cin >> input;
        if (input.size() == 1) {
            switch (input[0]) {
                case '1':
                    std::cout << "Wood Gecko Pokemon - Treecko\n";
                    selectedStarter = 1;
                    break;
                case '2':
                    std::cout << "Chick Pokemon - Torchic\n";
                    selectedStarter = 2;
                    break;
                case '3':
                    std::cout << "Mud Fish Pokemon - Mudkip\n";
                    selectedStarter = 3;
                    break;
                case 'Y':
                    starterWasChosen = true;
                    break;
                default:
                    std::cout << "Invalid input!\n";
            }
            if (input[0] >= '1' && input[0] <= '3')
                std::cout << "Type 'Y' to choose this Pokemon!\n";
        }
        else
            std::cout << "Invalid input!\n";
    }

    pokemon starter;
    switch (selectedStarter) {
        case 1:
            starter = treecko;
            break;
        case 2:
            starter = torchic;
            break;
        case 3:
            starter = mudkip;
            break;
        default:
            std::cout << "You're not supposed to see this!\n";
    }
    starter.changeStatus(1);

    // *** BATTLE SIMULATOR ***

    bool onRoute = true;
    while (onRoute) {
        for (int i = 0; i < 1; i++) {
            pokemon poochyena(10, 17, 10, 8,
                              darkType, noneType,
                              {tackleMove, howlMove, sand_attackMove},
                              "Poochyena", 4, 0);
            std::cout << "Go! " << starter.getName() << "!\n\n";

            while (poochyena.getHP() > 0 && starter.getHP() > 0) {
                std::cout << poochyena << std::endl << starter;
                move myMove = starter.selMove();
                std::cout << "--- " << starter.getName() << " used " << myMove.getName() << "! ---\n";
                poochyena.takeDamage(starter.damage(
                    myMove.getPower(), poochyena.getDefense(),
                    myMove.getType().getAttack(poochyena.getType1().getID()),
                    myMove.getType().getAttack(poochyena.getType2().getID())));
                if (poochyena.getHP() <= 0)
                    break;

                std::cout << std::endl << poochyena << std::endl << starter << std::endl;
                move oppMove = poochyena.getMoveset()[rand() % poochyena.getMoveset().size()];
                std::cout << "--- " << poochyena.getName() << " used " << oppMove.getName() << "! ---\n\n";
                starter.takeDamage(poochyena.damage(
                    oppMove.getPower(), starter.getDefense(),
                    oppMove.getType().getAttack(starter.getType1().getID()),
                    oppMove.getType().getAttack(starter.getType2().getID())));
            }
            if (starter.getHP() <= 0) {
                std::cout << starter.getName() << " fainted!\n\n";
                std::cout << "You blacked out!\n";
                onRoute = false;
            }
            else {
                std::string input;
                std::cout << "\nWild " << poochyena.getName() << " fainted!\n";
                std::cout << starter.getName() << " gained "
                          << starter.xpGain(poochyena.getXP(), poochyena.getLevel())
                          << " XP.\n\n";
                std::cout << "Do you want to leave Route 101? Y/N \n";
                while (std::cin >> input) {
                    if (input == "Y") {
                        onRoute = false;
                        break;
                    }
                    if (input == "N")
                        break;
                    std::cout << "Invalid input!\n";
                }
            }
        }
    }

    return 0;
}