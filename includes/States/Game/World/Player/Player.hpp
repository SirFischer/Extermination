/*
 * File: Player.hpp
 * Project: Extermination
 * File Created: Friday, 22nd October 2021 8:12:25 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Saturday, 23rd October 2021 5:00:33 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */
#pragma once
#include "Entities/Entity.hpp"

class Player : public Entity
{
private:
	/* data */
public:
	Player(/* args */);
	~Player();

	void	Update(Yuna::Core::EventHandler *tEventhandler);

};
