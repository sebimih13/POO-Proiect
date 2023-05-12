#pragma once

#include <string>
#include <memory>

#include <SFML/Graphics.hpp>

/** Forward Declarations */
class Player;
class Enemy;

class Card
{
private:
	std::string TextureName;
	std::string Name;
	std::string Description;

	unsigned int EnergyCost;

	bool IsSelected;

	sf::Sprite Sprite;

public:
	/** Constructor */
	explicit Card(const std::string& TextureName, const std::string& Name = "None", const std::string& Description = "None", const unsigned int EnergyCost = 0);

	/** Copy Constructor */
	explicit Card(const Card& other);

	/** Destructor */
	virtual ~Card();

	/** Operator = */
	Card& operator = (const Card& other);

	/** Operator << */
	friend std::ostream& operator << (std::ostream& os, const Card& c);

	/** Clone - Virtual Constructor */
	virtual std::shared_ptr<Card> Clone() const = 0;

	/** Draw */
	void Draw(sf::RenderWindow& Window, const sf::Vector2f& Position, const sf::Vector2f& Scale = sf::Vector2f(0.3f, 0.3f));

	/** Update */
	void Update(const sf::Vector2i& MousePosition);

	/** Getters */
	inline bool GetIsSelected() const { return IsSelected; }
	inline unsigned int GetEnergy() const { return EnergyCost; }

protected:
	virtual void Print(std::ostream& os) const;
};

class DamageCard : public Card
{
private:
	unsigned int Damage;

public:
	/** Constructor */
	explicit DamageCard(unsigned int Damage, const std::string& TextureName, const std::string& Name = "None", const std::string& Description = "None", const unsigned int EnergyCost = 0);

	/** Copy Constructor */
	explicit DamageCard(const DamageCard& other);

	/** Destructor */
	~DamageCard();

	/** Operator = */
	DamageCard& operator = (const DamageCard& other);

	/** Clone - Virtual Constructor */
	std::shared_ptr<Card> Clone() const override;

	void Use(Enemy* const CurrentEnemy);

protected:
	void Print(std::ostream& os) const override;
};

class ShieldCard : public Card
{
private:
	unsigned int Block;

public:
	/** Constructor */
	explicit ShieldCard(unsigned int Block, const std::string& TextureName, const std::string& Name = "None", const std::string& Description = "None", const unsigned int EnergyCost = 0);

	/** Copy Constructor */
	explicit ShieldCard(const ShieldCard& other);

	/** Destructor */
	~ShieldCard();

	/** Operator = */
	ShieldCard& operator = (const ShieldCard& other);

	/** Clone - Virtual Constructor */
	std::shared_ptr<Card> Clone() const override;

	void Use(Player* const CurrentPlayer);

protected:
	void Print(std::ostream& os) const override;
};

