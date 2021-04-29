#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include <SFML/Graphics.hpp>

#include "character.h"
#include "resource_holder.h"


class Aircraft : public Character
{
    public:
    	typedef ResourceHolder<sf::Texture, ResourcesID::Characters> ResourceTexture;

		Aircraft(ResourcesID::Characters type, ResourceTexture& textures);
		Aircraft(ResourcesID::Characters type, sf::Texture& texture);
		virtual ~Aircraft();

        virtual void DrawCurrent_(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		ResourcesID::Characters type_;
        sf::Sprite sprite_;
};
#endif // AIRCRAFT_H
