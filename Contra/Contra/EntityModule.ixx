import <SFML/Graphics.hpp>;
import <iostream>;
import <vector>;
import <memory>;

import ObjectModule;
import BulletModule;


export module EntityModule;

export class Entity : public Object
{
protected: 
	float speed;
	sf::Vector2i spriteSize;
	int health;
	sf::Texture bulletTexture;
	sf::Clock shootClock;
	sf::Clock JumpClock;
	float minTimeBetweenShots;
	float timeSinceLastShot;
	float minTimeBetweenJumps;
	float timeSinceLastJump;
	sf::Vector2i texturePosition;
	sf::Vector2f bulletSpawnOffset;	
	bool isGoingUpDuringJump;
	bool isJumping;

	
public:
	void shoot(const sf::Vector2f& direction,
		std::vector<std::unique_ptr<Object>>& objectVector,
		const int& angle, const sf::Vector2f& offset);

	void collisionHandle() override;

	void takeDmg();

	void jumpStart(const float& time);
	void jumpHandle(const float& time);

};
void Entity::shoot(const sf::Vector2f& direction,
	std::vector<std::unique_ptr<Object>>& objectVector,
	const int& angle, const sf::Vector2f& offset)
{
	timeSinceLastShot = shootClock.getElapsedTime().asMilliseconds();

	if (timeSinceLastShot > minTimeBetweenShots) 
	{
		objectVector.push_back(std::make_unique<Bullet>(direction, position, bulletTexture, angle, offset));

		shootClock.restart();
	}
}


void Entity::collisionHandle()
{
	takeDmg(); 
}

void Entity::takeDmg()
{
	health--;
}

void Entity::jumpHandle(const float& time)
{
	if (isGoingUpDuringJump)
	{
		if (486 > position.y)
		{
			position.y = 486;
			isGoingUpDuringJump = false;
			sprite.setPosition(position);
		}
		else
		{
			sprite.setPosition(position + sf::Vector2f(0, -2) * speed * time);
		}
	}
	else if (!isGoingUpDuringJump)
	{
		if (729>position.y)
			sprite.setPosition(position + sf::Vector2f(0, 2) * speed * time);
		else if (729 <= position.y)
		{
			position.y = 729;
			isJumping = false;
			sprite.setPosition(position);
		}
	}
}

void Entity::jumpStart(const float& time)
{
	timeSinceLastJump = JumpClock.getElapsedTime().asMilliseconds(); // Update the correct variable
	if (minTimeBetweenJumps < timeSinceLastJump && 729 == position.y)
	{
		isGoingUpDuringJump = true;
		isJumping = true;
		JumpClock.restart();
	}
}
