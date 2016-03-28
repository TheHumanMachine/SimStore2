#include "GameInteraction.h"


GameInteraction::GameInteraction()
{
	_store1;
	_player1;
}


GameInteraction::~GameInteraction()
{
}


void GameInteraction::printMainMenu()
{
	std::cout << "\n[1] Buy Item" << std::endl;
	std::cout << "[2] Sell Item" << std::endl;
	std::cout << "[3] Next Day" << std::endl;
	std::cout << "[4] Print Inventory" << std::endl;
	std::cout << "[5] End Game" << std::endl;
	std::cout << "*************************************" << std::endl;
	std::cout << "What do you want to do?: ";
}


void GameInteraction::playGame()
{
	int affordableItemAmount;
	int currentDay = 1, elapsedDays = 0;
	int itemPlace, itemQuantity;
	int menuResp, menuSize = 5;
	bool isDone = false;

	std::default_random_engine rand_engine;
	std::uniform_real_distribution<double> float_dist(0.0, 1.9);

	while (!isDone)
	{
		std::cout << "*************************************" << std::endl;
		std::cout << "\nCurrent Day: " << currentDay << std::endl;
		std::cout << "Store's Money: " << _store1.getMoney() << " You're Money: " << _player1.getMoney() << std::endl;
		printMainMenu();

		std::cin >> menuResp;

		if (menuResp < 1 || menuResp > menuSize){
			while (menuResp < 1 || menuResp > menuSize){
				std::cout << "Enter a number [1 and " << menuSize << "]";
				std::cin >> menuResp;
			}
		}

		switch (menuResp)
		{
		case 1: // Buy Menu
			std::cout << std::endl;
			_store1.printInventory();

			//if getItemPlace is not -1 it assumes it a correct input.
			itemPlace = getItemPlace(_store1.getInventorySize(), "buy");
			if (itemPlace == -1){
				break;
			}

			std::cout << "You can afford up to " << int(_player1.getMoney() / _store1.getItem(itemPlace)->getCost())
				<< " of these items" << std::endl;

			affordableItemAmount = int( _player1.getMoney() / _store1.getItem(itemPlace)->getCost() );
			itemQuantity = getItemQty( _store1.getItemQuantity(itemPlace), affordableItemAmount );

			if (itemQuantity == -1){
				break;
			}

			//_player1.buyItem() Returns True if the item can be bought and False is it can not be bought
			if ( _player1.buyItem( _store1.getItem(itemPlace), itemQuantity) ){
				_store1.addMoney( _store1.getItem(itemPlace)->getCost() * itemQuantity );
				_store1.getItem(itemPlace)->removeItemQuantity(itemQuantity);
			}

			else{
				std::cout << "You couldn't buy that item." << std::endl;
			}
			
			break;

		case 2: //Sell Menu

			std::cout << std::endl;

			std::cout << "\n********* Items to sell *********" << std::endl;
			_player1.printInventory();

			itemPlace = getItemPlace( _player1.getInventorySize(), "sell");
			if (itemPlace == -1){
				break;
			}

			//Store money divided by player's items cost
			affordableItemAmount = int( _store1.getMoney() / _player1.getItem(itemPlace)->getCost() );

			itemQuantity = getItemQty(_player1.getItemQuantity(itemPlace), affordableItemAmount);

			if (itemQuantity == -1){
				std::cout << "You didn't sell any items." << std::endl;
				break;
			}

			//_store1.buyItem() Returns True if the item can be bought and False is it can not be bought
			if (_store1.buyItem(_player1.getItem(itemPlace), itemQuantity))
			{
				_player1.addMoney(_player1.getItem(itemPlace)->getCost() * itemQuantity);
				_player1.getItem(itemPlace)->removeItemQuantity(itemQuantity);

			}
			else{
				std::cout << "The store could not buy your item." << std::endl;
			}
			break;


		case 3: //Next Day Option
			currentDay += 1;
			elapsedDays += 1;

			std::cout << "\n***** +1 Day *****" << std::endl;

			for (size_t i = 1; i < _player1.getInventorySize() + 1; i++){

				double numberChange = float_dist(rand_engine);
				numberChange = floor(numberChange * 100.00 + 0.5) / 100.00;
				_player1.getItem(i)->changeItemValue(numberChange);
				_store1.getItem(i)->changeItemValue(numberChange);
			}

			if (currentDay % 5 == 0){

				for (size_t i = 1; i < _store1.getInventorySize() + 1; i++){
					if (_store1.getItem(i)->getItemQuantity() <= 0){
						//Adds more items to store inventory
						_store1.addMoney();
						_store1.getItem(i)->addItemQuantity(1);
					}
				}
			}

			break;

		case 4: // Player Inventory
			_player1.printInventory();
			break;

		case 5: //End Game
			isDone = true;
			break;
		}


	}
}


int GameInteraction::getItemPlace(int inventorySize, std::string choice)
{
	int itemPlace;

	std::cout << "\nWhat item do you want to " << choice  << " [1-" << inventorySize << "]: ";
	std::cin >> itemPlace;

	if (itemPlace == -1){
		return -1;
	}

	if (itemPlace < 1 || itemPlace > inventorySize){
		while (itemPlace < 1 || itemPlace > inventorySize){
			std::cout << "Enter a number between 1 and " << inventorySize << "]";
			std::cin >> itemPlace;
		}
	}

	return itemPlace;
}

int GameInteraction::getItemQty(int itemQty, int affordableItemAmount)
{
	int userInputitemQuantity;
	std::cout << itemQty << std::endl;
	std::cout << "\nHow many do you want to buy/sell?: ";
	std::cin >> userInputitemQuantity;

	if (userInputitemQuantity < 1 || userInputitemQuantity > itemQty){
		std::cout << "Your input was out of range" << std::endl;

		while (userInputitemQuantity < 1 || userInputitemQuantity > itemQty){
			if (itemQty > 0){
				std::cout << "Enter a number betwee 1 and " << itemQty << "]";
				std::cin >> userInputitemQuantity;
			}
			else{
				return -1;
			}
		}
	}

	if (userInputitemQuantity > affordableItemAmount){

		std::cout << "The store can not afford to buy this many items" << std::endl;
		while (userInputitemQuantity > affordableItemAmount && userInputitemQuantity >= 1){

			std::cout << "\nOnly: " << affordableItemAmount << " item(s) can be bought/sold" << std::endl;
			std::cout << "Pick a quantity that you wish to buy between 1 and " << affordableItemAmount << ": ";
			std::cin >> userInputitemQuantity;

			if (userInputitemQuantity == 0){
				return -1;
			}
		}
	}
	return userInputitemQuantity;
}