#ifndef ELEMENT_H
#define ELEMENT_H


#include <SFML/Graphics.hpp>

#include "sequence_tree.h"
#include "texture_holder.h"


class Element : public SequenceTree
{
    public:
		Element(Textures::ID type, TextureHolder& textures);
		Element(Textures::ID type, sf::Texture& texture);
		Element(Textures::ID type, TextureHolder& texture, const sf::IntRect& rect);

    private:
        virtual void DrawCurrent_(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
    	Textures::ID type_;
        sf::Sprite sprite_;
};

#endif // ELEMENT_H
