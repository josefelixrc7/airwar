#ifndef ELEMENT_H
#define ELEMENT_H


#include <SFML/Graphics.hpp>

#include "sequence_tree.h"
#include "resource_holder.h"


class Element : public SequenceTree
{
    public:
    	typedef ResourceHolder<sf::Texture, ResourcesID::Elements> ResourceTexture;

		Element(ResourcesID::Elements type, ResourceTexture& textures);
		Element(ResourcesID::Elements type, sf::Texture& texture);
		Element(ResourcesID::Elements type, ResourceTexture& texture, const sf::IntRect& rect);

		sf::Vector2f get_velocity() const;

		void set_velocity(sf::Vector2f velocity);
		void set_velocity(float vx, float vy);

        virtual void UpdateCurrent_(sf::Time delta_time);

    protected:
        virtual void DrawCurrent_(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
    	sf::Vector2f velocity_;
    	ResourcesID::Elements type_;
        sf::Sprite sprite_;
};

#endif // ELEMENT_H
