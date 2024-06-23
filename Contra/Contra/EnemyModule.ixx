import <SFML/Graphics.hpp>;
import <iostream>;
import <vector>;
import <memory>;
import <thread>;

import EntityModule;


export module EnemyModule;

export class Enemy : public Entity
{
void update(const float& time,
	std::vector<std::unique_ptr<Object>>& objectVector,
	int& points,
	bool& plyState) override;
public:
	void loadTexturesConcurrently();
	Enemy(const sf::Vector2f& position);
};

void Enemy::update(const float& time,
	std::vector<std::unique_ptr<Object>>& objectVector,
	int& points,
	bool& plyState)
{
	shoot(sf::Vector2f(-1, 0), objectVector, 180, bulletSpawnOffset);
	if (health <= 0)
	{
		deleteObjectFromVector(objectVector, this);
		points++;
	}
}

void Enemy::loadTexturesConcurrently()
{
	std::vector<std::thread> threads;

	threads.emplace_back(&Enemy::load, this, std::ref(texture), "Assets/Enemy/Textures/EnyTxt.png");
	threads.emplace_back(&Enemy::load, this, std::ref(bulletTexture), "Assets/Enemy/Textures/BltTxtEny.png");

	for (auto& thread : threads)
		thread.join();
}

Enemy::Enemy(const sf::Vector2f& position)
{
	bulletSpawnOffset = sf::Vector2f(-12, 42);
	timeSinceLastShot = 0;

	minTimeBetweenShots = 1500.0f;
	speed = 1.0f;
	health = 2;

	texturePosition = sf::Vector2i(0, 0);
	this->position = position;

	spriteSize = sf::Vector2i(100, 110);

	sprite.setPosition(position);
	loadTexturesConcurrently();
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, spriteSize.x, spriteSize.y));
}
