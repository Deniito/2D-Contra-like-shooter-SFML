import <SFML/Graphics.hpp>;
import <iostream>;
import <vector>;
import <memory>;
import <ranges>;

export module ObjectModule;

export class Object
{
protected:
	sf::Vector2f position;

	sf::Sprite sprite;
	sf::Texture texture;
	sf::Vector2i spriteSize;

public:
	const sf::Sprite getSprite();
	virtual void update(const float& time,
		std::vector<std::unique_ptr<Object>>& objectVector,
		int& points,
		bool& plyState);

	virtual void draw(sf::RenderWindow& window);

	virtual void move(const sf::Vector2f& directionVector,
		const float& time,
		const float& speed);

	virtual void collisionHandle();

	void load(sf::Texture& textureToLoad, const std::string& path);

	void deleteObjectFromVector(std::vector<std::unique_ptr<Object>>& objectVector, Object* objToRemove);
};
const sf::Sprite Object::getSprite()
{
	return sprite;
}
void Object::update(const float& time,
	std::vector<std::unique_ptr<Object>>& objectVector,
	int& points,
	bool& plyState)
{
	//std::cout << "called update for object of class object" << std::endl;
}
void Object::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

void Object::move(const sf::Vector2f& directionVector, 
	const float& time, 
	const float& speed)
{
	position = sprite.getPosition();
	sprite.setPosition(position + directionVector * speed * time);
}

void Object::collisionHandle()
{
	std::cout << "called collisionHandle for object of class object" << std::endl;
}

void Object::load(sf::Texture& textureToLoad, const std::string& path)
{
	if (textureToLoad.loadFromFile(path))
		std::cout << path + " TXT LOADED" << std::endl;
	else
		std::cout << path + "TXT FAILED TO LOAD" << std::endl;
}

void Object::deleteObjectFromVector(std::vector<std::unique_ptr<Object>>& objectVector, Object* objToRemove)
{
	if (!objToRemove)
		return;

	auto it = std::ranges::find_if(objectVector, 
		[&](const std::unique_ptr<Object>& obj) 
		{
		return obj.get() == objToRemove;
		});

	if (it != objectVector.end())
		objectVector.erase(it);
}