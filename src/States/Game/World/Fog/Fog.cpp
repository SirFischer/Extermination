#include "Fog.hpp"

Fog::Fog(/* args */)
{
}

Fog::~Fog()
{
}

void Fog::Render(Yuna::Core::Window *tWindow)
{
    (void)tWindow;
}

void Fog::Update(double tDeltatime)
{
    for (auto &sprite : mFogSprites) {
        sprite.move(mFogSpeed * tDeltatime, 0);

    }
}