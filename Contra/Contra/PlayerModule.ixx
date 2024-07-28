import <SFML/Graphics.hpp>;
import <iostream>;
import <vector>;
import <memory>;
import <thread>;


import EntityModule;
import MapModule;

export module PlayerModule;


export class Player : public Entity
{
public:
	Player(bool lowerHpForHardDifficulty);
private:
	sf::Texture healthPointsTexture;

	void draw(sf::RenderWindow& window) override;
	void update(const float& time,
		std::vector<std::unique_ptr<Object>>& objectVector,
		int& points,
		bool& plyState) override;

	void loadTexturesConcurrently();
	void moveWorld(std::vector<std::unique_ptr<Object>>& objectVector,
		const sf::Vector2f directionVector, const float& time);
	void drawHeart(sf::RenderWindow& window);
};

void Player::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
	drawHeart(window);

}

void Player::drawHeart(sf::RenderWindow& window)
{
	sf::Sprite heartSprite(healthPointsTexture);

	const int heartSize = 5; // Adjust size of hearts as needed
	const int spacing = 50; // Adjust spacing between hearts as needed

	for (int i = 1; i <= health; i++)
	{
		heartSprite.setPosition(i * (heartSize + spacing), 20); // Position hearts in the top-left corner
		window.draw(heartSprite);
	}
}

void Player::update(const float& time,
	std::vector<std::unique_ptr<Object>>& objectVector,
	int& points,
	bool& plyState)
{
	if (0 >= health)
	{
		plyState = false;
		this->deleteObjectFromVector(objectVector, this);
	}

	//std::cout << isJumping << " " << isGoingUpDuringJump << " " << position.y << std::endl;

	position = sprite.getPosition();

	//jump/drop
	if (!isJumping && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		jumpStart(time);
	
	if (isJumping)
		jumpHandle(time);

	//move
	if (!isJumping)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			int xTexture = 0;
			xTexture = (int)sprite.getPosition().x / 30 % 4;
			xTexture = xTexture * 100;
			sprite.setTextureRect(sf::IntRect(xTexture, 1, spriteSize.x, spriteSize.y));

			if (100 > position.x)
				moveWorld(objectVector, sf::Vector2f(1, 0), time);
			else
				sprite.setPosition(position + sf::Vector2f(-1, 0) * speed * time);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			int xTexture = 0;
			xTexture = (int)sprite.getPosition().x / 30 % 4;
			xTexture = xTexture * 100;
			sprite.setTextureRect(sf::IntRect(xTexture, 0, spriteSize.x, spriteSize.y));

			if (650 < position.x)
				moveWorld(objectVector, sf::Vector2f(-1, 0), time);
			else
				sprite.setPosition(position + sf::Vector2f(1, 0) * speed * time);
		}
		//shoot
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
		{
			shoot(sf::Vector2f(1, -1), objectVector, -45, bulletSpawnOffset);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
		{
			shoot(sf::Vector2f(1, 0), objectVector, 0, bulletSpawnOffset);
		}
	}

}

void Player::moveWorld(std::vector<std::unique_ptr<Object>>& objectVector,
	const sf::Vector2f directionVector, const float& time)
{
	int xTexture = 0;
	int positionX;
	for (auto& object : objectVector)
	{
		if (typeid(*object) == typeid(GameMap))
			positionX = object.get()->getSprite().getTextureRect().left;
		if (this != object.get())
			object.get()->move(directionVector, time, speed);
	}
	xTexture = positionX / 30 % 4;
	xTexture = xTexture * 100;
	sprite.setTextureRect(sf::IntRect(xTexture, 1, spriteSize.x, spriteSize.y));
	
}


void Player::loadTexturesConcurrently() 
{
	std::vector<std::thread> threads;

	threads.emplace_back(&Player::load, this, std::ref(texture), "Assets/Player/Textures/PlyTxt.png");
	threads.emplace_back(&Player::load, this, std::ref(bulletTexture), "Assets/Player/Textures/BltTxt.png");
	threads.emplace_back(&Player::load, this, std::ref(healthPointsTexture), "Assets/Player/Textures/HeartTexture.png");

	for (auto& thread : threads) {
		thread.join();
	}
}

//constructor(s)
Player::Player(bool lowerHpForHardDifficulty)
{
	isGoingUpDuringJump = false;
	isJumping = false;
	bulletSpawnOffset = sf::Vector2f(112, 34);
	timeSinceLastShot = 0;


	minTimeBetweenJumps = 500.0f;
	timeSinceLastJump = 0.0f;

	minTimeBetweenShots = 500.0f;
	speed = 1.0f;
	if (lowerHpForHardDifficulty)
		health = 3;
	else
		health = 5;

	texturePosition = sf::Vector2i(0, 0);

	position = sf::Vector2f(300, 729);

	spriteSize = sf::Vector2i(100, 110);

	sprite.setPosition(position);
	
	loadTexturesConcurrently();

	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, spriteSize.x, spriteSize.y));

}