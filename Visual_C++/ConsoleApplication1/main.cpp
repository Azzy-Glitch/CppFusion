#include "Game.h"

int main()
{
    // Initialize random seed
    srand(static_cast<unsigned>(time(NULL)));

        // Create game object
    Game game;

    // Game loop
    while (game.running() && !game.getEndGame())
    {
        // Update the game
        game.update();
        // Render the game
        game.render();
    }

    return 0;
}
