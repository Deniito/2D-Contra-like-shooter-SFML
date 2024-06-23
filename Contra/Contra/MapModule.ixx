import <SFML/Graphics.hpp>;
import <iostream>;
import <vector>;
import <memory>;
import <string>;

import ObjectModule;

export module MapModule;

export class GameMap : public Object
{
public:
	GameMap();
	void move(const sf::Vector2f& directionVector,
				const float& time,
				const float& speed) override;
	float getTexturRecX();
private:
	

};

GameMap::GameMap()
{
	spriteSize = sf::Vector2i(1920, 1080);
	load(texture, "Assets/Map/Textures/Map.png");
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, spriteSize.x, spriteSize.y));
	sprite.setPosition(position);
}

float GameMap::getTexturRecX()
{
	return sprite.getTextureRect().left;
}

void GameMap::move(const sf::Vector2f& directionVector, const float& time, const float& speed)
{
	auto textureSize = sprite.getTexture()->getSize();
	auto textRect = sprite.getTextureRect();

	textRect.left += -directionVector.x * time * speed;

	if (textRect.left + textRect.width > textureSize.x)
		textRect.left = 0;
	else if (textRect.left  < 0) 
		textRect.left = textureSize.x - textRect.width;

	sprite.setTextureRect(textRect);

}