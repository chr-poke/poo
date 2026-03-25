#include "pokeType.h"
#include "move.h"
#include "pokemon.h"

pokeType noneType(0, "None",
          {1, 1, 1, 1, 1, 1, 1},
          {1, 1, 1, 1, 1, 1, 1});
pokeType normalType(1, "Normal",
          {1, 1, 1, 1, 1, 1, 1},
          {1, 1, 1, 1, 1, 1, 1});
pokeType fireType(2, "Fire",
          {1, 1, 0.5, 0.5, 2, 2, 1},
          {1, 1, 0.5, 2, 0.5, 0.5, 1});
pokeType waterType(3, "Water",
          {1, 1, 2, 0.5, 0.5, 1, 1},
          {1, 1, 0.5, 0.5, 2, 1, 1});
pokeType grassType(4, "Grass",
          {1, 1, 0.5, 2, 0.5, 0.5, 1},
          {1, 1, 2, 0.5, 0.5, 2, 1});
pokeType bugType(5, "Bug",
          {1, 1, 0.5, 1, 2, 1, 2},
          {1, 1, 2, 1, 0.5, 1, 1});
pokeType darkType(6, "Dark",
          {1, 1, 1, 1, 1, 1, 0.5},
           {1, 1, 1, 1, 1, 2, 0.5});

move leerMove(normalType, 0, "Leer");
move poundMove(normalType, 40, "Pound");
move absorbMove(grassType, 20, "Absorb");
move quick_attackMove(normalType, 40, "Quick Attack");
move growlMove(normalType, 0, "Growl");
move scratchMove(normalType, 40, "Scratch");
move focus_energyMove(normalType, 0, "Focus Energy");
move emberMove(fireType, 40, "Ember");
move tackleMove(normalType, 35, "Tackle");
move mud_slapMove(normalType, 20, "Mud Slap");
move water_gunMove(waterType, 40, "Water Gun");
move howlMove(normalType, 0, "Howl");
move sand_attackMove(normalType, 0, "Sand Attack");
move biteMove(darkType, 40, "Bite");

pokemon treecko(1, 19, 10, 9,
            grassType, noneType,
            {leerMove, poundMove, absorbMove},
            "Treecko", 5, 2);
pokemon torchic(4, 20, 11, 9,
            fireType, noneType,
            {growlMove, scratchMove, focus_energyMove},
            "Torchic", 5, 2);
pokemon mudkip(7, 20, 12, 10,
            waterType, noneType,
            {growlMove, tackleMove, mud_slapMove},
            "Mudkip", 5, 2);
