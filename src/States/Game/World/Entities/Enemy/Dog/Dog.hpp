#pragma once
#include "../Enemy.hpp"

class Dog : public Enemy
{
private:
	void LoadAnimations();

public:
	Dog(/* args */);
	~Dog();

	void	Init(Yuna::Core::ResourceManager *pResourceManager) override;
	void	Update(Yuna::Core::EventHandler *pEventHandler, float mDeltaTime) override;
};


