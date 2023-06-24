#include "LevelScreen.h"
#include "AssetManager.h"
#include "Game.h"
#include "Platform.h"
#include "Grenade.h"

LevelScreen::LevelScreen(Game* newGamePointer)
	:Screen(newGamePointer)
	,player1(this)
	,player2(this)
	,endPanel(newGamePointer->GetWindow())
	,platforms()
	,grenades()
	,gameRunning(true)
	,camera()
	,player1Lives()
	,player2Lives()
	,player1LivesText()
	,player2LivesText()
{
}

void LevelScreen::Update(sf::Time frameTime)
{
}

void LevelScreen::Draw(sf::RenderTarget& target)
{
}

void LevelScreen::TriggerEndState(bool win, std::string _winner)
{
}

void LevelScreen::AddGrenade()
{
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
	player1.SetPosition(30, 1000);
	player2.SetPosition(800, 1000);


	
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
