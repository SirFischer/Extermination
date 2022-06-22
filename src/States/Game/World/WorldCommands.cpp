/*
 * File: WorldCommands.cpp
 * Project: Extermination
 * File Created: Sunday, 5th June 2022 8:19:12 am
 * Author: Marek Fischer
 * -----
 * Last Modified: Saturday, 18th June 2022 10:10:45 am
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */

#include "World.hpp"



void		World::InitConsoleCommands(Yuna::Core::ResourceManager *pResourceManager)
{
	Yuna::Core::Console::sCommand reGenMapCommand;
	reGenMapCommand.mHelpShort = "Regenerate map";
	reGenMapCommand.mHelpLong = "This command reapplies perlin noise to generate a brand new map.\nThe first param is the size of the map.\nThe second param is the amplitude\nThe third param is the number of octaves\n and the last param is the start number of segments";
	reGenMapCommand.mFunction = [map = &mMap](std::vector<std::string> tParams){
		(void)tParams;
		if (tParams.size() != 4)
			return (Yuna::Core::Console::eCommandStatus::BAD_ARGUMENTS);
		map->Generate(std::stoi(tParams.at(0)), std::stoi(tParams.at(1)), std::stoi(tParams.at(2)), std::stoi(tParams.at(3)), time(0));
		return (Yuna::Core::Console::eCommandStatus::SUCCESS);
	};
	Yuna::Core::Console::AddCommand(reGenMapCommand, "regenerate_map");

	Yuna::Core::Console::sCommand spawnEnemy;
	reGenMapCommand.mHelpShort = "Spawn new enemies";
	reGenMapCommand.mHelpLong = "Spawn x amount of enemies at (optional) x y coordinates.\nUsage:\nspawn_enemy [amount] [x] [y]\n";
	reGenMapCommand.mFunction = [entities = &mEntities, pResourceManager](std::vector<std::string> tParams){
		if (tParams.size() != 1 && tParams.size() != 3)
			return (Yuna::Core::Console::eCommandStatus::BAD_ARGUMENTS);
		Yuna::Core::Console::AddString("Yes sir! Spawning enemies!");
		for (int i = 0; i < std::stoi(tParams[0]); i++)
		{
			entities->push_back(std::make_shared<Enemy>());
			entities->back()->Init(pResourceManager);
			entities->back()->SetSize(38, 54);
			if (tParams.size() == 3)
			{
				entities->back()->SetPosition(sf::Vector2f(std::stoi(tParams[1]), std::stoi(tParams[2])));
			}
		}
		return (Yuna::Core::Console::eCommandStatus::SUCCESS);
	};
	Yuna::Core::Console::AddCommand(reGenMapCommand, "spawn_enemy");
}