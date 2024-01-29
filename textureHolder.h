#pragma once
#include <map>
#include <memory>
#include <SFML/Graphics.hpp>

namespace Textures {
	enum ID { Spaceship, Laser, Meteor };
}

class TextureHolder {
public:
	void load(Textures::ID id, const std::string &fileName);
	sf::Texture &get(Textures::ID id);
	const sf::Texture &get(Textures::ID id) const;
	
private:
	std::map<Textures::ID, std::unique_ptr<sf::Texture>> textureMap;
};
