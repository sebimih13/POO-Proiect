#include "Character.h"

#include <iostream>

#include "Card.h"
#include "Item.h"

Character::Character(const std::string& Name, const unsigned int MaxHealth, const unsigned int MaxEnergy, const unsigned int Shield)
	: Name(Name), 
	  MaxHealth(MaxHealth), CurrentHealth(MaxHealth),
	  MaxEnergy(MaxEnergy), CurrentEnergy(MaxEnergy),
	  Shield(Shield)
{
	std::cout << "New Character\n";

	// Cards
	Card StrikeCard("assets/cards/Strike.png", "Strike", "Deal damage 10 damage", 2, CardType::Attack, CardRarity::Common);
	Card DefendCard("assets/cards/Defend.png", "Defend", "Gain 5 Block", 1, CardType::Skill, CardRarity::Common);
	Card HemokinesisCard("assets/cards/Hemokinesis.png", "Hemokinesis", "Hemokinesis ....", 0, CardType::Curse, CardRarity::Common);
	Card IronWaveCard("assets/cards/IronWave.png", "IronWave", "IronWave ....", 0, CardType::Skill, CardRarity::Common);

	Cards.push_back(StrikeCard);
	Cards.push_back(DefendCard);
	Cards.push_back(HemokinesisCard);
	Cards.push_back(IronWaveCard);

	// Items
	Item Potion("assets/items/BloodPotion.png", "Blood Potion", "Heal 20 HP");
	Item BlockPotion("assets/items/BlockPotion.png", "Block Potion", "Gain 20 Shield");
	Item EnergyPotion("assets/items/EnergyPotion.png", "Energy Potion", "Regenerates your Energy");
	Item HeartOfIronPotion("assets/items/HeartofIron.png", "Heart Of Iron", "Raise your max HP by 10");

	Items.push_back(Potion);
	Items.push_back(BlockPotion);
	Items.push_back(EnergyPotion);
	Items.push_back(HeartOfIronPotion);

	// Load Textures
	if (!EnergyBackgroundTexture.loadFromFile("assets/cards/EnergyBackground.png"))
	{
		std::cout << "Can't load : EnergyBackground.png \n";
	}

	EnergyBackgroundSprite.setTexture(EnergyBackgroundTexture);
}

Character::Character(const Character& other)
	: Name(other.Name),
	  MaxHealth(other.MaxHealth), CurrentHealth(other.CurrentHealth),
	  MaxEnergy(other.MaxEnergy), CurrentEnergy(other.CurrentEnergy),
	  Shield(other.Shield),
	  Cards(other.Cards), Items(other.Items)
{
	// TODO : EnergyBackground Texture + Sprite
} 

Character::~Character()
{
	std::cout << "Destruct Character\n";
}

Character& Character::operator = (const Character& other)
{
	Name = other.Name;

	MaxHealth = other.MaxHealth;
	CurrentHealth = other.CurrentHealth;

	MaxEnergy = other.MaxEnergy;
	CurrentEnergy = other.CurrentEnergy;

	Shield = other.Shield;

	Cards = other.Cards;
	Items = other.Items;

	// TODO : EnergyBackground Texture + Sprite

	return *this;
}

std::ostream& operator << (std::ostream& os, const Character& c)
{
	std::cout << "Name : " << c.Name << '\n';

	std::cout << "MaxHealth : " << c.MaxHealth << '\n';
	std::cout << "CurrentHealth : " << c.CurrentHealth << '\n';

	std::cout << "MaxEnergy : " << c.MaxEnergy << '\n';
	std::cout << "CurrentEnergy : " << c.CurrentEnergy << '\n';

	std::cout << "Shield : " << c.Shield << '\n';

	return os;
}

void Character::Draw(sf::RenderWindow& Window)
{
	// Load Font
	sf::Font Font;
	if (!Font.loadFromFile("assets/fonts/PoppinsRegular.ttf"))
	{
		std::cout << "Can't load font : PoppinsRegular \n";
	}

	// Draw Name
	sf::Text NameText;
	NameText.setFont(Font);
	NameText.setString(Name);
	NameText.setCharacterSize(24);
	NameText.setColor(sf::Color::White);
	NameText.setPosition(sf::Vector2f(20.0f, 20.0f));

	Window.draw(NameText);

	// Draw CurrentHealth + MaxHealth
	sf::Text HealthText;
	HealthText.setFont(Font);
	HealthText.setString("Health " + std::to_string(CurrentHealth) + "/" + std::to_string(MaxHealth));
	HealthText.setCharacterSize(24);
	HealthText.setColor(sf::Color::Red);

	float HealthTextPosX = 20.0f;
	float HealthTextPosY = NameText.getGlobalBounds().getPosition().y + NameText.getGlobalBounds().height + 30.0f;
	HealthText.setPosition(sf::Vector2f(HealthTextPosX, HealthTextPosY));

	Window.draw(HealthText);

	// Draw Shield
	sf::Text ShieldText;
	ShieldText.setFont(Font);
	ShieldText.setString("Shield " + std::to_string(Shield));
	ShieldText.setCharacterSize(24);
	ShieldText.setColor(sf::Color::Blue);

	float ShieldTextPosX = 20.0f;
	float ShieldTextPosY = HealthText.getGlobalBounds().getPosition().y + HealthText.getGlobalBounds().height + 20.0f;
	ShieldText.setPosition(sf::Vector2f(ShieldTextPosX, ShieldTextPosY));

	Window.draw(ShieldText);

	// Draw CurrentEnergy + MaxEnergy
	EnergyBackgroundSprite.setTexture(EnergyBackgroundTexture);

	float EnergyBackgroundSpritePosX = 400.0f - EnergyBackgroundTexture.getSize().y;
	EnergyBackgroundSprite.setPosition(sf::Vector2f(25.0f, EnergyBackgroundSpritePosX));

	Window.draw(EnergyBackgroundSprite);

	sf::Text EnergyText;
	EnergyText.setFont(Font);
	EnergyText.setString(std::to_string(CurrentEnergy) + "/" + std::to_string(MaxEnergy));
	EnergyText.setCharacterSize(30);
	EnergyText.setColor(sf::Color::Black);
	EnergyText.setStyle(sf::Text::Bold);

	float EnergyTextPosX = EnergyBackgroundSprite.getGlobalBounds().getPosition().x + EnergyBackgroundSprite.getGlobalBounds().width / 2.0f - EnergyText.getGlobalBounds().width / 2.0f;
	float EnergyTextPosY = EnergyBackgroundSprite.getGlobalBounds().getPosition().y + EnergyBackgroundSprite.getGlobalBounds().height / 2.0f - EnergyText.getGlobalBounds().height / 2.0f;
	EnergyText.setPosition(sf::Vector2f(EnergyTextPosX, EnergyTextPosY));
	
	Window.draw(EnergyText);

	// Draw Items
	for (unsigned int i = 0; i < Items.size() && i < 4; i++)	// TODO : change
	{
		Items[i].Draw(Window, ItemPosition[i]);
	}

	// Draw Cards
	for (unsigned int i = 0; i < Cards.size() && i < 5; i++)
	{
		Cards[i].Draw(Window, CardPosition[i]);
	}
}

void Character::AddCard(const Card& NewCard)
{
	Cards.push_back(NewCard);
}

void Character::AddItem(const Item& NewItem)
{
	Items.push_back(NewItem);
}

void Character::PrintCards() const
{
	for (const Card& c : Cards)
	{
		std::cout << c << '\n';
	}
}

void Character::PrintItems() const
{
	for (const Item& i : Items)
	{
		std::cout << i << '\n';
	}
}

void Character::IncreaseMaxHealth(const unsigned int Amount)
{
	MaxHealth += Amount;
}

void Character::Heal(const unsigned int Amount)
{
	CurrentHealth += Amount;
}

void Character::TakeDamage(const unsigned int Damage)
{
	CurrentHealth -= Damage;
}

void Character::ConsumeEnergy(const unsigned int Amount)
{
	CurrentEnergy -= Amount;
}

void Character::IncreaseShield(const unsigned int Amount)
{
	Shield += Amount;
}

