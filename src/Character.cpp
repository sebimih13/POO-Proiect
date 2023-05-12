#include "Character.h"

#include "Card.h"
#include "Item.h"
#include "ExceptionHierarchy.h"
#include "ResourceManager.h"

#include <iostream>
#include <random>

///////////////////////////////////////////////////////////////////////////
///////////////////////			Character			///////////////////////
///////////////////////////////////////////////////////////////////////////

Character::Character(const std::string& TextureName, const std::string& Name, const unsigned int MaxHealth, const unsigned int Shield)
	: Name(Name), 
	  MaxHealth(MaxHealth), CurrentHealth(MaxHealth),
	  Shield(Shield)
{
	std::cout << "New Character : " << Name << '\n';

	// Set Sprites
	CharacterSprite.setTexture(ResourceManager::GetInstance().GetTexture(TextureName));
}

Character::Character(const Character& other)
	: Name(other.Name),
	  MaxHealth(other.MaxHealth), CurrentHealth(other.CurrentHealth),
	  Shield(other.Shield),
	  CharacterSprite(other.CharacterSprite)
{
	// CharacterSprite.setTexture(ResourceManager::GetInstance().GetTexture(other.TextureName)); // TODO : mai trb?
} 

Character::~Character()
{
	std::cout << "Destruct Character : " << Name << '\n';
}

Character& Character::operator = (const Character& other)
{
	Name = other.Name;

	MaxHealth = other.MaxHealth;
	CurrentHealth = other.CurrentHealth;

	Shield = other.Shield;

	CharacterSprite = other.CharacterSprite;
	// CharacterSprite.setTexture(ResourceManager::GetInstance().GetTexture(other.TextureName)); // TODO : mai trb?

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

void Character::TakeDamage(unsigned int Damage)
{
	// Take damage from Shield
	if (int(Shield) - int(Damage) <= 0)
	{
		Damage -= Shield;
		Shield = 0;
	}
	else
	{
		Shield -= Damage;
		return;
	}

	// Take damage from Health
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

Player::Player(const std::string& TextureName, const std::string& Name, const unsigned int MaxHealth, const unsigned int Shield, const unsigned int MaxEnergy)
	: Character(TextureName, Name, MaxHealth, Shield),
	  MaxEnergy(MaxEnergy), CurrentEnergy(MaxEnergy),
	  CurrentEnemy(nullptr)
{
	std::cout << "New Player\n";

	// Set Sprites
	EnergyBackgroundSprite.setTexture(ResourceManager::GetInstance().GetTexture("EnergyBackground"));

	// Set Character Sprite Position
	CharacterSprite.setPosition(sf::Vector2f(150.0f, 280.0f));
}

Player::Player(const Player& other)
	: Character(other),
	  MaxEnergy(other.MaxEnergy), CurrentEnergy(other.CurrentEnergy),
	  CurrentEnemy(other.CurrentEnemy),
	  EnergyBackgroundSprite(other.EnergyBackgroundSprite)
{
	EnergyBackgroundSprite.setTexture(ResourceManager::GetInstance().GetTexture("EnergyBackground"));

	for (std::shared_ptr<Card> c : other.CardDeck)
	{
		CardDeck.push_back(c->Clone());
	}

	for (std::shared_ptr<Card> c : other.Cards)
	{
		Cards.push_back(c->Clone());
	}

	for (std::shared_ptr<Card> c : other.UnusedCards)
	{
		UnusedCards.push_back(c->Clone());
	}

	for (std::shared_ptr<Item> i : other.Items)
	{
		Items.push_back(i->Clone());
	}
}

Player::~Player()
{
	std::cout << "Destruct Player\n";

	Items.clear();

	CardDeck.clear();
	Cards.clear();
	UnusedCards.clear();
}

Player& Player::operator = (const Player& other)
{
	Character::operator=(other);

	MaxEnergy = other.MaxEnergy;
	CurrentEnergy = other.CurrentEnergy;

	CurrentEnemy = other.CurrentEnemy;

	CardDeck.clear();
	for (std::shared_ptr<Card> c : other.CardDeck)
	{
		CardDeck.push_back(c->Clone());
	}

	Cards.clear();
	for (std::shared_ptr<Card> c : other.Cards)
	{
		Cards.push_back(c->Clone());
	}

	UnusedCards.clear();
	for (std::shared_ptr<Card> c : other.UnusedCards)
	{
		UnusedCards.push_back(c->Clone());
	}

	Items.clear();
	for (std::shared_ptr<Item> i : other.Items)
	{
		Items.push_back(i->Clone());
	}

	EnergyBackgroundSprite = other.EnergyBackgroundSprite;
	EnergyBackgroundSprite.setTexture(ResourceManager::GetInstance().GetTexture("EnergyBackground"));

	return *this;
}

void Player::Draw(sf::RenderWindow& Window)
{
	// Draw Sprite
	Window.draw(CharacterSprite);

	// Draw Name
	sf::Text NameText;
	NameText.setFont(ResourceManager::GetInstance().GetFont("Poppins"));
	NameText.setString(Name);
	NameText.setCharacterSize(24);
	NameText.setFillColor(sf::Color::White);
	NameText.setPosition(sf::Vector2f(20.0f, 20.0f));

	Window.draw(NameText);

	// Draw CurrentHealth + MaxHealth
	sf::Text HealthText;
	HealthText.setFont(ResourceManager::GetInstance().GetFont("Poppins"));
	HealthText.setString("Health " + std::to_string(CurrentHealth) + "/" + std::to_string(MaxHealth));
	HealthText.setCharacterSize(24);
	HealthText.setFillColor(sf::Color::Red);

	float HealthTextPosX = 20.0f;
	float HealthTextPosY = NameText.getGlobalBounds().getPosition().y + NameText.getGlobalBounds().height + 30.0f;
	HealthText.setPosition(sf::Vector2f(HealthTextPosX, HealthTextPosY));

	Window.draw(HealthText);

	// Draw Shield
	sf::Text ShieldText;
	ShieldText.setFont(ResourceManager::GetInstance().GetFont("Poppins"));
	ShieldText.setString("Shield " + std::to_string(Shield));
	ShieldText.setCharacterSize(24);
	ShieldText.setFillColor(sf::Color::Cyan);

	float ShieldTextPosX = 20.0f;
	float ShieldTextPosY = HealthText.getGlobalBounds().getPosition().y + HealthText.getGlobalBounds().height + 20.0f;
	ShieldText.setPosition(sf::Vector2f(ShieldTextPosX, ShieldTextPosY));

	Window.draw(ShieldText);

	// Draw CurrentEnergy + MaxEnergy
	EnergyBackgroundSprite.setTexture(ResourceManager::GetInstance().GetTexture("EnergyBackground"));	// TODO : DELETE?

	float EnergyBackgroundSpritePosX = 400.0f - ResourceManager::GetInstance().GetTexture("EnergyBackground").getSize().y;
	EnergyBackgroundSprite.setPosition(sf::Vector2f(25.0f, EnergyBackgroundSpritePosX));

	Window.draw(EnergyBackgroundSprite);

	sf::Text EnergyText;
	EnergyText.setFont(ResourceManager::GetInstance().GetFont("Poppins"));
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
	for (std::shared_ptr<Card> const& c : Cards)
	{
		c->Update(MousePosition);
	}
	
	// Update Items
	for (std::shared_ptr<Item> const& i : Items)
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
			if (std::shared_ptr<DamageCard> Card = std::dynamic_pointer_cast<DamageCard>(Cards[i]))
			{
				std::cout << "DamageCard : cast pointer reusit\n";
				Card->Use(CurrentEnemy.get());
			}
			else
			{
				std::cout << "DamageCard : cast pointer nereusit\n";
			}

			if (std::shared_ptr<ShieldCard> Card = std::dynamic_pointer_cast<ShieldCard>(Cards[i]))
			{
				std::cout << "ShieldCard : cast pointer reusit\n";
				Card->Use(this);
			}
			else
			{
				std::cout << "ShieldCard : cast pointer nereusit\n";
			}

			ConsumeEnergy(Cards[i]->GetEnergy());
			Cards.erase(Cards.begin() + i);
		}
	}

	// Check Items
	for (unsigned int i = 0; i < Items.size(); i++)
	{
		if (Items[i]->GetIsSelected())
		{
			Items[i]->Use(this);
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
		std::cout << "Not enough energy\n";
	}
	else
	{
		CurrentEnergy -= Amount;
	}
}

void Player::AddCard(std::shared_ptr<Card> const NewCard)
{
	CardDeck.push_back(NewCard);
}

void Player::AddItem(std::shared_ptr<Item> const NewItem)
{
	Items.push_back(NewItem);
}

void Player::ShuffleCards()
{
	UnusedCards = CardDeck;

	for (unsigned int i = 0; i < UnusedCards.size(); i++)
	{
		int r = i + (rand() % (UnusedCards.size() - i));		
		std::swap(UnusedCards[i], UnusedCards[r]);
	}
}

void Player::NextCards()
{
	Cards.clear();

	if (UnusedCards.size() < 5)
	{
		ShuffleCards();
	}

	if (UnusedCards.size() < 5)
	{
		// TODO : delete
		std::cout << "ERROR : UnusedCards < 5 \n";
	}

	for (int i = 0; i < 5; i++)
	{
		Cards.push_back(UnusedCards.back());
		UnusedCards.pop_back();
	}
}

void Player::Print(std::ostream& os) const
{
	Character::Print(os);

	os << "MaxEnergy : " << MaxEnergy << '\n';
	os << "CurrentEnergy : " << CurrentEnergy << '\n';

	os << "Card Deck : " << CardDeck.size() << '\n';
	for (unsigned int i = 0; i < CardDeck.size(); i++)
	{
		os << *CardDeck[i] << '\n';
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

Enemy::Enemy(const std::string& TextureName, const std::string& Name, const unsigned int MaxHealth, const unsigned int Shield, unsigned int MaxNextMove)
	: Character(TextureName, Name, MaxHealth, Shield), NextMove(EnemyMove::None), IncomingMove(0), MaxNextMove(MaxNextMove)
{
	std::cout << "New Enemy\n";

	// Set Character Sprite Position
	CharacterSprite.setPosition(sf::Vector2f(600.0f, 250.0f));

	// Set Sprites
	float AttackSpritePosX = CharacterSprite.getGlobalBounds().getPosition().x + CharacterSprite.getGlobalBounds().getSize().x / 2.0f - ResourceManager::GetInstance().GetTexture("Attack").getSize().x / 2.0f;
	float AttackSpritePosY = CharacterSprite.getGlobalBounds().getPosition().y - 150.0f;
	NextMoveSprite.setPosition(sf::Vector2f(AttackSpritePosX, AttackSpritePosY));
}

Enemy::Enemy(const Enemy& other)
	: Character(other),
	  NextMove(other.NextMove), IncomingMove(other.IncomingMove), MaxNextMove(other.MaxNextMove),
	  NextMoveSprite(other.NextMoveSprite)
{
	// NextMoveSprite.setTexture();		// TODO : mai trb?
}

Enemy::~Enemy()
{
	std::cout << "Destruct Enemy\n";
}

Enemy& Enemy::operator = (const Enemy& other)
{
	Character::operator = (other);

	NextMove = other.NextMove;
	IncomingMove = other.IncomingMove;
	MaxNextMove = other.MaxNextMove;

	NextMoveSprite = other.NextMoveSprite;
	// NextMoveSprite.setTexture();			// TODO : mai trb?

	return *this;
}

void Enemy::Draw(sf::RenderWindow& Window)
{
	// Draw Sprite
	Window.draw(CharacterSprite);
	
	// Draw Next Move
	if (NextMove != EnemyMove::None)
	{
		sf::Text NextMoveText;
		NextMoveText.setFont(ResourceManager::GetInstance().GetFont("Poppins"));
		NextMoveText.setCharacterSize(25);
		NextMoveText.setFillColor(sf::Color::White);
		NextMoveText.setString(std::to_string(IncomingMove));

		switch (NextMove)
		{
			case EnemyMove::Attack:
				NextMoveSprite.setTexture(ResourceManager::GetInstance().GetTexture("Attack"));
				break;

			case EnemyMove::Shield:
				NextMoveSprite.setTexture(ResourceManager::GetInstance().GetTexture("Shield"));
				break;

			default:
				break;
		}

		float NextMoveTextPosX = NextMoveSprite.getGlobalBounds().getPosition().x + 30.0f;
		float NextMoveTextPosY = NextMoveSprite.getGlobalBounds().getPosition().y + NextMoveSprite.getGlobalBounds().getSize().y - 60.0f;
		NextMoveText.setPosition(sf::Vector2f(NextMoveTextPosX, NextMoveTextPosY));

		Window.draw(NextMoveSprite);
		Window.draw(NextMoveText);
	}

	// Draw Name
	sf::Text NameText;
	NameText.setFont(ResourceManager::GetInstance().GetFont("Poppins"));
	NameText.setString(Name);
	NameText.setCharacterSize(24);
	NameText.setFillColor(sf::Color::White);
	NameText.setPosition(sf::Vector2f(1000.0f, 20.0f));

	Window.draw(NameText);

	// Draw CurrentHealth + MaxHealth
	sf::Text HealthText;
	HealthText.setFont(ResourceManager::GetInstance().GetFont("Poppins"));
	HealthText.setString("Health " + std::to_string(CurrentHealth) + "/" + std::to_string(MaxHealth));
	HealthText.setCharacterSize(24);
	HealthText.setFillColor(sf::Color::Red);

	float HealthTextPosX = 1000.0f;
	float HealthTextPosY = NameText.getGlobalBounds().getPosition().y + NameText.getGlobalBounds().height + 30.0f;
	HealthText.setPosition(sf::Vector2f(HealthTextPosX, HealthTextPosY));

	Window.draw(HealthText);

	// Draw Shield
	sf::Text ShieldText;
	ShieldText.setFont(ResourceManager::GetInstance().GetFont("Poppins"));
	ShieldText.setString("Shield " + std::to_string(Shield));
	ShieldText.setCharacterSize(24);
	ShieldText.setFillColor(sf::Color::Cyan);

	float ShieldTextPosX = 1000.0f;
	float ShieldTextPosY = HealthText.getGlobalBounds().getPosition().y + HealthText.getGlobalBounds().height + 20.0f;
	ShieldText.setPosition(sf::Vector2f(ShieldTextPosX, ShieldTextPosY));

	Window.draw(ShieldText);
}

void Enemy::Print(std::ostream& os) const
{
	Character::Print(os);

	os << "Next Move : ";
	switch (NextMove)
	{
		case EnemyMove::Attack: os << "Attack "; break;
		case EnemyMove::Shield: os << "Shield "; break;
		default:				os << "None ";	 break;
	}

	os << IncomingMove << '\n';
}

void Enemy::NewMove()
{
	// Choose a random move
	int r = rand() % 2;
	if (r == 0)
	{
		NextMove = EnemyMove::Attack;
	}
	else
	{
		NextMove = EnemyMove::Shield;
	}

	IncomingMove = 1 + rand() % MaxNextMove;
}

unsigned int Enemy::GetIncomingAttack()
{
	if (NextMove == EnemyMove::Attack)
	{
		return IncomingMove;
	}
	return 0;
}

unsigned int Enemy::GetIncomingShield()
{
	if (NextMove == EnemyMove::Shield)
	{
		return IncomingMove;
	}
	return 0;
}

