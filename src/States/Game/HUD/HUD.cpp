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

#include <cmath>

#include "Yuna.hpp"

HUD::HUD(Yuna::Core::ResourceManager *pResourceManager)
:mResourceManager(pResourceManager)
{
}

HUD::~HUD()
{
}

void	HUD::InitNextWaveButton(const std::function<void()> &pClickAction)
{
	mNextWaveButton = mf::Button::Create();
	mNextWaveButton->SetPosition(0, 0)
	->SetSize(230, 50)
	->SetTextFont(*mResourceManager->LoadFont("assets/fonts/AlfaSlabOne-Regular.ttf").get())
	->SetCharacterSize(20)
	->SetText("Next wave")
	->SetTextColor(sf::Color::White)
	->SetBackground(*mResourceManager->LoadTexture("assets/textures/button.png"))
	->SetPosition(50, 50)->SetPositionPercentage(true, true)
	->AddEventListener(mf::eEvent::LEFT_CLICK, pClickAction);
	
}

void	HUD::HandleNextWaveButton(sf::Event &pEvent)
{
	mNextWaveButton->HandleEvent(pEvent);
}

void	HUD::UpdateNextWaveButton(float pTimeLeft)
{
	if (!mNextWaveButton)
		return ;
	//Ceil so the label reads "30" the moment the countdown starts and only
	//shows "0" on the frame the wave actually launches.
	int	secondsLeft = (int)std::ceil(pTimeLeft);
	if (secondsLeft < 0)
		secondsLeft = 0;
	mNextWaveButton->SetText("Next wave (" + std::to_string(secondsLeft) + "s)");
	CenterNextWaveButtonText();
}

void	HUD::CenterNextWaveButtonText()
{
	//The label width changes with the number of digits, so recenter it every
	//frame to keep it inside the button instead of overflowing its bounds.
	sf::FloatRect	textBounds = mNextWaveButton->GetTextBounds();
	sf::Vector2f	buttonSize = mNextWaveButton->GetSize();
	mNextWaveButton->SetTextPosition(
		(buttonSize.x - textBounds.width) / 2.f - textBounds.left,
		(buttonSize.y - textBounds.height) / 2.f - textBounds.top);
}

void	HUD::RenderNextWaveButton(Yuna::Core::Window *pWindow)
{
	mNextWaveButton->Render(pWindow->GetRenderWindow());
}

