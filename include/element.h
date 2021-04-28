#ifndef ELEMENT_H
#define ELEMENT_H


#include <SFML/Graphics.hpp>

#include "SceneNode.h"


class Element : public SceneNode
{
    public:
        explicit Element(const sf::Texture& texture);
        Element(const sf::Texture& texture, const sf::IntRect& rect);

    private:
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        sf::Sprite mSprite;
};

#endif // ELEMENT_H