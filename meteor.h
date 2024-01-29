#pragma once
#include <SFML/Graphics.hpp>
#include "collider.h"

class Meteor {
public:
	Meteor();
	~Meteor();
	Meteor &operator=(const Meteor &other);

	void update(float deltaTime);
	void draw(sf::RenderWindow &window);

	sf::Vector2f getPosition() const { return rect.getPosition(); }
	Collider getCollider() { return Collider(rect); }

	void setPosition(sf::Vector2f position) { rect.setPosition(position); }
	void setTexture(sf::Texture &texture) { rect.setTexture(&texture); }

private:
	sf::RectangleShape rect;
	sf::Vector2f direction;
	const float speed;
};
