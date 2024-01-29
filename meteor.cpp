#include "meteor.h"
#include <random>

Meteor::Meteor()
	: rect(sf::Vector2f(101, 84))
	, direction()
	, speed{ 400.0f } {

	rect.setOrigin(rect.getSize() / 2.0f);

	// Setup
	std::random_device rng;
	std::mt19937 gen(rng());

	// Size
	std::uniform_real_distribution<float> scaleDist(0.25, 1.5);
	float scale = scaleDist(gen);
	rect.setScale(scale, scale);

	// Position
	std::uniform_real_distribution<float> xPosDist(-200, 1040);
	std::uniform_real_distribution<float> yPosDist(-400, -200);
	rect.setPosition(xPosDist(gen), yPosDist(gen));

	// Direction
	std::uniform_real_distribution<float> xDirDist(-0.5, 0.5);
	std::uniform_real_distribution<float> yDirDist(0.75, 1.0);
	direction = sf::Vector2f(xDirDist(gen), yDirDist(gen));
}

Meteor::~Meteor() {}

Meteor &Meteor::operator=(const Meteor &other) {
	if (this != &other) {
		rect = other.rect;
		direction = other.direction;
	}

	return *this;
}

void Meteor::draw(sf::RenderWindow &window) {
	window.draw(rect);
}

void Meteor::update(float deltaTime) {
	sf::Vector2f velocity = direction * speed * deltaTime;
	rect.move(velocity);
}