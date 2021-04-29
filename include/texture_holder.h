#ifndef TEXTUREHOLDER_H
#define TEXTUREHOLDER_H

#include <SFML/Graphics.hpp>

namespace Textures
{
	enum ID
	{
	    kSky,
	    kMountains1,
	    kMountains2,
	    kAircraftEagle,
	    kRaptorEnemy
    };
}

class TextureHolder
{
    public:
        TextureHolder();
        void Load_(Textures::ID id, const std::string& filename);
        sf::Texture& Get_(Textures::ID id);
        const sf::Texture& Get_(Textures::ID id) const;

	private:
		std::map<Textures::ID, std::unique_ptr<sf::Texture>> textures_colector_;
};

#endif // TEXTUREHOLDER_H
