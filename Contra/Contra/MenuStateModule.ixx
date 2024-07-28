import MenuItemModule;

export module MenuStateModule;
import <SFML/Graphics.hpp>;

import <iostream>;

export class MenuState
{
public:
	virtual void handleSelect() = 0;
    void moveDown();
    void moveUp();
	void update(sf::Event event);
	void render(sf::RenderWindow& window);


protected:
	size_t selectedItemIndex = 0;
    std::vector<MenuItem> menuItems;
};

void MenuState::moveDown()
{
    if(selectedItemIndex < menuItems.size()-1)
	{
		menuItems[selectedItemIndex].setSelected(false);
		selectedItemIndex++;
		menuItems[selectedItemIndex].setSelected(true);
	}
    else
    {
        menuItems[selectedItemIndex].setSelected(false);
		selectedItemIndex = 0;
		menuItems[selectedItemIndex].setSelected(true);
    }
}

void MenuState::moveUp()
{
	if(selectedItemIndex > 0)
	{
		menuItems[selectedItemIndex].setSelected(false);
		selectedItemIndex--;
		menuItems[selectedItemIndex].setSelected(true);
	}
	else
	{
		menuItems[selectedItemIndex].setSelected(false);
		selectedItemIndex = menuItems.size() - 1;
		menuItems[selectedItemIndex].setSelected(true);
	}
}

void MenuState::update(sf::Event event)
{
	if (event.type == sf::Event::KeyReleased) 
	{
		switch (event.key.code) 
		{
		case sf::Keyboard::Up:
			moveUp();
			break;
		case sf::Keyboard::Down:
			moveDown();
			break;
		case sf::Keyboard::Enter:
			handleSelect();
			break;
		default:
			break;
		}
	}
}

void MenuState::render(sf::RenderWindow& windowPtr)
{
	windowPtr.clear(sf::Color::Black);
	for (auto& item : menuItems) 
	{
		windowPtr.draw(item.getItem());
	}
	windowPtr.display();
}