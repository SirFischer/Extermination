/*
 * File: Inventory.cpp
 * Project: Extermination
 * File Created: Saturday, 19th February 2022 3:10:16 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Sunday, 3rd July 2022 1:25:19 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */
#include "Inventory.hpp"

Inventory::Inventory()
{
	mItemContainer.setSize(sf::Vector2f(mSlotSize, mSlotSize));
	mItemContainer.setFillColor(sf::Color::Transparent);
	mItemContainer.setOutlineColor(sf::Color(60, 60, 60));
}

Inventory::~Inventory()
{
}

void	Inventory::AddItem(std::shared_ptr<Item> pItem)
{
	mInventorySlots.push_back(pItem);
}

void	Inventory::NextItem()
{
	mSelected++;
	if (mSelected >= mInventorySlots.size()) mSelected = 0;
}

void	Inventory::PreviousItem()
{
	mSelected--;
	if (mSelected >= mInventorySlots.size()) mSelected = mInventorySlots.size() - 1;
}


void	Inventory::Update()
{
	
}

void	Inventory::Render(Yuna::Core::Window *pWindow)
{
	int index = 0;
	int topPos = 200;

	for (auto &item : mInventorySlots)
	{
		(void)item;
		mItemContainer.setOutlineThickness((mSelected == index) ? 7 : 5);
		mItemContainer.setOutlineColor( (mSelected == index) ? sf::Color::Red :sf::Color(60, 60, 60));
		
		mItemContainer.setPosition(sf::Vector2f(20, topPos));
		//RENDER ITEM
		pWindow->Draw(mItemContainer);
		item->SetIconPosition(sf::Vector2f(25, topPos + 5));
		item->RenderIcon(pWindow);
		
		topPos += mSlotSize + 20;
		index++;
	}
}