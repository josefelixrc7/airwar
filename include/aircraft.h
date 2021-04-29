#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include <SFML/Graphics.hpp>

#include "character.h"
#include "resource_holder.h"


class Aircraft : public Character
{
    public:
		Aircraft(Textures::ID type, ResourceHolder<sf::Texture, Textures::ID>& textures);
		Aircraft(Textures::ID type, sf::Texture& texture);
		virtual ~Aircraft();

        virtual void DrawCurrent_(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		Textures::ID type_;
        sf::Sprite sprite_;
};
#endif // AIRCRAFT_H
