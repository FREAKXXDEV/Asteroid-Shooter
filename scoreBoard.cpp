#include "scoreBoard.h"

Scoreboard::Scoreboard(float xPos, float yPos) {
	score = 0u;
	scoreText = "SCORE: " + std::to_string(score);
	displayText.setPosition(xPos, yPos);
}

void Scoreboard::update() {
	scoreText = "SCORE: " + std::to_string(score);
	displayText = sf::Text(scoreText, font, 50u);
}

void Scoreboard::draw(sf::RenderWindow &window) {
	window.draw(displayText);
}
