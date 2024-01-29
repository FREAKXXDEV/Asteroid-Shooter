#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "laser.h"
#include "meteor.h"
#include "collider.h"
#include "scoreBoard.h"

class Player {
public:
	Player(sf::Vector2f position, std::vector<Meteor*> &meteors, Scoreboard &scoreboard);

	void draw(sf::RenderWindow &window);
	void update(float deltaTime);

	Collider getCollider() { return Collider(rect); }

	void setTexture(sf::Texture &texture) { rect.setTexture(&texture); }
	void loadLaserTexture(sf::Texture &texture) { laserTexture = std::make_unique<sf::Texture>(texture); }

	void setLaserMusic(const std::string &filepath) { laserMusic.openFromFile(filepath); }
	void setExplosionMusic(const std::string &filepath) { explosionMusic.openFromFile(filepath); }

private:
	void getInput();
	void move(float deltaTime);
	void wrapScreen();

	void shootLaser();
	void shootTimer(float deltaTime);
	void updateLasers(float deltaTime);

	void checkLaserMeteorCollision();

private:
	sf::RectangleShape rect;
	sf::Vector2f direction;
	const float speed;

	std::vector<Laser*> lasers;
	std::unique_ptr<sf::Texture> laserTexture;
	bool canShoot;
	float timeSinceShoot;

	std::vector<Meteor*> &meteors;

	sf::Music laserMusic;
	sf::Music explosionMusic;

	Scoreboard &scoreboard;
};
