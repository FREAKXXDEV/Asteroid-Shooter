#include "game.h"

Game::Game()
	: window(sf::VideoMode(840, 520), "Asteroid Shower", sf::Style::Close)
	, player(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y - 96.0f), meteors) 
	, meteors{}
	, canSpawnMeteor{ true }
	, timeSinceLastMeteor{} {

	textures.load(Textures::Spaceship, Filepaths::playerSprite);
	textures.load(Textures::Laser, Filepaths::laserSprite);
	textures.load(Textures::Meteor, Filepaths::meteorSprite);

	player.setTexture(textures.get(Textures::Spaceship));
	player.loadLaserTexture(textures.get(Textures::Laser));

	gameMusic.openFromFile(Filepaths::backgroundMusic);
	gameMusic.setLoop(true);
	gameMusic.setVolume(40);
	gameMusic.play();

	player.setLaserMusic(Filepaths::laserMusic);
	player.setExplosionMusic(Filepaths::explosion);
}

void Game::run() {
	sf::Clock clock;
	float deltaTime;

	while (window.isOpen()) {
		deltaTime = clock.restart().asSeconds();

		processEvents();
		update(deltaTime);
		render();
	}
}

void Game::processEvents() {
	sf::Event evnt;

	while (window.pollEvent(evnt)) {
		switch (evnt.type) {
		case sf::Event::Closed:
			window.close();
			break;
		}
	}
}

void Game::update(float deltaTime) {
	player.update(deltaTime);

	spawnMeteor();
	meteorTimer(deltaTime);
	updateMeteors(deltaTime);
}

void Game::render() {
	window.clear();
	
	for (int i = 0; i < meteors.size(); i++)
		meteors[i]->draw(window);
	player.draw(window);

	window.display();
}

void Game::spawnMeteor() {
	if (canSpawnMeteor) {
		Meteor *meteor = new Meteor();
		meteor->setTexture(textures.get(Textures::Meteor));
		timeSinceLastMeteor = 0.0f;
		canSpawnMeteor = false;

		meteors.push_back(meteor);
	}
}

void Game::meteorTimer(float deltaTime) {
	if (!canSpawnMeteor) {
		timeSinceLastMeteor += deltaTime;
		if (timeSinceLastMeteor > 1.0f / 3.0f)
			canSpawnMeteor = true;
	}
}

void Game::updateMeteors(float deltaTime) {
	for (auto it = meteors.begin(); it != meteors.end();) {
		(*it)->update(deltaTime);

		if ((*it)->getPosition().y > 720.0f) {
			delete *it;
			it = meteors.erase(it);
		}
		else ++it;
	}

	checkGameOver();
}

void Game::checkGameOver() {
	for (auto it = meteors.begin(); it != meteors.end(); it++) {
		Collider playerCollider = player.getCollider();
		Collider meteorCollider = (*it)->getCollider();
	
		if (playerCollider.isColliding(meteorCollider)) {
			printf("Game Over! \n");
			window.close();
			return;
		}
	}
}
