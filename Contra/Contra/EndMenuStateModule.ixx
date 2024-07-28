import MenuItemModule;
import MenuStateModule;
import MenuContextModule;

export module EndMenuStateModule;

export class EndMenuState : public MenuState
{
public:
    EndMenuState(MenuContext& context);
    void handleSelect() override;

private:
    MenuContext& context;
};

EndMenuState::EndMenuState(MenuContext& context) : context(context)
{
	sf::Font font;
	if (!font.loadFromFile("Assets/Fonts/arial.ttf"))
		std::cerr << "Error loading font" << std::endl;

	sf::Vector2f gameOverPosition(100, 500);
	sf::Vector2f backPosition(100, 600);

	menuItems.emplace_back("Game Over", font, gameOverPosition);
	menuItems.emplace_back("Back", font, backPosition);
	menuItems[0].setSelected(true);
}

void EndMenuState::handleSelect()
{
	switch (selectedItemIndex) {
	case 0:
		// Restart the game
		break;
	case 1:
		// Go back to the main menu
		context.close();
		break;
	default:
		break;
	}
}
