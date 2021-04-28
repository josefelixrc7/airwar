#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

#include "SceneNode.h"

class Entity : public SceneNode
{
	public:
        Entity();
        virtual ~Entity();
		void setVelocity(sf::Vector2f velocity);
		void setVelocity(float vx, float vy);
		sf::Vector2f getVelocity() const;

    public:
        virtual void updateCurrent(sf::Time dt);

	private:
		sf::Vector2f mVelocity;
};

#endif // ENTITY_H
