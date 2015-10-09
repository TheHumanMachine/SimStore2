#include "Player.h"


Player::Player()
{
	setInventory();

}

void Player::setInventory()
{
	_inventory.push_back(new Item("Helmet", 0));
	_inventory.push_back(new Item("Chest", 0));
	_inventory.push_back(new Item("Legging", 0));
	_inventory.push_back(new Item("Gaunlets", 0));
	_inventory.push_back(new Item("Boots", 0));
	_inventory.push_back(new Item("Potions", 0));
	_inventory.push_back(new Item("Scrolls", 0));

}

void Player::printInventory()
{
	for (size_t i = 0; i < _inventory.size(); i++){
		if (_inventory[i]->getItemQuantity() > 0){
			std::cout << i + 1 << " Name: " << _inventory[i]->getName() << " Cost: " << _inventory[i]->getCost() <<
				" Quantity: " << _inventory[i]->getItemQuantity() << std::endl;
		}
	}
}

bool Player::buyItem(Item *item, int quantity)
{
	if (quantity * item->getCost() <= _money){

		for (size_t i = 0; i < _inventory.size(); i++)
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