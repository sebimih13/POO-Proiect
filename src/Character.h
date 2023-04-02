#pragma once

#include <string>
#include <vector>

#include "Card.h"
#include "Item.h"

class Character
{
private:
	std::string Name;

	unsigned int MaxHealth;
	unsigned int CurrentHealth;

	unsigned int MaxEnergy;
	unsigned int CurrentEnergy;
	
	unsigned int Shield;

	std::vector<Card> Cards;
	std::vector<Item> Items;

	sf::Texture EnergyBackgroundTexture;
	sf::Sprite EnergyBackgroundSprite;

	const std::vector<sf::Vector2f> CardPosition = {
		  sf::Vector2f(100.0f, 525.0f),
		  sf::Vector2f(300.0f, 525.0f),
		  sf::Vector2f(500.0f, 525.0f),
		  sf::Vector2f(700.0f, 525.0f),
		  sf::Vector2f(900.0f, 525.0f)
	};

	const std::vector<sf::Vector2f> ItemPosition = {
		  sf::Vector2f(20.0f, 170.0f),
		  sf::Vector2f(70.0f, 170.0f),
		  sf::Vector2f(120.0f, 170.0f),
		  sf::Vector2f(170.0f, 170.0f)
	};

public:
	/** Constructor */
	Character(const std::string& Name = "None", const unsigned int MaxHealth = 100, const unsigned int MaxEnergy = 5, const unsigned int Shield = 0);

	/** Copy Constructor */
	Character(const Character& other);

	/** Destructor */
	~Character();

	/** Operator = */
	Character& operator = (const Character& other);

	/** Operator << */
	friend std::ostream& operator << (std::ostream& os, const Character& c);

	/** Draw */
	void Draw(sf::RenderWindow& Window);

	/** Cards/Items Funtions */
	void AddCard(const Card& NewCard);
	void AddItem(const Item& NewItem);

	void PrintCards() const;
	void PrintItems() const;

	/** Health */
	void IncreaseMaxHealth(const unsigned int Amount);
	void Heal(const unsigned int Amount);
	void TakeDamage(const unsigned int Damage);

	/** Energy */
	void ConsumeEnergy(const unsigned int Amount);

	/** Shield */
	void IncreaseShield(const unsigned int Amount);

	/** Getters / Setters */
	inline std::vector<Card>& GetCards() { return Cards; }
	inline std::vector<Item>& GetItems() { return Items; }
};

