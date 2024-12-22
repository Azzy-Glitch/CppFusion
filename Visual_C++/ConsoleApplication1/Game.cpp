#include "Game.h"

// Initialize game variables
void Game::initVariables()
{
    this->window = nullptr;

    this->endGame = false;
    this->points = 0;
    this->health = 10;
    this->enemySpawnTimerMax = 20.f;
    this->enemySpawnTimer = this->enemySpawnTimerMax;
    this->MaxEnemies = 12;
}

// Initialize game window
void Game::initWindow()
{
    this->videoMode.height = 850;
    this->videoMode.width = 1200;

    this->window = new RenderWindow(this->videoMode, "My First Game", Style::Titlebar | Style::Close);
    this->window->setFramerateLimit(144);
}


void Game::initFonts()
{
    if (!this->font.loadFromFile("Font/open-sans/OpenSans-SemiboldItalic.ttf"))
    {
        cout << "ERROR::GAME::INITFONTS::Failed to load font!" << endl;
    }
}



void Game::initText()
{
    this->uiText.setFont(this->font);
    this->uiText.setCharacterSize(12);
    this->uiText.setFillColor(Color::White);
    this->uiText.setString("None");
}

// Initialize enemy shape
void Game::initEnemies()
{
    this->enemy.setPosition(10.f, 10.f);
    this->enemy.setSize(Vector2f(100.f, 100.f));
    this->enemy.setScale(Vector2f(0.5f, 0.5f));
    this->enemy.setFillColor(Color::Cyan);
    //this->enemy.setOutlineColor(Color::Green);
    //this->enemy.setOutlineThickness(1.f);
}

// Constructor
Game::Game()
{
    this->initVariables();
    this->initWindow();
    this->initFonts();
    this->initText();
    this->initEnemies();
}

// Destructor
Game::~Game()
{
    delete this->window;
}

// Check if the game is running
const bool Game::running() const
{
    return this->window->isOpen();
}


const bool Game::getEndGame() const
{
    return this->endGame;
}

// Spawn a new enemy
void Game::spawnEnemy()
{
    this->enemy.setPosition(
        static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
        0.f);

    //Randomize enemy type
    int type = rand() % 5;

    switch (type)
    {
    case 0:
        this->enemy.setFillColor(Color::Green);
        this->enemy.setSize(Vector2f(20.f, 20.f));
        break;
    case 1:
        this->enemy.setFillColor(Color::Blue);
        this->enemy.setSize(Vector2f(40.f, 40.f));
        break;
    case 2:
        this->enemy.setFillColor(Color::Red);
        this->enemy.setSize(Vector2f(60.f, 60.f));
        break;
    case 3:
        this->enemy.setFillColor(Color::Yellow);
        this->enemy.setSize(Vector2f(80.f, 80.f));
        break;
    case 4:
        this->enemy.setFillColor(Color::White);
        this->enemy.setSize(Vector2f(100.f, 100.f));
        break;
    default:
        this->enemy.setFillColor(Color::Cyan);
        this->enemy.setSize(Vector2f(100.f, 100.f));
        break;
    }

    this->enemies.push_back(this->enemy);
    // Debug statement
  /*  cout << "Spawned Enemy. Total enemies: " << this->enemies.size() << std::endl;*/
}

// Handle events
void Game::pollEvents()
{
    while (this->window->pollEvent(this->Ev))
    {
        switch (this->Ev.type)
        {
        case Event::Closed:
            this->window->close();
            break;
        case Event::KeyPressed:
            if (Ev.key.code == Keyboard::Escape)
                this->window->close();
            break;
        }
    }
}

// Update mouse positions
void Game::updateMousePositions()
{
    this->mousePosWindow = Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}


void Game::updateText()
{
    stringstream ss;

    ss << " Points: " << this->points << endl << " Health: " << this->health << endl ;

    this->uiText.setString(ss.str());
}

// Update enemies
void Game::updateEnemies()
{
    // Check if there are fewer enemies than the maximum allowed
    if (this->enemies.size() < this->MaxEnemies)
    {
        // Check if the spawn timer has reached the maximum value
        if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
        {
            // Spawn a new enemy
            this->spawnEnemy();
            // Reset the spawn timer
            this->enemySpawnTimer = 0.f;
        }
        else
        {
            // Increment the spawn timer
            this->enemySpawnTimer += 1.f;
        }
    }

    // Move each enemy down the screen
    for (int i = 0; i < this->enemies.size(); i++)
    {
        bool deleted = false;
        this->enemies[i].move(0.f, 1.f);

        if (this->enemies[i].getPosition().y > this->window->getSize().y)
        {
            this->enemies.erase(this->enemies.begin() + i);
            this->health -= 1;
            cout << " Health: " << this->health << endl;
        }
    }


    if (Mouse::isButtonPressed(Mouse::Left))
    {
        if (this->mouseHeld == false)
        {
            this->mouseHeld == true;

            bool deleted = false;

            for (int i = 0; i < this->enemies.size() && deleted == false; i++)
            {
                if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
                {

                    /*Gain Points*/
                    if (this->enemies[i].getFillColor() == Color::Green) 
                    {
                        this->points += 20;
                    }
                    else if (this->enemies[i].getFillColor() == Color::Blue)
                    {
                        this->points += 15;
                    } 
                    else  if (this->enemies[i].getFillColor() == Color::Red)
                    {
                        this->points += 12;
                    } 
                    else  if (this->enemies[i].getFillColor() == Color::Yellow)
                    {
                        this->points += 10;
                    } 
                    else  if (this->enemies[i].getFillColor() == Color::White)
                    {
                        this->points += 5;
                    }

                    cout << " Points: " << this->points << endl;


                    deleted = true;
                    this->enemies.erase(this->enemies.begin() + i);

                   
                }
            }

        }
        else
            this->mouseHeld == false;
    }
    
}

// Update the game
void Game::update()
{
    // Handle events
    this->pollEvents();
   
    if (this->endGame == false)
    {
        
        this->updateMousePositions();

        this->updateText();
        
        this->updateEnemies();
    }
}


void Game::renderText(RenderTarget& target)
{
    target.draw(this->uiText);
}

// Render enemies
void Game::renderEnemies(RenderTarget& target)
{
    for (auto& e : this->enemies)
    {
        target.draw(e);
    }

    //End Game
    if (this->health <= 0)
    {
        this->endGame = true;
    }
}

// Render the game
void Game::render()
{
    // Clear the window
    this->window->clear();
   
    this->renderEnemies(*this->window);

    this->renderText(*this->window);
    
    this->window->display();
}
