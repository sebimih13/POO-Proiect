#pragma once

#include "Character.h"

#include <SFML/Graphics.hpp>

class Game
{
private:
	/** Constructor */
	Game();

	static Game Instance;

	/** Player */
	Player Player1;		// TODO : pointer?

	/** Enemy */
	Enemy Enemy1;		// TODO : pointer?

	/** End Turn Button */
	bool IsEndTurnButtonSelected;

	/** Textures / Sprites */
	sf::Texture EndTurnNormTexture;
	sf::Texture EndTurnHoverTexture;
	sf::Sprite EndTurnSprite;

	sf::Texture BackgroundTexture;
	sf::Sprite BackgroundSprite;

public:
	/** Copy Constructor */
	Game(const Game&) = delete;

	/** Operator = */
	Game& operator = (const Game&) = delete;

	/** Initialize */
	// TODO
	// void Init();

	/** Input */
	void ProcessInput(const sf::Event& e, sf::RenderWindow& Window);

	/** Update */
	void Update();

	/** Draw */
	void Draw(sf::RenderWindow& Window);
	
	/** Getters */
	inline static Game& GetInstance() { return Instance; }
};

