#include "Card.h"

#include <iostream>

Card::Card(const std::string& FilePath, const std::string& Name, const std::string& Description, const unsigned int EnergyCost, const CardType Type, const CardRarity Rarity)
	: FilePath(FilePath), Name(Name), Description(Description),
	  EnergyCost(EnergyCost),
	  Type(Type), Rarity(Rarity)
{
	std::cout << "New Card\n";

	if (!Texture.loadFromFile(FilePath))	// TODO : ResourceManager
	{
		std::cout << "Failed to load : " << FilePath << '\n';
	}
}

Card::Card(const Card& Other)
	: FilePath(Other.FilePath), Name(Other.Name), Description(Other.Description),
	  EnergyCost(Other.EnergyCost),
	  Type(Other.Type), Rarity(Other.Rarity),
	  Texture(Other.Texture), Sprite(Other.Sprite)
{

}

Card::~Card()
{
	std::cout << "Destructor Card\n";
}

Card& Card::operator = (const Card& Other) 
{
	FilePath = Other.FilePath;
	Name = Other.Name;
	Description = Other.Description;

	EnergyCost = Other.EnergyCost;

	Type = Other.Type;
	Rarity = Other.Rarity;

	Texture = Other.Texture;
	Sprite = Other.Sprite;

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

void Card::Draw(sf::RenderWindow& Window, const sf::Vector2f& Position, const sf::Vector2f& Scale)
{
	Sprite.setTexture(Texture);
	Sprite.setPosition(Position);
	Sprite.setScale(Scale);
	Window.draw(Sprite);
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

