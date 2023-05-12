#pragma once

#include <string>
#include <vector>
#include <memory>

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

	sf::Sprite CharacterSprite;

public:
	/** Constructor */
	explicit Character(const std::string& TextureName, const std::string& Name = "None", const unsigned int MaxHealth = 100, const unsigned int Shield = 0);

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
	inline bool IsDead() { return CurrentHealth == 0; }

	/** Shield */
	void IncreaseShield(const unsigned int Amount);

	/** Getters */
	inline const std::string& GetName() { return Name; }

protected:
	virtual void Print(std::ostream& os) const;
};

class Player : public Character
{
private:
	unsigned int MaxEnergy, CurrentEnergy;

	std::shared_ptr<Enemy> CurrentEnemy;

	std::vector<std::shared_ptr<Card>> CardDeck;
	std::vector<std::shared_ptr<Card>> Cards;
	std::vector<std::shared_ptr<Card>> UnusedCards;

	std::vector<std::shared_ptr<Item>> Items;

	sf::Sprite EnergyBackgroundSprite;

	static const std::vector<sf::Vector2f> CardPosition;
	static const std::vector<sf::Vector2f> ItemPosition;

	void ShuffleCards();

public:
	/** Constructor */
	explicit Player(const std::string& TextureName, const std::string& Name = "None", const unsigned int MaxHealth = 100, const unsigned int Shield = 0, const unsigned int MaxEnergy = 5);

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
	void AddCard(std::shared_ptr<Card> const NewCard);
	void AddItem(std::shared_ptr<Item> const NewItem);

	void NextCards();

	/** Setters */
	inline void SetCurrentEnemy(std::shared_ptr<Enemy> const NewEnemy) { CurrentEnemy = NewEnemy; }

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
	unsigned int MaxNextMove;

	sf::Sprite NextMoveSprite;

public:
	/** Constructor */
	explicit Enemy(const std::string& TextureName, const std::string& Name = "None", const unsigned int MaxHealth = 100, const unsigned int Shield = 0, unsigned int MaxNextMove = 15);

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

class EnemyFactory
{
public:
	static std::shared_ptr<Enemy> Gremlin()		{ return std::make_shared<Enemy>("GremlinLeader", "Gremlin", 50, 5); }
	static std::shared_ptr<Enemy> Book()		{ return std::make_shared<Enemy>("Book", "Book", 60, 5); }
	static std::shared_ptr<Enemy> Donut()		{ return std::make_shared<Enemy>("Donu", "Donut", 70, 10); }
	static std::shared_ptr<Enemy> Man()			{ return std::make_shared<Enemy>("Slaver", "Man", 80, 10); }
	static std::shared_ptr<Enemy> Slime()		{ return std::make_shared<Enemy>("Slime", "Slime", 90, 15); }
	static std::shared_ptr<Enemy> Guardian()	{ return std::make_shared<Enemy>("Guardian", "Guardian", 100, 15); }
	static std::shared_ptr<Enemy> Collector()	{ return std::make_shared<Enemy>("Collector", "Collector", 110, 20); }
	static std::shared_ptr<Enemy> Time()		{ return std::make_shared<Enemy>("Time", "Time", 120, 20); }
	static std::shared_ptr<Enemy> FinalBoss()	{ return std::make_shared<Enemy>("FinalBoss", "Final Boss", 150, 25); }
};

