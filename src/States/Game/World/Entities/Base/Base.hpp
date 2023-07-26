/*
 * File: Base.hpp
 * Project: Extermination
 * File Created: Friday, 4th November 2022 3:02:57 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Friday, 4th November 2022 3:11:08 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */
#pragma once

#include "Yuna.hpp"
#include "Entity.hpp"

class Base : public Entity
{
private:

public:
	Base(Yuna::Core::ResourceManager *pResourceManager);
	~Base();

	void		SetPosition(const sf::Vector2f &pPos);

};

