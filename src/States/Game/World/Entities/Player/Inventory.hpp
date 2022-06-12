/*
 * File: Inventory.hpp
 * Project: Extermination
 * File Created: Saturday, 19th February 2022 3:09:55 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Sunday, 12th June 2022 7:25:29 am
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */
#pragma once
#include "Item.hpp"
#include "Actions.hpp"
#include <vector>
#include <memory>

class Inventory
{
private:
	
	std::vector<std::shared_ptr<Item>>	mInventory;
	u_int8_t							mSelected;

public:
	Inventory(/* args */);
	~Inventory();

	Item	*GetSelectedItem() {return (mInventory[mSelected].get());}

	void	Update(Yuna::Core::EventHandler *pEventhandler);
	void	Render(Yuna::Core::Window *pWindow);
};
