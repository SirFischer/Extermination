#pragma once
#include <map>
#include "Animation.hpp"

enum class				eAnimationAction
{
	IDLE,
	WALK,
	FALL
};

class AnimationManager
{
private:
	typedef std::map<eAnimationAction, Animation>	AnimationMap;
	AnimationMap		mAnimationsLeft;
	AnimationMap		mAnimationsRight;
	eAnimationAction	mCurrentAnimation = eAnimationAction::IDLE;

public:
	AnimationManager(/* args */);
	~AnimationManager();

	void		AddAnimation(eAnimationAction pAction, Animation pAnimationRight);
	void		AddAnimation(eAnimationAction pAction, Animation pAnimationRight, Animation pAnimationLeft);
	void		Update();
	sf::IntRect	GetCurrentFrame(bool pFacingLeft);
	void 		SetCurrentAnimation(eAnimationAction pAction);
};

