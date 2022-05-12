/*
 * File: Background.cpp
 * Project: Extermination
 * File Created: Thursday, 12th May 2022 5:55:25 am
 * Author: Marek Fischer
 * -----
 * Last Modified: Thursday, 12th May 2022 4:12:50 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */

#include "Background.hpp"

Background::Background(const sf::Vector2i &pSize)
:mSize(pSize)
{
	
}

Background::~Background()
{
}

void	Background::LoadBackground(sf::Texture *pTexture)
{
	if (!pTexture) return;

	pTexture->setRepeated(true);
	mBackgroundSprite.setPosition(0, 0);
	mBackgroundSprite.setTexture(*pTexture);
	mBackgroundSprite.setScale((float)mSize.x / pTexture->getSize().x, (float)mSize.y / pTexture->getSize().y);
	mBackgroundSprite.setTextureRect(sf::IntRect(0, 0, mSize.x, mSize.y));
}

void	Background::SetMoveFactor(const sf::Vector2f &pMoveFactor)
{
	mMoveFactor = pMoveFactor;
}


void	Background::Update(const sf::Vector2f &pCamPos)
{
	mBackgroundSprite.setTextureRect(
		sf::IntRect((pCamPos.x - ((float)mSize.x / 2.f)) * mMoveFactor.x, (pCamPos.y - ((float)mSize.y / 2.f)) * mMoveFactor.y, mSize.x, mSize.y)
	);
}

void	Background::Render(Yuna::Core::Window *pWindow)
{
	pWindow->Draw(mBackgroundSprite);
}
