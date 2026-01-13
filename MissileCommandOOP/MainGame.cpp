#define PLAY_IMPLEMENTATION
#include "Play.h"
#include "constants.h"
#include "game.h"
#include "GameStateManager.h"

//GameStateManager state;
using namespace Play;

const Vector2f SCREEN_SIZE = Vector2f(DISPLAY_WIDTH, DISPLAY_HEIGHT);
const Vector2f SCREEN_MIDDLE = 0.5 * Vector2f(DISPLAY_WIDTH, DISPLAY_HEIGHT);

// The entry point for a PlayBuffer program
void MainGameEntry( PLAY_IGNORE_COMMAND_LINE )
{
	Play::CreateManager( DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE );

	init();
	//state.SetWorldSize(DISPLAY_WIDTH, DISPLAY_HEIGHT);
	//state.NewGame();
}

// Called by PlayBuffer every frame (60 times a second!)
bool MainGameUpdate( float elapsedTime )
{
	Play::ClearDrawingBuffer( Play::cBlack );

	//state.Update(elapsedTime);
	
	// ground
	DrawRect({ 0,0 }, { DISPLAY_WIDTH / 2, 16 }, cOrange, true);
	DrawLine({ 0,16 }, { DISPLAY_WIDTH / 2, 16 }, cGreen);

	drawCursor();
	drawBuildings();

	Play::PresentDrawingBuffer();
	return Play::KeyDown( KEY_ESCAPE );
}

// Gets called once when the player quits the game 
int MainGameExit( void )
{
	Play::DestroyManager();
	return PLAY_OK;
}
