/*
 * File: Player.hpp
 * Project: Extermination
 * File Created: Friday, 22nd October 2021 8:12:25 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Wednesday, 29th June 2022 6:30:58 am
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */
#pragma once
#include "../Entity.hpp"
#include "Actions.hpp"
#include "../../Items/CrateItem.hpp"
#include "Inventory.hpp"

class Player : public Entity
{
private:

	//dependencies
	Yuna::Core::ResourceManager *mResourceManager = nullptr;

	Inventory	mInventory;
	sf::Sprite	mArm;
	sf::Sprite	mItemSprite;

	void	LoadAnimations();

	void	RenderArm(Yuna::Core::Window *pWindow);
	void	HandleEvents(Yuna::Core::EventHandler *tEventhandler, float mDeltaTime);

public:
	Player(/* args */);
	~Player();

	void	Init(Yuna::Core::ResourceManager *pResourceManager);
	void	Update(Yuna::Core::EventHandler *tEventhandler, float mDeltaTime);
	void	EquipItem(Item *pItem);

	void	Render(Yuna::Core::Window *pWindow);


};
