#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "pokeType.h"
#include "move.h"

class pokemon {
private:
    int pokedexNumber; // Hoenn Pokedex
    int full_hp;
    int hp;
    int attack;
    int defense;
    pokeType type1;
    pokeType type2;
    std::vector<move> moveset;
    std::string name;
    int level;
    double xp;
    int status;
    // 0 - wild pokemon
    // 1 - team member
    // 2 - rejected starter

    static float getRandom();
    void setNickname();

public:
    pokemon();
    pokemon(int pokedexNumber_, int full_hp_,
            int attack_, int defense_,
            const pokeType& type1_, const pokeType& type2_,
            const std::vector<move>& moveset_, std::string name_,
            int level_, int status_);
    pokemon(const pokemon& other);
    pokemon& operator=(const pokemon& other) = default;
    ~pokemon();

    friend std::ostream& operator<<(std::ostream& os, const pokemon& obj);
    void changeStatus(int newStatus);
    int xpGain(double b, int l);
    void takeDamage(int damage);
    [[nodiscard]] int damage(int p, int d, float t1, float t2) const;
    move selMove();

    [[nodiscard]] const std::string& getName() const { return name; }
    [[nodiscard]] int getHP() const { return hp; }
    [[nodiscard]] int getDefense() const { return defense; }
    [[nodiscard]] const pokeType& getType1() const { return type1; }
    [[nodiscard]] const pokeType& getType2() const { return type2; }
    [[nodiscard]] const std::vector<move>& getMoveset() const { return moveset; }
    [[nodiscard]] double getXP() const { return xp; }
    [[nodiscard]] int getLevel() const { return level; }
};

extern pokemon treecko;
extern pokemon torchic;
extern pokemon mudkip;