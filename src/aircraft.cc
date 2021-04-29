#include "aircraft.h"


Aircraft::Aircraft(Aircraft::Type type, TextureHolder& textures):
    type_(type),
    sprite_(textures.Get_(ToTextureID_()))
{
}

Aircraft::Aircraft(Aircraft::Type type, sf::Texture& texture):
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

Textures::ID Aircraft::ToTextureID_()
{
    switch (type_)
    {
        case Aircraft::Eagle:
            return Textures::Eagle;
        case Aircraft::Raptor:
            return Textures::Raptor;
    }
}
