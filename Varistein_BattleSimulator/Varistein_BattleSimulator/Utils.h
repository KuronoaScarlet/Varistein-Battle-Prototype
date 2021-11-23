#ifndef __UTILS_H__
#define __UTILS_H__

#include <string>
#include <vector>

using namespace std;
bool pass = false;

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
	string GetName() { return name; }

	// Setters
	void SetHP(int _hp) { hp = _hp; }
	void SetDef(int _def) { hp = _def; }
	void SetAtk(int _atk) { hp = _atk; }

protected:
	int hp, def, atk;
	string name;

public:
	BattleState state = BattleState::UNKNOWN;
};

// Characters Lists
std::vector<Character*> allies;
std::vector<Character*> enemies;

// Various Methods
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
		cout << allies.at(i)->GetName() << "   " << "HP: " << allies.at(i)->GetHP() << endl;
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
		case 5:
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



#endif // !__UTILS_H__
