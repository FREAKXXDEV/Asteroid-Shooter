#include "laser.h"

Laser::Laser(sf::Vector2f position) 
	: rect(sf::Vector2f(13.0f, 54.0f))
	, direction(0.0f, -1.0f)
	, speed{ 800.0f } {
	
	rect.setOrigin(rect.getSize() / 2.0f);
	rect.setPosition(position);
}

Laser &Laser::operator=(const Laser &other) {
	if (this != &other) {
		rect = other.rect;
		direction = other.direction;
	}

	return *this;
}

void Laser::update(float deltaTime) {
	sf::Vector2f velocity(speed * direction * deltaTime);
	rect.move(velocity);
}

void Laser::draw(sf::RenderWindow &window) {
	window.draw(rect);
}
