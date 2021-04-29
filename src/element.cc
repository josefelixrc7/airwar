#include "element.h"

Element::Element(const sf::Texture& texture) :
    sprite_(texture)
{
}

Element::Element(const sf::Texture& texture, const sf::IntRect& rect) :
    sprite_(texture, rect)
{
}

void Element::DrawCurrent_(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite_, states);
}
