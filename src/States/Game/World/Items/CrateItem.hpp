/*
 * File: CrateItem.hpp
 * Project: Extermination
 * File Created: Wednesday, 16th February 2022 6:32:58 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Sunday, 5th June 2022 7:12:49 pm
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
	bool		mIsValid = false;

public:
	CrateItem(Yuna::Core::ResourceManager *pResourceManager);
	~CrateItem();

	void	SetIsValid(const bool &pIsValid) {mIsValid = pIsValid;}

	void	Render(Yuna::Core::Window *pWindow);
};

