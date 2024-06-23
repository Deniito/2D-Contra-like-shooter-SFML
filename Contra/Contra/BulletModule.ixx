import <SFML/Graphics.hpp>;
import <iostream>;
import <vector>;
import <memory>;

import ObjectModule;

export module BulletModule;

export class Bullet : public Object
{
private:
	const int dmg;
	const float speed;
	const sf::Vector2f direction;
public:
	void update(const float& time,
		std::vector<std::unique_ptr<Object>>& objectVector,
		int& points,
		bool& plyState) override;

	Bullet(const sf::Vector2f& direction,
		const sf::Vector2f& startingPosition,
		const sf::Texture& bulletTexture,
		const int& angle,
		const sf::Vector2f& offset);
};
void Bullet::update(const float& time,
	std::vector<std::unique_ptr<Object>>& objectVector,
	int& points,
	bool& plyState)
{
	position = sprite.getPosition();
	if (position.x < 0 || position.x > 1920 || position.y > 1080 || position.y < 0  )
	{
		deleteObjectFromVector(objectVector, this);
		return;
	}
	else 
	{
		sprite.setPosition(position + direction * speed * time);
	}
	
	for (size_t i = 1; i < objectVector.size(); i++)
	{
		if (this != objectVector[i].get() && typeid(*objectVector[i]) == typeid(Bullet)) // Check if the object is a bullet
		{
			/*
			if (sprite.getGlobalBounds().intersects(objectVector[i]->getSprite().getGlobalBounds()))
			{
				
			}
			*/
		}
		else if (this != objectVector[i].get() && sprite.getGlobalBounds().intersects(objectVector[i]->getSprite().getGlobalBounds()))
		{
			objectVector.at(i)->collisionHandle();
			deleteObjectFromVector(objectVector, this);
		}
	}	
}
Bullet::Bullet(const sf::Vector2f& direction,
	const sf::Vector2f& startingPosition,
	const sf::Texture& bulletTexture,
	const int& angle,
	const sf::Vector2f& offset)
	: dmg(1),
	speed(1.6f),
	direction(direction)
{
	this->position = startingPosition + offset;
	this->texture = bulletTexture;

	this->spriteSize = sf::Vector2i(12, 12);
	this->sprite.setPosition(position);
	this->sprite.setTexture(texture);
	this->sprite.rotate(angle);
}

