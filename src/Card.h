#pragma once

#include <string>

enum CardType
{
	Attack,
	Skill,
	Curse	 
};

enum CardRarity
{
	Common,
	Uncommon,
	Rare,
	Special
};

class Card
{
private:
	std::string Name;
	std::string Description;

	unsigned int EnergyCost;

	CardType Type;
	CardRarity Rarity;

public:
	/** Constructor */
	Card(const std::string& Name = "None", const std::string& Description = "None", const unsigned int EnergyCost = 0, const CardType Type = CardType::Attack, const CardRarity Rarity = CardRarity::Common);

	/** Copy Constructor */
	Card(const Card& other);

	/** Destructor */
	~Card();

	/** Operator = */
	Card& operator = (const Card& other);

	/** Operator << */
	friend std::ostream& operator << (std::ostream& os, const Card& c);

	/** Get string based on enum type */
	static const std::string GetType(const CardType Type);
	static const std::string GetRarity(const CardRarity Rarity);

	/** Use Card */
	// virtual void Use();
};

