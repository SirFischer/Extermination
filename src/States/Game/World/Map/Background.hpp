/*
 * File: Background.hpp
 * Project: Extermination
 * File Created: Thursday, 12th May 2022 5:55:15 am
 * Author: Marek Fischer
 * -----
 * Last Modified: Sunday, 12th June 2022 4:10:51 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */
#pragma once

#include <SFML/Graphics.hpp>
#include <Yuna.hpp>

class Background
{
private:
	sf::Vector2i	mSize;
	sf::Vector2i	mBackgroundSize = sf::Vector2i(0, 0);
	sf::Vector2f	mMoveFactor = sf::Vector2f(0.f, 0.f);
	sf::Sprite		mBackgroundSprite;

public:
	Background(const sf::Vector2i &pSize);
	~Background();

	void	LoadBackground(sf::Texture *pTexture);
	void	SetMoveFactor(const sf::Vector2f &pMoveFactor);
	void	SetScale(const sf::Vector2f &pScale);

	void	Update(const sf::Vector2f &pCamPos);

	void	Render(Yuna::Core::Window *pWindow);
};

