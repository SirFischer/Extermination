/*
 * File: PathNode.hpp
 * Project: Extermination
 * File Created: Saturday, 26th February 2022 8:27:25 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Saturday, 14th May 2022 9:49:38 am
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */
#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

struct PathNode;

struct Path
{
	std::shared_ptr<PathNode>	mTarget;
};

struct PathNode
{
	bool				mOpen = true;
	bool				mIsBreakable = false;
	sf::Vector2f		mPosition;
	std::vector<Path>	mConnectedPaths;
};
