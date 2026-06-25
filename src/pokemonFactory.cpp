#include "pokemonFactory.h"
#include "rngEngine.h"
#include "move.h"

pokemon pokemonFactory::spawn() {
    switch (rngEngine::getInstance().getRandomInt(0, 8)) {
        case 0:
            return pokemon(12, 17, 8, 8, 8, 8,
                           normalType, noneType,
                           {growlMove, tackleMove},
                           "Zigzagoon", 4, 0);
        case 1:
            return pokemon(12, 19, 9, 9, 9, 9,
                           normalType, noneType,
                           {growlMove, tackleMove, tail_whipMove},
                           "Zigzagoon", 5, 0);
        case 2:
            return pokemon(12, 21, 10, 10, 10, 10,
                           normalType, noneType,
                           {growlMove, tackleMove, tail_whipMove, headbuttMove},
                           "Zigzagoon", 6, 0);
        case 3:
            return pokemon(14, 18, 9, 8, 7, 8,
                           bugType, noneType,
                           {string_shotMove, tackleMove},
                           "Wurmple", 4, 0);
        case 4:
            return pokemon(14, 20, 10, 9, 8, 9,
                           bugType, noneType,
                           {string_shotMove, tackleMove, poison_stingMove},
                           "Wurmple", 5, 0);
        case 5:
            return pokemon(14, 22, 10, 9, 8, 10,
                           bugType, noneType,
                           {string_shotMove, tackleMove, poison_stingMove},
                           "Wurmple", 6, 0);
        case 6:
            return pokemon(10, 17, 10, 8, 8, 8,
                           darkType, noneType,
                           {tackleMove, howlMove},
                           "Poochyena", 4, 0);
        case 7:
            return pokemon(10, 19, 11, 9, 9, 9,
                           darkType, noneType,
                           {tackleMove, howlMove, sand_attackMove},
                           "Poochyena", 5, 0);
        case 8:
            return pokemon(190, 17, 10, 12, 8, 10,
                           steelType, psychicType,
                           {take_downMove},
                           "Beldum", 4, 0);
        default:
            return {};
    }
}
