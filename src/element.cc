#include "element.h"

Element::Element(Textures::ID type, TextureHolder& textures) :
    type_(type),
    sprite_(textures.Get_(type_))
{

}

Element::Element(Textures::ID type, sf::Texture& texture) :
    type_(type),
    sprite_(texture)
{

}

Element::Element(Textures::ID type, TextureHolder& textures, const sf::IntRect& rect) :
    type_(type),
    sprite_(textures.Get_(type), rect)
{

}

void Element::DrawCurrent_(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite_, states);
}
