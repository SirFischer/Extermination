#include "Menu.hpp"
#include "Utils/Utils.hpp"

void	Menu::InitMenuItems()
{
	mf::GUI::ClearWidgets();

	auto btnPlay = mf::Button::Create();
	btnPlay->SetClickEvent([this, clickSound = &mClickSound](){
		this->mActive = false;
		this->mStateAction = Yuna::Core::eStateControls::NEXT_STATE;
		this->mNextState = (uint8_t)eStates::GAME;
		Utils::playClickSound(clickSound);
	});
	btnPlay->GetText()->LoadFont(*mResourceManager.LoadFont("assets/fonts/AlfaSlabOne-Regular.ttf").get());
	btnPlay->GetText()->SetString("Play");
	btnPlay->GetText()->SetColor(sf::Color::White);
	btnPlay->GetText()->SetPos(sf::Vector2f(10, 5));
	btnPlay->GetBackground()->SetBackground(*mResourceManager.LoadTexture("assets/textures/button.png"));
	btnPlay->SetPosition(3, 200);
	btnPlay->SetPositionPercentage(true, false);
	Utils::initBtnHover(btnPlay, &mResourceManager, &mHoverSound);

	auto btnOptions = mf::Button::Create();
	btnOptions->SetClickEvent([this, clickSound = &mClickSound](){
		this->mActive = false;
		this->mStateAction = Yuna::Core::eStateControls::NEXT_STATE;
		this->mNextState = (uint8_t)eStates::OPTIONS;
		Utils::playClickSound(clickSound);
	});
	btnOptions->GetText()->LoadFont(*mResourceManager.LoadFont("assets/fonts/AlfaSlabOne-Regular.ttf").get());
	btnOptions->GetText()->SetString("Options");
	btnOptions->GetText()->SetColor(sf::Color::White);
	btnOptions->GetText()->SetPos(sf::Vector2f(10, 5));
	btnOptions->GetBackground()->SetBackground(*mResourceManager.LoadTexture("assets/textures/button.png"));
	btnOptions->SetSize(160, 50);
	btnOptions->SetPosition(3, 300);
	btnOptions->SetPositionPercentage(true, false);
	Utils::initBtnHover(btnOptions, &mResourceManager, &mHoverSound);

	auto list = mf::List::Create();
	list->SetPosition(3, 10);
	list->SetPositionPercentage(true, true);
	list->SetSize(30, 80);
	list->SetSizePercentage(true, true);
	list->GetBackground()->SetBackground(sf::Color(0, 0, 0, 0));
	list->SetItemSpacing(50);
	list->AddWidget(btnPlay);
	list->AddWidget(btnOptions);
	mf::GUI::AddWidget(list);

	auto btn = mf::Button::Create();
	btn->SetClickEvent([this, clickSound = &mClickSound](){
		this->mActive = false;
		this->mStateAction = Yuna::Core::eStateControls::EXIT;
		Utils::playClickSound(clickSound);
	});
	btn->GetText()->LoadFont(*mResourceManager.LoadFont("assets/fonts/AlfaSlabOne-Regular.ttf").get());
	btn->GetText()->SetString("Exit");
	btn->GetText()->SetColor(sf::Color::White);
	btn->GetText()->SetPos(sf::Vector2f(10, 5));
	btn->GetBackground()->SetBackground(*mResourceManager.LoadTexture("assets/textures/button.png"));
	btn->SetPosition(1, 93);
	btn->SetPositionPercentage(true, true);
	Utils::initBtnHover(btn, &mResourceManager, &mHoverSound);
	mf::GUI::AddWidget(btn);
}

void	Menu::InitMenuControls()
{
	mEventHandler.BindKey(sf::Keyboard::Tab, (uint32_t)eAction::CONSOLE_TOGGLE);
	mEventHandler.BindKey(sf::Keyboard::Enter, (uint32_t)eAction::CONSOLE_CONFIRM);
	mEventHandler.BindKey(sf::Keyboard::Up, (uint32_t)eAction::CONSOLE_NEXT_IN_HISTORY);
	mEventHandler.BindKey(sf::Keyboard::Down, (uint32_t)eAction::CONSOLE_PREVIOUS_IN_HISTORY);
}
