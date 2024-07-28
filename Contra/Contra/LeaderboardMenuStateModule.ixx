import MenuItemModule;
import MenuStateModule;
import MenuContextModule;

export module LeaderboardMenuStateModule;

export class LeaderboardMenuState : public MenuState
{
public:
    LeaderboardMenuState(MenuContext& context);
    void handleSelect() override;
    void loadLeaderboard(const sf::Font& font);

private:
    MenuContext& context;
};

