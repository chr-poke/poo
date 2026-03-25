#include <iostream>
#include <string>
#include <random>
#include <utility>
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

    pokeType(const int id_, std::string name_,
         const std::vector<float>& attack_,
         const std::vector<float>& defense_) : id{id_}, name{std::move(name_)},
                attack{attack_}, defense{defense_} {}

    pokeType(const pokeType& other) {
        this->id = other.id;
        this->name = other.name;
        this->attack = other.attack;
        this->defense = other.defense;
    }

    pokeType& operator=(const pokeType& other) = default;

    friend std::ostream& operator<<(std::ostream& os, const pokeType& obj) {
        os << "The " << obj.name << " Type has the id " << obj.id << ".\n";
        return os;
    }

    [[nodiscard]] float getAttack(int i) const {
        return attack[i];
    }
    [[nodiscard]] float getDefense(int i) const {
        return defense[i];
    }
    [[nodiscard]] const std::string& getName() const {
        return name;
    }
    [[nodiscard]] int getID() const {
        return id;
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

    move(const pokeType& type_, const int power_, std::string name_) :
        type{type_}, name{std::move(name_)}, power{power_} {}

    friend std::ostream& operator<<(std::ostream& os, const move& obj) {
        os << obj.name << " is a " << obj.type.getName()
           << " Type move and it has " << obj.power << " power.\n";
        return os;
    }

    [[nodiscard]] int getPower() const {
        return power;
    }
    [[nodiscard]] const pokeType& getType() const {
        return type;
    }
    [[nodiscard]] const std::string& getName() const {
        return name;
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
    pokemon() {
        this->pokedexNumber = 0;
        this->full_hp = 0;
        this->hp = 0;
        this->attack = 0;
        this->defense = 0;
        this->type1 = noneType;
        this->type2 = noneType;
        this->moveset = {};
        this->name = "Unknown";
        this->level = 0;
        this->xp = 0;
        this->status = 2;
    }

    pokemon(const int pokedexNumber_, const int full_hp_,
            const int attack_, const int defense_,
            const pokeType& type1_, const pokeType& type2_,
            const std::vector<move>& moveset_, std::string  name_,
            const int level_, const int status_) :
                pokedexNumber{pokedexNumber_}, full_hp{full_hp_},
                attack{attack_}, defense{defense_},
                type1{type1_}, type2{type2_},
                moveset{moveset_}, name{std::move(name_)},
                level{level_}, status{status_} {
        this->hp = full_hp;
        this->xp = pow(level, 3);
        if (status == 0)
            std::cout << "Wild " << name << " appeared!\n";
    }

    pokemon(const pokemon& other) {
        this->pokedexNumber = other.pokedexNumber;
        this->full_hp = other.full_hp;
        this->hp = other.full_hp;
        this->attack = other.attack;
        this->defense = other.defense;
        this->type1 = other.type1;
        this->type2 = other.type2;
        this->moveset = other.moveset;
        this->name = other.name;
        this->level = other.level;
        this->xp = pow(other.level, 3);
        this->status = other.status;
    }

    pokemon& operator=(const pokemon& other) = default;

    ~pokemon() {
        if (status == 1)
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

    int xpGain(double b, int l) {
        // b = xp of the defeated Pokemon
        // l = level of the defeated Pokemon
        xp += b * l / 7;
        if (xp >= pow(level + 1, 3)) {
            level++;
            attack++;
            defense++;
            full_hp += 2;
        }
        return b * l / 7;
    }

    void takeDamage(int damage) {
        hp -= damage;
        if (hp < 0)
            hp = 0;
    }

    [[nodiscard]] int damage(const int p, const int d, const float t1, const float t2) const {
        // p = move power
        // d = defense of target
        // t1 = target's 1st type effectiveness
        // t2 = target's 2nd type effectiveness
        // r = random number between 217/255 and 1
        const float r = getRandom();
        return std::floor(
            (static_cast<float>(((2 * level) / 5 + 2) * p * attack) / static_cast<float>(d)) / 50.0 * t1 * t2 * r);
    }

    move selMove() {
        std::string input;
        std::cout << "| ";
        for (unsigned long i = 0; i < moveset.size(); i++)
            std::cout << i + 1 << ". " << moveset[i].getName() << " | ";
        std::cout << std::endl << std::endl;
        std::cout << "Use a move by typing '1'-'"
                  << std::to_string(moveset.size()) << "'.\n";
        std::cout << "Type 'help' to learn more about " << name << "'s moves.\n";
        while (std::cin >> input) {
            if (input == "help")
                for (unsigned long i = 0; i < moveset.size(); i++)
                    std::cout << i + 1 << ". " << moveset[i];
            else if (stol(input) >= 1 && static_cast<unsigned long>(stol(input)) <= moveset.size())
                return moveset[stoi(input) - 1];
            else
                std::cout << "Invalid input!\n";
        }
        move none;
        return none;
    }

    [[nodiscard]] const std::string& getName() const {
        return name;
    }
    [[nodiscard]] int getHP() const {
        return hp;
    }
    [[nodiscard]] int getDefense() const {
        return defense;
    }
    [[nodiscard]] const pokeType& getType1() const {
        return type1;
    }
    [[nodiscard]] const pokeType& getType2() const {
        return type2;
    }
    [[nodiscard]] const std::vector<move>& getMoveset() const {
        return moveset;
    }
    [[nodiscard]] double getXP() const {
        return xp;
    }
    [[nodiscard]] int getLevel() const {
        return level;
    }
};

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

    pokemon starter;
    switch (selectedStarter) {
        case 1:
            starter = treecko;
            break;
        case 2:
            starter = torchic;
            break;
        case 3:
            starter = mudkip;
            break;
        default:
            std::cout << "You're not supposed to see this!\n";
    }
    starter.changeStatus(1);

    // *** BATTLE SIMULATOR ***

    bool onRoute = true;
    while (onRoute) {
        for (int i = 0; i < 1; i++) {
            pokemon poochyena(10, 17, 10, 8,
                              darkType, noneType,
                              {tackleMove, howlMove, sand_attackMove},
                              "Poochyena", 4, 0);
            std::cout << "Go! " << starter.getName() << "!\n\n";

            while (poochyena.getHP() > 0 && starter.getHP() > 0) {
                std::cout << poochyena << std::endl << starter;
                move myMove = starter.selMove();
                std::cout << "--- " << starter.getName() << " used " << myMove.getName() << "! ---\n";
                poochyena.takeDamage(starter.damage(
                    myMove.getPower(), poochyena.getDefense(),
                    myMove.getType().getAttack(poochyena.getType1().getID()),
                    myMove.getType().getAttack(poochyena.getType2().getID())));
                if (poochyena.getHP() <= 0)
                    break;

                std::cout << std::endl << poochyena << std::endl << starter << std::endl;
                move oppMove = poochyena.getMoveset()[rand() % poochyena.getMoveset().size()];
                std::cout << "--- " << poochyena.getName() << " used " << oppMove.getName() << "! ---\n\n";
                starter.takeDamage(poochyena.damage(
                    oppMove.getPower(), starter.getDefense(),
                    oppMove.getType().getAttack(starter.getType1().getID()),
                    oppMove.getType().getAttack(starter.getType2().getID())));
            }
            if (starter.getHP() <= 0) {
                std::cout << starter.getName() << " fainted!\n\n";
                std::cout << "You blacked out!\n";
                onRoute = false;
            }
            else {
                std::string input;
                std::cout << "\nWild " << poochyena.getName() << " fainted!\n";
                std::cout << starter.getName() << " gained "
                          << starter.xpGain(poochyena.getXP(), poochyena.getLevel())
                          << " XP.\n\n";
                std::cout << "Do you want to leave Route 101? Y/N \n";
                while (std::cin >> input) {
                    if (input == "Y") {
                        onRoute = false;
                        break;
                    }
                    if (input == "N")
                        break;
                    std::cout << "Invalid input!\n";
                }
            }
        }
    }

    return 0;
}