/*
 * File: Actions.cpp
 * Project: Extermination
 * File Created: Sunday, 2nd January 2022 8:04:13 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Sunday, 2nd January 2022 8:04:25 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */
#include "Actions.hpp"

std::map<uint32_t, std::string>	*GetActionNames()
{
	static std::map<uint32_t, std::string> names = std::map<uint32_t, std::string>();
	if (!names.size())
	{
		names[(uint32_t)eAction::JUMP] = "jump";
		names[(uint32_t)eAction::MOVE_RIGHT] = "move_right";
		names[(uint32_t)eAction::MOVE_LEFT] = "move_left";
	}
	return (&names);
}