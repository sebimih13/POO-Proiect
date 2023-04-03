#pragma once

#include <string>

#include <SFML/Graphics.hpp>

/** Forward Declarations */
class Player;
class Enemy;

class Card
{
private:
	std::string FilePath;
	std::string Name;
	std::string Description;

	unsigned int EnergyCost;

	bool IsSelected;

	sf::Texture Texture;
	sf::Sprite Sprite;

public:
	/** Constructor */
	explicit Card(const std::string& FilePath, const std::string& Name = "None", const std::string& Description = "None", const unsigned int EnergyCost = 0);

	/** Copy Constructor */
	explicit Card(const Card& other);

	/** Destructor */
	virtual ~Card();

	/** Operator = */
	Card& operator = (const Card& other);

	/** Operator << */
	friend std::ostream& operator << (std::ostream& os, const Card& c);

	/** Draw */
	void Draw(sf::RenderWindow& Window, const sf::Vector2f& Position, const sf::Vector2f& Scale = sf::Vector2f(0.3f, 0.3f));

	/** Update */
	void Update(const sf::Vector2i& MousePosition);

	/** Getters */
	inline bool GetIsSelected() const { return IsSelected; }
	inline unsigned int GetEnergy() const { return EnergyCost; }

	/** Get string based on enum type */
	//static const std::string GetType(const CardType Type);
	//static const std::string GetRarity(const CardRarity Rarity);
};

class DamageCard : public Card
{
private:
	unsigned int Damage;

public:
	/** Constructor */
	explicit DamageCard(unsigned int Damage, const std::string& FilePath, const std::string& Name = "None", const std::string& Description = "None", const unsigned int EnergyCost = 0);

	/** Copy Constructor */
	explicit DamageCard(const DamageCard& other);

	/** Destructor */
	~DamageCard();

	// TODO : overload operators

	void Use(Enemy* CurrentEnemy);
};

class ShieldCard : public Card
{
private:
	unsigned int Block;

public:
	/** Constructor */
	explicit ShieldCard(unsigned int Block, const std::string& FilePath, const std::string& Name = "None", const std::string& Description = "None", const unsigned int EnergyCost = 0);

	/** Copy Constructor */
	explicit ShieldCard(const ShieldCard& other);

	/** Destructor */
	~ShieldCard();

	// TODO : overload operators

	void Use(Player* CurrentPlayer);
};

