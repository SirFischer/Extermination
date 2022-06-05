/*
 * File: Block.hpp
 * Project: Extermination
 * File Created: Monday, 25th October 2021 7:58:30 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Sunday, 5th June 2022 8:10:17 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */
#pragma once
#include <SFML/Graphics.hpp>
#include "Yuna.hpp"
#include <string>

enum class eBlockType
{
	GRASS,
	DIRT,
	CRATE
};

class Block : public Yuna::World::Object
{
protected:
	bool			mIsBreakable = false;
	bool			mSolid = true;
	sf::Color		mColor = sf::Color(255, 255, 255, 255);
	std::string		mTexturePath = "assets/textures/green400x400.png";
	sf::Vector2f	mPosition;
	sf::Vector2f	mSize;
	eBlockType		mType;

public:
	Block(/* args */);
	~Block();

	/**
	 * Setters
	 **/
	void			SetPosition(const sf::Vector2f &pPosition){mPosition = pPosition;}
	void			SetSize(const sf::Vector2f &pSize){mSize = pSize;}
	void			SetTexturePath(const std::string &pPath){mTexturePath = pPath;}
	void			SetColor(const sf::Color &pColor){mColor = pColor;}

	/**
	 * Getters
	 **/
	std::string			GetTexturePath() const {return (mTexturePath);}
	sf::Vector2f		GetPosition() const {return (mPosition);}
	sf::Vector2f		GetSize() const {return (mSize);}
	sf::Color			GetColor() const {return (mColor);}

	bool			IsSolid() {return (mSolid);}
	bool			IsBreakable() const {return (mIsBreakable);}
};
