/*
 * File: Animation.hpp
 * Project: Extermination
 * File Created: Sunday, 9th January 2022 11:18:19 am
 * Author: Marek Fischer
 * -----
 * Last Modified: Sunday, 9th January 2022 11:53:47 am
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

struct AnimationFrame
{
	sf::IntRect				mRect;
	sf::Time				mDuration;
	std::function<void()>	mAction;
};

class Animation
{

private:
	std::vector<AnimationFrame>	mFrames;
	sf::Clock					mClock;
	size_t						mCurrentFrame = 0;

public:
	Animation(/* args */);
	~Animation();

	void		AddFrame(AnimationFrame pFrame) {mFrames.push_back(pFrame);};
	void		Update();
	sf::IntRect	GetCurrentFrame();

	Animation	InvertXAxis();
};
