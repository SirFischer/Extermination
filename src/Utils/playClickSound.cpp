#include "Utils/Utils.hpp"
#include <SFML/Audio.hpp>

namespace Utils {

void playClickSound(sf::Sound *pClickSound)
{
	pClickSound->setPlayingOffset(sf::seconds(0.2f));
	pClickSound->play();
}

}