#include "sequence_tree.h"

SequenceTree::SequenceTree()
{

}

void SequenceTree::attachChild(UniqueSequence child)
{
	child->mParent = this;
	mChildren.push_back(std::move(child));
}

SequenceTree::UniqueSequence SequenceTree::detachChild(const SequenceTree& node)
{
	auto found = std::find_if(mChildren.begin(), mChildren.end(), [&] (UniqueSequence& p) -> bool { return p.get() == &node; });
	//assert(found != mChildren.end());
	UniqueSequence result = std::move(*found);
	result->mParent = nullptr;
	mChildren.erase(found);
	return result;
}
void SequenceTree::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    drawCurrent(target, states);
    for (auto itr = mChildren.begin();itr != mChildren.end(); ++itr)
    {
        (*itr)->draw(target, states);
    }
}

void SequenceTree::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{

}

void SequenceTree::update(sf::Time dt)
{
    updateCurrent(dt);
    updateChildren(dt);
}
void SequenceTree::updateCurrent(sf::Time)
{
}
void SequenceTree::updateChildren(sf::Time dt)
{
    for(const auto& child : mChildren)
        child->update(dt);
}

sf::Transform SequenceTree::getWorldTransform() const
{
    sf::Transform transform = sf::Transform::Identity;
    for (const SequenceTree* node = this;node != nullptr; node = node->mParent)
        transform = node->getTransform() * transform;

    return transform;
}

sf::Vector2f SequenceTree::getWorldPosition() const
{
    return getWorldTransform() * sf::Vector2f();
}
