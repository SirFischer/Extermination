#pragma once
#include "Yuna.hpp"

/**
 * This class will generate continuous fog using perling noise. It will use a separate thread to generate the fog.
*/
class Fog
{
private:
    /* data */
    sf::Texture mFogTextures[3];
    sf::Sprite mFogSprites[3];

    int mFogSpeed = 1;

    void GenerateFog();

public:
    Fog(/* args */);
    ~Fog();

    void Render(Yuna::Core::Window *tWindow);
    void Update(double tDeltatime);
};

