#include <iostream>
#include "Utils.h"

using namespace std;

int main()
{
	srand(time(NULL));

	int combatNum = 0;
	while (combatNum == 0)
	{
		cout << "Que combate debes realizar? Introduce el numero que se te ha indicado en Twine." << endl;
		cin >> combatNum;
		if (combatNum != 1 && combatNum != 2 && combatNum != 3 && combatNum != 4)
		{
			combatNum = 0;
		}
	}
	system("cls");

	Character* player = nullptr;
	Character* enemy = nullptr;

	if (combatNum == 1)
	{
		//Node 18
		//Combate vs Guardia (Nivel 10)
		player = new Character(280, 31, 28, "Nicole");

		Ability* punch = new Ability(0, 40, 0, "Punch", Tag::OFFENSIVE);
		player->abilities.push_back(punch);
		Ability* empower = new Ability(1, 20, 0, "Empower", Tag::EFFECT);
		player->abilities.push_back(empower);
		Ability* chargedPunch = new Ability(2, 60, 0, "Charged Punch", Tag::OFFENSIVE);
		player->abilities.push_back(chargedPunch);
		
		
		enemy = new Character(280, 28, 28, "Guard");

		Ability* whack = new Ability(0, 40, 0, "Whack", Tag::OFFENSIVE);
		enemy->abilities.push_back(whack);


		allies.push_back(player);
		enemies.push_back(enemy);
	}
	if (combatNum == 2)
	{
		//Node 21
		//Combate vs Guardia (Nivel 25)
		player = new Character(580, 61, 58, "Nicole");

		Ability* punch = new Ability(0, 70, 0, "Punch", Tag::OFFENSIVE);
		player->abilities.push_back(punch);
		Ability* empower = new Ability(1, 30, 0, "Empower", Tag::EFFECT);
		player->abilities.push_back(empower);
		Ability* chargedPunch = new Ability(2, 90, 0, "Charged Punch", Tag::OFFENSIVE);
		player->abilities.push_back(chargedPunch);


		enemy = new Character(590, 59, 59, "Guard");

		Ability* whack = new Ability(0, 70, 0, "Whack", Tag::OFFENSIVE);
		enemy->abilities.push_back(whack);


		allies.push_back(player);
		enemies.push_back(enemy);
	}
	if (combatNum == 3)
	{
		//Node 30
		//Combate vs Bandido (Nivel 50)
		player = new Character(1080, 111, 108, "Nicole");

		Ability* groovyImpact = new Ability(0, 130, 0, "Groovy Impact", Tag::OFFENSIVE);
		player->abilities.push_back(groovyImpact);
		Ability* superBoost = new Ability(1, 45, 0, "Super-boost", Tag::EFFECT);
		player->abilities.push_back(superBoost);
		Ability* desintegrate = new Ability(2, 150, 0, "Desintegrate", Tag::OFFENSIVE);
		player->abilities.push_back(desintegrate);


		enemy = new Character(1100, 110, 110, "Bandido");

		Ability* serpentFang = new Ability(0, 130, 0, "Serpent's Fang", Tag::OFFENSIVE);
		enemy->abilities.push_back(serpentFang);


		allies.push_back(player);
		enemies.push_back(enemy);
	}
	if (combatNum == 4)
	{
		//Node 37
		//Combate vs Kal (Nivel 80)
		player = new Character(1680, 171, 168, "Nicole");

		Ability* destruction = new Ability(0, 190, 0, "Destruction", Tag::OFFENSIVE);
		player->abilities.push_back(destruction);
		Ability* hyperBoost = new Ability(2, 60, 0, "Hyper-boost", Tag::EFFECT);
		player->abilities.push_back(hyperBoost);
		Ability* ceforsTruth = new Ability(3, 210, 0, "Cefor's truth", Tag::OFFENSIVE);
		player->abilities.push_back(ceforsTruth);
		Ability* energyBloom = new Ability(6, 300, 0, "Energy Bloom", Tag::OFFENSIVE);
		player->abilities.push_back(energyBloom);


		enemy = new Character(1720, 172, 172, "Kal, the Great Master");

		Ability* decapitation = new Ability(0, 200, 0, "Decapitation", Tag::OFFENSIVE);
		enemy->abilities.push_back(decapitation);


		allies.push_back(player);
		enemies.push_back(enemy);
	}

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
		if (player->state != BattleState::RUN && player->state != BattleState::OBJECT && enemies.size() != 0)
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
		player->SetDefState(false);
		pass = false;
		order.clear();

		cout << endl << endl;

	} while (cont);

	if (player->GetHP() <= 0) cout << "You died." << endl;

	system("pause");
	return 0;
}