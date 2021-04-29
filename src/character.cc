#include "character.h"

Character::Character()
{

}

Character::~Character()
{

}

sf::Vector2f Character::get_velocity() const
{
	return velocity_;
}

void Character::set_velocity(sf::Vector2f velocity)
{
	velocity_ = velocity;
}

void Character::set_velocity(float vx, float vy)
{
	velocity_.x = vx;
	velocity_.y = vy;
}

void Character::UpdateCurrent_(sf::Time delta_time)
{
    move(velocity_ * delta_time.asSeconds());
}
