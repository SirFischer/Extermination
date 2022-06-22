/*
 * File: Inventory.cpp
 * Project: Extermination
 * File Created: Saturday, 19th February 2022 3:10:16 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Wednesday, 22nd June 2022 9:23:23 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */
#include "Inventory.hpp"

Inventory::Inventory(/* args */)
{
	mInventorySlots.push_back(std::make_shared<Item>());
	mInventorySlots.push_back(std::make_shared<Weapon>());
}

Inventory::~Inventory()
{
}

void	Inventory::Update(Yuna::Core::EventHandler *pEventhandler)
{
	if (pEventhandler->GetEventState((uint32_t)eAction::NEXT_ITEM))
	{
		mSelected++;
		if (mSelected >= mInventorySlots.size()) mSelected = 0;
		pEventhandler->SetEventState((uint32_t)eAction::NEXT_ITEM, false);
	}

	if (pEventhandler->GetEventState((uint32_t)eAction::PREVIOUS_ITEM))
	{
		mSelected--;
		if (mSelected >= mInventorySlots.size()) mSelected = mInventorySlots.size() - 1;
		pEventhandler->SetEventState((uint32_t)eAction::PREVIOUS_ITEM, false);
	}
}

void	Inventory::Render(Yuna::Core::Window *pWindow)
{
	sf::RectangleShape itemContainer(sf::Vector2f(60, 60));
	itemContainer.setFillColor(sf::Color::Transparent);
	itemContainer.setOutlineColor(sf::Color(60, 60, 60));
	int index = 0;
	int topPos = 200;

	for (auto &item : mInventorySlots)
	{
		(void)item;
		itemContainer.setOutlineThickness((mSelected == index) ? 7 : 5);
		itemContainer.setPosition(sf::Vector2f(20, topPos));
		topPos += 80;
		//RENDER ITEM
		pWindow->Draw(itemContainer);
		index++;
	}
}