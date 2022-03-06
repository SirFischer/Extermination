/*
 * File: Player.hpp
 * Project: Extermination
 * File Created: Friday, 22nd October 2021 8:12:25 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Sunday, 6th March 2022 12:17:12 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */
#pragma once
#include "../Entity.hpp"
#include "Actions.hpp"
#include "CrateItem.hpp"

class Player : public Entity
{
private:
	void	LoadAnimations();
public:
	Player(/* args */);
	~Player();

	void	Init(Yuna::Core::ResourceManager *pResourceManager);
	void	Update(Yuna::Core::EventHandler *tEventhandler, float mDeltaTime);
	void	EquipItem(Item *pItem);

};
