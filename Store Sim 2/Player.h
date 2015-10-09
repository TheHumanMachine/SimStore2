#pragma once
#include <vector>
#include <iostream>
#include "Item.h"

class Player
{
public:
	Player();

	int getInventorySize() const { return _inventory.size(); }
	double getMoney() const { return _money; }
	Item *getItem(int itemPlace) { return _inventory[itemPlace - 1]; }
	int getItemQuantity(int itemPlace) const { return _inventory[itemPlace - 1]->getItemQuantity(); }

	void setInventory();
	void printInventory();

	bool buyItem(Item *item, int quantity);

	void removeMoney(double m){ _money -= floor(m * 100.00 + 0.5) / 100.00; }
	void addMoney(double m) { _money += floor(m * 100.00 + 0.5) / 100.00; }

private:
	double _money = 500;
	std::vector<Item*> _inventory;
	

};

