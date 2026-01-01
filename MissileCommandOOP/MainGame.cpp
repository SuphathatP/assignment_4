#define PLAY_IMPLEMENTATION
#include "Play.h"
#include "GameStateManager.h"

int DISPLAY_WIDTH = 240;
int DISPLAY_HEIGHT = 160;
int DISPLAY_SCALE = 4;

GameStateManager state;

// The entry point for a PlayBuffer program
void MainGameEntry( PLAY_IGNORE_COMMAND_LINE )
{
	Play::CreateManager( DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE );
	
	state.SetWorldSize(DISPLAY_WIDTH, DISPLAY_HEIGHT);
	state.NewGame();
}

// Called by PlayBuffer every frame (60 times a second!)
bool MainGameUpdate( float elapsedTime )
{
	Play::ClearDrawingBuffer( Play::cBlack );
	
	state.Update(elapsedTime);

	Play::PresentDrawingBuffer();
	return Play::KeyDown( KEY_ESCAPE );
}

// Gets called once when the player quits the game 
int MainGameExit( void )
{
	Play::DestroyManager();
	return PLAY_OK;
}
