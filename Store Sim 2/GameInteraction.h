#pragma once
#include "Player.h"
#include "Store.h"
#include <random>
#include <iostream>


class GameInteraction
{
public:
	GameInteraction();
	~GameInteraction();
	void printMainMenu();
	void playGame();
	int getItemPlace(int inventorySize);
	int getItemQty(int itemQty, int affordableItemAmount);

private:
	Store _store1;
	Player _player1;
};

