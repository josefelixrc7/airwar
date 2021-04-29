#include "aircraft.h"


Aircraft::Aircraft(Textures::ID type, TextureHolder& textures):
    type_(type),
    sprite_(textures.Get_(type_))
{
}

Aircraft::Aircraft(Textures::ID type, sf::Texture& texture):
    type_(type),
    sprite_(texture)
{
}

Aircraft::~Aircraft()
{

}

void Aircraft::DrawCurrent_(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite_, states);
}
