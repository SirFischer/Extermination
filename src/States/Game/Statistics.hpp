/*
 * File: Statistics.hpp
 * Project: Extermination
 * File Created: Tuesday, 11th January 2022 7:14:59 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Monday, 11th April 2022 12:47:31 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */
#pragma once
#include <SFML/Graphics.hpp>
#include <Yuna.hpp>
#include <mfGUI.hpp>

class Statistics
{
private:
	Yuna::Core::ResourceManager *mResourceManager;

	uint32_t		mFPS = 0;
	float			mFrameTime = 0;
	float			mMinFrameTime = 999;
	float			mMaxFrameTime = 0;
	sf::Vector2f	mPosition = sf::Vector2f(0, 0);
	sf::Vector2f	mVelocity = sf::Vector2f(0, 0);

	sf::Text		mFPSText;
	sf::Text		mPlayerTransformText;

	void			InitFPSText();
	void			InitPlayerTransformText();

public:
	Statistics(Yuna::Core::ResourceManager *pResourceManager);
	~Statistics();

	void			Update();
	void			Render(Yuna::Core::Window *pWindow);

	float			GetFPS(){return (mFPS);}
	float			GetFrameTime(){return (mFrameTime);}
	sf::Vector2f	GetPosition(){return (mPosition);}
	sf::Vector2f	GetVelocity(){return (mVelocity);}

	void			SetFPS(uint32_t pFPS){mFPS = pFPS;}
	void			SetFrameTime(float pFrameTime);
	void			SetPosition(sf::Vector2f pPosition){mPosition = pPosition;}
	void			SetVelocity(sf::Vector2f pVelocity){mVelocity = pVelocity;}
};
