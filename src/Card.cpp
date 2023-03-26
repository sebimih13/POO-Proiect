#include "Card.h"

#include <iostream>

Card::Card(const std::string& Name, const std::string& Description, const unsigned int Energy, const CardType Type, const CardRarity Rarity)
	: Name(Name), Description(Description),
	  EnergyCost(Energy),
	  Rarity(Rarity), Type(Type)
{
	std::cout << "New Card\n";
}

Card::Card(const Card& Other)
	: Name(Other.Name), Description(Other.Description),
	  EnergyCost(Other.EnergyCost),
	  Type(Other.Type), Rarity(Other.Rarity)
{

}

Card::~Card()
{
	std::cout << "Destructor Card\n";
}

Card& Card::operator = (const Card& other) 
{
	Name = other.Name;
	Description = other.Description;

	EnergyCost = other.EnergyCost;

	Type = other.Type;
	Rarity = other.Rarity;

	return *this;
}

std::ostream& operator << (std::ostream& os, const Card& c)
{
	os << "Name : " << c.Name << '\n';
	os << "Description : " << c.Description << '\n';

	os << "Energy : " << c.EnergyCost << '\n';

	os << "Type : " << Card::GetType(c.Type) << '\n';
	os << "Rarity : " << Card::GetRarity(c.Rarity) << '\n';

	return os;
}

const std::string Card::GetType(const CardType Type)
{
	switch (Type)
	{
		case CardType::Attack:	return "Attack";	break;
		case CardType::Curse:	return "Curse";		break;
		case CardType::Skill:	return "Skill";		break;
		default:				return "None";		break;
	}
}

const std::string Card::GetRarity(const CardRarity Rarity)
{
	switch (Rarity)
	{
		case CardRarity::Common:	return "Common";	break;
		case CardRarity::Uncommon:	return "Uncommon";	break;
		case CardRarity::Rare:		return "Rare";		break;
		case CardRarity::Special:	return "Special";	break;
		default:					return "None";		break;
	}
}

