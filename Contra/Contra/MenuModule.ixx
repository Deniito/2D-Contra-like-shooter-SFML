import <SFML/Graphics.hpp>;
import <iostream>;
import <vector>;
import <memory>;
import <cstdlib>;
import <filesystem>;
import <fstream>;
import <ranges>;
import <algorithm>;

import MenuContextModule;

export module MenuModule;


/////////////////////////////////////////////////////////////////////////
/*
export class Menu
{
public:
    Menu(float width, float height, sf::RenderWindow* window);
	void runMenu();
    void runEndMenu(const int& points);
    bool isDifficultyHard();

private:
    bool isOpen();
    
	std::vector<std::string> loadLeaderboard(std::string filename);

    void draw(const std::string& title, const std::vector<std::string>& dataToDraw, float positionOnX);

    void moveUp();
    void moveUp(const int& minValue);

    void moveDown(const int& minValue);

    int getSelectedItemIndex();
    void runOptionsMenu();
    void runLeaderboardMenu();
    void difficultyChange();
 
    sf::RenderWindow* windowPtr;

    std::vector<std::string> leaderboardMenuItems;
    std::vector<std::string> mainMenuItems;
    std::vector<std::string> optionsMenuItems;
    std::vector<std::string> EndMenuItems;


    int selectedItemIndex;
    bool open;
    sf::Vector2f screenSize;

    sf::Font font;
    sf::Text menuText;
};

Menu::Menu(float width, float height, sf::RenderWindow* window)
{
    windowPtr = window;

    screenSize.x = width;
    screenSize.y = height;

    font.loadFromFile("Assets/Fonts/arial.ttf");

    // Set up menu items
    mainMenuItems.push_back("Play");
	mainMenuItems.push_back("Leaderboard");
    mainMenuItems.push_back("Options");
    mainMenuItems.push_back("Exit");

    optionsMenuItems.push_back("Difficulty: Normal");
    optionsMenuItems.push_back("Back");

    EndMenuItems.push_back("Main Menu");
    EndMenuItems.push_back("Quit Game");

    
    menuText.setFont(font);
    menuText.setFillColor(sf::Color::White);
    menuText.setCharacterSize(40);

    // Set up initial position of menu
    menuText.setPosition(sf::Vector2f(screenSize.x / 2, screenSize.y / (mainMenuItems.size() + 1)));

    selectedItemIndex = 0;
}

std::vector<std::string> Menu::loadLeaderboard(std::string filename)
{
    filename = "Assets/GameData/" + filename + ".txt";

    std::filesystem::path filepath(filename);


    if (std::filesystem::exists(filepath))
    {

        std::ifstream file(filename);
		leaderboardMenuItems.clear();
        int i = 1;
        std::string line;
        while (std::getline(file, line))
        {
            leaderboardMenuItems.push_back(std::to_string(i) + ": " + line);
            i++;
            if (i == 11)
                break;
        }
		leaderboardMenuItems.push_back("Back");
    }
    else
    {
        std::cout << "File not found" << std::endl;
    }
	return leaderboardMenuItems;
}

void Menu::draw(const std::string& title, const std::vector<std::string>& dataToDraw, float positionOnX)
{
	menuText.setString(title);
	menuText.setFillColor(sf::Color::White);
	menuText.setOrigin(menuText.getLocalBounds().width / 2, menuText.getLocalBounds().height / 2);
	menuText.setPosition(positionOnX, screenSize.y/4);
	windowPtr->draw(menuText);

    for (int i = 0; i < dataToDraw.size(); i++)
    {

        menuText.setString(dataToDraw[i]);

        if (i == selectedItemIndex)
            menuText.setFillColor(sf::Color::Red);
        else
            menuText.setFillColor(sf::Color::White);

        menuText.setOrigin(menuText.getLocalBounds().width / 2, menuText.getLocalBounds().height);

        menuText.setPosition(sf::Vector2f(positionOnX, screenSize.y / 3 + (i + 1) * 1.2 * menuText.getCharacterSize()));

        windowPtr->draw(menuText);
    }
}

void Menu::moveUp() 
{
    if (selectedItemIndex - 1 >= 0)
        selectedItemIndex--;
}

void Menu::moveUp(const int& maxValue)
{
    if (selectedItemIndex - 1 >= maxValue)
        selectedItemIndex--;
}

void Menu::moveDown(const int& minValue)
{
    if (selectedItemIndex + 1 < minValue)
        selectedItemIndex++;
}

bool Menu::isDifficultyHard()
{
	return optionsMenuItems[0] == "Difficulty: Hard";
}

int Menu::getSelectedItemIndex() 
{
	return selectedItemIndex;
}

void Menu::runMenu() 
{
    selectedItemIndex = 0;

    open = true;
    while (isOpen()) 
    {
        sf::Event event;
        while (windowPtr->pollEvent(event)) 
        {
            switch (event.type) 
            {
            case sf::Event::KeyReleased:
                switch (event.key.code) 
                {
                case sf::Keyboard::Up:
                    moveUp();
                    break;
                case sf::Keyboard::Down:
                    moveDown(mainMenuItems.size());
                    break;
                case sf::Keyboard::Return:
                    // Placeholder for handling menu selection
                    switch (getSelectedItemIndex()) 
                    {
                    case 0:
                        open = false;
                        break;
                    case 1:
						runLeaderboardMenu();
                        selectedItemIndex = 0;
                        break;
                    case 2:
                        runOptionsMenu();
                        selectedItemIndex = 0;
                        break;
                    case 3:
                        std::exit(0);
                        break;
                    }
                    break;
                }
                break;
            case sf::Event::Closed:
                std::exit(0);
                break;
            }
        }

        windowPtr->clear(sf::Color::Black);
        draw("Main Menu", mainMenuItems, screenSize.x/10);
        windowPtr->display();
    }
    open = false;
}

void Menu::runOptionsMenu()
{
    selectedItemIndex = 0;

    while (isOpen())
    {
        sf::Event event;
        while (windowPtr->pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::KeyReleased:
                switch (event.key.code)
                {
                case sf::Keyboard::Up:
                    moveUp();
                    break;
                case sf::Keyboard::Down:
                    moveDown(optionsMenuItems.size());
                    break;
                case sf::Keyboard::Return:
                    // Placeholder for handling menu selection
                    switch (getSelectedItemIndex())
                    {
                    case 0:
                        difficultyChange();
                        break;
                    case 1:
                        return;
                        break;
                    }
                    break;
                }
                break;
            case sf::Event::Closed:
                std::exit(0);
                break;
            }
        }

        windowPtr->clear(sf::Color::Black);
        draw("Options", optionsMenuItems, screenSize.x/10);
        windowPtr->display();
    }
}

void Menu::runLeaderboardMenu()
{
    selectedItemIndex = 10;

    while (isOpen())
    {
        sf::Event event;
        while (windowPtr->pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::KeyReleased:
                switch (event.key.code)
                {
                case sf::Keyboard::Up:
                    moveUp(10);
                    break;
                case sf::Keyboard::Down:
                    moveDown(11);
                    break;
                case sf::Keyboard::Return:
                    switch (getSelectedItemIndex())
                    {
                    case 10:
                        return;
                        break;
                    }
                    break;
                }
                break;
            case sf::Event::Closed:
                std::exit(0);
                break;
            }
        }

		leaderboardMenuItems = loadLeaderboard("leaderboardData");

        windowPtr->clear(sf::Color::Black);
        draw("Leaderboard: ", leaderboardMenuItems, screenSize.x/2);
        windowPtr->display();
        
    }
}

void Menu::runEndMenu(const int& points)
{
    selectedItemIndex = 0;

    open = true;
    std::string titleForEndMenu = "GAME OVER\nPoints: " + std::to_string(points);
    while (isOpen())
    {
        sf::Event event;
        while (windowPtr->pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::KeyReleased:
                switch (event.key.code)
                {
                case sf::Keyboard::Up:
                    moveUp();
                    break;
                case sf::Keyboard::Down:
                    moveDown(EndMenuItems.size());
                    break;
                case sf::Keyboard::Return:
                    switch (getSelectedItemIndex())
                    {
                    case 0:
                        return;
                        break;
                    case 1:
                        std::exit(0);
                        break;
                    }
                    break;
                }
                break;
            case sf::Event::Closed:
                std::exit(0);
                break;
            }
        }
        windowPtr->clear(sf::Color::Black);
        draw(titleForEndMenu,EndMenuItems, screenSize.x/2);
        windowPtr->display();
    }
    open = false;
}

bool Menu::isOpen() 
{
	return open;
}

void Menu::difficultyChange()
{
    if (optionsMenuItems[0] == "Difficulty: Normal")
        optionsMenuItems[0] = "Difficulty: Hard";
    else
        optionsMenuItems[0] = "Difficulty: Normal";
}
*/

