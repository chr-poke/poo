#include <iostream>
#include <vector>
#include <memory>
#include "pokemon.h"
#include "exceptions.h"
#include "rngEngine.h"
#include "pokemonFactory.h"
#include "registry.h"

bool battle(pokemon& partner, pokemon& foe, registry<std::map<std::string, std::shared_ptr<move>>>& seenMovesLog) {
    std::cout << "Go! " << partner.getName() << "!\n\n";
    while (foe.getHP() > 0 && partner.getHP() > 0) {
        std::cout << foe << std::endl << partner;
        std::shared_ptr<move> myMove = partner.selMove();
        auto& partnersMoves = seenMovesLog.get(partner.getName());
        if (!partnersMoves.contains(myMove->getName()))
            partnersMoves[myMove->getName()] = myMove;
        auto sMove = std::dynamic_pointer_cast<statusMove>(myMove);
        if (sMove && foe.getPokedexNumber() == 190 && sMove->loweringStats())
            std::cout << "ABILITY: Clear Body\n"
                      << "The opposing Beldum's stats were not lowered\n";
        else
            myMove->execute(partner, foe);
        if (foe.getHP() <= 0)
            break;

        const auto oppMove = rngEngine::getInstance().pickRandom<std::shared_ptr<move>>(foe.getMoveset());
        auto& foesMoves = seenMovesLog.get(foe.getName());
        if (!foesMoves.contains(oppMove->getName()))
            foesMoves[oppMove->getName()] = oppMove;
        oppMove->execute(foe, partner);
    }

    partner.resetEffects();
    if (partner.getHP() <= 0) {
        std::cout << partner.getName() << " fainted!\n\n";
        std::cout << "You blacked out!\n\n";
        return false;
    }
    pokemon::incrementDefeated();
    std::cout << "Wild " << foe.getName() << " fainted!\n";
    partner.xpGain(foe.getXP(), foe.getLevel());
    return true;
}

int main() {
    try {
        registry<pokemon> pokedex;
        registry<std::map<std::string, std::shared_ptr<move>>> seenMoves;

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
        pokedex.add(starter.getName(), starter);
        starter.changeStatus(1);

        // *** FIRST BATTLE ***

        pokemon poochyena(10, 17, 10, 8, 8, 8,
                                  darkType, noneType,
                                  {tackleMove, howlMove},
                                  "Poochyena", 4, 0);
        pokedex.add(poochyena.getName(), poochyena);
        std::cout << "Wild " << poochyena.getName() << " appeared!\n";

        bool onRoute = false;
        if (battle(starter, poochyena, seenMoves)) {
            std::cout << "Do you want to continue exploring Route 101? Y/N \n";
            while (std::cin >> input) {
                if (input == "Y") {
                    onRoute = true;
                    starter.heal(starter.getFullHP());
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
            pokemon wildPokemon = pokemonFactory::spawn();
            if (!pokedex.hasSeen(wildPokemon.getName()))
                pokedex.add(wildPokemon.getName(), wildPokemon);
            std::cout << "Wild " << wildPokemon.getName() << " appeared!\n";

            if (!battle(starter, wildPokemon, seenMoves))
                break;

            std::cout << "Do you want to continue exploring Route 101? Y/N \n";
            while (std::cin >> input) {
                if (input == "Y") {
                    onRoute = true;
                    starter.heal(starter.getFullHP());
                    break;
                }
                if (input == "N") {
                    onRoute = false;
                    break;
                }
                std::cout << "Invalid input!\n";
            }
        }

        // *** GAME STATS ***

        std::cout << "==========================================\n";
        std::cout << "POKEDEX ENTRIES: \n\n";

        for (const auto& pair : pokedex.getDatabase()) {
            std::string pokeName = pair.first;
            std::cout << "> " << pokeName << "\n";

            const auto& movesMap = seenMoves.get(pokeName);
            if (movesMap.empty())
                std::cout << "      Moves seen: (None)\n";
            else {
                std::cout << "      Moves seen:\n";
                for (const auto& movePair : movesMap)
                    std::cout << "      - " << movePair.first << "\n";
            }
            std::cout << std::endl;
        }
        std::cout << "TOTAL WILD POKEMON DEFEATED: " << pokemon::getTotalDefeated() << std::endl;
        std::cout << "==========================================\n\n";

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