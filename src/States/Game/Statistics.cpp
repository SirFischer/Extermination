/*
 * File: Statistics.cpp
 * Project: Extermination
 * File Created: Tuesday, 11th January 2022 7:14:37 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Friday, 14th January 2022 6:47:02 am
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */
#include "Statistics.hpp"

Statistics::Statistics(Yuna::Core::ResourceManager *pResourceManager)
{
	mResourceManager = pResourceManager;
	
	InitFPSText();
	InitPlayerTransformText();
	
}

Statistics::~Statistics(){

}

void	Statistics::InitFPSText()
{
	mFPSText.setFont(*(mResourceManager->LoadFont("assets/fonts/FiraCode-VariableFont_wght.ttf")));
	mFPSText.setFillColor(sf::Color::Black);
	mFPSText.setCharacterSize(15);
}

void	Statistics::InitPlayerTransformText()
{
	mPlayerTransformText.setFont(*(mResourceManager->LoadFont("assets/fonts/FiraCode-VariableFont_wght.ttf")));
	mPlayerTransformText.setFillColor(sf::Color::Black);
	mPlayerTransformText.setCharacterSize(15);
	mPlayerTransformText.setPosition(0, mPlayerTransformText.getCharacterSize());
}

void	Statistics::Update()
{
	mFPSText.setString("avg. fps: " + std::to_string(mFPS) +
	"  fps: " + std::to_string(1.0 / mFrameTime) +
	"  max frame time: " + std::to_string(mMaxFrameTime) +
	"  min fps: " + std::to_string(1.0 / mMaxFrameTime) +
	"  min frame time: " + std::to_string(mMinFrameTime) +
	"  max fps: " + std::to_string(1.0 / mMinFrameTime));
	mPlayerTransformText.setString("player position X: " + std::to_string(mPosition.x) +
	" Y: " + std::to_string(mPosition.y) +
	"  velocity X: " + std::to_string(mVelocity.x) +
	" Y: " + std::to_string(mVelocity.y));
}

void	Statistics::Render(Yuna::Core::Window *pWindow)
{
	pWindow->Draw(mFPSText);
	pWindow->Draw(mPlayerTransformText);
}

void	Statistics::SetFrameTime(float pFrameTime)
{
	if (mMinFrameTime > pFrameTime)
		mMinFrameTime = pFrameTime;
	if (mMaxFrameTime < pFrameTime)
		mMaxFrameTime = pFrameTime;
	mFrameTime = pFrameTime;
}

