#include "GameDisplay.h"
#include "Windows.h"

GameDisplay::GameDisplay()
{
	sdlWinRef = nullptr; //initialise to generate null access violation for debugging. 
	HWND h = GetDesktopWindow(); //Gets resolution of desktop  //////Note only tested on windows, not mac or linux////////
	RECT r; //Reference to desktop window points
	GetClientRect(h, &r); 

	windowWidth = r.right - r.left; //Sets window width equal to that of client's desktop width
	windowHeight = r.bottom - r.top; //Sets window width equal to that of client's desktop height
}

GameDisplay::~GameDisplay()
{
	SDL_GL_DeleteContext(glConRef); // delete context
	SDL_DestroyWindow(sdlWinRef); // delete window 
	SDL_Quit();
}


float GameDisplay::getWindowWidth() //Gets screen width
{ return windowWidth; } 

float GameDisplay::getWindowHeight() //Gets screen height
{ return windowHeight; }

void GameDisplay::returnError(std::string error)
{
	std::cout << error << std::endl;
	std::cout << "press any  key to quit...";
	int in;
	std::cin >> in;
	SDL_Quit();
}

void GameDisplay::switchBuffer()
{
	SDL_GL_SwapWindow(sdlWinRef); //swap buffers
}

void GameDisplay::wipeDisplay(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear colour and depth buffer 
}

void GameDisplay::initialiseDisplay()
{
	SDL_Init(SDL_INIT_EVERYTHING); //initalise everything

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8); //Min no of bits used to diplay colour
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);// set up z-buffer
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // set up double buffer   

	sdlWinRef = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, (int)windowWidth, (int)windowHeight, SDL_WINDOW_OPENGL); // create window

	if (sdlWinRef == nullptr)
	{
		returnError("window failed to create");  //Gives error if window doesn't create
	}

	glConRef = SDL_GL_CreateContext(sdlWinRef);

	if (glConRef == nullptr)
	{
		returnError("SDL_GL context failed to create");
	}

	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		returnError("GLEW failed to initialise");
	}

	glEnable(GL_DEPTH_TEST); //enable z-buffering 
	glEnable(GL_CULL_FACE); //dont draw faces that are not pointing at the camera

	glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
}