export module MainMenuStateModule;

import MenuItemModule;
import MenuStateModule;
import MenuContextModule;

import LeaderboardMenuStateModule;
import OptionsMenuStateModule;

import <iostream>;

export class MainMenuState : public MenuState
{
public:
    MainMenuState(MenuContext& context);
    void handleSelect() override;

private:
    MenuContext& context;
};

MainMenuState::MainMenuState(MenuContext& context) : context(context) 
{
    sf::Font font;
    if (!font.loadFromFile("Assets/Fonts/arial.ttf"))
        std::cerr << "Error loading font" << std::endl;
    
    sf::Vector2f playPosition(100, 500);
    sf::Vector2f leaderboardPosition(100, 600);
    sf::Vector2f optionsPosition(100, 700);
    sf::Vector2f exitPosition(100, 800);

    menuItems.emplace_back("Play", font, playPosition);
    menuItems.emplace_back("Leaderboard", font, leaderboardPosition);
    menuItems.emplace_back("Options", font, optionsPosition);
    menuItems.emplace_back("Exit", font, exitPosition);
    menuItems[0].setSelected(true);
}


void MainMenuState::handleSelect()
{
    switch (selectedItemIndex)
    {
    case 0:
        //start game
        context.close();
        break;
    case 1:
        //open leaderboard
        context.changeState(std::make_shared<LeaderboardMenuState>(context));
        break;
    case 2:
        //open options
        context.changeState(std::make_shared<OptionsMenuState>(context));
        break;
    case 3:
        // Exit the game
        context.getWindow().close();
        context.close();
        break;
    }
}