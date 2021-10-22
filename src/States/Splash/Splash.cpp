#include "Splash.hpp"

Splash::Splash(Yuna::Core::Window* tWindow)
:State(tWindow)
{
	
}

Splash::~Splash()
{
}

void	Splash::Init()
{
	mSplashClock.restart();
	mf::GUI::ClearWidgets();
	mf::GUI::AddWidget(
		mf::Image::Create("assets/images/logo_small_trans.png")
		->SetSizePercentage(false, false)->SetSize(400, 400)
		->SetPositionPercentage(true, true)->SetPosition(35, 25));
}

void	Splash::Update()
{
	if (mSplashClock.getElapsedTime() >= mSplashDuration)
	{
		mActive = false;
		mStateAction = Yuna::Core::eStateControls::REPLACE_STATE;
		mNextState = (uint8_t)eStates::MENU;
	}
}

void	Splash::HandleEvents()
{
	sf::Event event;
	while (mWindow->PollEvent(event))
	{
		mEventHandler.HandleEvent(event);
	}
}

void	Splash::Render()
{
	mWindow->Clear(sf::Color::White);
	mf::GUI::Render();
	mWindow->Render();
}