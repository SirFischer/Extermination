/*
 * File: Player.hpp
 * Project: Extermination
 * File Created: Friday, 22nd October 2021 8:12:25 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Wednesday, 27th October 2021 7:46:26 am
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */
#pragma once
#include "Entities/Entity.hpp"
#include "Actions.hpp"

class Player : public Entity
{
private:
	/* data */
public:
	Player(/* args */);
	~Player();

	void	Update(Yuna::Core::EventHandler *tEventhandler);

};
