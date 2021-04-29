#ifndef RESOURCEHOLDER_H
#define RESOURCEHOLDER_H

#include <SFML/Graphics.hpp>

struct ResourcesID
{
	enum Elements
	{
	    kSky,
	    kMountains1,
	    kMountains2
    };
	enum Characters
	{
	    kAircraftEagle,
	    kRaptorEnemy
    };
};

template <class Resource, class Identifier>
class ResourceHolder
{
    public:
        ResourceHolder();
        void Load_(Identifier id, const std::string& filename);
        Resource& Get_(Identifier id);
        const Resource& Get_(Identifier id) const;

	private:
		std::map<Identifier, std::unique_ptr<Resource>> resources_colector_;
};

template <class Resource, class Identifier>
ResourceHolder<Resource, Identifier>::ResourceHolder()
{

}

template <class Resource, class Identifier>
void ResourceHolder<Resource, Identifier>::Load_(Identifier id, const std::string& filename)
{
    std::unique_ptr<Resource> recource(new Resource());
    if (!recource->loadFromFile(filename))
        throw std::runtime_error("ResourceHolder::load -Failed to load "+ filename);
    resources_colector_.insert(std::make_pair(id, std::move(recource)));
}

template <class Resource, class Identifier>
Resource& ResourceHolder<Resource, Identifier>::Get_(Identifier id)
{
	auto found = resources_colector_.find(id);

	return *found->second;
}

template <class Resource, class Identifier>
const Resource& ResourceHolder<Resource, Identifier>::Get_(Identifier id) const
{
	auto found = resources_colector_.find(id);

	return *found->second;
}

#endif // RESOURCEHOLDER_H
