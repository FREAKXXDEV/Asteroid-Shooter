#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "filepaths.h"
#include "textureHolder.h"
#include "player.h"
#include "meteor.h"
#include "laser.h"
#include "collider.h"
#include "scoreBoard.h"

class Game {
public:
	Game();
	void run();

private:
	void processEvents();
	void update(float deltaTime);
	void render();

	void spawnMeteor();
	void meteorTimer(float deltaTime);
	void updateMeteors(float deltaTime);

	void checkGameOver();

private:
	sf::RenderWindow window;
	TextureHolder textures;
	Player player;

	std::vector<Meteor*> meteors;
	bool canSpawnMeteor;
	float timeSinceLastMeteor;

	sf::Music gameMusic;
	sf::Music explosionMusic;

	Scoreboard scoreboard;
	float runtimeScore;
};
