#include "Card.h"

#include "Character.h"
#include "ExceptionHierarchy.h"

#include <iostream>

///////////////////////////////////////////////////////////////////////////
///////////////////////				Card			///////////////////////
///////////////////////////////////////////////////////////////////////////

Card::Card(const std::string& FilePath, const std::string& Name, const std::string& Description, const unsigned int EnergyCost)
	: FilePath(FilePath), Name(Name), Description(Description),
	  EnergyCost(EnergyCost),
	  IsSelected(false)
{
	std::cout << "New Card\n";

	if (!Texture.loadFromFile(FilePath))	// TODO : ResourceManager
	{
		throw TextureError(FilePath);
	}

	Sprite.setTexture(Texture);
}

Card::Card(const Card& Other)
	: FilePath(Other.FilePath), Name(Other.Name), Description(Other.Description),
	  EnergyCost(Other.EnergyCost),
	  IsSelected(Other.IsSelected),
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

	IsSelected = Other.IsSelected;

	Texture = Other.Texture;
	Sprite = Other.Sprite;

	return *this;
}

std::ostream& operator << (std::ostream& os, const Card& c)
{
	c.Print(os);
	return os;
}

void Card::Draw(sf::RenderWindow& Window, const sf::Vector2f& Position, const sf::Vector2f& Scale)
{
	Sprite.setTexture(Texture);
	Sprite.setPosition(Position);
	Sprite.setScale(Scale);

	// Select Box
	if (IsSelected)
	{
		float BoxPosX = Sprite.getGlobalBounds().getPosition().x;
		float BoxPosY = Sprite.getGlobalBounds().getPosition().y;

		float BoxSizeX = Sprite.getGlobalBounds().width;
		float BoxSizeY = Sprite.getGlobalBounds().height;

		sf::RectangleShape Box;
		Box.setPosition(sf::Vector2f(BoxPosX, BoxPosY));
		Box.setSize(sf::Vector2f(BoxSizeX, BoxSizeY));
		Box.setFillColor(sf::Color::Transparent);
		Box.setOutlineColor(sf::Color::Yellow);
		Box.setOutlineThickness(3.0f);
		
		Window.draw(Box);
	}

	Window.draw(Sprite);
}

void Card::Update(const sf::Vector2i& MousePosition)
{
	// Check if this card is selected
	if (Sprite.getGlobalBounds().getPosition().x <= float(MousePosition.x) && float(MousePosition.x) <= Sprite.getGlobalBounds().getPosition().x + Sprite.getGlobalBounds().width &&
		Sprite.getGlobalBounds().getPosition().y <= float(MousePosition.y) && float(MousePosition.y) <= Sprite.getGlobalBounds().getPosition().y + Sprite.getGlobalBounds().height)
	{
		IsSelected = true;
	}
	else
	{
		IsSelected = false;
	}
}

void Card::Print(std::ostream& os) const
{
	os << "FilePath : " << FilePath << '\n';
	os << "Name : " << Name << '\n';
	os << "Description : " << Description << '\n';

	os << "Energy : " << EnergyCost << '\n';
}

///////////////////////////////////////////////////////////////////////////
///////////////////////			DamageCard			///////////////////////
///////////////////////////////////////////////////////////////////////////

DamageCard::DamageCard(unsigned int Damage, const std::string& FilePath, const std::string& Name, const std::string& Description, const unsigned int EnergyCost)
	: Card(FilePath, Name, Description, EnergyCost),
	  Damage(Damage)
{
	std::cout << "New DamageCard\n";
}

DamageCard::DamageCard(const DamageCard& other)
	: Card(other),
	  Damage(other.Damage)
{

}

DamageCard::~DamageCard()
{
	std::cout << "Destructor DamageCard\n";
}

DamageCard& DamageCard::operator = (const DamageCard& other)
{
	Card::operator=(other);

	Damage = other.Damage;

	return *this;
}

Card* DamageCard::Clone() const
{
	return new DamageCard(*this);
}

void DamageCard::Use(Enemy* CurrentEnemy)
{
	// TODO : exceptie -> folosita doar pt clasa Enemy
	CurrentEnemy->TakeDamage(Damage);
}

void DamageCard::Print(std::ostream& os) const
{
	Card::Print(os);

	os << "Damage : " << Damage << '\n';
}

///////////////////////////////////////////////////////////////////////////
///////////////////////			ShieldCard			///////////////////////
///////////////////////////////////////////////////////////////////////////

ShieldCard::ShieldCard(unsigned int Block, const std::string& FilePath, const std::string& Name, const std::string& Description, const unsigned int EnergyCost)
	: Card(FilePath, Name, Description, EnergyCost),
	  Block(Block)
{
	std::cout << "New ShieldCard\n";
}

ShieldCard::ShieldCard(const ShieldCard& other)
	: Card(other),
	  Block(other.Block)
{

}

ShieldCard::~ShieldCard()
{
	std::cout << "Destructor ShieldCard\n";
}

ShieldCard& ShieldCard::operator = (const ShieldCard& other)
{
	Card::operator=(other);

	Block = other.Block;

	return *this;
}

Card* ShieldCard::Clone() const
{
	return new ShieldCard(*this);
}

void ShieldCard::Use(Player* CurrentPlayer)
{
	// TODO : exceptie -> folosita doar pt clasa Player
	CurrentPlayer->IncreaseShield(Block);
}

void ShieldCard::Print(std::ostream& os) const
{
	Card::Print(os);

	os << "Block : " << Block << '\n';
}

