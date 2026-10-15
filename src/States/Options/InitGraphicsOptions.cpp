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
	mGraphicsOptionsList = mf::List::Create();
	mGraphicsOptionsList->GetBackground()->SetBackground(sf::Color(0, 0, 0, 0));
	mGraphicsOptionsList->SetSize(95, 95);
	mGraphicsOptionsList->SetSizePercentage(true, true);
	mGraphicsOptionsList->SetItemSpacing(10);
	mGraphicsOptionsList->SetPosition(2.5, 2.5);
	mGraphicsOptionsList->SetPositionPercentage(true, true);
	mOptionsContainer->AddWidget(mGraphicsOptionsList);
	mGraphicsOptionsList->SetDisabled(true);

	// Fullscreen
	auto fullscreen = mf::Button::Create();
	fullscreen->GetText()->LoadFont("assets/fonts/AlfaSlabOne-Regular.ttf");
	fullscreen->GetText()->SetString("Fullscreen: Off");
	fullscreen->GetBackground()->SetBackground(*mResourceManager.LoadTexture("assets/textures/button.png"));
	fullscreen->SetSize(275, 50);
	fullscreen->GetText()->SetColor(sf::Color::White);
	fullscreen->GetText()->SetPos(sf::Vector2f(10, 5));
	fullscreen->SetClickEvent([this, fullscreen, clickSound = &mClickSound]() {
		this->mWindow->SetFullscreen(!this->mWindow->IsFullscreen());
		Utils::playClickSound(clickSound);
		fullscreen->GetText()->SetString(std::string("Fullscreen: ") + (this->mWindow->IsFullscreen() ? "On" : "Off"));
	});
	Utils::initBtnHover(fullscreen, &mResourceManager, &mHoverSound);
	mGraphicsOptionsList->AddWidget(fullscreen);


	// VSync
	auto vsync = mf::Button::Create();
	vsync->GetText()->LoadFont("assets/fonts/AlfaSlabOne-Regular.ttf");
	vsync->GetText()->SetString(std::string("VSync: ") + (this->mWindow->IsVSync() ? "On" : "Off"));
	vsync->GetText()->SetColor(sf::Color::White);
	vsync->GetBackground()->SetBackground(*mResourceManager.LoadTexture("assets/textures/button.png"));
	vsync->SetSize(275, 50);
	vsync->GetText()->SetPos(sf::Vector2f(10, 5));
	vsync->SetClickEvent([this, vsync, clickSound = &mClickSound]() {
		this->mWindow->SetVSync(!this->mWindow->IsVSync());
		Utils::playClickSound(clickSound);
		vsync->GetText()->SetString(std::string("VSync: ") + (this->mWindow->IsVSync() ? "On" : "Off"));
	});
	Utils::initBtnHover(vsync, &mResourceManager, &mHoverSound);
	mGraphicsOptionsList->AddWidget(vsync);

	// Resolution options
	auto resolutionContainer = mf::Container::Create();
	resolutionContainer->GetBackground()->SetBackground(sf::Color(0, 0, 0, 0));
	resolutionContainer->SetSize(100, 240);
	resolutionContainer->SetSizePercentage(true, false);
	
	auto resolutionHeader = mf::Text::Create();
	resolutionHeader->GetText()->LoadFont("assets/fonts/AlfaSlabOne-Regular.ttf");
	resolutionHeader->GetText()->SetString("Resolution:");
	resolutionHeader->GetText()->SetSize(20);
	resolutionHeader->GetText()->SetColor(sf::Color::White);
	resolutionHeader->GetBackground()->SetBackground(sf::Color(0, 0, 0, 0));
	resolutionHeader->SetClickThrough(true);
	resolutionHeader->SetPosition(10, 5);
	resolutionContainer->AddWidget(resolutionHeader);
	
	// Resolution preset buttons container
	auto presetButtonsContainer = mf::Container::Create();
	presetButtonsContainer->GetBackground()->SetBackground(sf::Color(0, 0, 0, 0));
	presetButtonsContainer->SetPosition(0, 30);
	presetButtonsContainer->SetSize(275, 110);
	resolutionContainer->AddWidget(presetButtonsContainer);
	
	// Preset button for 1280x720
	auto res720p = mf::Button::Create();
	res720p->GetText()->LoadFont("assets/fonts/AlfaSlabOne-Regular.ttf");
	res720p->GetText()->SetString("1280 x 720");
	res720p->GetBackground()->SetBackground(*mResourceManager.LoadTexture("assets/textures/button.png"));
	res720p->SetSize(260, 50);
	res720p->SetPosition(0, 0);
	res720p->GetText()->SetColor(sf::Color::White);
	res720p->GetText()->SetPos(sf::Vector2f(10, 5));
	res720p->SetClickEvent([this, clickSound = &mClickSound]() {
		this->mWindow->SetSize(sf::Vector2i(1280, 720));
		this->mWindow->Create();
		this->mWindow->ResetView(true);
		Utils::playClickSound(clickSound);
	});
	Utils::initBtnHover(res720p, &mResourceManager, &mHoverSound);
	presetButtonsContainer->AddWidget(res720p);
	
	// Preset button for 1600x900
	auto res900p = mf::Button::Create();
	res900p->GetText()->LoadFont("assets/fonts/AlfaSlabOne-Regular.ttf");
	res900p->GetText()->SetString("1600 x 900");
	res900p->GetBackground()->SetBackground(*mResourceManager.LoadTexture("assets/textures/button.png"));
	res900p->SetSize(260, 50);
	res900p->SetPosition(0, 55);
	res900p->GetText()->SetColor(sf::Color::White);
	res900p->GetText()->SetPos(sf::Vector2f(10, 5));
	res900p->SetClickEvent([this, clickSound = &mClickSound]() {
		this->mWindow->SetSize(sf::Vector2i(1600, 900));
		this->mWindow->Create();
		this->mWindow->ResetView(true);
		Utils::playClickSound(clickSound);
	});
	Utils::initBtnHover(res900p, &mResourceManager, &mHoverSound);
	presetButtonsContainer->AddWidget(res900p);
	
	// Preset button for 1920x1080
	auto res1080p = mf::Button::Create();
	res1080p->GetText()->LoadFont("assets/fonts/AlfaSlabOne-Regular.ttf");
	res1080p->GetText()->SetString("1920 x 1080");
	res1080p->GetBackground()->SetBackground(*mResourceManager.LoadTexture("assets/textures/button.png"));
	res1080p->SetSize(260, 50);
	res1080p->SetPosition(0, 110);
	res1080p->GetText()->SetColor(sf::Color::White);
	res1080p->GetText()->SetPos(sf::Vector2f(10, 5));
	res1080p->SetClickEvent([this, clickSound = &mClickSound]() {
		this->mWindow->SetSize(sf::Vector2i(1920, 1080));
		this->mWindow->Create();
		this->mWindow->ResetView(true);
		Utils::playClickSound(clickSound);
	});
	Utils::initBtnHover(res1080p, &mResourceManager, &mHoverSound);
	presetButtonsContainer->AddWidget(res1080p);
	
	// Preset button for 2560x1440
	auto res1440p = mf::Button::Create();
	res1440p->GetText()->LoadFont("assets/fonts/AlfaSlabOne-Regular.ttf");
	res1440p->GetText()->SetString("2560 x 1440");
	res1440p->GetBackground()->SetBackground(*mResourceManager.LoadTexture("assets/textures/button.png"));
	res1440p->SetSize(260, 50);
	res1440p->SetPosition(0, 165);
	res1440p->GetText()->SetColor(sf::Color::White);
	res1440p->GetText()->SetPos(sf::Vector2f(10, 5));
	res1440p->SetClickEvent([this, clickSound = &mClickSound]() {
		this->mWindow->SetSize(sf::Vector2i(2560, 1440));
		this->mWindow->Create();
		this->mWindow->ResetView(true);
		Utils::playClickSound(clickSound);
	});
	Utils::initBtnHover(res1440p, &mResourceManager, &mHoverSound);
	presetButtonsContainer->AddWidget(res1440p);
	
	mGraphicsOptionsList->AddWidget(resolutionContainer);

	// FPS
	auto fpsContainer = mf::Container::Create();
	fpsContainer->GetBackground()->SetBackground(sf::Color(0, 0, 0, 0));
	auto fps = mf::Slider::Create();
	fps->SetSize(275, 40);
	fps->GetBackground()->SetBackground(sf::Color(100, 100, 100, 255));
	fps->SetDirection(mf::eDirection::HORIZONTAL);
	fps->SetValue(60);
	fps->GetButton()->GetBackground()->SetBackground(sf::Color(255, 255, 255, 255));
	fpsContainer->AddWidget(fps);

	auto fpsText = mf::Text::Create();
	fpsText->GetText()->LoadFont("assets/fonts/AlfaSlabOne-Regular.ttf");
	fpsText->GetText()->SetString("FPS: " + (mWindow->GetMaxFPS() ? std::to_string(mWindow->GetMaxFPS()) : "unlimited"));
	fpsText->GetText()->SetSize(20);
	fpsText->GetText()->SetColor(sf::Color::White);
	fpsText->GetBackground()->SetBackground(sf::Color(0, 0, 0, 0));
	fpsText->SetClickThrough(true);
	fpsText->SetPosition(10, 5);
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

		fpsText->GetText()->SetString(std::string("FPS: ") + newFps);
		Utils::playClickSound(clickSound);
	});

	mGraphicsOptionsList->AddWidget(fpsContainer);


}
