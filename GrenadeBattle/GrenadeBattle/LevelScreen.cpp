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
}

void LevelScreen::ResetPlay()
{
}
