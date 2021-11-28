#ifndef __UTILS_H__
#define __UTILS_H__

#include <string>
#include <vector>

using namespace std;
bool pass = false;
float auxDmg = 0;

enum struct Tag
{
	OFFENSIVE,
	EFFECT,
};

class Ability
{
public:
	Ability(int _energy, float _value, int _cooldown, const char* _name, Tag _tag) : energy(_energy), value(_value), cooldown(_cooldown), name(_name), tag(_tag) {}
	~Ability() {}

	// Getters
	int GetEnergy() { return energy; }
	float GetValue() { return value; }
	int GetCooldown() { return cooldown; }
	string GetName() { return name; }
	Tag GetTag() { return tag; }

	// Setters
	void SetEffect(int boost, int* dmg) { auxDmg = (*dmg);  (*dmg) = (boost * 0.01) * (*dmg); }
private:
	int energy;
	float value;
	int cooldown = 0;
	string name;
	Tag tag;
};

enum class BattleState
{
	UNKNOWN,
	ATTACK,
	DEFEND,
	OBJECT,
	RUN
};

// Characters Class
class Character
{
public:
	Character(int _hp, int _def, int _atk, const char* _name) : hp(_hp), def(_def), atk(_atk), name(_name) {}
	~Character() {}

	// Getters
	int GetHP() { return hp; }
	int GetDef() { return def; }
	int GetAtk() { return atk; }
	int GetEnergy() { return energy; }
	string GetName() { return name; }

	// Setters
	void SetHP(int _hp) { hp = _hp; }
	void SetDef(int _def) { def = _def; }
	void SetAtk(int _atk) { atk = _atk; }
	void SetEnergy(int _energy) { energy = _energy; }
	void SetDefState(bool _defendState) { defendState = _defendState; }

protected:
	int hp, def, atk;
	bool defendState = false;
	int energy = 2;
	string name;

public:
	BattleState state = BattleState::UNKNOWN;
	std::vector<Ability*> abilities;
};

// Characters Lists
std::vector<Character*> allies;
std::vector<Character*> enemies;

// First Menu's Methods
int Menu()
{
	int select;
	cout << "Choose action:" << endl << "   1. Attack" << endl << "   2. Defend" << endl << "   3. Object" << endl <<"   4. Run" << endl;
	scanf_s("%d", &select);
	return select;
}

void ShowStats()
{
	for (int i = 0; i < allies.size(); i++)
	{
		cout << allies.at(i)->GetName() << "   " << "HP: " << allies.at(i)->GetHP() << "   " << "Energy: " << allies.at(i)->GetEnergy() << endl;
	}
	cout << endl;
	for (int i = 0; i < enemies.size(); i++)
	{
		cout << enemies.at(i)->GetName() << "   " << "HP: " << enemies.at(i)->GetHP() << endl;
	}
	cout << endl << endl;
}

void SelectAction()
{
	ShowStats();

	int selection;

	while (pass == false)
	{
		selection = Menu();

		switch (selection)
		{
		case 1:
			system("cls");
			cout << "Attack!" << endl;
			pass = true;
			allies.at(0)->state = BattleState::ATTACK;
			break;
		case 2:
			system("cls");
			cout << "Defending!" << endl;
			allies.at(0)->state = BattleState::DEFEND;
			pass = true;
			break;
		case 3:
			system("cls");
			cout << "Object!" << endl;
			allies.at(0)->state = BattleState::OBJECT;
			pass = true;
			break;
		case 4:
			system("cls");
			cout << "Running!" << endl;
			allies.at(0)->state = BattleState::RUN;
			pass = true;
			break;
		case 0:
			system("cls");
			allies.at(0)->SetHP(0);
			pass = true;
			break;
		default:
			system("cls");
			cout << "Repeat the input" << endl;
			break;
		}
	}
}

// Combat Selector Methods
void AttackMenu()
{
	for (int i = 0; i < allies.at(0)->abilities.size(); i++)
	{
		cout << allies.at(0)->abilities.at(i)->GetName() << "   " << "Energy: " << allies.at(0)->abilities.at(i)->GetEnergy();
		if (allies.at(0)->abilities.at(i)->GetTag() == Tag::OFFENSIVE)
		{
			cout << "    " << "Damage: " << allies.at(0)->abilities.at(i)->GetValue() << endl;
		}
		else if (allies.at(0)->abilities.at(i)->GetTag() == Tag::EFFECT)
		{
			cout << "    " << "Boost: " << allies.at(0)->abilities.at(i)->GetValue() << "%" << endl;
		}
	}

	int selection;

	scanf_s("%d", &selection);



}

void ObjectMenu()
{

}

void CombatState()
{
	switch (allies.at(0)->state)
	{
	case BattleState::ATTACK:
		ShowStats();
		AttackMenu();
		break;
	case BattleState::DEFEND:
		allies.at(0)->SetDefState(true);
		pass = false;
		break;
	case BattleState::OBJECT:
		ObjectMenu();
		break;
	default:
		break;
	}
}




#endif // !__UTILS_H__
