/*
 * File: InitGraphicsMenu.cpp
 * Project: Extermination
 * File Created: Sunday, 7th November 2021 10:43:08 am
 * Author: Marek Fischer
 * -----
 * Last Modified: Saturday, 1st January 2022 2:22:39 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */

#include "Options.hpp"
#include "Utils/Utils.hpp"

void	Options::InitGraphicsOptions()
{
	// Graphics options
	mGraphicsOptionsList = mf::List::Create()
	->SetBackgroundColor(sf::Color(0, 0, 0, 0))
	->SetSize(95, 95)->SetSizePercentage(true, true)
	->SetPosition(2.5, 2.5)->SetPositionPercentage(true, true);
	mOptionsContainer->AddWidget(mGraphicsOptionsList);
	mGraphicsOptionsList->SetDisabled(true);

	// Fullscreen
	mf::Button *fullscreen = mf::Button::Create();
	fullscreen->SetTextFont("assets/fonts/AlfaSlabOne-Regular.ttf")
	->SetText("Fullscreen: Off")
	->SetBackground(*mResourceManager.LoadTexture("assets/textures/button.png"))
	->SetSize(275, 50)
	->SetTextColor(sf::Color::White)
	->SetTextPosition(10, 5)
	->SetClickEvent([this, fullscreen, clickSound = &mClickSound]() {
		this->mWindow->SetFullscreen(!this->mWindow->IsFullscreen());
		Utils::playClickSound(clickSound);
		fullscreen->SetText(std::string("Fullscreen: ") + (this->mWindow->IsFullscreen() ? "On" : "Off"));
	});
	Utils::initBtnHover(fullscreen, &mResourceManager, &mHoverSound);
	mGraphicsOptionsList->AddWidget(fullscreen);


	// VSync
	mf::Button *vsync = mf::Button::Create();
	vsync->SetTextFont("assets/fonts/AlfaSlabOne-Regular.ttf")
	->SetText(std::string("VSync: ") + (this->mWindow->IsVSync() ? "On" : "Off"))
	->SetTextColor(sf::Color::White)
	->SetBackground(*mResourceManager.LoadTexture("assets/textures/button.png"))
	->SetSize(275, 50)
	->SetTextPosition(10, 5)
	->SetClickEvent([this, vsync, clickSound = &mClickSound]() {
		this->mWindow->SetVSync(!this->mWindow->IsVSync());
		Utils::playClickSound(clickSound);
		vsync->SetText(std::string("VSync: ") + (this->mWindow->IsVSync() ? "On" : "Off"));
	});
	Utils::initBtnHover(vsync, &mResourceManager, &mHoverSound);
	mGraphicsOptionsList->AddWidget(vsync);

	// FPS
	mf::Slider *fps = mf::Slider::Create();
	fps->SetSize(275, 40)
	->SetBackgroundColor(sf::Color(100, 100, 100, 255))
	->SetDirection(mf::eDirection::HORIZONTAL)
	->SetValue(60);
	mGraphicsOptionsList->AddWidget(fps);


}
