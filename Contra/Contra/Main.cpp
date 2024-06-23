import <SFML/Graphics.hpp>;
import <iostream>;
import <vector>;
import <memory>;

import ObjectModule;
import EntityModule;
import PlayerModule;
import GameLogicModule;

int main()
{
    GameLogic game;
    game.start();
    

    while (game.isRunning())
    {
        game.update();

        game.draw();
    }
    
    
    return 0;
}
