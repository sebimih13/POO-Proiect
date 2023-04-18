#include "Item.h"

#include <iostream>

#include "Character.h"

///////////////////////////////////////////////////////////////////////////
///////////////////////				Item			///////////////////////
///////////////////////////////////////////////////////////////////////////

Item::Item(const std::string& FilePath, const std::string& Name, const std::string& Description)
	: FilePath(FilePath), Name(Name), Description(Description),
	  IsSelected(false)
{
	std::cout << "New Item\n";

	if (!Texture.loadFromFile(FilePath))		// TODO : ResourceManager
	{
		std::cout << "Can't load : " << FilePath << '\n';
	}

	Sprite.setTexture(Texture);
}

Item::Item(const Item& other)
	: FilePath(other.FilePath), Name(other.Name), Description(other.Description),
	  IsSelected(other.IsSelected),
	  Texture(other.Texture), Sprite(other.Sprite)
{

}

Item::~Item()
{
	std::cout << "Destruct Item\n";
}

Item& Item::operator = (const Item& other)
{
	FilePath = other.FilePath;
	Name = other.Name;
	Description = other.Description;

	IsSelected = other.IsSelected;

	Texture = other.Texture;
	Sprite = other.Sprite;

	return *this;
}

std::ostream& operator << (std::ostream& os, const Item& i)
{
	i.Print(os);
	return os;
}

void Item::Draw(sf::RenderWindow& Window, const sf::Vector2f& Position, const sf::Vector2f& Scale)
{
	Sprite.setTexture(Texture);
	Sprite.setPosition(Position);
	Sprite.setScale(Scale);

	// Select Box
	if (IsSelected)
	{
		float BoxPosX = Sprite.getGlobalBounds().getPosition().x + 10.0f;
		float BoxPosY = Sprite.getGlobalBounds().getPosition().y + 10.0f;

		float BoxSizeX = Sprite.getGlobalBounds().width - 20.0f;
		float BoxSizeY = Sprite.getGlobalBounds().height - 10.0f;

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

void Item::Update(const sf::Vector2i& MousePosition)
{
	// Check if this item is selected
	float StartX = Sprite.getGlobalBounds().getPosition().x + 10.0f;
	float StartY = Sprite.getGlobalBounds().getPosition().y + 10.0f;

	float EndX = Sprite.getGlobalBounds().getPosition().x + Sprite.getGlobalBounds().width - 20.0f;
	float EndY = Sprite.getGlobalBounds().getPosition().y + Sprite.getGlobalBounds().height - 10.0f;

	if (StartX <= float(MousePosition.x) && float(MousePosition.x) <= EndX &&
		StartY <= float(MousePosition.y) && float(MousePosition.y) <= EndY)
	{
		IsSelected = true;
	}
	else
	{
		IsSelected = false;
	}
}

void Item::Print(std::ostream& os) const
{
	os << "Name : " << Name << '\n';
	os << "Description : " << Description << '\n';
}

///////////////////////////////////////////////////////////////////////////
///////////////////////			HealthPotion		///////////////////////
///////////////////////////////////////////////////////////////////////////

HealthPotion::HealthPotion(const unsigned int HP, const std::string& FilePath, const std::string& Name, const std::string& Description)
	: Item(FilePath, Name, Description),
	  HP(HP)
{
	std::cout << "New HealthPotion\n";
}

HealthPotion::~HealthPotion()
{
	std::cout << "Destruct HealthPotion\n";
}

HealthPotion& HealthPotion::operator = (const HealthPotion& other)
{
	Item::operator=(other);

	HP = other.HP;

	return *this;
}

Item* HealthPotion::Clone() const
{
	return new HealthPotion(*this);
}

void HealthPotion::Use(Player* Owner)
{
	Owner->Heal(HP);
}

void HealthPotion::Print(std::ostream& os) const
{
	Item::Print(os);

	os << "Health : " << HP << '\n';
}

///////////////////////////////////////////////////////////////////////////
///////////////////////			BlockPotion			///////////////////////
///////////////////////////////////////////////////////////////////////////

BlockPotion::BlockPotion(const unsigned int Block, const std::string& FilePath, const std::string& Name, const std::string& Description)
	: Item(FilePath, Name, Description),
	  Block(Block)
{
	std::cout << "New BlockPotion\n";
}

BlockPotion::~BlockPotion()
{
	std::cout << "Destruct BlockPotion\n";
}

BlockPotion& BlockPotion::operator = (const BlockPotion& other)
{
	Item::operator=(other);

	Block = other.Block;

	return *this;
}

Item* BlockPotion::Clone() const
{
	return new BlockPotion(*this);
}

void BlockPotion::Use(Player* Owner)
{
	Owner->IncreaseShield(Block);
}

void BlockPotion::Print(std::ostream& os) const
{
	Item::Print(os);

	os << "Block : " << Block << '\n';
}

///////////////////////////////////////////////////////////////////////////
///////////////////////			EnergyPotion		///////////////////////
///////////////////////////////////////////////////////////////////////////

FullEnergyPotion::FullEnergyPotion(const std::string& FilePath, const std::string& Name, const std::string& Description)
	: Item(FilePath, Name, Description)
{
	std::cout << "New FullEnergyPotion\n";
}

FullEnergyPotion::~FullEnergyPotion()
{
	std::cout << "Destruct FullEnergyPotion\n";
}

FullEnergyPotion& FullEnergyPotion::operator = (const FullEnergyPotion& other)
{
	Item::operator=(other);

	return *this;
}

Item* FullEnergyPotion::Clone() const
{
	return new FullEnergyPotion(*this);
}

void FullEnergyPotion::Use(Player* Owner)
{
	Owner->RegenerateFullEnergy();
}

///////////////////////////////////////////////////////////////////////////
///////////////////////			MaxHealthPotion		///////////////////////
///////////////////////////////////////////////////////////////////////////

MaxHealthPotion::MaxHealthPotion(const unsigned int HP, const std::string& FilePath, const std::string& Name, const std::string& Description)
	: Item(FilePath, Name, Description), 
	  HP(HP)
{
	std::cout << "New MaxHealthPotion\n";
}

MaxHealthPotion::~MaxHealthPotion()
{
	std::cout << "Destruct MaxHealthPotion\n";
}

MaxHealthPotion& MaxHealthPotion::operator = (const MaxHealthPotion& other)
{
	Item::operator=(other);

	HP = other.HP;

	return *this;
}

Item* MaxHealthPotion::Clone() const
{
	return new MaxHealthPotion(*this);
}

void MaxHealthPotion::Use(Player* Owner)
{
	Owner->IncreaseMaxHealth(HP);
}

void MaxHealthPotion::Print(std::ostream& os) const
{
	Item::Print(os);

	os << "Increase Max Health : " << HP << '\n';
}

