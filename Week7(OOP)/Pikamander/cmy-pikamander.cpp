#include <iostream>
#include <string>

using namespace std;

class BasePokemon {
protected:
    string name;
    int hp;
    enum Type { ELECTRIC, FIRE, ELECTROFIRE } type;
public:
    BasePokemon(string name, int hp, Type type) : name(name), hp(hp), type(type) {}
    virtual ~BasePokemon() {}

    Type getType() const { return type; }
    virtual void attack(BasePokemon& opponent) = 0;

    // to access protected variables
    string getName() const { return name; }
    int get_hp() const { return hp; }
    void set_hp(int new_hp) { hp = new_hp; }
};

class ElectricPokemon : virtual public BasePokemon {
public:
    int electricLevel;
    ElectricPokemon(string name, int hp, int electricLevel) : BasePokemon(name, hp, ELECTRIC), electricLevel(electricLevel) {}
};

class FirePokemon : virtual public BasePokemon {
public:
    int flameLevel;

    FirePokemon(string name, int hp, int flameLevel) : BasePokemon(name, hp, FIRE), flameLevel(flameLevel) {}
};

class Pikachu : public ElectricPokemon {
public:
    string cry;
    Pikachu() : BasePokemon("Pikachu", 100, ELECTRIC), ElectricPokemon("Pikachu", 100, 10), cry("Pika pika!") {}
    void attack(BasePokemon& opponent) override {
        if (opponent.getType() == FIRE) {
            opponent.set_hp(opponent.get_hp() - (electricLevel-2));
        } else {
            opponent.set_hp(opponent.get_hp() - electricLevel);
        }
    }
};

class Charmander : public FirePokemon {
public:
    int height;
    Charmander() : BasePokemon("Charmander", 200, FIRE), FirePokemon("Charmander", 200, 5), height(15) {}
    void attack(BasePokemon& opponent) override {
        if (opponent.getType() == ELECTRIC) {
            opponent.set_hp(opponent.get_hp() - (flameLevel + 2));
        } else {
            opponent.set_hp(opponent.get_hp() - flameLevel);
        }
    }
};

class Pikamander : public ElectricPokemon, public FirePokemon {
public:
    Pikamander() : BasePokemon("Pikamander", 300, ELECTROFIRE), ElectricPokemon("Pikamander", 300, 10), FirePokemon("Pikamander", 300, 5) { }

    void attack(BasePokemon& opponent) override {
        if (opponent.getType() == ELECTRIC) {
            opponent.set_hp(opponent.get_hp() - (electricLevel + 2));
        } else if (opponent.getType() == FIRE) {
            opponent.set_hp(opponent.get_hp() - (flameLevel + 2));
        } else {
            opponent.set_hp(opponent.get_hp() - (electricLevel + flameLevel) / 2);
        }
    }
};


int main() {
    // Create instances of Pokemon
    Pikachu pikachu;
    Charmander charmander;
    Pikamander pikamander;

    // Display initial HP
    cout << "Initial HP:" << endl;
    cout << "Pikachu: " << pikachu.get_hp() << endl;
    cout << "Charmander: " << charmander.get_hp() << endl;
    cout << "Pikamander: " << pikamander.get_hp() << endl;

    // Pikachu attacks Charmander
    cout << "\nPikachu attacks Charmander!" << endl;
    pikachu.attack(charmander);
    cout << "Charmander's HP after attack: " << charmander.get_hp() << endl;

    // Charmander attacks Pikachu
    cout << "\nCharmander attacks Pikachu!" << endl;
    charmander.attack(pikachu);
    cout << "Pikachu's HP after attack: " << pikachu.get_hp() << endl;

    // Pikamander attacks Pikachu
    cout << "\nPikamander attacks Pikachu!" << endl;
    pikamander.attack(pikachu);
    cout << "Pikachu's HP after Pikamander's attack: " << pikachu.get_hp() << endl;

    // Pikachu attacks Pikamander
    cout << "\nPikachu attacks Pikamander!" << endl;
    pikachu.attack(pikamander);
    cout << "Pikamander's HP after Pikachu's attack: " << pikamander.get_hp() << endl;

    return 0;
}