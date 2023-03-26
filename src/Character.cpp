#include "Character.h"

#include <iostream>

#include "Card.h"
#include "Item.h"

Character::Character(const std::string& Name, const unsigned int MaxHealth, const unsigned int MaxEnergy, const unsigned int Shield)
	: Name(Name), 
	  MaxHealth(MaxHealth), CurrentHealth(MaxHealth),
	  MaxEnergy(MaxEnergy), CurrentEnergy(MaxEnergy),
	  Shield(Shield)
{
	std::cout << "New Character\n";

	// Cards
	Card AttackCard("Strike", "Deal damage 10 damage", 2, CardType::Attack, CardRarity::Common);
	Card ShieldCard("Defend", "Gain 5 Block", 1, CardType::Skill, CardRarity::Common);
	Card CurseCard("Curse", "Unplayable. Cannot be removed from your deck.", 0, CardType::Curse, CardRarity::Common);

	Cards.push_back(AttackCard);
	Cards.push_back(ShieldCard);
	Cards.push_back(CurseCard);

	// Items
	Item Potion("Potion", "Heal 20 HP");
	Item BlockPotion("Block Potion", "Gain 20 Shield");
	Item EnergyPotion("Energy Potion", "Regenerates your Energy");
	Item HeartOfIron("Heart Of Iron", "Raise your max HP by 10");

	Items.push_back(Potion);
	Items.push_back(BlockPotion);
	Items.push_back(EnergyPotion);
	Items.push_back(HeartOfIron);
}

Character::Character(const Character& other)
	: Name(other.Name),
	  MaxHealth(other.MaxHealth), CurrentHealth(other.CurrentHealth),
	  MaxEnergy(other.MaxEnergy), CurrentEnergy(other.CurrentEnergy),
	  Shield(other.Shield)
{

}

Character::~Character()
{
	std::cout << "Destruct Character\n";
}

Character& Character::operator = (const Character& other)
{
	Name = other.Name;

	MaxHealth = other.MaxHealth;
	CurrentHealth = other.CurrentHealth;

	MaxEnergy = other.MaxEnergy;
	CurrentEnergy = other.CurrentEnergy;

	Shield = other.Shield;

	return *this;
}

std::ostream& operator << (std::ostream& os, const Character& c)
{
	std::cout << "Name : " << c.Name << '\n';

	std::cout << "MaxHealth : " << c.MaxHealth << '\n';
	std::cout << "CurrentHealth : " << c.CurrentHealth << '\n';

	std::cout << "MaxEnergy : " << c.MaxEnergy << '\n';
	std::cout << "CurrentEnergy : " << c.CurrentEnergy << '\n';

	std::cout << "Shield : " << c.Shield << '\n';

	return os;
}

void Character::AddCard(const Card& NewCard)
{
	Cards.push_back(NewCard);
}

void Character::AddItem(const Item& NewItem)
{
	Items.push_back(NewItem);
}

void Character::PrintCards()
{
	for (Card& c : Cards)
	{
		std::cout << c << '\n';
	}
}

void Character::PrintItems()
{
	for (Item& i : Items)
	{
		std::cout << i << '\n';
	}
}

void Character::IncreaseMaxHealth(const unsigned int Amount)
{
	MaxHealth += Amount;
}

void Character::Heal(const unsigned int Amount)
{
	CurrentHealth += Amount;
}

void Character::TakeDamage(const unsigned int Damage)
{
	CurrentHealth -= Damage;
}

void Character::ConsumeEnergy(const unsigned int Amount)
{
	CurrentEnergy -= Amount;
}

void Character::IncreaseShield(const unsigned int Amount)
{
	Shield += Amount;
}

