#pragma once

#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

/** Forward Declarations */
class Card;
class Item;
class Enemy;
class Player;

class Character
{
protected:
	std::string Name;

	unsigned int MaxHealth, CurrentHealth;
	unsigned int Shield;

	sf::Texture CharacterTexture;
	sf::Sprite CharacterSprite;

public:
	/** Constructor */
	explicit Character(const std::string& Name = "None", const unsigned int MaxHealth = 100, const unsigned int Shield = 0);

	/** Copy Constructor */
	explicit Character(const Character& other);

	/** Destructor */
	virtual ~Character();

	/** Operator = */
	Character& operator = (const Character& other);

	/** Operator << */
	friend std::ostream& operator << (std::ostream& os, const Character& c);

	/** Draw */
	virtual void Draw(sf::RenderWindow& Window) = 0;

	/** Health */
	void Heal(const unsigned int Amount);
	void TakeDamage(const unsigned int Damage);

	/** Shield */
	void IncreaseShield(const unsigned int Amount);

protected:
	virtual void Print(std::ostream& os) const;
};

class Player : public Character
{
private:
	unsigned int MaxEnergy, CurrentEnergy;

	Enemy* CurrentEnemy;

	std::vector<Card*> Cards;
	std::vector<Item*> Items;

	sf::Texture EnergyBackgroundTexture;
	sf::Sprite EnergyBackgroundSprite;

	const std::vector<sf::Vector2f> CardPosition = {
		  sf::Vector2f(80.0f, 525.0f),
		  sf::Vector2f(300.0f, 525.0f),
		  sf::Vector2f(520.0f, 525.0f),
		  sf::Vector2f(740.0f, 525.0f),
		  sf::Vector2f(960.0f, 525.0f)
	};

	const std::vector<sf::Vector2f> ItemPosition = {
		  sf::Vector2f(20.0f, 170.0f),
		  sf::Vector2f(70.0f, 170.0f),
		  sf::Vector2f(120.0f, 170.0f),
		  sf::Vector2f(170.0f, 170.0f)
	};

public:
	/** Constructor */
	explicit Player(const std::string& Name = "None", const unsigned int MaxHealth = 100, const unsigned int Shield = 0, const unsigned int MaxEnergy = 5);

	/** Copy Constructor */
	explicit Player(const Player& other);

	/** Destructor */
	~Player();

	/** Operator = */
	Player& operator = (const Player& other);

	/** Draw */
	void Draw(sf::RenderWindow& Window) override;

	/** Update */
	void Update(const sf::Vector2i& MousePosition);

	/** Select card/item */
	void Select();

	/** Health */
	void IncreaseMaxHealth(const unsigned int Amount);

	/** Energy */
	void RegenerateFullEnergy();
	void RegenerateEnergy(const unsigned int Amount);
	void ConsumeEnergy(const unsigned int Amount);

	/** Cards/Items Funtions */
	void AddCard(Card* const NewCard);
	void AddItem(Item* const NewItem);

	/** Setters */
	inline void SetCurrentEnemy(Enemy* const NewEnemy) { CurrentEnemy = NewEnemy; }

protected:
	void Print(std::ostream& os) const override;
};

class Enemy : public Character
{
private:
	// TODO : add

public:
	/** Constructor */
	explicit Enemy(const std::string& Name = "None", const unsigned int MaxHealth = 100, const unsigned int Shield = 0);

	/** Copy Constructor */
	explicit Enemy(const Player& other);

	/** Destructor */
	~Enemy();
	
	/** Operator = */
	Enemy& operator = (const Enemy& other);

	/** Draw */
	void Draw(sf::RenderWindow& Window) override;

protected:
	void Print(std::ostream& os) const override;
};

