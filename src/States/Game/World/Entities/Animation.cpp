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

Animation::Animation(/* args */)
{
}

Animation::~Animation()
{
}

void	Animation::Update()
{
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