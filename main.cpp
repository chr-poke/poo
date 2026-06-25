#include <iostream>
#include <vector>
#include <memory>
#include "pokemon.h"
#include "exceptions.h"
#include "rngEngine.h"

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

        const int randomMoveIndex = rngEngine::getInstance().getRandomInt(0, foe.getMoveset().size() - 1);
        const std::shared_ptr<move> oppMove = foe.getMoveset()[randomMoveIndex];
        oppMove->execute(foe, partner);
    }

    partner.resetEffects();
    if (partner.getHP() <= 0) {
        std::cout << partner.getName() << " fainted!\n\n";
        std::cout << "You blacked out!\n";
        return false;
    }
    pokemon::incrementDefeated();
    std::cout << "Wild " << foe.getName() << " fainted!\n";
    partner.xpGain(foe.getXP(), foe.getLevel());
    return true;
}

int main() {
    try {
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
                                  {tackleMove, howlMove},
                                  "Poochyena", 4, 0);

        bool onRoute = false;
        if (battle(starter, poochyena)) {
            std::cout << "Do you want to continue exploring Route 101? Y/N \n";
            while (std::cin >> input) {
                if (input == "Y") {
                    onRoute = true;
                    break;
                }
                if (input == "N") {
                    onRoute = false;
                    break;
                }
                std::cout << "Invalid input!\n";
            }
        }

        // *** WILD ENCOUNTERS ***

        while (onRoute) {
            pokemon wildPokemon;
            switch (rngEngine::getInstance().getRandomInt(0, 8)) {
                case 0:
                    wildPokemon = pokemon(12, 17, 8, 8, 8, 8,
                                normalType, noneType,
                                {growlMove, tackleMove},
                                "Zigzagoon", 4, 0);
                    break;
                case 1:
                    wildPokemon = pokemon(12, 19, 9, 9, 9, 9,
                                normalType, noneType,
                                {growlMove, tackleMove, tail_whipMove},
                                "Zigzagoon", 5, 0);
                    break;
                case 2:
                    wildPokemon = pokemon(12, 21, 10, 10, 10, 10,
                                normalType, noneType,
                                {growlMove, tackleMove, tail_whipMove, headbuttMove},
                                "Zigzagoon", 6, 0);
                    break;
                case 3:
                    wildPokemon = pokemon(14, 18, 9, 8, 7, 8,
                                bugType, noneType,
                                {string_shotMove, tackleMove},
                                "Wurmple", 4, 0);
                    break;
                case 4:
                    wildPokemon = pokemon(14, 20, 10, 9, 8, 9,
                                bugType, noneType,
                                {string_shotMove, tackleMove, poison_stingMove},
                                "Wurmple", 5, 0);
                    break;
                case 5:
                    wildPokemon = pokemon(14, 22, 10, 9, 8, 10,
                                bugType, noneType,
                                {string_shotMove, tackleMove, poison_stingMove},
                                "Wurmple", 6, 0);
                    break;
                case 6:
                    wildPokemon = pokemon(10, 17, 10, 8, 8, 8,
                                darkType, noneType,
                                {tackleMove, howlMove},
                                "Poochyena", 4, 0);
                    break;
                case 7:
                    wildPokemon = pokemon(10, 19, 11, 9, 9, 9,
                                darkType, noneType,
                                {tackleMove, howlMove, sand_attackMove},
                                "Poochyena", 5, 0);
                    break;
                case 8:
                    wildPokemon = pokemon(190, 17, 10, 12, 8, 10,
                                steelType, psychicType,
                                {take_downMove},
                                "Beldum", 4, 0);
                    break;
                default: ;
            }

            if (!battle(starter, wildPokemon))
                break;

            std::cout << "Do you want to continue exploring Route 101? Y/N \n";
            while (std::cin >> input) {
                if (input == "Y") {
                    onRoute = true;
                    break;
                }
                if (input == "N") {
                    onRoute = false;
                    break;
                }
                std::cout << "Invalid input!\n";
            }
        }

        std::cout << "Total wild Pokemon defeated: " << pokemon::getTotalDefeated() << std::endl << std::endl;

    } catch (const statException& e) {
        std::cerr << "\n[GAME CRASHED] " << e.what() << " Fix the Pokédex data.\n";
    } catch (const inputException& e) {
        std::cerr << "\n[GAME ABORTED] " << e.what() << " You left the game.\n";
    } catch (const battleException& e) {
        std::cerr << "\n[SYSTEM ERROR] " << e.what() << " The Pokémon trainer ran away.\n";
    } catch (const pokeException& e) {
        std::cerr << "\n[ERROR] " << e.what() << "\n";
    } catch (const std::exception& e) {
        std::cerr << "\n[FATAL ERROR] " << e.what() << "\n";
    }

    return 0;
}