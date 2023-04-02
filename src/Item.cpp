#include "Item.h"

#include <iostream>

Item::Item(const std::string& FilePath, const std::string& Name, const std::string& Description)
	: FilePath(FilePath), Name(Name), Description(Description)
{
	std::cout << "New Item\n";

	if (!Texture.loadFromFile(FilePath))		// TODO : ResourceManager
	{
		std::cout << "Can't load : " << FilePath << '\n';
	}

	Sprite.setTexture(Texture);
}

Item::Item(const Item & other)
	: FilePath(other.FilePath), Name(other.Name), Description(other.Description),
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

	Texture = other.Texture;
	Sprite = other.Sprite;

	return *this;
}

std::ostream& operator << (std::ostream& os, const Item& i)
{
	std::cout << "Name : " << i.Name << '\n';
	std::cout << "Description : " << i.Description << '\n';

	return os;
}

void Item::Draw(sf::RenderWindow& Window, const sf::Vector2f& Position, const sf::Vector2f& Scale)
{
	Sprite.setTexture(Texture);
	Sprite.setPosition(Position);
	Sprite.setScale(Scale);
	Window.draw(Sprite);
}

