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
	->SetItemSpacing(10)
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

	// Resolution options
	mf::Container *resolutionContainer = mf::Container::Create();
	resolutionContainer->SetBackground(sf::Color(0, 0, 0, 0));
	resolutionContainer->SetSize(100, 240);
	resolutionContainer->SetSizePercentage(true, false);
	
	mf::Text *resolutionHeader = mf::Text::Create();
	resolutionHeader->SetTextFont("assets/fonts/AlfaSlabOne-Regular.ttf")
	->SetText("Resolution:")
	->SetCharacterSize(20)
	->SetTextColor(sf::Color::White)
	->SetBackgroundColor(sf::Color(0, 0, 0, 0))
	->SetClickThrough(true)
	->SetPosition(10, 5);
	resolutionContainer->AddWidget(resolutionHeader);
	
	// Resolution preset buttons container
	mf::Container *presetButtonsContainer = mf::Container::Create();
	presetButtonsContainer->SetBackground(sf::Color(0, 0, 0, 0))
	->SetPosition(0, 30)
	->SetSize(275, 110);
	resolutionContainer->AddWidget(presetButtonsContainer);
	
	// Preset button for 1280x720
	mf::Button *res720p = mf::Button::Create();
	res720p->SetTextFont("assets/fonts/AlfaSlabOne-Regular.ttf")
	->SetText("1280 x 720")
	->SetBackground(*mResourceManager.LoadTexture("assets/textures/button.png"))
	->SetSize(260, 50)
	->SetPosition(0, 0)
	->SetTextColor(sf::Color::White)
	->SetTextPosition(10, 5)
	->SetClickEvent([this, clickSound = &mClickSound]() {
		this->mWindow->SetSize(sf::Vector2i(1280, 720));
		this->mWindow->Create();
		this->mWindow->ResetView(true);
		Utils::playClickSound(clickSound);
	});
	Utils::initBtnHover(res720p, &mResourceManager, &mHoverSound);
	presetButtonsContainer->AddWidget(res720p);
	
	// Preset button for 1600x900
	mf::Button *res900p = mf::Button::Create();
	res900p->SetTextFont("assets/fonts/AlfaSlabOne-Regular.ttf")
	->SetText("1600 x 900")
	->SetBackground(*mResourceManager.LoadTexture("assets/textures/button.png"))
	->SetSize(260, 50)
	->SetPosition(0, 55)
	->SetTextColor(sf::Color::White)
	->SetTextPosition(10, 5)
	->SetClickEvent([this, clickSound = &mClickSound]() {
		this->mWindow->SetSize(sf::Vector2i(1600, 900));
		this->mWindow->Create();
		this->mWindow->ResetView(true);
		Utils::playClickSound(clickSound);
	});
	Utils::initBtnHover(res900p, &mResourceManager, &mHoverSound);
	presetButtonsContainer->AddWidget(res900p);
	
	// Preset button for 1920x1080
	mf::Button *res1080p = mf::Button::Create();
	res1080p->SetTextFont("assets/fonts/AlfaSlabOne-Regular.ttf")
	->SetText("1920 x 1080")
	->SetBackground(*mResourceManager.LoadTexture("assets/textures/button.png"))
	->SetSize(260, 50)
	->SetPosition(0, 110)
	->SetTextColor(sf::Color::White)
	->SetTextPosition(10, 5)
	->SetClickEvent([this, clickSound = &mClickSound]() {
		this->mWindow->SetSize(sf::Vector2i(1920, 1080));
		this->mWindow->Create();
		this->mWindow->ResetView(true);
		Utils::playClickSound(clickSound);
	});
	Utils::initBtnHover(res1080p, &mResourceManager, &mHoverSound);
	presetButtonsContainer->AddWidget(res1080p);
	
	// Preset button for 2560x1440
	mf::Button *res1440p = mf::Button::Create();
	res1440p->SetTextFont("assets/fonts/AlfaSlabOne-Regular.ttf")
	->SetText("2560 x 1440")
	->SetBackground(*mResourceManager.LoadTexture("assets/textures/button.png"))
	->SetSize(260, 50)
	->SetPosition(0, 165)
	->SetTextColor(sf::Color::White)
	->SetTextPosition(10, 5)
	->SetClickEvent([this, clickSound = &mClickSound]() {
		this->mWindow->SetSize(sf::Vector2i(2560, 1440));
		this->mWindow->Create();
		this->mWindow->ResetView(true);
		Utils::playClickSound(clickSound);
	});
	Utils::initBtnHover(res1440p, &mResourceManager, &mHoverSound);
	presetButtonsContainer->AddWidget(res1440p);
	
	mGraphicsOptionsList->AddWidget(resolutionContainer);

	// FPS
	mf::Container *fpsContainer = mf::Container::Create();
	fpsContainer->SetBackground(sf::Color(0, 0, 0, 0));
	mf::Slider *fps = mf::Slider::Create();
	fps->SetSize(275, 40)
	->SetBackgroundColor(sf::Color(100, 100, 100, 255))
	->SetDirection(mf::eDirection::HORIZONTAL)
	->SetValue(60);
	fps->GetButton()->SetBackground(sf::Color(255, 255, 255, 255));
	fpsContainer->AddWidget(fps);

	mf::Text *fpsText = mf::Text::Create();
	fpsText->SetTextFont("assets/fonts/AlfaSlabOne-Regular.ttf")
	->SetText("FPS: " + (mWindow->GetMaxFPS() ? std::to_string(mWindow->GetMaxFPS()) : "unlimited"))
	->SetCharacterSize(20)
	->SetTextColor(sf::Color::White)
	->SetBackgroundColor(sf::Color(0, 0, 0, 0))
	->SetClickThrough(true)
	->SetPosition(10, 5);
	fpsContainer->AddWidget(fpsText);

	fps->SetChangeEventListener([this, fps, fpsText, clickSound = &mClickSound]() {
		const int MAX_FPS = 300;
		const float value = fps->GetValue();
		std::string newFps = std::to_string((int)(value * MAX_FPS));

		if (value < 0.1f)
		{
			newFps = "30";
			this->mWindow->SetMaxFPS(30);
		}
		else if (value > 0.98f)
		{
			newFps = "unlimited";
			this->mWindow->SetMaxFPS(0);
		}
		else
		{
			newFps = std::to_string((int)(value * MAX_FPS));
			this->mWindow->SetMaxFPS((int)(value * MAX_FPS));
		}

		fpsText->SetText(std::string("FPS: ") + newFps);
		Utils::playClickSound(clickSound);
	});

	mGraphicsOptionsList->AddWidget(fpsContainer);


}
