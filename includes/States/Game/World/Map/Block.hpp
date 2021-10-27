/*
 * File: Block.hpp
 * Project: Extermination
 * File Created: Monday, 25th October 2021 7:58:30 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Wednesday, 27th October 2021 5:23:51 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */
#pragma once
#include <SFML/Graphics.hpp>
#include <string>

enum class eBlockType
{
	GRASS,
	DIRT,
	CRATE
};

class Block
{
private:
	bool			mIsBreakable = false;
	float			mHealth = 100.f;
	std::string		mTexturePath = "assets/textures/dirt_w_grass.png";
	sf::Vector2f	mPosition;
	eBlockType		mType;

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
