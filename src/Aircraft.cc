#include "Aircraft.h"


Aircraft::Aircraft(Aircraft::Type type, TextureHolder& textures):
    mType(type),
    mSprite(textures.get(toTextureID(type)))
{
}

Aircraft::Aircraft(Aircraft::Type type, sf::Texture& texture):
    mType(type),
    mSprite(texture)
{
}

Aircraft::~Aircraft()
{
    //dtor
}

void Aircraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}

Textures::ID Aircraft::toTextureID(Aircraft::Type type)
{
    switch (type)
    {
        case Aircraft::Eagle:
            return Textures::Eagle;
        case Aircraft::Raptor:
            return Textures::Raptor;
    }
}
