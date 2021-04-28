#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include <SFML/Graphics.hpp>

#include "Entity.h"
#include "ResourceHolder.h"
#include "TextureHolder.h"


class Aircraft : public Entity
{
    public:
        //typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
        enum Type
        {
            Eagle,
            Raptor,
        };

	public:
		Aircraft(Type type, TextureHolder& textures);
		Aircraft(Type type, sf::Texture& texture);
		virtual ~Aircraft();
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        Textures::ID toTextureID(Type type);

	private:
		Type mType;
        sf::Sprite mSprite;
};
#endif // AIRCRAFT_H
