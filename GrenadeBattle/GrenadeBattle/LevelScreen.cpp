#include "LevelScreen.h"
#include "AssetManager.h"
#include "Game.h"
#include "Platform.h"
#include "Grenade.h"
#include <iostream>

LevelScreen::LevelScreen(Game* newGamePointer)
	:Screen(newGamePointer)
	,player1(this, 1)
	,player2(this, 2)
	,endPanel(newGamePointer->GetWindow())
	,platforms()
	,grenades()
	,gameRunning(true)
	,camera()
	,player1Lives()
	,player2Lives()
	,player1LivesText()
	,player2LivesText()
	,floor(sf::Vector2f(0,0))
	
{
}

void LevelScreen::Update(sf::Time frameTime)
{
	if (gameRunning)
	{

	}
}

void LevelScreen::Draw(sf::RenderTarget& target)
{
	//update the camera based on the render target size 
	camera = target.getDefaultView();
	
	//update the render target to use the camera
	target.setView(camera);

	for (int i = 0; i < platforms.size(); ++i)
	{
		if (platforms[i] != nullptr)
		{
			platforms[i]->Draw(target);
		}
	}
	player1.Draw(target);
	player2.Draw(target);

	for (int i = 0; i < grenades.size(); ++i)
	{
		if (grenades[i] != nullptr)
		{
			grenades[i]->Draw(target);
		}
	}

	if (!gameRunning)
	{
		endPanel.Draw(target);
	}


}

void LevelScreen::TriggerEndState(bool win, std::string _winner)
{
	if (_winner == "player1")
	{
		endPanel.SetWinner("Player 1 Wins!");
		endPanel.StartAnimation();
	}
	else if (_winner == "player2")
	{
		endPanel.SetWinner("Player 2 Wins!");
		endPanel.StartAnimation();
	}
	gameRunning = false;
}

void LevelScreen::AddGrenade(std::string playerWhoLaunched)
{
	sf::Vector2f spawnPoint;
	if (playerWhoLaunched == "player1")
	{
		spawnPoint = player1.GetPosition();
		grenades.push_back(new Grenade(spawnPoint, &player1, this));
		std::cout << "player1 successfully launched a grenade!" << std::endl;
	}
	if (playerWhoLaunched == "player2")
	{
		spawnPoint = player2.GetPosition();
		grenades.push_back(new Grenade(spawnPoint, &player2, this));
		std::cout << "player2 successfully launched a grenade!" << std::endl;
	}
}



void LevelScreen::Restart()
{
	//clear the level in case it has already been running
	for (int i = 0; i < grenades.size(); ++i)
	{
		delete grenades[i];
		grenades[i] = nullptr;

	}
	grenades.clear();

	for (int i = 0; i < platforms.size(); ++i)
	{
		delete platforms[i];
		platforms[i] = nullptr;
	}
	platforms.clear();

	//reset player lives
	player1.SetLives(3);
	player2.SetLives(3);

	//reset positions
	player1.SetPosition(30, 1079);
	player2.SetPosition(800, 1079);

	platforms.push_back(new Platform(sf::Vector2f(96, 1000)));
	platforms.push_back(new Platform(sf::Vector2f(112, 1000)));
	platforms.push_back(new Platform(sf::Vector2f(208, 950)));
	platforms.push_back(new Platform(sf::Vector2f(224, 950)));
	platforms.push_back(new Platform(sf::Vector2f(352, 900)));
	platforms.push_back(new Platform(sf::Vector2f(368, 900)));
	platforms.push_back(new Platform(sf::Vector2f(496, 950)));
	platforms.push_back(new Platform(sf::Vector2f(512, 950)));
	platforms.push_back(new Platform(sf::Vector2f(640, 1000)));
	platforms.push_back(new Platform(sf::Vector2f(656, 1000)));
	floor.SetPosition(0, 1080);
	
}

void LevelScreen::ResetPlay()
{
	for (int i = 0; i < grenades.size(); ++i)
	{
		delete grenades[i];
		grenades[i] = nullptr;

	}
	grenades.clear();

	player1.SetPosition(30, 1000);
	player2.SetPosition(800, 1000);
}
