#pragma once
#include <SFML/Graphics.hpp>
#include "collider.h"

class Laser {
public:
	Laser(sf::Vector2f position);
	Laser &operator=(const Laser &other);

	void update(float deltaTime);
	void draw(sf::RenderWindow &window);

	sf::Vector2f getPosition() const { return rect.getPosition(); }
	Collider getCollider() { return Collider(rect); }

	void setTexture(sf::Texture &texture) { rect.setTexture(&texture); }

private:
	sf::RectangleShape rect;
	sf::Vector2f direction;
	const float speed;
};
