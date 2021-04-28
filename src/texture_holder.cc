#include "texture_holder.h"

TextureHolder::TextureHolder()
{

}

void TextureHolder::Load_(Textures::ID id, const std::string& filename)
{
    std::unique_ptr<sf::Texture> texture(new sf::Texture());
    if (!texture->loadFromFile(filename))
        throw std::runtime_error("TextureHolder::load -Failed to load "+ filename);
    auto inserted = textures_colector_.insert(std::make_pair(id, std::move(texture)));
}

sf::Texture& TextureHolder::Get_(Textures::ID id)
{
	auto found = textures_colector_.find(id);

	return *found->second;
}

const sf::Texture& TextureHolder::Get_(Textures::ID id) const
{
	auto found = textures_colector_.find(id);

	return *found->second;
}
