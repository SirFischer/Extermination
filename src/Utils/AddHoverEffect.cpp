/*
 * File: AddHoverEffect.cpp
 * Project: Extermination
 * File Created: Saturday, 1st January 2022 10:45:17 am
 * Author: Marek Fischer
 * -----
 * Last Modified: Saturday, 1st January 2022 2:19:56 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */
#include "Utils/Utils.hpp"

namespace Utils {

void initBtnHover(mf::Button *pBtn, Yuna::Core::ResourceManager *pResourceManager)
{
	pBtn->AddEventListener(mf::eEvent::ENTERED, [pBtn, pResourceManager](){
		pBtn->SetBackground(*(pResourceManager->LoadTexture("assets/textures/button-hover.png")));
		sf::Vector2f pos = pBtn->GetTextPosition();
		pBtn->SetTextPosition(sf::Vector2f(pos.x + 3, pos.y + 3));
	});
	pBtn->AddEventListener(mf::eEvent::EXITED, [pBtn, pResourceManager](){
		pBtn->SetBackground(*(pResourceManager->LoadTexture("assets/textures/button.png")));
		sf::Vector2f pos = pBtn->GetTextPosition();
		pBtn->SetTextPosition(sf::Vector2f(pos.x - 3, pos.y - 3));
	});
}

}
