#include "move.h"
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