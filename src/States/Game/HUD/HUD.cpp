/*
 * File: HUD.cpp
 * Project: Extermination
 * File Created: Monday, 28th February 2022 3:55:00 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Sunday, 26th February 2023 3:20:48 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */

#include "HUD.hpp"

#include "Yuna.hpp"

HUD::HUD(/* args */)
{
}

HUD::~HUD()
{
}

void	HUD::InitNextWaveButton(const std::function<void()> &pClickAction)
{
	mNextWaveButton = mf::Button::Create();
	mNextWaveButton->SetPosition(0, 0);
	mNextWaveButton->SetSize(100, 100);
	mNextWaveButton->SetBackground(sf::Color::Red);
	mNextWaveButton->AddEventListener(mf::eEvent::LEFT_CLICK, pClickAction);
	
}

void	HUD::HandleNextWaveButton(sf::Event &pEvent)
{
	mNextWaveButton->HandleEvent(pEvent);
}

void	HUD::RenderNextWaveButton(Yuna::Core::Window *pWindow)
{
	mNextWaveButton->Render(pWindow->GetRenderWindow());
}

