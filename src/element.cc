#include "element.h"

Element::Element(ResourcesID::Elements type, ResourceTexture& textures) :
    type_(type),
    sprite_(textures.Get_(type_))
{

}

Element::Element(ResourcesID::Elements type, sf::Texture& texture) :
    type_(type),
    sprite_(texture)
{

}

Element::Element(ResourcesID::Elements type, ResourceTexture& textures, const sf::IntRect& rect) :
    type_(type),
    sprite_(textures.Get_(type), rect)
{

}

sf::Vector2f Element::get_velocity() const
{
	return velocity_;
}

void Element::set_velocity(sf::Vector2f velocity)
{
	velocity_ = velocity;
}
void Element::set_velocity(float vx, float vy)
{
	velocity_.x = vx;
	velocity_.y = vy;
}

void Element::DrawCurrent_(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite_, states);
}

void Element::UpdateCurrent_(sf::Time delta_time)
{
    move(velocity_ * delta_time.asSeconds());
}
