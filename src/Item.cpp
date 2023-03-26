#include "Item.h"

#include <iostream>

Item::Item(const std::string& Name, const std::string& Description)
	: Name(Name), Description(Description)
{
	std::cout << "New Item\n";
}

Item::Item(const Item & other)
	: Name(other.Name), Description(other.Description)
{

}

Item::~Item()
{
	std::cout << "Destruct Item\n";
}

Item& Item::operator = (const Item& other)
{
	Name = other.Name;
	Description = other.Description;

	return *this;
}

std::ostream& operator << (std::ostream& os, const Item& i)
{
	std::cout << "Name : " << i.Name << '\n';
	std::cout << "Description : " << i.Description << '\n';

	return os;
}

