#pragma once
#include "Yuna.hpp"

class Splash : public Yuna::Core::State
{
private:

	void	Update();
	void	HandleEvents();
	void	Render();
public:
	void	Init();

	Splash(Yuna::Core::Window* tWindow);
	~Splash();
};

