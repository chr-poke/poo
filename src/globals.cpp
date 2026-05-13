#include "pokeType.h"
#include "move.h"
#include "pokemon.h"

// https://img.pokemondb.net/images/typechart-gen2345.png
// https://www.psypokes.com/dex/stats.php

pokeType noneType(0, "None",
          {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
          {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1});
pokeType normalType(1, "Normal",
          {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0.5},
          {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1});
pokeType fireType(2, "Fire",
          {1, 1, 0.5, 0.5, 2, 1, 1, 1, 2, 1, 2},
          {1, 1, 0.5, 2, 0.5, 1, 2, 1, 0.5, 1, 0.5});
pokeType waterType(3, "Water",
          {1, 1, 2, 0.5, 0.5, 1, 2, 1, 1, 1, 1},
          {1, 1, 0.5, 0.5, 2, 1, 1, 1, 1, 1, 0.5});
pokeType grassType(4, "Grass",
          {1, 1, 0.5, 2, 0.5, 0.5, 2, 1, 0.5, 1, 0.5},
          {1, 1, 2, 0.5, 0.5, 2, 0.5, 1, 2, 1, 1});
pokeType poisonType(5, "Poison",
        {1, 1, 1, 1, 2, 0.5, 0.5, 1, 1, 1, 0},
        {1, 1, 1, 1, 0.5, 0.5, 2, 2, 0.5, 1, 1});
pokeType groundType(6, "Ground",
        {1, 1, 2, 1, 0.5, 2, 1, 1, 0.5, 1, 2},
        {1, 1, 1, 2, 2, 0.5, 1, 1, 1, 1, 1});
pokeType psychicType(7, "Psychic",
        {1, 1, 1, 1, 1, 2, 1, 0.5, 1, 0, 0.5},
        {1, 1, 1, 1, 1, 1, 1, 0.5, 2, 2, 1});
pokeType bugType(8, "Bug",
          {1, 1, 0.5, 1, 2, 0.5, 1, 2, 1, 2, 0.5},
          {1, 1, 2, 1, 0.5, 1, 0.5, 1, 1, 1, 1});
pokeType darkType(9, "Dark",
          {1, 1, 1, 1, 1, 1, 1, 2, 1, 0.5, 0.5},
           {1, 1, 1, 1, 1, 1, 1, 0, 2, 0.5, 1});
pokeType steelType(10, "Steel",
        {1, 1, 0.5, 0.5, 1, 1, 1, 1, 1, 1, 0.5},
        {1, 0.5, 2, 1, 0.5, 0, 2, 0.5, 0.5, 0.5, 0.5});

std::shared_ptr<move> leerMove = std::make_shared<statusMove>(normalType, 0, "Leer", std::vector{0, -1, 0, 0, 0, 0, 0, 0});
std::shared_ptr<move> poundMove = std::make_shared<physicalMove>(normalType, 40, "Pound");
std::shared_ptr<move> absorbMove = std::make_shared<specialMove>(grassType, 20, "Absorb");
std::shared_ptr<move> quick_attackMove = std::make_shared<physicalMove>(normalType, 40, "Quick Attack");
std::shared_ptr<move> growlMove = std::make_shared<statusMove>(normalType, 0, "Growl", std::vector{-1, 0, 0, 0, 0, 0, 0, 0});
std::shared_ptr<move> scratchMove = std::make_shared<physicalMove>(normalType, 40, "Scratch");
std::shared_ptr<move> focus_energyMove = std::make_shared<statusMove>(normalType, 0, "Focus Energy", std::vector{0, 0, 0, 0, 0, 0, 1, 0});
std::shared_ptr<move> emberMove = std::make_shared<specialMove>(fireType, 40, "Ember");
std::shared_ptr<move> tackleMove = std::make_shared<physicalMove>(normalType, 35, "Tackle");
std::shared_ptr<move> mud_slapMove = std::make_shared<specialMove>(groundType, 20, "Mud Slap");
std::shared_ptr<move> water_gunMove = std::make_shared<specialMove>(waterType, 40, "Water Gun");
std::shared_ptr<move> howlMove = std::make_shared<statusMove>(normalType, 0, "Howl", std::vector{0, 0, 0, 0, 1, 0, 0, 0});
std::shared_ptr<move> sand_attackMove = std::make_shared<statusMove>(groundType, 0, "Sand Attack", std::vector{0, 0, 0, -1, 0, 0, 0, 0});
std::shared_ptr<move> biteMove = std::make_shared<physicalMove>(darkType, 40, "Bite");
std::shared_ptr<move> tail_whipMove = std::make_shared<statusMove>(normalType, 0, "Tail Whip", std::vector{0, -1, 0, 0, 0, 0, 0, 0});
std::shared_ptr<move> headbuttMove = std::make_shared<physicalMove>(normalType, 70, "Headbutt");
std::shared_ptr<move> string_shotMove = std::make_shared<statusMove>(bugType, 0, "String Shot", std::vector{-1, 0, -1, 0, 0, 0, 0, 0});
std::shared_ptr<move> poison_stingMove = std::make_shared<physicalMove>(poisonType, 15, "Poison Sting");
std::shared_ptr<move> take_downMove = std::make_shared<physicalMove>(normalType, 90, "Take Down");

pokemon treecko(1, 19, 10, 9, 12, 11,
            grassType, noneType,
            {leerMove, poundMove, absorbMove},
            "Treecko", 5, 2);
pokemon torchic(4, 20, 11, 9, 12, 10,
            fireType, noneType,
            {growlMove, scratchMove, focus_energyMove},
            "Torchic", 5, 2);
pokemon mudkip(7, 20, 12, 10, 10, 10,
            waterType, noneType,
            {growlMove, tackleMove, mud_slapMove},
            "Mudkip", 5, 2);
