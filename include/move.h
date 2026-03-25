#pragma once
#include <iostream>
#include <string>
#include "pokeType.h"

class move {
private:
    pokeType type;
    std::string name;
    int power;

public:
    move();
    move(const pokeType& type_, int power_, std::string name_);

    friend std::ostream& operator<<(std::ostream& os, const move& obj);
    [[nodiscard]] int getPower() const { return power; }
    [[nodiscard]] const pokeType& getType() const { return type; }
    [[nodiscard]] const std::string& getName() const { return name; }
};

extern move leerMove;
extern move poundMove;
extern move absorbMove;
extern move quick_attackMove;
extern move growlMove;
extern move scratchMove;
extern move focus_energyMove;
extern move emberMove;
extern move tackleMove;
extern move mud_slapMove;
extern move water_gunMove;
extern move howlMove;
extern move sand_attackMove;
extern move biteMove;