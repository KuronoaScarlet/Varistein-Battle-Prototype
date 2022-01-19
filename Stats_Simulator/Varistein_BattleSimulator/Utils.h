#ifndef __UTILS_H__
#define __UTILS_H__

#include <string>
#include <vector>
#include <time.h>

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
	Character(int _hp, int _def, int _atk, int _cc, const char* _name) : hp(_hp), def(_def), atk(_atk), cc(_cc), name(_name) {}
	~Character() {}

	// Getters
	int GetHP() { return hp; }
	int GetDef() { return def; }
	int GetAtk() { return atk; }
	int GetCc() { return cc; }
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
	void SetCc(int _cc) { cc = _cc; }
	void SetEnergy(int _energy) { energy = _energy; }
	void SetTotalEnergy(int _totalEnergy) { totalEnergy = _totalEnergy; }
	void SetOverchargedValue(int _overchargedValue) { overchargedValue = _overchargedValue; }
	void SetDefState(bool _defendState) { defendState = _defendState; }
	void SetOverchaged(bool _overcharged) { overcharged = _overcharged; }

protected:
	int hp, def, atk, cc;
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

bool Check()
{
	for (int i = 0; i < enemies.size(); i++)
	{
		if (enemies.at(i)->GetHP() <= 0)
		{
			enemies.at(i)->abilities.clear();
			enemies.pop_back();
			return false;
		}
	}

	for (int i = 0; i < allies.size(); i++)
	{
		if (allies.at(i)->GetHP() <= 0)
		{
			allies.at(i)->abilities.clear();
			allies.pop_back();
			return false;
		}
	}

	return true;
}

bool CriticalAttack(std::vector<Character*>& attacker)
{
	int crit = rand() % 100 + 1;
	if (crit <= attacker[0]->GetCc())
	{
		return true;
	}
	else
	{
		return false;
	}
}

void PerformSimulatedAction(std::vector<Character*>& attacker, std::vector<Character*>& defender)
{
	int totalDmg = 0;
	int select;


	if (attacker[0]->abilities.size() > 1)
	{
		select = rand() % 2;
	}
	else
	{
		select = 0;
	}

	// Damage Formula (HP = HP - ((Atk + abilitydmg) - Def)) Boosted Dmg is calculated earlier.
	int totalAttackDmg = attacker.at(0)->GetAtk() + attacker.at(0)->abilities.at(select)->GetValue();
	if (CriticalAttack(attacker))
	{
		totalAttackDmg *= 1.5;
	}
	int dmgDone;

	dmgDone = totalAttackDmg - defender.at(0)->GetDef();
			
	defender.at(0)->SetHP(defender.at(0)->GetHP() - dmgDone);
	totalDmg += dmgDone;
	
	
}

#endif // !__UTILS_H__
