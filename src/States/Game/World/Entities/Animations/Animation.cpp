/*
 * File: Animation.cpp
 * Project: Extermination
 * File Created: Sunday, 9th January 2022 11:18:11 am
 * Author: Marek Fischer
 * -----
 * Last Modified: Sunday, 9th January 2022 11:56:35 am
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */

#include "Animation.hpp"
#include <iostream>

Animation::Animation(/* args */)
{
}



Animation::~Animation()
{
}


void	Animation::Update()
{
	if (!mFrames.size())
		return ;
	if (mFrames[mCurrentFrame].mDuration < mClock.getElapsedTime())
	{
		mClock.restart();
		mCurrentFrame++;
		if (mCurrentFrame >= mFrames.size())
			mCurrentFrame = 0;
		if (mFrames[mCurrentFrame].mAction)
			mFrames[mCurrentFrame].mAction();
	}
}

sf::IntRect	Animation::GetCurrentFrame()
{
	if (!mFrames.size())
		return (sf::IntRect(-1, -1, -1, -1));
	return (mFrames[mCurrentFrame].mRect);	
}

Animation	Animation::InvertXAxis()
{
	Animation invertedAnimation(*this);
	for (size_t i = 0; i < invertedAnimation.mFrames.size(); i++)
	{
		invertedAnimation.mFrames[i].mRect.left = invertedAnimation.mFrames[i].mRect.left + invertedAnimation.mFrames[i].mRect.width;
		invertedAnimation.mFrames[i].mRect.width = -invertedAnimation.mFrames[i].mRect.width;
	}
	return (invertedAnimation);
}
