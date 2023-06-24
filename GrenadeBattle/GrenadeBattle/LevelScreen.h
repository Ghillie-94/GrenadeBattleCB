#pragma once
#include "Screen.h"
#include "Game.h"
#include "AssetManager.h"
#include "Player.h"
#include "EndPanel.h"
#include "Floor.h"



// forward declarations for vector of pointers
class Grenade;
class Platform;

class Game;

class LevelScreen :
    public Screen
{
public:

    LevelScreen(Game* newGamePointer);

    void Update(sf::Time frameTime) override;
    void Draw(sf::RenderTarget& target) override;

    void TriggerEndState(bool win, std::string _winner);

    void AddGrenade();

private:
    void Restart();

    void ResetPlay();

    Player player1;
    Player player2;
    EndPanel endPanel;

    std::vector<Platform*> platforms;
    std::vector<Grenade*> grenades;

    bool gameRunning;
    sf::View camera;

    int player1Lives;
    int player2Lives;
    sf::Text player1LivesText;
    sf::Text player2LivesText;
    Floor floor;
};

