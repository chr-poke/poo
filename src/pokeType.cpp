#include "pokeType.h"
#include <utility>

pokeType::pokeType() {
    this->id = 0;
    this->name = "None";
    this->attack = {1, 1, 1, 1, 1, 1, 1};
    this->defense = {1, 1, 1, 1, 1, 1, 1};
}

pokeType::pokeType(const int id_, std::string name_,
                   const std::vector<float>& attack_,
                   const std::vector<float>& defense_)
    : id{id_}, name{std::move(name_)},
      attack{attack_},
      defense{defense_} {}

pokeType::pokeType(const pokeType& other) {
    this->id = other.id;
    this->name = other.name;
    this->attack = other.attack;
    this->defense = other.defense;
}

std::ostream& operator<<(std::ostream& os, const pokeType& obj) {
    os << "The " << obj.name << " Type has the id " << obj.id << ".\n";
    return os;
}