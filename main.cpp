#include <iostream>
#include <string>
#include <random>
#include <vector>
#include <cmath>
#include <set>

class pokeType {
private:
    int id;
    std::string name;
    std::vector<float> attack;
    std::vector<float> defense;

public:
    pokeType() {
        this->id = 0;
        this->name = "None";
        this->attack = {1, 1, 1, 1, 1, 1, 1};
        this->defense = {1, 1, 1, 1, 1, 1, 1};
    }

    pokeType(const int id, const std::string& name,
         const std::vector<float>& attack,
         const std::vector<float>& defense) {
        this->id = id;
        this->name = name;
        this->attack = attack;
        this->defense = defense;
    }

    pokeType(const pokeType& other) {
        this->id = other.id;
        this->name = other.name;
        this->attack = other.attack;
        this->defense = other.defense;
    }

    pokeType& operator=(const pokeType& other) = default;

    [[nodiscard]] float getAttack(int i) const {
        return attack[i];
    }
    [[nodiscard]] float getDefense(int i) const {
        return defense[i];
    }
};

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

class move {
private:
    pokeType type;
    std::string name;
    int power;

public:
    move() {
        this->type = noneType;
        this->name = "None";
        this->power = 0;
    }

    move(const pokeType& type, const int power, const std::string& name) {
        this->type = type;
        this->name = name;
        this->power = power;
    }

    [[nodiscard]] int getPower() const {
        return power;
    }
    [[nodiscard]] pokeType getType() const {
        return type;
    }
};

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

    static float getRandom() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dist(217.0f / 255.0f, 1.0f);
        return dist(gen);
    }

    void setNickname() {
        std::string input;
        bool dialog = true;
        while (dialog) {
            std::cout << "Give a nickname to the captured " + name + "? Y/N\n";
            std::cin >> input;
            if (input.size() == 1 && (input[0] == 'Y' || input[0] == 'N')) {
                dialog = false;
                if (input[0] == 'Y') {
                    std::cout << "Type your nickname:\n";
                    std::cin >> this->name;
                }
            }
        }
    }

public:
    pokemon(const int pokedexNumber, const int full_hp,
                const int attack, const int defense,
                const pokeType& type1, const pokeType& type2,
                const std::vector<move>& moveset, const std::string& name,
                const int level) {
        this->pokedexNumber = pokedexNumber;
        this->full_hp = full_hp;
        this->hp = full_hp;
        this->attack = attack;
        this->defense = defense;
        this->type1 = type1;
        this->type2 = type2;
        this->moveset = moveset;
        this->name = name;
        this->level = level;
        this->xp = pow(level, 3);
        this->status = 0;
    }

    ~pokemon() {
        if (status == 0)
            std::cout << "Wild " + name + " fainted!\n";
        else if (status == 1)
            std::cout << name + " was released.\n"
                      << "Bye-bye, " + name + "!\n";
    }

    friend std::ostream& operator<<(std::ostream& os, const pokemon& obj) {
        os << obj.name << " (Level " << obj.level << ")\n"
           << "HP: " << obj.hp << "/" << obj.full_hp << "\n";
        return os;
    }

    void changeStatus(int newStatus) {
        status = newStatus;
        if (newStatus == 1)
            setNickname();
    }

    void xpGain(int b, int l) {
        // b = xp of the defeated Pokemon
        // l = level of the defeated Pokemon
        xp += b * l / 7;
        if (xp >= pow(level + 1, 3)) {
            level++;
            attack++;
            defense++;
            hp += 2;
        }
    }

    [[nodiscard]] int damage(const int p, const int d, const float t1, const float t2) const {
        const float r = getRandom();
        return std::floor(
            (static_cast<float>(((2 * level) / 5 + 2) * p * attack) / static_cast<float>(d)) / 50.0 * t1 * t2 * r);
    }
};

pokemon treecko(1, 19, 10, 9,
            grassType, noneType,
            {leerMove, poundMove, absorbMove},
            "Treecko", 5);
pokemon torchic(4, 20, 11, 9,
            fireType, noneType,
            {growlMove, scratchMove, focus_energyMove},
            "Torchic", 5);
pokemon mudkip(7, 20, 12, 10,
            waterType, noneType,
            {growlMove, tackleMove, mud_slapMove},
            "Mudkip", 5);
pokemon poochyena(10, 13, 7, 6,
            darkType, noneType,
            {tackleMove, howlMove, sand_attackMove},
            "Poochyena", 2);

int main() {
    // *** STARTER SELECTION ***

    int selectedStarter = 0;
    bool starterWasChosen = false;
    std::cout << "Professor Birch is in trouble! Release a Pokemon and rescue him!\n"
                 "Type '1', '2' or '3' to show details about each Pokemon.\n";
    while (!starterWasChosen) {
        std::string input;
        std::cin >> input;
        if (input.size() == 1) {
            switch (input[0]) {
                case '1':
                    std::cout << "Wood Gecko Pokemon - Treecko\n";
                    selectedStarter = 1;
                    break;
                case '2':
                    std::cout << "Chick Pokemon - Torchic\n";
                    selectedStarter = 2;
                    break;
                case '3':
                    std::cout << "Mud Fish Pokemon - Mudkip\n";
                    selectedStarter = 3;
                    break;
                case 'Y':
                    starterWasChosen = true;
                    break;
                default:
                    std::cout << "Invalid input!\n";
            }
            if (input[0] >= '1' && input[0] <= '3')
                std::cout << "Type 'Y' to choose this Pokemon!\n";
        }
        else
            std::cout << "Invalid input!\n";
    }

    switch (selectedStarter) {
        case 1:
            treecko.changeStatus(1);
            torchic.changeStatus(2);
            mudkip.changeStatus(2);
            std::cout << treecko << std::endl;
            break;
        case 2:
            treecko.changeStatus(2);
            torchic.changeStatus(1);
            mudkip.changeStatus(2);
            std::cout << torchic << std::endl;
            break;
        case 3:
            treecko.changeStatus(2);
            torchic.changeStatus(2);
            mudkip.changeStatus(1);
            std::cout << mudkip << std::endl;
            break;
        default:
            std::cout << "Invalid input!\n";
    }

    return 0;
}
