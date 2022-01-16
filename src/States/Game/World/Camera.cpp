/*
 * File: Camera.cpp
 * Project: Extermination
 * File Created: Saturday, 15th January 2022 8:05:29 am
 * Author: Marek Fischer
 * -----
 * Last Modified: Sunday, 16th January 2022 8:59:45 am
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */
#include "Camera.hpp"
#include <math.h>

Camera::Camera(/* args */)
{
}

Camera::~Camera()
{
}


void	Camera::Update(const float &pDeltaTime)
{
	FollowTarget();
	mPosition.x += mVelocity.x * pDeltaTime;
	mPosition.y += mVelocity.y * pDeltaTime;
	if (mPosition.x - (mSize.x / 2.f) < mBoundries.left)
		mPosition.x = mBoundries.left + (mSize.x / 2.f);
	if (mPosition.x + (mSize.x / 2.f) > mBoundries.width)
		mPosition.x = mBoundries.width - (mSize.x / 2.f);
	mView.setCenter(mPosition);
	mView.setSize(mSize);
}

void	Camera::FollowTarget()
{
	float dx = (mPosition.x - mTargetPosition.x);
	float dy = (mPosition.y - mTargetPosition.y);
	float dist = std::sqrt((dx * dx) + (dy * dy));
	if (dist > mActiveAreaRadius)
	{
		mLinearVelocity += (mSpeed * (std::max((dist - mActiveAreaRadius) / 200.f, 1.f)));
		mVelocity.x = (-dx / dist) * mLinearVelocity;
		mVelocity.y = (-dy / dist) * mLinearVelocity;
		mLinearVelocity *= 0.98;
	}
	else
	{
		mLinearVelocity *= 0.90;
		mVelocity.x *= 0.9;
		mVelocity.y *= 0.9;
	}
}

void	Camera::SetPosition(const float &pX, const float &pY)
{
	SetPosition(sf::Vector2f(pX, pY));
}

void	Camera::SetPosition(const sf::Vector2f &pPosition)
{
	mPosition = pPosition;
}

void	Camera::SetTargetPosition(const sf::Vector2f &pTargetPosition)
{
	mTargetPosition = pTargetPosition;
}

void	Camera::SetActiveArea(float pRadius)
{
	mActiveAreaRadius = pRadius;
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
