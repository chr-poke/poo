#include "move.h"
#include "pokemon.h"
#include <utility>

move::move() {
    this->type = noneType;
    this->name = "None";
    this->power = 0;
}

move::move(const pokeType& type_, const int power_, std::string name_) 
    : type{type_}, name{std::move(name_)}, power{power_} {}

std::ostream& operator<<(std::ostream& os, const move& obj) {
    os << obj.name << " is a " << obj.type.getName()
       << " Type move and it has " << obj.power << " power.\n";
    return os;
}

void physicalMove::execute(pokemon& attacker, pokemon& defender) {
    std::cout << "--- " << attacker.getName() << " used " << name << "! ---\n";
    const int dmg = attacker.damage(false, power, defender.getDefense(),
                              type.getAttack(defender.getType1().getID()),
                              type.getAttack(defender.getType2().getID()));
    defender.takeDamage(dmg);
}

void specialMove::execute(pokemon& attacker, pokemon& defender) {
    std::cout << "--- " << attacker.getName() << " used " << name << "! ---\n";
    const int dmg = attacker.damage(true, power, defender.getSpDefense(),
                              type.getAttack(defender.getType1().getID()),
                              type.getAttack(defender.getType2().getID()));
    defender.takeDamage(dmg);
}

void statusMove::execute(pokemon& attacker, pokemon& defender) {
    std::cout << "--- " << attacker.getName() << " used " << name << "! ---\n";
    std::vector<std::string> statNames = {
        "Attack", "Defense", "Special Attack", "Special Defense",
        "Attack", "Defense", "Special Attack", "Special Defense"
    };

    for (int i = 0; i < 8; i++) {
        if (effects[i] == 0)
            continue;
        pokemon& target = (i < 4) ? defender : attacker;
        std::string action = (effects[i] < 0) ? "fell" : "rose";
        target.setEffect(i % 4, effects[i]);
        std::cout << target.getName() << "'s " << statNames[i] << " " << action << "!\n";
    }
}