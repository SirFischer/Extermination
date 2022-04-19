/*
 * File: Enemy.hpp
 * Project: Extermination
 * File Created: Monday, 24th January 2022 6:44:10 am
 * Author: Marek Fischer
 * -----
 * Last Modified: Monday, 24th January 2022 6:46:40 am
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */
#pragma once

#include "../Entity.hpp"

class Enemy : public Entity
{
private:
	
	void	Init(Yuna::Core::ResourceManager *pResourceManager);
	
public:
	Enemy(/* args */);
	~Enemy();
};

