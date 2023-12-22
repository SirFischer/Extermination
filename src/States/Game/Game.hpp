/*
 * File: Game.hpp
 * Project: Extermination
 * File Created: Friday, 22nd October 2021 2:25:47 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Thursday, 14th April 2022 7:56:40 am
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */
#pragma once
#include "Yuna.hpp"
#include "World/World.hpp"
#include "Statistics.hpp"
#include "../../Actions.hpp"
#include "Config.hpp"
#include "HUD/HUD.hpp"
#include "Console.hpp"

class Game : public Yuna::Core::State
{
private:
	World	mWorld;

	sf::Clock	mFPSClock;
	Statistics	mStatistics;
	GameConsole	mConsole;
	HUD			mHUD;

	//Post-effect
	std::shared_ptr<sf::Shader>  mPostEffectShader = nullptr;

	void	Update();
	void	HandleEvents();
	void	Render();
	
	//Init functions
	void	InitGameControls();
	void	InitGameCommands();

	//Misc
	void	UpdateFPS();

	//Commands
	void	InitExitCommand(bool *active, Yuna::Core::eStateControls *action);
	void	InitQtreeRenderingCommand();
	void	InitPathNodeRenderingCommand();


public:
	Game(Yuna::Core::Window* tWindow);
	~Game();

	void	Init();

};

