#include "AnimationManager.hpp"
#include <iostream>

AnimationManager::AnimationManager(/* args */)
{
}

AnimationManager::~AnimationManager()
{
}


void	AnimationManager::AddAnimation(eAnimationAction pAction, Animation pAnimationRight)
{
	AddAnimation(pAction, pAnimationRight, pAnimationRight.InvertXAxis());
}


void	AnimationManager::AddAnimation(eAnimationAction pAction, Animation pAnimationRight, Animation pAnimationLeft)
{
	mAnimationsLeft[pAction] = pAnimationLeft;
	mAnimationsRight[pAction] = pAnimationRight;
}

void	AnimationManager::Update()
{
	if (mAnimationsLeft.find(mCurrentAnimation) == mAnimationsLeft.end() || mAnimationsRight.find(mCurrentAnimation) == mAnimationsRight.end())
		return ;
	mAnimationsLeft[mCurrentAnimation].Update();
	mAnimationsRight[mCurrentAnimation].Update();
}

sf::IntRect	AnimationManager::GetCurrentFrame(bool pFacingLeft)
{
	if (mAnimationsLeft.find(mCurrentAnimation) == mAnimationsLeft.end() || mAnimationsRight.find(mCurrentAnimation) == mAnimationsRight.end())
		return (sf::IntRect(-1, -1, -1, -1));
	if (pFacingLeft)
		return (mAnimationsLeft[mCurrentAnimation].GetCurrentFrame());
	return (mAnimationsRight[mCurrentAnimation].GetCurrentFrame());
}

void 	AnimationManager::SetCurrentAnimation(eAnimationAction pAction)
{
	mCurrentAnimation = pAction;
}