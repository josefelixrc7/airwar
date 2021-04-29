#include "sequence_tree.h"

SequenceTree::SequenceTree()
{

}

void SequenceTree::AttachChild_(UniqueSequence child)
{
	child->parent_ = this;
	children_colector_.push_back(std::move(child));
}

SequenceTree::UniqueSequence SequenceTree::DetachChild_(const SequenceTree& child)
{
	auto found = std::find_if(children_colector_.begin(), children_colector_.end(), [&] (UniqueSequence& p) -> bool { return p.get() == &child; });
	UniqueSequence result = std::move(*found);
	result->parent_ = nullptr;
	children_colector_.erase(found);
	return result;
}
void SequenceTree::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    DrawCurrent_(target, states);
    for (auto itr = children_colector_.begin();itr != children_colector_.end(); ++itr)
    {
        (*itr)->draw(target, states);
    }
}

void SequenceTree::DrawCurrent_(sf::RenderTarget& target, sf::RenderStates states) const
{

}

void SequenceTree::Update_(sf::Time delta_time)
{
    UpdateCurrent_(delta_time);
    UpdateChildren_(delta_time);
}

void SequenceTree::UpdateCurrent_(sf::Time delta_time)
{

}

void SequenceTree::UpdateChildren_(sf::Time delta_time)
{
    for(const auto& child : children_colector_)
        child->Update_(delta_time);
}

sf::Transform SequenceTree::GetWorldTransform_() const
{
    sf::Transform transform = sf::Transform::Identity;
    for (const SequenceTree* node = this;node != nullptr; node = node->parent_)
        transform = node->getTransform() * transform;

    return transform;
}

sf::Vector2f SequenceTree::GetWorldPosition_() const
{
    return GetWorldTransform_() * sf::Vector2f();
}
