/*
 * File: Menu.cpp
 * Project: Extermination
 * File Created: Saturday, 24th September 2022 8:31:53 am
 * Author: Marek Fischer
 * -----
 * Last Modified: Saturday, 24th September 2022 8:37:39 am
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */
#include "Menu.hpp"

Menu::Menu(Yuna::Core::Window* tWindow)
:State(tWindow)
{

}

Menu::~Menu()
{
}

void	Menu::Init()
{
	mActive = true;
}

void	Menu::Update()
{

}

void	Menu::HandleEvents()
{

}

void	Menu::Render()
{
	mWindow->Clear();
	mf::GUI::Render();
	mWindow->Render();
}