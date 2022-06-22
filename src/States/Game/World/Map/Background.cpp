/*
 * File: Background.cpp
 * Project: Extermination
 * File Created: Thursday, 12th May 2022 5:55:25 am
 * Author: Marek Fischer
 * -----
 * Last Modified: Sunday, 12th June 2022 8:04:47 pm
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
	mBackgroundSize = sf::Vector2i(pTexture->getSize());
}

void	Background::SetMoveFactor(const sf::Vector2f &pMoveFactor)
{
	mMoveFactor = pMoveFactor;
}

void	Background::SetScale(const sf::Vector2f &pScale)
{
	mBackgroundSprite.setScale(pScale);
}


void	Background::Update(const sf::Vector2f &pCamPos)
{
	mBackgroundSprite.setTextureRect(
		sf::IntRect((pCamPos.x - ((float)mSize.x / 2.f)) * mMoveFactor.x, (pCamPos.y - ((float)mSize.y / 2.f)) * mMoveFactor.y, mBackgroundSize.x, mBackgroundSize.y)
	);
}

void	Background::Render(Yuna::Core::Window *pWindow)
{
	pWindow->Draw(mBackgroundSprite);
}
