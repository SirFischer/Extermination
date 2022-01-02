#include "Menu.hpp"
#include "Utils/Utils.hpp"

void	Menu::InitMenuItems()
{
	mf::GUI::ClearWidgets();

	auto btnPlay = mf::Button::Create()
	->SetClickEvent([this](){
		this->mActive = false;
		this->mStateAction = Yuna::Core::eStateControls::NEXT_STATE;
		this->mNextState = (uint8_t)eStates::GAME;
	})
	->SetTextFont(*mResourceManager.LoadFont("assets/fonts/AlfaSlabOne-Regular.ttf").get())
	->SetText("Play")
	->SetBackground(*mResourceManager.LoadTexture("assets/textures/button.png"))
	->SetTextPosition(15, 5)
	->SetPosition(3, 200)->SetPositionPercentage(true, false);
	Utils::initBtnHover(btnPlay, &mResourceManager);

	auto btnOptions = mf::Button::Create()
	->SetClickEvent([this](){
		this->mActive = false;
		this->mStateAction = Yuna::Core::eStateControls::NEXT_STATE;
		this->mNextState = (uint8_t)eStates::OPTIONS;
	})
	->SetTextFont(*mResourceManager.LoadFont("assets/fonts/AlfaSlabOne-Regular.ttf").get())
	->SetText("Options")
	->SetBackground(*mResourceManager.LoadTexture("assets/textures/button.png"))
	->SetTextPosition(15, 5)
	->SetSize(160, 50)
	->SetPosition(3, 300)->SetPositionPercentage(true, false);
	Utils::initBtnHover(btnOptions, &mResourceManager);


	mf::GUI::AddWidget(mf::List::Create()
	->SetPosition(3, 10)->SetPositionPercentage(true, true)
	->SetSize(30, 80)->SetSizePercentage(true, true)
	->SetBackgroundColor(sf::Color(0, 0, 0, 0))
	->SetItemSpacing(50)
	->AddWidget(btnPlay)
	->AddWidget(btnOptions));

	auto btn = mf::Button::Create()
	->SetClickEvent([this](){
		this->mActive = false;
		this->mStateAction = Yuna::Core::eStateControls::EXIT;
	})
	->SetTextFont(*mResourceManager.LoadFont("assets/fonts/AlfaSlabOne-Regular.ttf").get())
	->SetText("Exit")
	->SetBackground(*mResourceManager.LoadTexture("assets/textures/button.png"))
	->SetTextPosition(15, 5)
	->SetPosition(1, 93)->SetPositionPercentage(true, true);
	Utils::initBtnHover(btn, &mResourceManager);
	mf::GUI::AddWidget(btn);
}

void	Menu::InitMenuControls()
{
	mEventHandler.BindKey(sf::Keyboard::Tab, (uint32_t)eAction::CONSOLE_TOGGLE);
	mEventHandler.BindKey(sf::Keyboard::Enter, (uint32_t)eAction::CONSOLE_CONFIRM);
	mEventHandler.BindKey(sf::Keyboard::Up, (uint32_t)eAction::CONSOLE_NEXT_IN_HISTORY);
	mEventHandler.BindKey(sf::Keyboard::Down, (uint32_t)eAction::CONSOLE_PREVIOUS_IN_HISTORY);
}