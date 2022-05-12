/*
 * File: Background.hpp
 * Project: Extermination
 * File Created: Thursday, 12th May 2022 5:55:15 am
 * Author: Marek Fischer
 * -----
 * Last Modified: Thursday, 12th May 2022 4:15:27 pm
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
	sf::Vector2f	mMoveFactor = sf::Vector2f(0.f, 0.f);
	sf::Sprite		mBackgroundSprite;

public:
	Background(const sf::Vector2i &pSize);
	~Background();

	void	LoadBackground(sf::Texture *pTexture);
	void	SetMoveFactor(const sf::Vector2f &pMoveFactor);

	void	Update(const sf::Vector2f &pCamPos);

	void	Render(Yuna::Core::Window *pWindow);
};

