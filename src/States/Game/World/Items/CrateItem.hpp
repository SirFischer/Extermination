/*
 * File: CrateItem.hpp
 * Project: Extermination
 * File Created: Wednesday, 16th February 2022 6:32:58 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Sunday, 6th March 2022 11:41:42 am
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */

#pragma once

#include "Item.hpp"

class CrateItem : public Item
{
private:
	sf::Sprite	mSprite;

public:
	CrateItem(Yuna::Core::ResourceManager *pResourceManager);
	~CrateItem();

	void	Render(Yuna::Core::Window *pWindow);
};

