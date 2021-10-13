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
	
}

void	Splash::Update()
{

}

void	Splash::HandleEvents()
{
	mEventHandler.HandleEvent();
}

void	Splash::Render()
{
	mWindow->Clear();
	mf::GUI::Render();
	mWindow->Render();
}