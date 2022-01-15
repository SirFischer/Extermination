/*
 * File: Camera.cpp
 * Project: Extermination
 * File Created: Saturday, 15th January 2022 8:05:29 am
 * Author: Marek Fischer
 * -----
 * Last Modified: Saturday, 15th January 2022 10:19:16 am
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */
#include "Camera.hpp"

Camera::Camera(/* args */)
{
}

Camera::~Camera()
{
}

void	Camera::Update(const float &pDeltaTime)
{
	(void)pDeltaTime;
	mPosition.x += mVelocity.x * pDeltaTime;
	mPosition.y += mVelocity.y * pDeltaTime;
	if (mPosition.x - (mSize.x / 2.f) < mBoundries.left)
		mPosition.x = mBoundries.left + (mSize.x / 2.f);
	if (mPosition.x + (mSize.x / 2.f) > mBoundries.width)
		mPosition.x = mBoundries.width - (mSize.x / 2.f);
	mView.setCenter(mPosition);
	mView.setSize(mSize);
}

void	Camera::SetPosition(const float &pX, const float &pY)
{
	SetPosition(sf::Vector2f(pX, pY));
}

void	Camera::SetPosition(const sf::Vector2f &pPosition)
{
	mPosition = pPosition;
}

void	Camera::SetView(const sf::View &pView)
{
	mView = pView;
	mPosition = pView.getCenter();
	mSize = pView.getSize();
}

void	Camera::SetBoundries(const sf::IntRect &pBoundries)
{
	mBoundries = pBoundries;
}
