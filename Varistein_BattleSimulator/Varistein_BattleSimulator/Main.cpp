#include <iostream>
#include "Utils.h"

using namespace std;

int main()
{
	// Starter variables
	Character* player = new Character(70, 15, 20, "Nicole");
	Character* enemy = new Character(200, 10, 10, "Monster");

	allies.push_back(player);
	enemies.push_back(enemy);

	Ability* punch = new Ability(0, 20, 0, "Punch", Tag::OFFENSIVE);
	player->abilities.push_back(punch);
	Ability* empower = new Ability(1, 20, 0, "Empower", Tag::EFFECT);
	player->abilities.push_back(empower);
	Ability* chargedPunch = new Ability(2, 40, 0, "Charged Punch", Tag::OFFENSIVE);
	player->abilities.push_back(chargedPunch);

	Ability* cleave = new Ability(0, 20, 0, "Cleave", Tag::OFFENSIVE);
	enemy->abilities.push_back(cleave);

	bool cont = true;

	do 
	{
		// Player Action
		SelectAction();

		if (player->state != BattleState::RUN)
		{
			CombatState();

			if (player->state == BattleState::ATTACK)
			{
				PerformAction();
			}

			Check();
			if (player->GetEnergy() < 10)
			{
				player->SetTotalEnergy(player->GetTotalEnergy() + 1);
				player->SetEnergy(player->GetTotalEnergy() - player->GetOverchargedValue());
			}
		}
		
		// Enemy Action
		if (player->state != BattleState::RUN && player->state != BattleState::OBJECT)
		{
			system("cls");
			ShowStats();
			system("pause");
			system("cls");
			cout << endl << enemies.at(0)->GetName() << " attacks!" << endl;
			PerformEnemyAction();
			Check();
		}

		// Checkers
		if (player->GetOvercharged() == true && overchargedTurn == 0)
		{
			player->SetOverchaged(false);
			cout << "You're no longer Overcharged!" << endl;
		}
		if (overchargedTurn > 0) overchargedTurn--;

		if (player->state == BattleState::RUN || enemies.size() == 0 || allies.size() == 0) cont = false;

		player->state = BattleState::UNKNOWN;
		pass = false;
		order.clear();

		cout << endl << endl;

	} while (cont);

	if (player->GetHP() <= 0) cout << "You died." << endl;

	system("pause");
	return 0;
}