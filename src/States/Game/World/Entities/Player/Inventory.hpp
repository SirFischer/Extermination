/*
 * File: Inventory.hpp
 * Project: Extermination
 * File Created: Saturday, 19th February 2022 3:09:55 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Wednesday, 29th June 2022 6:22:15 am
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */
#pragma once
#include "Item.hpp"
#include "CrateItem.hpp"
#include "Weapon.hpp"
#include "Actions.hpp"
#include <vector>
#include <memory>

class Inventory
{
private:
	
	std::vector<std::shared_ptr<Item>>	mInventorySlots;
	u_int8_t							mSelected = 0;
	sf::RectangleShape					mItemContainer;
	const int							mSlotSize = 60;

public:
	Inventory();
	~Inventory();

	Item	*GetSelectedItem() {return (mInventorySlots[mSelected].get());}

	void	AddItem(std::shared_ptr<Item> pItem);
	void	NextItem();
	void	PreviousItem();

	void	Update();
	void	Render(Yuna::Core::Window *pWindow);
};
