#pragma once
#include "../Enemy.hpp"

class Dog : public Enemy
{
private:
	/* data */
public:
	Dog(/* args */);
	~Dog();

	void	Init(Yuna::Core::ResourceManager *pResourceManager) override;
};


