/*
 * File: PathNode.hpp
 * Project: Extermination
 * File Created: Saturday, 26th February 2022 8:27:25 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Saturday, 26th February 2022 8:39:29 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */
#pragma once

#include <SFML/Graphics.hpp>

struct PathNode
{
	bool			open = true;
	sf::Vector2f	mPosition;
};
