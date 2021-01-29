#pragma once
#include <SDL/SDL.h>
#include <GL\glew.h>
#include <iostream>
#include <string>
using namespace std;

class GameDisplay
{
public:
	GameDisplay();
	~GameDisplay();
	void initialiseDisplay();  //Initialises display
	void switchBuffer();
	void wipeDisplay(float r, float g, float b, float a);  //Resets the display

	float getWindowWidth(); //Gets the window width
	float getWindowHeight(); //Gets the window height

private:

	void returnError(std::string error); //Returns an error message if something doesn't load correctly 
	 
	SDL_GLContext glConRef; //global variable to hold the context
	SDL_Window* sdlWinRef; //holds pointer to out window
	float windowWidth;
	float windowHeight;
};