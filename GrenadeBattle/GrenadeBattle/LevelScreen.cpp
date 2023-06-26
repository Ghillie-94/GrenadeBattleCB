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
	,floor(sf::Vector2f(0,620))
	
{
	
	Restart();
}

void LevelScreen::Update(sf::Time frameTime)
{
	if (gameRunning)
	{
		
		player1.Update(frameTime);
		player2.Update(frameTime);
		
		for (int i = 0; i < grenades.size(); ++i)
		{
			if (grenades[i] != nullptr)
			{
				grenades[i]->Update(frameTime);
				grenades[i]->DamageCheck(player1);
				grenades[i]->DamageCheck(player2);

			}
			
		}
		floor.Update(frameTime);
		
		if (player1.CheckCollision(floor))
		{
			player1.SetColliding(true);
			player1.HandleCollision(floor);
		}
		if (player2.CheckCollision(floor))
		{
			player2.SetColliding(true);
			player2.HandleCollision(floor);
		}
		
	}
	else
	{
		endPanel.Update(frameTime);
		if (sf::Joystick::isButtonPressed(0, 7) || sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			Restart();
		}
	}
}

void LevelScreen::Draw(sf::RenderTarget& target)
{
	//update the camera based on the render target size 
	camera = target.getDefaultView();
	sf::Vector2f cameraCentre = camera.getCenter();
	cameraCentre.x = 540;
	cameraCentre.y = 960;
	camera.setCenter(cameraCentre);
	
	
	//update the render target to use the camera
	//target.setView(camera);
	
	
	for (int i = 0; i < platforms.size(); ++i)
	{
		if (platforms[i] != nullptr)
		{
			platforms[i]->Draw(target);
		}
	}

	
	player1.Draw(target);
	player2.Draw(target);
	floor.Draw(target);

	for (int i = 0; i < grenades.size(); ++i)
	{
		if (grenades[i] != nullptr)
		{
			grenades[i]->Draw(target);
			grenades[i]->DamageCheck(player1);
			grenades[i]->DamageCheck(player2);
		}
	}

	if (!gameRunning)
	{
		endPanel.Draw(target);
	}


}

void LevelScreen::TriggerEndState(bool win, std::string _loser)
{
	if (_loser == "player1")
	{
		endPanel.SetWinner("Player 2 Wins!");
		endPanel.StartAnimation();
	}
	else if (_loser == "player2")
	{
		endPanel.SetWinner("Player 1 Wins!");
		endPanel.StartAnimation();
	}
	gameRunning = false;
}

void LevelScreen::AddGrenade(std::string playerWhoLaunched)
{
	sf::Vector2f spawnPoint;
	sf::Vector2f initialVelocity;
	if (playerWhoLaunched == "player1")
	{
		spawnPoint = player1.GetPosition();
		initialVelocity = player1.GetInitialLaunchVelocity();
		grenades.push_back(new Grenade(spawnPoint, &player1, this, initialVelocity));
		std::cout << "player1 successfully launched a grenade!" << std::endl;
	}
	if (playerWhoLaunched == "player2")
	{
		spawnPoint = player2.GetPosition();
		initialVelocity = player2.GetInitialLaunchVelocity();
		grenades.push_back(new Grenade(spawnPoint, &player2, this, initialVelocity));
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
	player1.SetPosition(30, 580);
	player2.SetPosition(800, 580);

	platforms.push_back(new Platform(sf::Vector2f(96, 460)));
	platforms.push_back(new Platform(sf::Vector2f(112, 460)));
	platforms.push_back(new Platform(sf::Vector2f(208, 500)));
	platforms.push_back(new Platform(sf::Vector2f(224, 500)));
	platforms.push_back(new Platform(sf::Vector2f(352, 540)));
	platforms.push_back(new Platform(sf::Vector2f(368, 540)));
	platforms.push_back(new Platform(sf::Vector2f(496, 500)));
	platforms.push_back(new Platform(sf::Vector2f(512, 500)));
	platforms.push_back(new Platform(sf::Vector2f(640, 460)));
	platforms.push_back(new Platform(sf::Vector2f(656, 460)));
	floor.SetPosition(0, 620);
	

	//todo set gameRunning to true
	gameRunning = true;
}

void LevelScreen::ResetPlay()
{
	for (int i = 0; i < grenades.size(); ++i)
	{
		delete grenades[i];
		grenades[i] = nullptr;

	}
	grenades.clear();

	player1.SetPosition(30, 580);
	player2.SetPosition(800, 580);
}
