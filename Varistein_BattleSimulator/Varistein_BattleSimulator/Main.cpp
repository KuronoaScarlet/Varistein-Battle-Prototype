#include <iostream>
#include "Utils.h"

using namespace std;

int main()
{
	Character* player = new Character(50, 10, 15, "Nicole");
	Character* enemy = new Character(100, 5, 10, "Monster");

	allies.push_back(player);
	enemies.push_back(enemy);

	Ability* punch = new Ability(0, 15, 0, "Punch", Tag::OFFENSIVE);
	player->abilities.push_back(punch);
	Ability* empower = new Ability(1, 10, 0, "Empower", Tag::EFFECT);
	player->abilities.push_back(empower);
	Ability* chargedPunch = new Ability(2, 30, 0, "Charged Punch", Tag::OFFENSIVE);
	player->abilities.push_back(chargedPunch);

	do 
	{
		SelectAction();

		if (player->state != BattleState::RUN)
		{
			CombatState();

			// PerformAction();

			// Check();
		}

	} while (player->GetHP() > 0 && player->state != BattleState::RUN);

	if (player->GetHP() <= 0) cout << "You died." << endl;

	system("pause");
	return 0;
}