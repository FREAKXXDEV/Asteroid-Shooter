#include "player.h"

Player::Player(sf::Vector2f position, std::vector<Meteor*> &meteors)
	: rect(sf::Vector2f(99, 75))
	, direction(0.0f, 0.0f) 
	, speed{ 600.0f }
	, lasers{}
	, canShoot{ true } 
	, timeSinceShoot{} 
	, meteors{ meteors } {

	rect.setOrigin(rect.getSize() / 2.0f);
	rect.setPosition(position);
}

void Player::draw(sf::RenderWindow &window) {
	for (auto laser = lasers.begin(); laser != lasers.end(); laser++)
		(*laser)->draw(window);
	window.draw(rect);
}

void Player::update(float deltaTime) {
	getInput();
	move(deltaTime);
	wrapScreen();

	updateLasers(deltaTime);
	shootTimer(deltaTime);

	checkLaserMeteorCollision();
}

void Player::getInput() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		direction.x = -1.0f;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
		direction.x = 1.0f;
	else direction.x = 0.0f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) 
		direction.y = -1.0f;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) 
		direction.y = 1.0f;
	else direction.y = 0.0f;

	if (direction.x != 0.0f && direction.y != 0.0f) direction /= sqrt(2.0f);
	
	shootLaser();
}

void Player::move(float deltaTime) {
	sf::Vector2f veloclasery = direction * speed * deltaTime;
	rect.move(veloclasery);
}

void Player::wrapScreen() {
	float left = 0.0f - rect.getSize().x / 2.0f;
	float right = 840.0f + rect.getSize().x / 2.0f;
	float top = 0.0f - rect.getSize().y / 2.0f;
	float bottom = 520.0f + rect.getSize().y / 2.0f;

	if (rect.getPosition().x < left) rect.setPosition(right, rect.getPosition().y);
	else if (rect.getPosition().x > right) rect.setPosition(left, rect.getPosition().y);
	if (rect.getPosition().y < top) rect.setPosition(rect.getPosition().x, bottom);
	else if (rect.getPosition().y > bottom) rect.setPosition(rect.getPosition().x, top);
}

void Player::shootLaser() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canShoot) {
		laserMusic.play();
		Laser *laser = new Laser(rect.getPosition() - sf::Vector2f(0, 32));
		laser->setTexture(*laserTexture);
		lasers.push_back(laser);
		canShoot = false;
		timeSinceShoot = 0.0f;
	}
}

void Player::shootTimer(float deltaTime) {
	float totalTime;
	if (!canShoot) {
		timeSinceShoot += deltaTime;
		if (timeSinceShoot >  0.5f)
			canShoot = true;
	}
}

void Player::updateLasers(float deltaTime) {
	for (auto it = lasers.begin(); it != lasers.end();) {
		(*it)->update(deltaTime);

		if ((*it)->getPosition().y < -200.0f) {
			delete *it;
			it = lasers.erase(it);
		}
		else ++it;
	}
}

void Player::checkLaserMeteorCollision() {
	for (auto laser = lasers.begin(); laser != lasers.end();) {
		bool laserDeleted = false;

		for (auto meteor = meteors.begin(); meteor != meteors.end();) {
			Collider laserCollider = (*laser)->getCollider();
			Collider meteorCollider = (*meteor)->getCollider();

			if (laserCollider.isColliding(meteorCollider)) {
				explosionMusic.play();

				delete *meteor;
				meteor = meteors.erase(meteor);

				delete *laser;
				laser = lasers.erase(laser);
				laserDeleted = true;
				break;
			}
			else ++meteor;
		}

		if (!laserDeleted) ++laser;
	}
}
