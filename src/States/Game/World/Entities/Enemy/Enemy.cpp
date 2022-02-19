/*
 * File: Enemy.cpp
 * Project: Extermination
 * File Created: Monday, 24th January 2022 6:45:02 am
 * Author: Marek Fischer
 * -----
 * Last Modified: Monday, 24th January 2022 6:46:58 am
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */
#include "Enemy/Enemy.hpp"


Enemy::Enemy(/* args */)
{
	
}

Enemy::~Enemy()
{
}

void	Enemy::Init(Yuna::Core::ResourceManager *pResourceManager)
{
	mSprite.setTexture(*pResourceManager->LoadTexture("assets/images/enemy/Zombie.png"));
	mSprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
	mSize = sf::Vector2f(mSprite.getGlobalBounds().width, mSprite.getGlobalBounds().height);
}
