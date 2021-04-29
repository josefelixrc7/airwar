#include "element.h"

Element::Element(const sf::Texture& texture) :
    mSprite(texture)
{
}

Element::Element(const sf::Texture& texture, const sf::IntRect& rect) :
    mSprite(texture, rect)
{
}

void Element::DrawCurrent_(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}
