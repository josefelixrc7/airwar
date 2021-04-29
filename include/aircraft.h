#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include <SFML/Graphics.hpp>

#include "character.h"
#include "texture_holder.h"


class Aircraft : public Character
{
    public:
        enum Type
        {
            Eagle,
            Raptor,
        };

		Aircraft(Type type, TextureHolder& textures);
		Aircraft(Type type, sf::Texture& texture);
		virtual ~Aircraft();

        virtual void DrawCurrent_(sf::RenderTarget& target, sf::RenderStates states) const;
        Textures::ID ToTextureID_();

	private:
		Type type_;
        sf::Sprite sprite_;
};
#endif // AIRCRAFT_H
