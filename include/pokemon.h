#pragma once
#include <memory>
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
    int sp_attack;
    int sp_defense;
    std::vector<int> effects;
    pokeType type1;
    pokeType type2;
    std::vector<std::shared_ptr<move>> moveset;
    std::string name;
    int level;
    double xp;
    int status;
    // 0 - wild pokemon
    // 1 - team member
    // 2 - rejected starter
    static int totalDefeated;

    void setNickname();

public:
    pokemon();
    pokemon(int pokedexNumber_, int full_hp_,
            int attack_, int defense_,
            int sp_attack_, int sp_defense_,
            const pokeType& type1_, const pokeType& type2_,
            std::vector<std::shared_ptr<move>> moveset_, std::string name_,
            int level_, int status_);
    pokemon(const pokemon& other);
    pokemon& operator=(pokemon other);
    ~pokemon();

    friend std::ostream& operator<<(std::ostream& os, const pokemon& obj);
    friend void swap(pokemon& first, pokemon& second) noexcept;
    void changeStatus(int newStatus);
    void xpGain(double b, int l);
    [[nodiscard]] int getAttack() const;
    [[nodiscard]] int getDefense() const;
    [[nodiscard]] int getSpAttack() const;
    [[nodiscard]] int getSpDefense() const;
    void setEffect(int stat, int change);
    void resetEffects();
    void heal(int amount);
    void takeDamage(int amount);
    [[nodiscard]] int damage(bool sp, int p, int d, float t1, float t2) const;
    std::shared_ptr<move> selMove();

    [[nodiscard]] const std::string& getName() const { return name; }
    [[nodiscard]] int getHP() const { return hp; }
    [[nodiscard]] int getFullHP() const { return full_hp; }
    [[nodiscard]] const pokeType& getType1() const { return type1; }
    [[nodiscard]] const pokeType& getType2() const { return type2; }
    [[nodiscard]] const std::vector<std::shared_ptr<move>>& getMoveset() const { return moveset; }
    [[nodiscard]] double getXP() const { return xp; }
    [[nodiscard]] int getLevel() const { return level; }
    [[nodiscard]] int getPokedexNumber() const { return pokedexNumber; }
    static int getTotalDefeated() { return totalDefeated; }
    static void incrementDefeated() { totalDefeated++; }
};

extern pokemon treecko;
extern pokemon torchic;
extern pokemon mudkip;