#include "Character.h"

#include <iostream>

#include "Card.h"
#include "Item.h"

///////////////////////////////////////////////////////////////////////////
///////////////////////			Character			///////////////////////
///////////////////////////////////////////////////////////////////////////

Character::Character(const std::string& Name, const unsigned int MaxHealth, const unsigned int Shield)
	: Name(Name), 
	  MaxHealth(MaxHealth), CurrentHealth(MaxHealth),
	  Shield(Shield)
{
	std::cout << "New Character\n";
}

Character::Character(const Character& other)
	: Name(other.Name),
	  MaxHealth(other.MaxHealth), CurrentHealth(other.CurrentHealth),
	  Shield(other.Shield),
	  CharacterTexture(other.CharacterTexture), CharacterSprite(other.CharacterSprite)
{

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

	Shield = other.Shield;

	CharacterTexture = other.CharacterTexture;
	CharacterSprite = other.CharacterSprite;

	return *this;
}

std::ostream& operator << (std::ostream& os, const Character& c)
{
	c.Print(os);
	return os;
}

void Character::Heal(const unsigned int Amount)
{
	if (CurrentHealth + Amount >= MaxHealth)
	{
		CurrentHealth = MaxHealth;
	}
	else
	{
		CurrentHealth += Amount;
	}
}

void Character::TakeDamage(const unsigned int Damage)
{
	if (int(CurrentHealth) - int(Damage) <= 0)
	{
		CurrentHealth = 0;
	}
	else
	{
		CurrentHealth -= Damage;
	}
}

void Character::IncreaseShield(const unsigned int Amount)
{
	Shield += Amount;
}

void Character::Print(std::ostream& os) const
{
	os << "Name : " << Name << '\n';

	os << "MaxHealth : " << MaxHealth << '\n';
	os << "CurrentHealth : " << CurrentHealth << '\n';

	os << "Shield : " << Shield << '\n';
}

///////////////////////////////////////////////////////////////////////////
///////////////////////			Player				///////////////////////
///////////////////////////////////////////////////////////////////////////

// Initialization of static const
const std::vector<sf::Vector2f> Player::CardPosition = {
		  sf::Vector2f(80.0f, 525.0f),
		  sf::Vector2f(300.0f, 525.0f),
		  sf::Vector2f(520.0f, 525.0f),
		  sf::Vector2f(740.0f, 525.0f),
		  sf::Vector2f(960.0f, 525.0f)
};

const std::vector<sf::Vector2f> Player::ItemPosition = {
		  sf::Vector2f(20.0f, 170.0f),
		  sf::Vector2f(70.0f, 170.0f),
		  sf::Vector2f(120.0f, 170.0f),
		  sf::Vector2f(170.0f, 170.0f)
};

Player::Player(const std::string& Name, const unsigned int MaxHealth, const unsigned int Shield, const unsigned int MaxEnergy)
	: Character(Name, MaxHealth, Shield),
	  MaxEnergy(MaxEnergy), CurrentEnergy(MaxEnergy),
	  CurrentEnemy(nullptr)
{
	std::cout << "New Player\n";

	// Load Textures
	if (!EnergyBackgroundTexture.loadFromFile("assets/others/EnergyBackground.png"))		// TODO : ResourceManager
	{
		std::cout << "Can't load : EnergyBackground.png \n";
	}

	EnergyBackgroundSprite.setTexture(EnergyBackgroundTexture);

	if (!CharacterTexture.loadFromFile("assets/characters/Ironclad.png"))      // TODO : Resource Manager
	{
		std::cout << "Can't load : assets/characters/Ironclad.png";
	}

	CharacterSprite.setTexture(CharacterTexture);
	CharacterSprite.setPosition(sf::Vector2f(150.0f, 280.0f));
}

Player::Player(const Player& other)
	: Character(other),
	  MaxEnergy(other.MaxEnergy), CurrentEnergy(other.CurrentEnergy),
	  CurrentEnemy(other.CurrentEnemy),
	  EnergyBackgroundTexture(other.EnergyBackgroundTexture), EnergyBackgroundSprite(other.EnergyBackgroundSprite)
{
	for (Card* c : other.Cards)
	{
		Cards.push_back(c->Clone());
	}

	for (Item* i : other.Items)
	{
		Items.push_back(i->Clone());
	}
}

Player::~Player()
{
	for (unsigned int i = 0; i < Items.size(); i++)
	{
		delete Items[i];
	}

	for (unsigned int i = 0; i < Cards.size(); i++)
	{
		delete Cards[i];
	}
}

Player& Player::operator = (const Player& other)
{
	Character::operator=(other);

	MaxEnergy = other.MaxEnergy;
	CurrentEnergy = other.CurrentEnergy;

	CurrentEnemy = other.CurrentEnemy;

	for (Card* c : other.Cards)
	{
		Cards.push_back(c->Clone());
	}

	for (Item* i : other.Items)
	{
		Items.push_back(i->Clone());
	}

	EnergyBackgroundTexture = other.EnergyBackgroundTexture;
	EnergyBackgroundSprite = other.EnergyBackgroundSprite;

	return *this;
}

void Player::Draw(sf::RenderWindow& Window)
{
	// Load Font
	sf::Font Font;
	if (!Font.loadFromFile("assets/fonts/PoppinsRegular.ttf"))
	{
		std::cout << "Can't load font : PoppinsRegular \n";
	}

	// Draw Sprite
	Window.draw(CharacterSprite);

	// Draw Name
	sf::Text NameText;
	NameText.setFont(Font);
	NameText.setString(Name);
	NameText.setCharacterSize(24);
	NameText.setFillColor(sf::Color::White);
	NameText.setPosition(sf::Vector2f(20.0f, 20.0f));

	Window.draw(NameText);

	// Draw CurrentHealth + MaxHealth
	sf::Text HealthText;
	HealthText.setFont(Font);
	HealthText.setString("Health " + std::to_string(CurrentHealth) + "/" + std::to_string(MaxHealth));
	HealthText.setCharacterSize(24);
	HealthText.setFillColor(sf::Color::Red);

	float HealthTextPosX = 20.0f;
	float HealthTextPosY = NameText.getGlobalBounds().getPosition().y + NameText.getGlobalBounds().height + 30.0f;
	HealthText.setPosition(sf::Vector2f(HealthTextPosX, HealthTextPosY));

	Window.draw(HealthText);

	// Draw Shield
	sf::Text ShieldText;
	ShieldText.setFont(Font);
	ShieldText.setString("Shield " + std::to_string(Shield));
	ShieldText.setCharacterSize(24);
	ShieldText.setFillColor(sf::Color::Blue);

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
	EnergyText.setFillColor(sf::Color::Black);
	EnergyText.setStyle(sf::Text::Bold);

	float EnergyTextPosX = EnergyBackgroundSprite.getGlobalBounds().getPosition().x + EnergyBackgroundSprite.getGlobalBounds().width / 2.0f - EnergyText.getGlobalBounds().width / 2.0f;
	float EnergyTextPosY = EnergyBackgroundSprite.getGlobalBounds().getPosition().y + EnergyBackgroundSprite.getGlobalBounds().height / 2.0f - EnergyText.getGlobalBounds().height / 2.0f;
	EnergyText.setPosition(sf::Vector2f(EnergyTextPosX, EnergyTextPosY));
	
	Window.draw(EnergyText);

	// Draw Items
	for (unsigned int i = 0; i < Items.size() && i < 4; i++)	// TODO : change
	{
		Items[i]->Draw(Window, ItemPosition[i]);
	}

	// Draw Cards
	for (unsigned int i = 0; i < Cards.size() && i < 5; i++)
	{
		Cards[i]->Draw(Window, CardPosition[i]);
	}
}

void Player::Update(const sf::Vector2i& MousePosition)
{
	// Update Cards
	for (Card* const c : Cards)
	{
		c->Update(MousePosition);
	}
	
	// Update Items
	for (Item* const i : Items)
	{
		i->Update(MousePosition);
	}
}

void Player::Select()
{
	// Check Cards
	for (unsigned int i = 0; i < Cards.size(); i++)
	{
		if (Cards[i]->GetIsSelected() && CurrentEnergy >= Cards[i]->GetEnergy())	// TODO : functie separata pt: CurrentEnergy >= Cards[i]->GetEnergy()
		{
			// Dynamic Cast
			if (DamageCard* Card = dynamic_cast<DamageCard*>(Cards[i])) 
			{
				std::cout << "DamageCard : cast pointer reusit\n";
				Card->Use(CurrentEnemy);
			}
			else
			{
				std::cout << "DamageCard : cast pointer nereusit\n";
			}

			if (ShieldCard* Card = dynamic_cast<ShieldCard*>(Cards[i]))
			{
				std::cout << "ShieldCard : cast pointer reusit\n";
				Card->Use(this);
			}
			else
			{
				std::cout << "ShieldCard : cast pointer nereusit\n";
			}

			ConsumeEnergy(Cards[i]->GetEnergy());
			delete Cards[i];
			Cards.erase(Cards.begin() + i);
		}
	}

	// Check Items
	for (unsigned int i = 0; i < Items.size(); i++)
	{
		if (Items[i]->GetIsSelected())
		{
			Items[i]->Use(this);
			delete Items[i];
			Items.erase(Items.begin() + i);
		}
	}
}

void Player::IncreaseMaxHealth(const unsigned int Amount)
{
	MaxHealth += Amount;
}

void Player::RegenerateFullEnergy()
{
	CurrentEnergy = MaxEnergy;
}

void Player::RegenerateEnergy(const unsigned int Amount)
{
	if (CurrentEnergy + Amount >= MaxEnergy)
	{
		CurrentEnergy = MaxEnergy;
	}
	else
	{
		CurrentEnergy += Amount;
	}
}

void Player::ConsumeEnergy(const unsigned int Amount)
{
	if (int(CurrentEnergy) - int(Amount) < 0)
	{
		std::cout << "Not enough energy\n";	// TODO : delete
	}
	else
	{
		CurrentEnergy -= Amount;
	}
}

void Player::AddCard(Card* const NewCard)
{
	Cards.push_back(NewCard);
}

void Player::AddItem(Item* const NewItem)
{
	Items.push_back(NewItem);
}

void Player::Print(std::ostream& os) const
{
	Character::Print(os);

	os << "MaxEnergy : " << MaxEnergy << '\n';
	os << "CurrentEnergy : " << CurrentEnergy << '\n';

	os << "Cards : " << Cards.size() << '\n';
	for (unsigned int i = 0; i < Cards.size(); i++)
	{
		os << *Cards[i] << '\n';
	}

	os << "Items : " << Items.size() << '\n';
	for (unsigned int i = 0; i < Items.size(); i++)
	{
		os << *Items[i] << '\n';
	}

	if (CurrentEnemy)
	{
		os << "Enemy target valid\n";
	}
}

///////////////////////////////////////////////////////////////////////////
///////////////////////			Enemy				///////////////////////
///////////////////////////////////////////////////////////////////////////

Enemy::Enemy(const std::string& Name, const unsigned int MaxHealth, const unsigned int Shield)
	: Character(Name, MaxHealth, Shield)
{
	std::cout << "New Enemy\n";

	// Load Textures
	if (!CharacterTexture.loadFromFile("assets/characters/GremlinLeader.png"))  // TODO : Resource Manager
	{
		std::cout << "Can't load : assets/characters/GremlinLeader.png";
	}

	CharacterSprite.setTexture(CharacterTexture);
	CharacterSprite.setPosition(sf::Vector2f(650.0f, 250.0f));
}

Enemy::Enemy(const Player& other)
	: Character(other)
{

}

Enemy::~Enemy()
{
	std::cout << "Destruct Enemy\n";
}

Enemy& Enemy::operator = (const Enemy& other)
{
	Character::operator=(other);

	// TODO : add

	return *this;
}

void Enemy::Draw(sf::RenderWindow& Window)
{
	// Load Font
	sf::Font Font;
	if (!Font.loadFromFile("assets/fonts/PoppinsRegular.ttf"))
	{
		std::cout << "Can't load font : PoppinsRegular \n";
	}

	// Draw Sprite
	Window.draw(CharacterSprite);

	// Draw Name
	sf::Text NameText;
	NameText.setFont(Font);
	NameText.setString(Name);
	NameText.setCharacterSize(24);
	NameText.setFillColor(sf::Color::White);
	NameText.setPosition(sf::Vector2f(1000.0f, 20.0f));

	Window.draw(NameText);

	// Draw CurrentHealth + MaxHealth
	sf::Text HealthText;
	HealthText.setFont(Font);
	HealthText.setString("Health " + std::to_string(CurrentHealth) + "/" + std::to_string(MaxHealth));
	HealthText.setCharacterSize(24);
	HealthText.setFillColor(sf::Color::Red);

	float HealthTextPosX = 1000.0f;
	float HealthTextPosY = NameText.getGlobalBounds().getPosition().y + NameText.getGlobalBounds().height + 30.0f;
	HealthText.setPosition(sf::Vector2f(HealthTextPosX, HealthTextPosY));

	Window.draw(HealthText);

	// Draw Shield
	sf::Text ShieldText;
	ShieldText.setFont(Font);
	ShieldText.setString("Shield " + std::to_string(Shield));
	ShieldText.setCharacterSize(24);
	ShieldText.setFillColor(sf::Color::Blue);

	float ShieldTextPosX = 1000.0f;
	float ShieldTextPosY = HealthText.getGlobalBounds().getPosition().y + HealthText.getGlobalBounds().height + 20.0f;
	ShieldText.setPosition(sf::Vector2f(ShieldTextPosX, ShieldTextPosY));

	Window.draw(ShieldText);
}

void Enemy::Print(std::ostream& os) const
{
	Character::Print(os);

	// TODO
	os << "Print Enemy \n";
}

