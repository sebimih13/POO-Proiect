#pragma once

#include <string>

#include <SFML/Graphics.hpp>

/** Forward Declarations */
class Player;

class Item
{
private:
	std::string FilePath;
	std::string Name;
	std::string Description;

	sf::Texture Texture;
	sf::Sprite Sprite;

	bool IsSelected;

public:
	/** Constructor */
	explicit Item(const std::string& FilePath, const std::string& Name = "None", const std::string& Description = "None");

	/** Copy Constructor */
	Item(const Item& other);

	/** Destructor */
	virtual ~Item();

	/** Operator = */
	Item& operator = (const Item& other);

	/** Operator << */
	friend std::ostream& operator << (std::ostream& os, const Item& i);

	/** Draw */
	void Draw(sf::RenderWindow& Window, const sf::Vector2f& Position, const sf::Vector2f& Scale = sf::Vector2f(1.0f, 1.0f));

	/** Update */
	void Update(const sf::Vector2i& MousePosition);

	/** Use Item */
	virtual void Use(Player* Owner) = 0;

	/** Getters */
	inline const bool GetIsSelected() const { return IsSelected; }
};

class HealthPotion : public Item
{
private:
	unsigned int HP;

public:
	/** Constructor */
	explicit HealthPotion(const unsigned int HP, const std::string& FilePath, const std::string& Name = "None", const std::string& Description = "None");

	/** Destructor */
	~HealthPotion() override;

	/** Use Item */
	void Use(Player* Owner) override;
};

class BlockPotion : public Item
{
private:
	unsigned int Block;

public:
	/** Constructor */
	explicit BlockPotion(const unsigned int Block, const std::string& FilePath, const std::string& Name = "None", const std::string& Description = "None");

	/** Destructor */
	~BlockPotion() override;

	/** Use Item */
	void Use(Player* Owner) override;
};

class FullEnergyPotion : public Item
{
public:
	/** Constructor */
	explicit FullEnergyPotion(const std::string& FilePath, const std::string& Name = "None", const std::string& Description = "None");

	/** Destructor */
	~FullEnergyPotion() override;

	/** Use Item */
	void Use(Player* Owner) override;
};

class MaxHealthPotion : public Item
{
private:
	unsigned int HP;

public:
	/** Constructor */
	explicit MaxHealthPotion(const unsigned int HP, const std::string& FilePath, const std::string& Name = "None", const std::string& Description = "None");

	/** Destructor */
	~MaxHealthPotion() override;

	/** Use Item */
	void Use(Player* Owner) override;
};

