#pragma once
#include "Yuna.hpp"

class Menu : public Yuna::Core::State
{
private:
	void	InitMenuItems();

	void	Update();
	void	HandleEvents();
	void	Render();
public:
	void	Init();

	Menu(Yuna::Core::Window* tWindow);
	~Menu();
};

