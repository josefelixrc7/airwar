#include "aircraft.h"


Aircraft::Aircraft(ResourcesID::Characters type, ResourceTexture& textures):
    type_(type),
    sprite_(textures.Get_(type_))
{
}

Aircraft::Aircraft(ResourcesID::Characters type, sf::Texture& texture):
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
