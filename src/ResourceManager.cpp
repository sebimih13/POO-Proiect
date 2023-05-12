#include "ResourceManager.h"

#include "ExceptionHierarchy.h"

#include <vector>

ResourceManager::ResourceManager()
{
	std::cout << "New Resource Manager\n";
}

ResourceManager::~ResourceManager()
{

}

void ResourceManager::Init()
{
	// Load Fonts
	if (!Fonts["Poppins"].loadFromFile("assets/fonts/PoppinsRegular.ttf"))
	{
		throw FontError("assets/fonts/PoppinsRegular.ttf");
	}

	// Load Textures
	std::vector<std::pair<std::string, std::string>> AllTextures = {
		std::make_pair("EndTurnNorm", "assets/others/endTurnButtonNorm.png"),
		std::make_pair("EndTurnHover", "assets/others/endTurnButtonHover.png"),
		std::make_pair("Background", "assets/others/Background1.png"),
		std::make_pair("EnergyBackground", "assets/others/EnergyBackground.png"),

		std::make_pair("Attack", "assets/others/attack.png"),
		std::make_pair("Shield", "assets/others/defend.png"),

		std::make_pair("Ironclad", "assets/characters/Ironclad.png"),

		std::make_pair("GremlinLeader", "assets/characters/GremlinLeader.png"),
		std::make_pair("Book", "assets/characters/Book-of-stabbing-pretty.png"),
		std::make_pair("Donu", "assets/characters/Donu.png"),
		std::make_pair("Slaver", "assets/characters/Slaver-blue-pretty.png"),
		std::make_pair("Slime", "assets/characters/slime.png"),
		std::make_pair("Guardian", "assets/characters/Spheric-guardian-pretty.png"),
		std::make_pair("Collector", "assets/characters/TheCollector.png"),
		std::make_pair("Time", "assets/characters/Time-eater-pretty.png"),
		std::make_pair("FinalBoss", "assets/characters/Champ.png"),

		std::make_pair("Strike", "assets/cards/Strike.png"),
		std::make_pair("Bludgeon", "assets/cards/Bludgeon.png"),
		std::make_pair("Defend", "assets/cards/Defend.png"),
		std::make_pair("Impervious", "assets/cards/Impervious.png"),

		std::make_pair("BloodPotion", "assets/items/BloodPotion.png"),
		std::make_pair("BlockPotion", "assets/items/BlockPotion.png"),
		std::make_pair("EnergyPotion", "assets/items/EnergyPotion.png"),
		std::make_pair("HeartofIron", "assets/items/HeartofIron.png")
	};

	for (auto& i : AllTextures)
	{
		if (!Textures[i.first].loadFromFile(i.second))
		{
			throw TextureError(i.second);
		}
	}
}

