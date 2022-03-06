/*
 * File: Block.hpp
 * Project: Extermination
 * File Created: Monday, 25th October 2021 7:58:30 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Wednesday, 16th February 2022 6:37:55 pm
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
protected:
	bool			mIsBreakable = false;
	float			mHealth = 100.f;
	sf::Color		mColor = sf::Color(255, 255, 255, 255);
	std::string		mTexturePath = "assets/textures/green400x400.png";
	sf::Vector2f	mPosition;
	eBlockType		mType;

public:
	Block(/* args */);
	~Block();

	/**
	 * Setters
	 **/
	void			SetPosition(sf::Vector2f pPosition){mPosition = pPosition;}
	void			SetTexturePath(std::string pPath){mTexturePath = pPath;}
	void			SetColor(sf::Color pColor){mColor = pColor;}

	/**
	 * Getters
	 **/
	std::string		GetTexturePath(){return (mTexturePath);}
	sf::Vector2f	GetPosition(){return (mPosition);}
	sf::Color		GetColor(){return (mColor);}
};
