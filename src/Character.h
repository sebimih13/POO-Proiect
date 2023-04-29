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
	void TakeDamage(unsigned int Damage);

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

	std::vector<Card*> CardDeck;
	std::vector<Card*> Cards;
	std::vector<Card*> UnusedCards;

	std::vector<Item*> Items;

	sf::Texture EnergyBackgroundTexture;
	sf::Sprite EnergyBackgroundSprite;

	static const std::vector<sf::Vector2f> CardPosition;
	static const std::vector<sf::Vector2f> ItemPosition;

	void ShuffleCards();

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

	void NextCards();

	/** Setters */
	inline void SetCurrentEnemy(Enemy* const NewEnemy) { CurrentEnemy = NewEnemy; }

protected:
	void Print(std::ostream& os) const override;
};

enum class EnemyMove
{
	Attack,
	Shield,
	None
};

class Enemy : public Character
{
private:
	EnemyMove NextMove;
	unsigned int IncomingMove;

	sf::Texture AttackTexture;
	sf::Texture ShieldTexture;
	sf::Sprite NextMoveSprite;

public:
	/** Constructor */
	explicit Enemy(const std::string& Name = "None", const unsigned int MaxHealth = 100, const unsigned int Shield = 0);

	/** Copy Constructor */
	explicit Enemy(const Enemy& other);

	/** Destructor */
	~Enemy();
	
	/** Operator = */
	Enemy& operator = (const Enemy& other);

	/** Draw */
	void Draw(sf::RenderWindow& Window) override;

	/** Set next move */
	void NewMove();

	/** Getters */
	unsigned int GetIncomingAttack();
	unsigned int GetIncomingShield();

protected:
	void Print(std::ostream& os) const override;
};

