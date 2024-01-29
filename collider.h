#pragma once
#include <SFML/Graphics.hpp>

class Collider {
public:
	Collider(sf::RectangleShape &rect);
	bool isColliding(Collider &other);

private:
	sf::RectangleShape &rect;
};
