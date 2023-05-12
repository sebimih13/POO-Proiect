#pragma once

#include "Singleton.h"

#include <string>
#include <map>

#include <SFML/Graphics.hpp>

class ResourceManager : public Singleton<ResourceManager>
{
private:
	std::map<std::string, sf::Font> Fonts;
	std::map<std::string, sf::Texture> Textures;

public:
	/** Constructor */
	ResourceManager();

	/** Destructor */
	~ResourceManager();

	/** Initialize */
	void Init();

	/** Getters */
	inline sf::Font& GetFont(const std::string& Name) { return Fonts[Name]; }			// if daca nu exista
	inline sf::Texture& GetTexture(const std::string& Name) { return Textures[Name]; }	// if daca nu exista
};

