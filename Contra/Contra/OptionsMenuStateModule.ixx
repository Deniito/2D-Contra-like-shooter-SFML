export module OptionsMenuStateModule;

import MenuItemModule;
import MenuStateModule;
import MenuContextModule;

export class OptionsMenuState : public MenuState
{
public:
    OptionsMenuState(MenuContext& context);
    void handleSelect() override;

private:
    MenuContext& context;
};
