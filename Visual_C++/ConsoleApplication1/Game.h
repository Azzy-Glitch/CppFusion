#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include<sstream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

using namespace sf;
using namespace std;

class Game
{
private:
    // Main window
    RenderWindow* window; 
    // Video mode (resolution)
    VideoMode videoMode;
    // SFML event
    Event Ev;

    // Mouse Positions
    // Current mouse position
    Vector2i mousePosWindow; 
    Vector2f mousePosView;

    //Resources
    Font font;

    //Text
    Text  uiText;

    // Game Logic
    // Game points
    bool endGame;

    unsigned points;

    int health;
   
    float enemySpawnTimer;
    
    float enemySpawnTimerMax;
    
    int MaxEnemies;

    bool mouseHeld;

    // Game Objects
    // Vector to store enemies
    vector<RectangleShape> enemies;
   
    RectangleShape enemy;

    // Private functions
    
    void initVariables();
    
    void initWindow();

    void initFonts();

    void initText();
    
    void initEnemies();

public:
    // Constructor
    Game();

    // Destructor
    virtual ~Game();

    // Accessors
    // Check if the game is running
    const bool running() const; 
    const bool getEndGame() const;

    // Functions
    // Spawn a new enemy
    void spawnEnemy(); 
    
    void pollEvents();
   
    void updateMousePositions(); 

    void updateText();
  
    void updateEnemies();
   
    void update();

    void renderText(RenderTarget& target);
   
    void renderEnemies(RenderTarget& target);
    
    void render(); 
};
