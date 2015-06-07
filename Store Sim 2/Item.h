#pragma once
#include <string>



class Item
{
public:
	Item(std::string name, int itemQuantity);
	
	void changeItemValue(double valueChange){ _cost *= floor(valueChange * 100.00 + 0.5) / 100.00; }
	float setNewCost(double newCost){ _cost = newCost; }

	std::string getName() const { return _name; }
	double getCost() const { return floor(_cost * 100.00 + 0.5) / 100.00; }
	int getItemQuantity() const { return _itemQuantity; }
	
	void removeItemQuantity(int removeAmount) { _itemQuantity -= removeAmount; }
	void addItemQuantity(int addedAmount) { _itemQuantity += addedAmount; }

private:
	int _itemQuantity;
	std::string _name;
	double _cost;

};

