#include <iostream>
#include <vector>
#include <memory>
#include <ctime>
#include "pokemon.h"

bool battle(pokemon& partner, pokemon& foe) {
    std::cout << "Go! " << partner.getName() << "!\n\n";
    while (foe.getHP() > 0 && partner.getHP() > 0) {
        std::cout << foe << std::endl << partner;
        std::shared_ptr<move> myMove = partner.selMove();
        auto sMove = std::dynamic_pointer_cast<statusMove>(myMove);
        if (sMove && foe.getPokedexNumber() == 190 && sMove->loweringStats())
            std::cout << "ABILITY: Clear Body\n"
                      << "The opposing Beldum's stats were not lowered\n";
        else
            myMove->execute(partner, foe);
        if (foe.getHP() <= 0)
            break;

        std::cout << std::endl << foe << std::endl << partner << std::endl;
        std::shared_ptr<move> oppMove = foe.getMoveset()[rand() % foe.getMoveset().size()];
        oppMove->execute(foe, partner);
    }

    partner.resetEffects();
    if (partner.getHP() <= 0) {
        std::cout << partner.getName() << " fainted!\n\n";
        std::cout << "You blacked out!\n";
        return false;
    }
    std::cout << "\nWild " << foe.getName() << " fainted!\n";
    std::cout << partner.getName() << " gained "
              << partner.xpGain(foe.getXP(), foe.getLevel())
              << " XP.\n\n";
    return true;
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    std::string input;

    // *** STARTER SELECTION ***

    int selectedStarter = 0;
    bool starterWasChosen = false;
    std::cout << "Professor Birch is in trouble! Release a Pokemon and rescue him!\n"
                 "Type '1', '2' or '3' to show details about each Pokemon.\n";
    while (!starterWasChosen) {
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
        default: ;
    }
    starter.changeStatus(1);

    // *** FIRST BATTLE ***

    pokemon poochyena(10, 17, 10, 8, 8, 8,
                              darkType, noneType,
                              {tackleMove, howlMove, sand_attackMove},
                              "Poochyena", 4, 0);
    battle(starter, poochyena);

    // *** WILD ENCOUNTERS ***

    bool onRoute = false;
    std::cout << "Do you want to continue exploring Route 101? Y/N \n";
    while (std::cin >> input) {
        if (input == "Y") {
            onRoute = true;
            break;
        }
        if (input == "N")
            break;
        std::cout << "Invalid input!\n";
    }
    while (onRoute) {
        pokemon wildPokemon;
        int chance = rand() % 9;
        if (chance < 3)
            wildPokemon = pokemon(12, 17, 8, 8, 8, 8,
                            normalType, noneType,
                            {growlMove, tackleMove, tail_whipMove},
                            "Zigzagoon", 4, 0);
        else if (chance < 6)
            wildPokemon = pokemon(14, 18, 9, 8, 7, 8,
                            bugType, noneType,
                            {string_shotMove, tackleMove, poison_stingMove},
                            "Wurmple", 4, 0);
        else if (chance < 8)
            wildPokemon = pokemon(10, 17, 10, 8, 8, 8,
                            darkType, noneType,
                            {tackleMove, howlMove, sand_attackMove},
                            "Poochyena", 4, 0);
        else
            wildPokemon = pokemon(190, 17, 10, 12, 8, 10,
                            steelType, psychicType,
                            {take_downMove},
                            "Beldum", 4, 0);

        if (!battle(starter, wildPokemon))
            break;

        std::cout << "Do you want to continue exploring Route 101? Y/N \n";
        while (std::cin >> input) {
            if (input == "Y") {
                onRoute = true;
                break;
            }
            if (input == "N")
                break;
            std::cout << "Invalid input!\n";
        }
    }

    return 0;
}