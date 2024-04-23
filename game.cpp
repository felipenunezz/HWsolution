#include <iostream>
#include <string>

class Character {
    std::string name;
    int health;
    int power;
    int armor;
 public:
    static int history_count;
    static int count;

    Character(const Character& c) : health(c.health),
    armor(c.armor), power(c.power) {
        history_count++; count++;
        std::cout << "Copy constructer called\n";
    }

    Character(std::string _name = "", int _health = 100, int _power = 10,
    int _armor = 20) : health(_health), power(_power), armor(_armor) {
        if (_name == "") 
            name = "Character_" + std::to_string(history_count);
        else 
            name = _name;
        count++;
        history_count++;
    }

    int _power() {return power;}
    int _health() {return health;}
    int _armor() {return armor;}

    bool crit () 
    {
        return (rand() % 101) >= 95; 
    }
    
    int attack (Character& c, int _power) 
    {
        c.health -= _power * (1 + crit()) - _power * (c.armor / 100);
        return c.health;
    }

    int parry () {}


    ~Character() {
        count--;
        std::cout <<
        "Character with name " << 
        name << " was deleted, count of characters: " <<
        count << "\n";
    }
};

class Mage : public Character 
{
    int mana;

 public:
    int attack_cooldow = 0;
    Mage(std::string _name = "", int _health = 100, int _power = 10, int _armor = 0, int _mana = 100): Character(_name, _health, _power, _armor) , mana(_mana)
    {}

    void Small_attack (Character& c) 
    {
        if (mana >= 10) 
        {   
            mana -= 10;
            this->attack(c, _power() + _power() / 2);
            attack_cooldow --;
        }
        else this->attack(c, _power() / 2); mana += 15; 
    }

    void Big_attack (Character& c) 
    {
        if (mana >= 20)
        {
            mana -= 20;
            this->attack(c, _power() * 2);
            attack_cooldow = 2;
        }

    }

};
class Priest: public Character 
{
    int Hpower;

    public:

};
class Asassin: public Character {};
class Paladin: public Character {};
class Archer: public Character {};

int Character::history_count = 0;
int Character::count = 0;

int main() {
    Character p1, p2("Bob", 120, 10, 30), p3("Piter");
    std::cout << p1.count << " " << Character::count << "\n";
    
    
    p1.save(p2, p2.attack(p1));
 
    return 0;
}