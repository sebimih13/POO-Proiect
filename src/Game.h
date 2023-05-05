#pragma once

#include <memory>

#include <SFML/Graphics.hpp>

/** Forward Declarations */
class Player;
class Enemy;
struct EnemyInfo;

class Game
{
private:
	/** Constructor */
	Game();

	static Game Instance;

	/** Player */
	std::unique_ptr<Player> Player1;

	/** Enemy */
	std::unique_ptr<Enemy> Enemy1;

	/** End Turn Button */
	bool IsEndTurnButtonSelected;

	/** Textures / Sprites */
	sf::Texture EndTurnNormTexture;
	sf::Texture EndTurnHoverTexture;
	sf::Sprite EndTurnSprite;

	sf::Texture BackgroundTexture;
	sf::Sprite BackgroundSprite;

	/** Levels */
	static bool EndGame;
	static unsigned int CurrentLevel;
	static const std::vector<std::shared_ptr<EnemyInfo>> LevelEnemy;

	/** Font */
	sf::Font Font;

public:
	/** Destructor */
	~Game();

	/** Copy Constructor */
	Game(const Game&) = delete;

	/** Operator = */
	Game& operator = (const Game&) = delete;

	/** Initialize */
	void Init();

	/** Input */
	void ProcessInput(const sf::Event& e, sf::RenderWindow& Window);

	/** Update */
	void Update();

	/** Draw */
	void Draw(sf::RenderWindow& Window);
	
	/** Getters */
	inline static Game& GetInstance() { return Instance; }
};

