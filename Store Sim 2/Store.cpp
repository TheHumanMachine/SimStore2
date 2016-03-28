#include "Store.h"


Store::Store()
{
	setInventory();
}


void Store::setInventory()
{
	_inventory.push_back(new Item("Helmet", 5));
	_inventory.push_back(new Item("Chest", 5));
	_inventory.push_back(new Item("Legging", 5));
	_inventory.push_back(new Item("Gaunlets", 5));
	_inventory.push_back(new Item("Boots", 5));
	_inventory.push_back(new Item("Potions", 5));
	_inventory.push_back(new Item("Scrolls", 5));
}

void Store::printInventory()
{
	inventoryWelcome();

	for (int i = 0; i < _inventory.size(); i++){
		std::cout << i + 1 << " Item: " << _inventory[i]->getName() << " Cost: $" << _inventory[i]->getCost() 
			<< " In Stock: " << _inventory[i]->getItemQuantity() << std::endl;
	}
}

void Store::inventoryWelcome()
{
	std::cout << "\n******** Welcome to the Store Inventory ********\n" << std::endl;

}


bool Store::buyItem(Item *item, int quantity)
{
	if (quantity * item->getCost() <= _money){

		for (int i = 0; i < _inventory.size(); i++)
		{
			if (item->getName() == _inventory[i]->getName())
			{
				_inventory[i]->addItemQuantity(quantity);
				removeMoney(quantity * item->getCost());
				return true;
			}
		}

	}

	return false;
}
