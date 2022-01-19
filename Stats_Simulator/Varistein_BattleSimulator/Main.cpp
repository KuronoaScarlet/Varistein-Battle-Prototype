#include <iostream>
#include "Utils.h"
#include <sys/types.h>

using namespace std;

int main()
{
	srand(time(NULL));

	float repeat = 10, simNum = 1000, allyWins, enemWins;
	int atk = 4, def = 5, hp = 100, cc = 10;
	int eatk = 10, edef = 10, ehp = 100, ecc = 10;

	Ability* punch = new Ability(0, 20, 0, "Punch", Tag::OFFENSIVE);
	Ability* chargedPunch = new Ability(2, 40, 0, "Charged Punch", Tag::OFFENSIVE);
	Ability* cleave = new Ability(0, 40, 0, "Cleave", Tag::OFFENSIVE);

	bool cont = true;
	for (unsigned int i = 0; i < repeat; i++)
	{
		allyWins = enemWins = 0;

		for (unsigned int i = 0; i < simNum; i++)
		{
			// Starter variables
			Character* player = new Character(hp, def, atk, cc, "Nicole");
			Character* enemy = new Character(ehp, edef, eatk, ecc, "Monster");

			allies.push_back(player);
			enemies.push_back(enemy);

			player->abilities.push_back(punch);
			player->abilities.push_back(chargedPunch);
			enemy->abilities.push_back(cleave);

			do
			{
				// Player Action
				if (allies.size() != 0)
				{
					PerformSimulatedAction(allies, enemies);
					cont = Check();
				}

				// Enemy Action
				if (enemies.size() != 0)
				{
					PerformSimulatedAction(enemies, allies);
					cont = Check();
				}
			} while (cont);

			if (allies.size() != 0)
			{
				allyWins++;
				allies[0]->abilities.clear();
				allies.clear();
			}
			if (enemies.size() != 0)
			{
				enemWins++;
				enemies[0]->abilities.clear();
				enemies.clear();
			}
			cont = true;
		}

		float aWr = (allyWins / simNum) * 100.0f;
		float eWr = (enemWins / simNum) * 100.0f;

		std::cout << "Allies Wr: " << aWr << "%" << endl << "Enemies Wr: " << eWr << "%" << endl << endl;
	}
	

	system("pause");
	return 0;
}