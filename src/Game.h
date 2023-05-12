#pragma once

#include <memory>

#include "Singleton.h"

#include <SFML/Graphics.hpp>

/** Forward Declarations */
class Player;
class Enemy;
struct EnemyInfo;

class Game : public Singleton<Game>
{
private:
	/** Player */
	std::shared_ptr<Player> Player1;

	/** Enemy */
	std::shared_ptr<Enemy> Enemy1;

	/** End Turn Button */
	bool IsEndTurnButtonSelected;

	/** Sprites */
	sf::Sprite EndTurnSprite;
	sf::Sprite BackgroundSprite;

	/** Levels */
	const unsigned int MaxLevel;
	static unsigned int CurrentLevel;
	static bool EndGame;

	std::shared_ptr<Enemy> GetNextEnemy();

public:
	/** Constructor */
	Game();

	/** Destructor */
	~Game();

	/** Initialize */
	void Init();

	/** Input */
	void ProcessInput(const sf::Event& e, sf::RenderWindow& Window);

	/** Update */
	void Update();

	/** Draw */
	void Draw(sf::RenderWindow& Window);
};

