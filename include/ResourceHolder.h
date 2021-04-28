#ifndef RESOURCEHOLDER_H
#define RESOURCEHOLDER_H

#include <string>
#include <map>
#include <memory>
#include <stdexcept>

template <typename Resource, typename Identifier>
class ResourceHolder
{
	public:
		void load(Identifier id, const std::string& filename);
		Resource& get(Identifier id);
		const Resource& get(Identifier id) const;

	private:
		std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;
};

#endif // RESOURCEHOLDER_H
