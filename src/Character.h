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
	void AddCard(const Card& NewCard);
	void AddItem(const Item& NewItem);

	void PrintCards();
	void PrintItems();

	/** Health */
	void IncreaseMaxHealth(const unsigned int Amount);
	void Heal(const unsigned int Amount);
	void TakeDamage(const unsigned int Damage);

	/** Energy */
	void ConsumeEnergy(const unsigned int Amount);

	/** Shield */
	void IncreaseShield(const unsigned int Amount);
};

