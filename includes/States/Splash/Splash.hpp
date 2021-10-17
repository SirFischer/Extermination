#pragma once
#include "Yuna.hpp"
#include "States.hpp"

class Splash : public Yuna::Core::State
{
private:

	void	Update();
	void	HandleEvents();
	void	Render();

	sf::Clock	mSplashClock;
	sf::Time	mSplashDuration = sf::seconds(3);

public:
	void	Init();

	Splash(Yuna::Core::Window* tWindow);
	~Splash();
};

