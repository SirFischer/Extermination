/*
 * File: Camera.hpp
 * Project: Extermination
 * File Created: Saturday, 15th January 2022 8:05:39 am
 * Author: Marek Fischer
 * -----
 * Last Modified: Saturday, 15th January 2022 12:17:40 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */
#pragma once

#include <SFML/Graphics.hpp>

class Camera
{
private:
	sf::View		mView;
	sf::Vector2f	mPosition = sf::Vector2f(0, 0);
	sf::IntRect		mTargetArea = sf::IntRect(0, 0, 50, 50);
	sf::Vector2f	mSize = sf::Vector2f(900, 800);
	sf::Vector2f	mVelocity = sf::Vector2f(0, 0);
	sf::IntRect		mBoundries = sf::IntRect(0, -999, 9999, 9999);

public:
	Camera(/* args */);
	~Camera();

	void		Update(const float &pDeltaTime);

	void		Move(const float &pX, const float &pY);

	void		SetPosition(const float &pX, const float &pY);
	void		SetPosition(const sf::Vector2f &pPosition);
	void		SetVelocity(const float &pX, const float &pY);
	void		SetBoundries(const sf::IntRect &pBoundries);
	void		SetView(const sf::View &pView);
	

	sf::Vector2f	GetPosition() {return (mPosition);}
	sf::View		GetView() {return (mView);}
};
