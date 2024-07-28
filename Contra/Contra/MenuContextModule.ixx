import <SFML/Graphics.hpp>;
import <vector>;

import MenuStateModule;

export module MenuContextModule;

export class MenuContext {
public:
    MenuContext(sf::RenderWindow& window);
    void setState(std::shared_ptr<MenuState> state);
    void update(sf::Event event);
    void render();
    void run();
    void close();
    
    void changeState(std::shared_ptr<MenuState> state);

    sf::RenderWindow& getWindow();
    const bool getIsDifficultyHard();
    void setIsDifficultyHard(bool isHard);
private:
    std::shared_ptr<MenuState> currentState;
    sf::RenderWindow& window;

    bool shouldChangeState = false;
    std::shared_ptr<MenuState> nextState;

    bool isOpen = false;
    bool isDifficultyHard = false;
};

MenuContext::MenuContext(sf::RenderWindow& window)
    : window(window) {}

void MenuContext::setState(std::shared_ptr<MenuState> state)
{
	currentState = state;
}

void MenuContext::update(sf::Event event)
{
	currentState->update(event);
}

void MenuContext::render()
{
    if (currentState) {
        currentState->render(window);
    }
}

void MenuContext::run()
{
    isOpen = true;
    sf::Event event;
    while (isOpen)
    {
        while (getWindow().pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                getWindow().close();
                isOpen = false;
            }
            else
            {
                update(event);
            }
        }

        render();
        if (shouldChangeState)
        {
            setState(nextState);
            shouldChangeState = false;
            nextState.reset();
        }
    }
}

void MenuContext::close()
{
    isOpen = false;
}

void MenuContext::changeState(std::shared_ptr<MenuState> state)
{
    shouldChangeState = true;
    nextState = state;
}

sf::RenderWindow& MenuContext::getWindow()
{
    return window;
}

const bool MenuContext::getIsDifficultyHard()
{
    return isDifficultyHard;
}

void MenuContext::setIsDifficultyHard(bool isHard)
{
    this->isDifficultyHard = isHard;
}
