#pragma once

#include <string>
#include <vector>

/** Forward Declarations */
class Item;
class Card;

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

	/** Cards/Items Funtions */
	void AddCard(Card NewCard);
	void AddItems(Item NewItem);

	void PrintCards();
	void PrintItems();

	/** Health */
	void IncreaseMaxHealth(unsigned int Amount);
	void TakeDamage(unsigned int Damage);

	/** Energy */
	void ConsumeEnergy(unsigned int Amount);

	/** Shield */
	void IncreaseShield(unsigned int Amount);
};

