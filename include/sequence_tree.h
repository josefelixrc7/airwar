#ifndef SEQUENCETREE_H
#define SEQUENCETREE_H

#include <SFML/Graphics.hpp>

class SequenceTree :
	public sf::Transformable,
	public sf::Drawable,
	private sf::NonCopyable
{
	public:
		typedef std::unique_ptr<SequenceTree> UniqueSequence;

	public:
		SequenceTree();
		void attachChild(UniqueSequence child);
		UniqueSequence detachChild(const SequenceTree& node);
		void update(sf::Time dt);
		sf::Transform getWorldTransform() const;
		sf::Vector2f getWorldPosition() const;

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
		virtual void updateCurrent(sf::Time dt);
		void updateChildren(sf::Time dt);

	private:
		std::vector<UniqueSequence> mChildren;
		SequenceTree* mParent;
};

#endif // SEQUENCETREE_H
