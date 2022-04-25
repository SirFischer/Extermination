/*
 * File: Inventory.hpp
 * Project: Extermination
 * File Created: Saturday, 19th February 2022 3:09:55 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Monday, 25th April 2022 6:02:09 am
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */
#pragma once
#include "Item.hpp"
#include <list>
#include <memory>

class Inventory
{
private:
	int mInventoryCapacity = 10;

	std::list<std::shared_ptr<Item>> mInventory;

public:
	Inventory(/* args */);
	~Inventory();
};
