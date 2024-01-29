#pragma once
#include <SFML/Graphics.hpp>

class Scoreboard {
public:
	Scoreboard(float xPos, float yPos);
	void update();
	void draw(sf::RenderWindow &window);

	void incrementScore(unsigned int score) { this->score += score; }
	void loadFont(const std::string &filepath) { font.loadFromFile(filepath); }

	unsigned int getScore() const { return score; }

private:
	unsigned int score;
	std::string scoreText; 
	sf::Font font;
	sf::Text displayText;
};
