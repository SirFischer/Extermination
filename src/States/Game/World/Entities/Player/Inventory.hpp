/*
 * File: Inventory.hpp
 * Project: Extermination
 * File Created: Saturday, 19th February 2022 3:09:55 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Tuesday, 21st June 2022 6:17:16 am
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */
#pragma once
#include "Item.hpp"
#include "Weapon.hpp"
#include "Actions.hpp"
#include <vector>
#include <memory>

class Inventory
{
private:
	
	std::vector<std::shared_ptr<Item>>	mInventorySlots;
	u_int8_t							mSelected;

public:
	Inventory(/* args */);
	~Inventory();

	Item	*GetSelectedItem() {return (mInventorySlots[mSelected].get());}

	void	Update(Yuna::Core::EventHandler *pEventhandler);
	void	Render(Yuna::Core::Window *pWindow);
};
