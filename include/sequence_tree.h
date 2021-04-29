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

		SequenceTree();

		void AttachChild_(UniqueSequence child);
		UniqueSequence DetachChild_(const SequenceTree& node);
		void Update_(sf::Time dt);
		sf::Transform GetWorldTransform_() const;
		sf::Vector2f GetWorldPosition_() const;

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		virtual void DrawCurrent_(sf::RenderTarget& target, sf::RenderStates states) const;
		virtual void UpdateCurrent_(sf::Time dt);
		void UpdateChildren_(sf::Time dt);

		std::vector<UniqueSequence> children_colector_;
		SequenceTree* parent_;
};

#endif // SEQUENCETREE_H
