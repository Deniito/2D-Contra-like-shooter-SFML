import <string>;
import <SFML/Graphics.hpp>;
import <vector>;

export module MenuItemModule;

export class MenuItem
{
public:
    MenuItem(const std::string& text);
	MenuItem(const std::string& text, const sf::Font& font, const sf::Vector2f& position);

	const bool& isSelected() const;
    void setSelected(bool isSelected);

	const std::string& getString();
	void setString(const std::string& text);

	sf::Text getItem();

private:
	sf::Vector2f position;
	std::string text;
    bool selected;
	sf::Font font;
};

MenuItem::MenuItem(const std::string& text)
{
	font.loadFromFile("Assets/Fonts/arial.ttf");


	this->selected = false;
	position = sf::Vector2f(0, 0);
}
MenuItem::MenuItem(const std::string& text, const sf::Font& font, const sf::Vector2f& position)
	: text(text), font(font), position(position) 
{
	this->selected = false;
}

void MenuItem::setSelected(bool isSelected)
{
	this->selected = isSelected;
}

const std::string& MenuItem::getString()
{
	return text;
}

void MenuItem::setString(const std::string& text)
{
	this->text = text;
}

const bool& MenuItem::isSelected() const
{
    return selected;
}

sf::Text MenuItem::getItem()
{
	sf::Text item;

	item.setFont(font);
	item.setString(text);
	item.setCharacterSize(40);
	item.setPosition(position);

	if (selected)
		item.setFillColor(sf::Color::Red);
	else
		item.setFillColor(sf::Color::White);

	return item;
}
