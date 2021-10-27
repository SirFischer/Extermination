/*
 * File: Block.hpp
 * Project: Extermination
 * File Created: Monday, 25th October 2021 7:58:30 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Tuesday, 26th October 2021 7:08:22 am
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */
#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Block
{
private:
	bool			mIsBreakable = false;
	float			mHealth = 100.f;
	std::string		mTexturePath = "assets/textures/dirt_w_grass.png";
	sf::Vector2f	mPosition;

public:
	Block(/* args */);
	~Block();

	/**
	 * Setters
	 **/
	void			SetPosition(sf::Vector2f pPosition){mPosition = pPosition;}

	/**
	 * Getters
	 **/
	std::string		GetTexturePath(){return (mTexturePath);}
	sf::Vector2f	GetPosition(){return (mPosition);}
};
