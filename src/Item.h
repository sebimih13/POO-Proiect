#pragma once

#include <string>

#include <SFML/Graphics.hpp>

class Item
{
private:
	std::string FilePath;
	std::string Name;
	std::string Description;

	sf::Texture Texture;
	sf::Sprite Sprite;

public:
	/** Constructor */
	Item(const std::string& FilePath, const std::string& Name = "None", const std::string& Description = "None");

	/** Copy Constructor */
	Item(const Item& other);

	/** Destructor */
	~Item();

	/** Operator = */
	Item& operator = (const Item& other);

	/** Operator << */
	friend std::ostream& operator << (std::ostream& os, const Item& i);

	/** Draw */
	void Draw(sf::RenderWindow& Window, const sf::Vector2f& Position, const sf::Vector2f& Scale = sf::Vector2f(1.0f, 1.0f));

	// 3 functii
	/** Use Item */
	// void Use();
};

