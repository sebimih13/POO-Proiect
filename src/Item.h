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

	bool IsSelected;

	sf::Texture Texture;
	sf::Sprite Sprite;

public:
	/** Constructor */
	explicit Item(const std::string& FilePath, const std::string& Name = "None", const std::string& Description = "None");

	/** Copy Constructor */
	explicit Item(const Item& other);

	/** Destructor */
	virtual ~Item();

	/** Operator = */
	Item& operator = (const Item& other);

	/** Operator << */
	friend std::ostream& operator << (std::ostream& os, const Item& i);

	/** Clone - Virtual Constructor */
	virtual std::shared_ptr<Item> Clone() const = 0;

	/** Draw */
	void Draw(sf::RenderWindow& Window, const sf::Vector2f& Position, const sf::Vector2f& Scale = sf::Vector2f(1.0f, 1.0f));

	/** Update */
	void Update(const sf::Vector2i& MousePosition);

	/** Use Item */
	virtual void Use(Player* const Owner) = 0;

	/** Getters */
	inline bool GetIsSelected() const { return IsSelected; }

protected:
	virtual void Print(std::ostream& os) const;
};

class HealthPotion : public Item
{
private:
	unsigned int HP;

public:
	/** Constructor */
	explicit HealthPotion(const unsigned int HP, const std::string& FilePath, const std::string& Name = "None", const std::string& Description = "None");

	/** Copy Constructor */
	explicit HealthPotion(const HealthPotion& other);

	/** Destructor */
	~HealthPotion() override;

	/** Operator = */
	HealthPotion& operator = (const HealthPotion& other);

	/** Clone - Virtual Constructor */
	std::shared_ptr<Item> Clone() const override;

	/** Use Item */
	void Use(Player* const Owner) override;

protected:
	void Print(std::ostream& os) const override;
};

class BlockPotion : public Item
{
private:
	unsigned int Block;

public:
	/** Constructor */
	explicit BlockPotion(const unsigned int Block, const std::string& FilePath, const std::string& Name = "None", const std::string& Description = "None");

	/** Copy Constructor */
	explicit BlockPotion(const BlockPotion& other);

	/** Destructor */
	~BlockPotion() override;

	/** Operator = */
	BlockPotion& operator = (const BlockPotion& other);

	/** Clone - Virtual Constructor */
	std::shared_ptr<Item> Clone() const override;

	/** Use Item */
	void Use(Player* const Owner) override;

protected:
	void Print(std::ostream& os) const override;
};

class FullEnergyPotion : public Item
{
public:
	/** Constructor */
	explicit FullEnergyPotion(const std::string& FilePath, const std::string& Name = "None", const std::string& Description = "None");

	/** Copy Constructor */
	explicit FullEnergyPotion(const FullEnergyPotion& other);

	/** Destructor */
	~FullEnergyPotion() override;

	/** Operator = */
	FullEnergyPotion& operator = (const FullEnergyPotion& other);

	/** Clone - Virtual Constructor */
	std::shared_ptr<Item> Clone() const override;

	/** Use Item */
	void Use(Player* const Owner) override;
};

class MaxHealthPotion : public Item
{
private:
	unsigned int HP;

public:
	/** Constructor */
	explicit MaxHealthPotion(const unsigned int HP, const std::string& FilePath, const std::string& Name = "None", const std::string& Description = "None");

	/** Copy Constructor */
	explicit MaxHealthPotion(const MaxHealthPotion& other);

	/** Destructor */
	~MaxHealthPotion() override;

	/** Operator = */
	MaxHealthPotion& operator = (const MaxHealthPotion& other);

	/** Clone - Virtual Constructor */
	std::shared_ptr<Item> Clone() const override;

	/** Use Item */
	void Use(Player* const Owner) override;

protected:
	void Print(std::ostream& os) const override;
};

