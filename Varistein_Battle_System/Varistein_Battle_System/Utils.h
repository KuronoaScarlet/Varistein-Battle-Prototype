#ifndef __UTILS_H__
#define __UTILS_H__

#include <string>
#include <vector>

using namespace std;
bool pass = false;
int overchargedTurn = 0;
int auxDmg = 0;

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
	bool GetBoosted() { return boosted; }
	string GetName() { return name; }
	Tag GetTag() { return tag; }

	// Setter
	void SetEffect(int boost) { value = value + (boost * 0.01) * value; boosted = true; }
	void SetValue(int _value) { value = _value; }
	void SetBoosted(int boost) { boosted = boost; }
private:
	int energy;
	float value;
	int cooldown = 0;
	bool boosted = false;
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
	int GetTotalEnergy() { return totalEnergy; }
	int GetOverchargedValue() { return overchargedValue; }
	bool GetDefState() { return defendState; }
	bool GetOvercharged() { return overcharged; }

	string GetName() { return name; }

	// Setters
	void SetHP(int _hp) { hp = _hp; }
	void SetDef(int _def) { def = _def; }
	void SetAtk(int _atk) { atk = _atk; }
	void SetEnergy(int _energy) { energy = _energy; }
	void SetTotalEnergy(int _totalEnergy) { totalEnergy = _totalEnergy; }
	void SetOverchargedValue(int _overchargedValue) { overchargedValue = _overchargedValue; }
	void SetDefState(bool _defendState) { defendState = _defendState; }
	void SetOverchaged(bool _overcharged) { overcharged = _overcharged; }

protected:
	int hp, def, atk;
	bool defendState = false;
	bool overcharged = false;
	int energy = 2;
	int totalEnergy = energy;
	int overchargedValue = 0;
	string name;

public:
	BattleState state = BattleState::UNKNOWN;
	std::vector<Ability*> abilities;
};

// Characters Lists
std::vector<Character*> allies;
std::vector<Character*> enemies;

// Ability Order List
std::vector<Ability*> order;

// First Menu's Methods
int Menu()
{
	int select;
	cout << "Choose action:" << endl << "   1. Attack" << endl << "   2. Defend" << endl << "   3. Object" << endl << "   4. Run" << endl;
	scanf_s("%d", &select);
	return select;
}

void ShowStats()
{
	for (int i = 0; i < allies.size(); i++)
	{
		cout << allies.at(i)->GetName() << "   " << "HP: " << allies.at(i)->GetHP() << "   " << "Energy: " << allies.at(i)->GetEnergy() << "/" << allies.at(i)->GetTotalEnergy() << endl;
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
		cout << i + 1 << ". " << allies.at(0)->abilities.at(i)->GetName() << "   " << "Energy: " << allies.at(0)->abilities.at(i)->GetEnergy();
		if (allies.at(0)->abilities.at(i)->GetTag() == Tag::OFFENSIVE)
		{
			cout << "    " << "Damage: " << allies.at(0)->abilities.at(i)->GetValue() << endl;
		}
		else if (allies.at(0)->abilities.at(i)->GetTag() == Tag::EFFECT)
		{
			cout << "    " << "Boost: " << allies.at(0)->abilities.at(i)->GetValue() << "%" << endl;
		}
	}
	cout << endl << "Select the sequence of the abilities you want to use! Be careful with the energy, using more energy than your total will overcharge yourself! (Example, input 21): " << endl;

	int selection;

	scanf_s("%d", &selection);

	system("cls");

	while (selection > 0)
	{
		int ability = (selection % 10) - 1;
		selection = selection / 10;

		order.push_back(allies.at(0)->abilities.at(ability));
	}

	int aux = 0;

	for (int i = order.size() - 1; i >= 0; i--)
	{
		aux = aux + order.at(i)->GetEnergy();
	}

	if (aux <= allies.at(0)->GetEnergy())
	{
		cout << "Energy used: " << aux << endl;
	}
	else if (aux > allies.at(0)->GetEnergy())
	{
		if (allies.at(0)->GetOvercharged() == false)
		{
			cout << "Energy used: " << aux << endl << "Overcharge!" << endl << endl;
			allies.at(0)->SetOverchargedValue(aux - allies.at(0)->GetEnergy());
			allies.at(0)->SetOverchaged(true);
			overchargedTurn = 1;
		}
		else if (allies.at(0)->GetOvercharged() == true)
		{
			cout << "You're on an overcharged state! Select again your abilities!" << endl;
			order.clear();
			AttackMenu();
		}
	}
	system("pause");
}

void PerformAction()
{
	int totalDmg = 0;
	for (int i = order.size() - 1; i >= 0; i--)
	{
		if (order.at(i)->GetTag() == Tag::OFFENSIVE)
		{
			// Damage Formula (HP = HP - ((Atk + abilitydmg) - Def)) Boosted Dmg is calculated earlier.
			int totalAttackDmg = allies.at(0)->GetAtk() + order.at(i)->GetValue();
			int dmgDone = totalAttackDmg - enemies.at(0)->GetDef();
			enemies.at(0)->SetHP(enemies.at(0)->GetHP() - dmgDone);
			cout << order.at(i)->GetName() << " did " << dmgDone << " damage to " << enemies.at(0)->GetName() << "." << endl << endl;
			totalDmg += dmgDone;

			if (order.at(i)->GetBoosted() == true)
			{
				order.at(i)->SetValue(auxDmg);
				order.at(i)->SetBoosted(false);
			}

			system("pause");
		}
		else if (order.at(i)->GetTag() == Tag::EFFECT && order.at(i - 1)->GetTag() == Tag::OFFENSIVE)
		{
			auxDmg = order.at(i - 1)->GetValue();
			order.at(i - 1)->SetEffect(order.at(i)->GetValue());
			cout << order.at(i)->GetName() << " boosted " << order.at(i - 1)->GetName() << " by a " << order.at(i)->GetValue() << "%" << endl << endl;

			system("pause");
		}
	}

	cout << "You did " << totalDmg << " total damage to " << enemies.at(0)->GetName() << "." << endl;
}

void Check()
{
	for (int i = 0; i < enemies.size(); i++)
	{
		if (enemies.at(i)->GetHP() <= 0)
		{
			cout << enemies.at(i)->GetName() << " has died!" << endl;
			enemies.pop_back();
		}
	}

	for (int i = 0; i < allies.size(); i++)
	{
		if (allies.at(i)->GetHP() <= 0)
		{
			cout << allies.at(i)->GetName() << " has died!" << endl;
			allies.pop_back();
		}
	}
}

void ObjectMenu()
{
	cout << "This feature is not up yet! Take another action!" << endl;
	allies.at(0)->state = BattleState::UNKNOWN;
	system("pause");
	system("cls");
	pass = false;
	SelectAction();
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

void PerformEnemyAction()
{
	int totalDmg = 0;

	for (int i = 0; i < enemies.at(0)->abilities.size(); i++)
	{
		if (enemies.at(0)->abilities.at(i)->GetTag() == Tag::OFFENSIVE)
		{
			// Damage Formula (HP = HP - ((Atk + abilitydmg) - Def)) Boosted Dmg is calculated earlier.
			int totalAttackDmg = enemies.at(0)->GetAtk() + enemies.at(0)->abilities.at(i)->GetValue();
			int dmgDone;
			if (allies.at(0)->GetDefState() == false)
			{
				dmgDone = totalAttackDmg - allies.at(0)->GetDef();
			}
			else
			{
				dmgDone = totalAttackDmg - (allies.at(0)->GetDef() * 2);
				if (dmgDone < 0)
				{
					dmgDone = 0;
				}
			}
			allies.at(0)->SetHP(allies.at(0)->GetHP() - dmgDone);
			cout << enemies.at(0)->abilities.at(i)->GetName() << " did " << dmgDone << " damage to " << allies.at(0)->GetName() << "." << endl << endl;
			totalDmg += dmgDone;

			system("pause");
		}
	}
}
#endif // !__UTILS_H__
