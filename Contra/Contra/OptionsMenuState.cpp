import OptionsMenuStateModule;

import MainMenuStateModule;

OptionsMenuState::OptionsMenuState(MenuContext& context) : context(context)
{
	sf::Font font;
	if (!font.loadFromFile("Assets/Fonts/arial.ttf"))
		std::cerr << "Error loading font" << std::endl;

	sf::Vector2f difficultyPosition(100, 500);
	sf::Vector2f backPosition(100, 600);

	if (context.getIsDifficultyHard())
		menuItems.emplace_back("Difficulty: Hard", font, difficultyPosition);
	else
		menuItems.emplace_back("Difficulty: Normal", font, difficultyPosition);
	menuItems.emplace_back("Back", font, backPosition);
	menuItems[0].setSelected(true);
}

void OptionsMenuState::handleSelect()
{
	switch (selectedItemIndex) {
	case 0:
		if (menuItems[0].getString() == "Difficulty: Normal")
		{
			menuItems[0].setString("Difficulty: Hard");
			context.setIsDifficultyHard(true);
		}
		else
		{
			menuItems[0].setString("Difficulty: Normal");
			context.setIsDifficultyHard(false);
		}
		break;
	case 1:
		context.changeState(std::make_shared<MainMenuState>(context));
		break;
	default:
		break;
	}
}

