#include <iostream>
#include <random>

#include "Player.h"
#include"Store.h"

void playerBuy(Player player1, Store store1, int itemPlace, int itemQuantity);
void printMainMenu();

int main()
{
	Player player1;
	Store store1;

	int affordableItemAmount;
	int currentDay = 1, elapsedDays = 0;
	int itemPlace, itemQuantity;
	int menuResp, menuSize = 5;
	bool isDone = false;

	std::default_random_engine rand_engine;
	std::uniform_real_distribution<double> float_dist(0.0, 1.9);

	while (!isDone)
	{
		std::cout << "Current Day: " << currentDay << std::endl;
		std::cout << "Store's Money: " << store1.getMoney() << " You're Money: " << player1.getMoney() << std::endl;
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
			store1.printInventory();

			std::cout << "\nWhat item do you want to buy? [1-" << store1.getInventorySize() << "]: ";
			std::cin >> itemPlace;

			if (itemPlace == -1){
				break;
			}

			if (itemPlace < 1 || itemPlace > store1.getInventorySize()){
				while (itemPlace < 1 || itemPlace > store1.getInventorySize()){
					std::cout << "Enter a number between 1 and " << store1.getInventorySize() << "]";
					std::cin >> itemPlace;
				}
			}

			std::cout << "You can afford up to " << int(player1.getMoney() / store1.getItem(itemPlace)->getCost())
				<<" of these items"  << std::endl;
			std::cout << "\nHow many do you want to buy?: ";
			std::cin >> itemQuantity;

			if (itemQuantity < 1 || itemQuantity > store1.getItemQuantity(itemPlace)){

				std::cout << "Your input was out of range" << std::endl;
				while (itemQuantity < 1 || itemQuantity > store1.getItemQuantity(itemPlace)){
					if (store1.getItemQuantity(itemPlace) > 0){
						std::cout << "Enter a number betwee 1 and " << store1.getItemQuantity(itemPlace) << "]";
						std::cin >> itemQuantity;
					}
					else{
						std::cout << "The store doesn't have any of that item in stock at the moment." << std::endl;
						break;
					}
				}
			}
			
			affordableItemAmount = int(player1.getMoney() / store1.getItem(itemPlace)->getCost());
			if (itemQuantity > affordableItemAmount){
				std::cout << "You can not afford that many items, please select another amount" << std::endl;
				bool quit = false;
				while (!quit || itemQuantity > affordableItemAmount && itemQuantity > 0){

					std::cout << "Enter -1 to quit buying item" << std::endl;
					std::cout << "You can afford: " << affordableItemAmount << " item(s)" << std::endl;
					std::cout << "Pick a quantity that you wish to buy between 1 and " << affordableItemAmount << ": "<< std::endl;
					std::cin >> itemQuantity;
					
				}
			}

			if (player1.buyItem(store1.getItem(itemPlace), itemQuantity)){
				store1.addMoney(store1.getItem(itemPlace)->getCost() * itemQuantity);
				store1.getItem(itemPlace)->removeItemQuantity(itemQuantity);

			}
			else{
				std::cout << "You couldn't buy that item." << std::endl;
			}

			break;

		case 2: //Sell Menu

			std::cout << std::endl;
			player1.printInventory();

			std::cout << "\nWhat item do you want to sell? [1-" << player1.getInventorySize() << "]: ";
			std::cin >> itemPlace;

			if (itemPlace < 1 || itemPlace > player1.getInventorySize()){
				while (itemPlace < 1 || itemPlace > player1.getInventorySize()){
					std::cout << "Enter a number betwee 1 and " << player1.getInventorySize() << "]";
					std::cin >> itemPlace;
				}
			}

			std::cout << "\nHow many do you want to sell?: ";
			std::cin >> itemQuantity;

			if (itemQuantity < 1 || itemQuantity > player1.getItemQuantity(itemPlace)){
				std::cout << "Your input was out of range" << std::endl;
				while (itemQuantity < 1 || itemQuantity > player1.getItemQuantity(itemPlace)){
					if (player1.getItemQuantity(itemPlace) > 0){
						std::cout << "Enter a number betwee 1 and " << player1.getItemQuantity(itemPlace) << "]";
						std::cin >> itemQuantity;
					}
					else{
						std::cout << "You currently don't have any of that item to sell" << std::endl;
						break;
					}
				}
			}


			if (store1.buyItem(player1.getItem(itemPlace), itemQuantity))
			{
				player1.addMoney(player1.getItem(itemPlace)->getCost() * itemQuantity);
				player1.getItem(itemPlace)->removeItemQuantity(itemQuantity);

			}
			else{
				std::cout << "The store could not buy your item." << std::endl;
			}
			break;


		case 3: //Next Day Option
			currentDay += 1;
			elapsedDays += 1;


			for (size_t i = 1; i < player1.getInventorySize() + 1; i++){

				float numberChange = float_dist(rand_engine);
				numberChange = floor(numberChange * 100.00 + 0.5) / 100.00; 
				player1.getItem(i)->changeItemValue(numberChange);
				store1.getItem(i)->changeItemValue(numberChange);
			}

			if (currentDay % 5 == 0){
				for (size_t i = 0; player1.getInventorySize() + 1; i++){
					if (store1.getItem(i)->getItemQuantity() <= 0){
						store1.getItem(i)->addItemQuantity(5);
					}
				}
			}

			break;

		case 4: // Player Inventory
			player1.printInventory();
			break;

		case 5: //End Game
			isDone = true;
			break;
		}


	}

	return 0;

}

void printMainMenu()
{
	std::cout << "\n[1] Buy Item" << std::endl;
	std::cout << "[2] Sell Item" << std::endl;
	std::cout << "[3] Next Day" << std::endl;
	std::cout << "[4] Print Inventory" << std::endl;
	std::cout << "[5] End Game" << std::endl;
	std::cout << "What do you want to do?: ";

}