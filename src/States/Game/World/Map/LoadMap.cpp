/*
 * File: LoadMap.cpp
 * Project: Extermination
 * File Created: Saturday, 23rd October 2021 10:20:43 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Sunday, 24th October 2021 8:27:52 am
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */
#include "Map.hpp"

void	Map::Load(std::string pPath)
{
	std::fstream		mapFile;
	std::string			line;
	uint8_t				format;

	mapFile.open(pPath, std::ios::in);
	while (std::getline(mapFile, line))
	{
		std::stringstream ss(line);
		std::string token;
		std::getline(ss, token, '=');
		if (token.find("format") != std::string::npos)
		{
			std::getline(ss, token, '=');
			format = (uint8_t)std::stoi(token);
		} else if (token.find("signature") != std::string::npos)
		{
			std::getline(ss, token, '=');
			std::stringstream ss2(token);
			std::getline(ss2, token, ' ');
			uint32_t	signature = (uint32_t)std::stoi(token);
			std::getline(ss2, token, ' ');
			size_t pos = token.find("defaultResources");
			if (pos != std::string::npos)
				token.replace(pos, 16, "textures");
			mSignatures[signature] = *mResourceManager->LoadTexture(token);
		}else if (token.find("map") != std::string::npos)
		{
			std::list<sBlock>	list;
			if (format == 0)
				ReadBasicFormat(mapFile, list);
			else
				ReadAdvancedFormat(mapFile, list);
			list.sort([](sBlock &e1, sBlock &e2){
				return (e1.mSignature < e2.mSignature);
			});
			for (auto &i : list)
				mBlocks.push_back(i);
			break;
		}
	}
	mapFile.close();
}

void		Map::ReadBasicFormat(std::fstream &pFile, std::list<sBlock> &pList)
{
	std::string			line;

	int y = 0;
	while (std::getline(pFile, line))
	{
		y++;
		int x = 0;
		for (auto &i : line)
		{
			x++;
			if (i == ' ')
				continue;
			pList.push_back((sBlock){.mPos = sf::Vector2f(x, y), .mSignature = (uint32_t)i});
		}
	}
}

void		Map::ReadAdvancedFormat(std::fstream &pFile, std::list<sBlock> &pList)
{
	std::string						line;

	while (std::getline(pFile, line))
	{
		std::stringstream ss(line);
		std::string token;
		std::getline(ss, token, '=');
		if (token.find("elem") != std::string::npos)
		{
			std::getline(ss, token, '=');
			pList.push_back((sBlock){.mPos = sf::Vector2f(0, 0), .mSignature = (uint32_t)std::stoi(token)});
		} else if (token.find("pos") != std::string::npos)
		{
			std::getline(ss, token, '=');
			std::stringstream ss2(token);
			std::getline(ss2, token, ' ');
			float tmp = std::stof(token);
			std::getline(ss2, token, ' ');
			pList.back().mPos = sf::Vector2f(tmp, std::stof(token));
		}
	}
}