#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>

#include "sequence_tree.h"

class Character : public SequenceTree
{
	public:
        Character();
        virtual ~Character();

		sf::Vector2f get_velocity() const;

		void set_velocity(sf::Vector2f velocity);
		void set_velocity(float vx, float vy);

    public:
        virtual void updateCurrent(sf::Time dt);

	private:
		sf::Vector2f velocity_;
};

#endif // CHARACTER_H
