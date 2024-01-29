#include "collider.h"

Collider::Collider(sf::RectangleShape &rect) 
	: rect(rect) {
}

bool Collider::isColliding(Collider &other) {
	if (rect.getGlobalBounds().intersects(other.rect.getGlobalBounds()))
		return true;
	return false;
}
