#pragma once
#include <vector>
#include <iostream>
#include "Item.h"
class Store
{
public:
	Store();
	
	int getInventorySize() const { return _inventory.size(); }
	Item *getItem(int itemPlace) { return _inventory[itemPlace - 1]; }
	int getItemQuantity(int itemPlace) const { return _inventory[itemPlace]->getItemQuantity(); }

	void setInventory();

	bool buyItem(Item *item, int quantity);

	float getMoney() const { return _money; }
	void removeMoney(float m){ _money -= floor(m * 100.00 + 0.5) / 100.00; }
	void addMoney(float m) { _money += floor(m * 100.00 + 0.5) / 100.00; }

	void printInventory();
	void inventoryWelcome();

private:
	float _money = 100;
	std::vector<Item*> _inventory;
};

