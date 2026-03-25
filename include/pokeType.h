#pragma once
#include <iostream>
#include <string>
#include <vector>

class pokeType {
private:
    int id;
    std::string name;
    std::vector<float> attack;
    std::vector<float> defense;

public:
    pokeType();
    pokeType(int id_, std::string name_,
             const std::vector<float>& attack_,
             const std::vector<float>& defense_);
    pokeType(const pokeType& other);
    pokeType& operator=(const pokeType& other) = default;

    friend std::ostream& operator<<(std::ostream& os, const pokeType& obj);
    [[nodiscard]] float getAttack(int i) const { return attack[i]; }
    [[nodiscard]] float getDefense(int i) const { return defense[i]; }
    [[nodiscard]] const std::string& getName() const { return name; }
    [[nodiscard]] int getID() const { return id; }
};

extern pokeType noneType;
extern pokeType normalType;
extern pokeType fireType;
extern pokeType waterType;
extern pokeType grassType;
extern pokeType bugType;
extern pokeType darkType;