#include <iostream>
#include "Utils.h"

using namespace std;

int main()
{
	Character* player = new Character(50, 10, 15, "Nicole");
	Character* enemy = new Character(100, 5, 10, "Monster");

	allies.push_back(player);
	enemies.push_back(enemy);

	do 
	{
		ShowStats();
		SelectAction();
		ShowStats();

		// Combate kekw
	} while (player->GetHP() > 0 && player->state != BattleState::RUN);

	if (player->GetHP() <= 0) cout << "You died." << endl;

	system("pause");
	return 0;
}