#pragma once
#include <string>



class Item
{
public:
	Item(std::string name, int itemQuantity);
	
	void changeItemValue(float valueChange){ _cost *= floor(valueChange * 100.00 + 0.5) / 100.00; }
	float setNewCost(float newCost){ _cost = newCost; }

	std::string getName() const { return _name; }
	float getCost() const { return _cost; }
	int getItemQuantity() const { return _itemQuantity; }
	
	void removeItemQuantity(int removeAmount) { _itemQuantity -= removeAmount; }
	void addItemQuantity(int addedAmount) { _itemQuantity += addedAmount; }

private:
	int _itemQuantity;
	std::string _name;
	float _cost;

};

