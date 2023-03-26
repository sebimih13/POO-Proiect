#pragma once

#include <string>

class Item
{
private:
	std::string Name;
	std::string Description;

public:
	/** Constructor */
	Item(const std::string& Name = "None", const std::string& Description = "None");

	/** Copy Constructor */
	Item(const Item& other);

	/** Destructor */
	~Item();

	/** Operator = */
	Item& operator = (const Item& other);

	/** Operator << */
	friend std::ostream& operator << (std::ostream& os, const Item& i);

	// 3 functii
	/** Use Item */
	// void Use();
};

