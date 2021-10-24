/*
 * File: Map.hpp
 * Project: Extermination
 * File Created: Saturday, 23rd October 2021 7:33:28 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Sunday, 24th October 2021 8:27:20 am
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */
#pragma once
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <list>
#include <SFML/Graphics.hpp>
#include "Yuna.hpp"

class Map
{
private:

	Yuna::Core::ResourceManager			*mResourceManager;

	struct sBlock
	{
		sf::Vector2f	mPos;
		uint32_t		mSignature;
	};
	
	std::vector<sBlock>					mBlocks;
	std::map<uint32_t, sf::Texture>		mSignatures;
	sf::Sprite							mSprite;

	void	ReadBasicFormat(std::fstream &pFile, std::list<sBlock> &pList);
	void	ReadAdvancedFormat(std::fstream &pFile, std::list<sBlock> &pList);
	
public:
	Map(Yuna::Core::ResourceManager *mResourceManager);
	~Map();

	void	Load(std::string pPath);

	void	Render(Yuna::Core::Window *pWindow);

};

