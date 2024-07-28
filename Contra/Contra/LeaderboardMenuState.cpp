import LeaderboardMenuStateModule;
import MainMenuStateModule;

import <filesystem>;
import <fstream>;
import <iostream>;

LeaderboardMenuState::LeaderboardMenuState(MenuContext& context) : context(context)
{
	sf::Font font;
	if (!font.loadFromFile("Assets/Fonts/arial.ttf"))
		std::cerr << "Error loading font" << std::endl;

	sf::Vector2f leaderboardPosition(100, 200);
	sf::Vector2f backPosition(100, 850);

	menuItems.emplace_back("Leaderboard", font, leaderboardPosition);
    loadLeaderboard(font);
	menuItems.emplace_back("Back", font, backPosition);

    menuItems.back().setSelected(true);
}
void LeaderboardMenuState::loadLeaderboard(const sf::Font& font)
{

    std::filesystem::path filepath("Assets/GameData/leaderboardData.txt");

    if (std::filesystem::exists(filepath)) 
    {
        std::ifstream file(filepath);

        if (!file.is_open()) {
            std::cerr << "Error opening file" << std::endl;
            return;
        }

        int i = 1;
        std::string line;
        while (std::getline(file, line)) {
            if (i > 10) break;

            std::string leaderboardEntry = std::to_string(i) + ": " + line;
            sf::Vector2f entryPosition(100, 250 + 50 * i);

            menuItems.emplace_back(leaderboardEntry, font, entryPosition);
            i++;
        }

        file.close();
    }
    else {
        std::cout << "File not found" << std::endl;
    }
}


void LeaderboardMenuState::handleSelect()
{
	switch (selectedItemIndex) 
	{
	case 11:
		context.changeState(std::make_shared<MainMenuState>(context));
		break;
	default:
		break;
	}
}
