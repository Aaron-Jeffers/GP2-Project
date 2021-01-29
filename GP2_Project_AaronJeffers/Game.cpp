#include "Game.h"
#include "GameCam.h"
#include <iostream>
#include <string>
#include <windows.h>

Vertex vertices[] = { Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(0.0, 0.0)),
					Vertex(glm::vec3(0, 0.5, 0), glm::vec2(0.5, 1.0)),
					Vertex(glm::vec3(0.5, -0.5, 0), glm::vec2(1.0, 0.0)) };

unsigned int indices[] = { 0, 1, 2 };

Tran transform;

bool KEYS[322];

Game::Game()
{
	gameState = GameState::PLAY;  //Sets gamestate to be playing
	GameDisplay* gameDisplay = new GameDisplay(); //new display
	Mesh* mesh1(), mesh2(),mesh3();	
}

Game::~Game()
{
}

void Game::play()
{
	initialiseSystems(); //STarts the game
	gameRunLoop(); //Runs the game
}

void Game::initialiseSystems()
{
	gameDisplay.initialiseDisplay(); //Initialises the display

	//Initialise audio sources
	collisionAsteroidShip = audio.loadSound("..\\res\\explosion.wav");
	collisionSunShip = audio.loadSound("..\\res\\sizzle.wav");
	thrust = audio.loadSound("..\\res\\thrust.wav");
	backGround = audio.loadSound("..\\res\\sonar.wav");

	//Initialise textures
	textureSun.initialise("..\\res\\sun.jpg"); 
	textureRocket.initialise("..\\res\\chrome.jpg"); 
	textureAsteroid.initialise("..\\res\\meteor.jpg"); 

	//Initialise shader
	shader.initialise("..\\res\\shader"); //new shader

	//Load models
	rocket.loadModel("..\\res\\rocket.obj");
	sun.loadModel("..\\res\\sphere.obj");
	asteroid1.loadModel("..\\res\\sphere.obj");
	asteroid2.loadModel("..\\res\\sphere.obj");
	asteroid3.loadModel("..\\res\\sphere.obj");

	//Initialise camera
	gameCam.initialiseCamera(glm::vec3(0, 0, -30), 70.0f, (float)gameDisplay.getWindowWidth() / gameDisplay.getWindowHeight(), 0.01f, 1000.0f);

	shader.initialise("..\\res\\shader");

	timer = 1.0f;

	//Initialise inputs
	for (int i = 0; i < 322; i++)
	{
		KEYS[i] = false;
	}
	
}

//Runs the game
void Game::gameRunLoop()
{
	while (gameState == GameState::PLAY)
	{
		input();
		draw();
		collision(rocket.getSpherePosition(),rocket.getSphereRadius(),sun.getSpherePosition(),sun.getSphereRadius(),asteroid1.getSpherePosition(),asteroid1.getSphereRadius(), asteroid2.getSpherePosition(), asteroid2.getSphereRadius(), asteroid3.getSpherePosition(), asteroid3.getSphereRadius());
		playSound(backGround, gameCam.getPosition());

		if (collision(rocket.getSpherePosition(), rocket.getSphereRadius(), sun.getSpherePosition(), sun.getSphereRadius(), asteroid1.getSpherePosition(), asteroid1.getSphereRadius(), asteroid2.getSpherePosition(), asteroid2.getSphereRadius(), asteroid3.getSpherePosition(), asteroid3.getSphereRadius()))
		{
			Sleep(700); //Pauses for 0.7 seconds to play audio and stop game before quitting
			std::cout << "You crashed your ship into " + collisionObject + ". You lost." << std::endl;
			gameState = GameState::QUIT;
		}
	}
}

//Handles user input
void Game::input()
{
	SDL_Event event;

	while (SDL_PollEvent(&event)) //get and process events
	{
		switch (event.type)
		{
		case SDL_QUIT:
			gameState = GameState::QUIT;
			break;

		case SDL_KEYDOWN:
			KEYS[event.key.keysym.sym] = true;
			break;
		case SDL_KEYUP:
			KEYS[event.key.keysym.sym] = false;
			break;
		}
	}

	//Sets velocities if user presses W A S D
	if ((KEYS[SDLK_w] && KEYS[SDLK_s]) || (KEYS[SDLK_w] == false && KEYS[SDLK_s] == false))
	{
		rocketSpeedY = 0;
	}
	else if (KEYS[SDLK_w])
	{
		rocketSpeedY = velocity;
	}
	else if (KEYS[SDLK_s])
	{
		rocketSpeedY = -velocity;
	}

	if ((KEYS[SDLK_a] && KEYS[SDLK_d]) || (KEYS[SDLK_a] == false && KEYS[SDLK_d] == false))
	{
		rocketSpeedX = 0;
	}
	else if (KEYS[SDLK_a])
	{
		rocketSpeedX = -velocity;
	}
	else if (KEYS[SDLK_d])
	{
		rocketSpeedX = velocity;
	}

	//Updates rocket position
	rocketPosX += rocketSpeedX;
	rocketPosY += rocketSpeedY;

	//Sets temporary rocket rotation equal to it's last rotation, used if no user input is detected as a tan function is used to set the rocket's rotation it defaults to zero degrees with an input value of zero i.e [tan^-1(0/0) = 0]
	float tempRotHold;
	tempRotHold = rocketRot;

	//If user input is detected rocket rotation is updated and audio is played
	if ((rocketSpeedX != 0) || (rocketSpeedY != 0))
	{			
		rocketRot = atan2(rocketSpeedX, rocketSpeedY);
		playSound(thrust, rocket.getSpherePosition());
    }
	//Else last rotation set is preserved
	else
	{		
		rocketRot = tempRotHold;
		stopSound(thrust);
	}
}

//Boolean to detect if a collision has occured
bool Game::collision(glm::vec3 rocketPos, float rocketRad, glm::vec3 sunPos, float sunRad, glm::vec3 astPos1, float astRad1, glm::vec3 astPos2, float astRad2, glm::vec3 astPos3, float astRad3)
{
	//Float values for distance between rocket and different game objects
	float distanceSun = distance(rocketPos, sunPos);
	float distanceAst1 = distance(rocketPos, astPos1);
	float distanceAst2 = distance(rocketPos, astPos2);
	float distanceAst3 = distance(rocketPos, astPos3);

	//Detects if collision occured between the rocket and the sun, plays appropriate audio, quits game and display appropriate loss message
	if ((distanceSun < rocketRad + sunRad))
	{
		glm::vec3 temp = gameCam.getPosition();
		audio.setlistener(temp, rocketPos); //add bool to mesh
		playSound(collisionSunShip, rocketPos);
		collisionObject = "the sun";
		return true;
	}
	//Detects if collision occured between the rocket and an asteroid, plays appropriate audio, quits game and display appropriate loss message
	else if ((distanceAst1 < rocketRad + astRad1) || (distanceAst2 < rocketRad + astRad2) || (distanceAst3 < rocketRad + astRad3))
	{
		glm::vec3 temp = gameCam.getPosition();
		audio.setlistener(temp, rocketPos); //add bool to mesh
		playSound(collisionAsteroidShip, rocketPos);
		collisionObject = "an asteroid";
		return true;
	}
	else
	{
		return false;
	}
}

//Returns distance value between two objects
float Game::distance(glm::vec3 a, glm::vec3 b)
{
	float dist = sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z));
	return dist;
}

//Plays game sound
void Game::playSound(unsigned int source, glm::vec3 position)
{
	ALint state;
	alGetSourcei(source, AL_SOURCE_STATE, &state);

	if (AL_PLAYING != state)
	{
		audio.playSound(source, position);
	}
}

//Stops game sound
void Game::stopSound(unsigned int source)
{
	audio.stopSound(source);
}

//Draws the game
void Game::draw()
{
	gameDisplay.wipeDisplay(0.0f, 0.0f, 0.0f, 1.0f);  //Clears the display

	transform.SetPosition(glm::vec3(-rocketPosX, rocketPosY, 0));  //Sets position of model
	transform.SetRotation(glm::vec3(0.0, 0.0, rocketRot));  //Sets rotation of model
	transform.SetScale(glm::vec3(0.08, 0.08, 0.08));  //Sets scale of model
	shader.BindTexture();  //Binds the texture
	shader.Update(transform, gameCam); //Updates shader of the model
	textureRocket.TextureBind(0);  //Binds the texture
	rocket.drawMesh();  //Draws mesh of model
	rocket.updateSphereVars(*transform.GetPosition(), 0.7f); //Updates collision sphere data of model


	//Subsequent functions operate the same as one above, albeit for different models with different variable

	transform.SetPosition(glm::vec3(0, 0, 0));
	transform.SetRotation(glm::vec3(0.0, timer, 0));
	transform.SetScale(glm::vec3(0.5, 0.5, 0.5));
	shader.BindTexture();
	shader.Update(transform, gameCam);
	textureSun.TextureBind(0);
	sun.drawMesh();
	sun.updateSphereVars(*transform.GetPosition(), 1.3f);

	transform.SetPosition(glm::vec3(sinf(timer) * 9, -cosf(timer) * 6, 0));
	transform.SetRotation(glm::vec3(0.0, timer, timer / 2));
	transform.SetScale(glm::vec3(0.15, 0.15, 0.15));
	shader.BindTexture();
	shader.Update(transform, gameCam);
	textureAsteroid.TextureBind(0);
	asteroid1.drawMesh();
	asteroid1.updateSphereVars(*transform.GetPosition(), 0.5f);

	transform.SetPosition(glm::vec3(-sinf(timer) * 8, cosf(timer) * 11, 0));
	transform.SetRotation(glm::vec3(0.0, timer, timer/2));
	transform.SetScale(glm::vec3(0.15, 0.15, 0.15));
	shader.BindTexture();
	shader.Update(transform, gameCam);
	textureAsteroid.TextureBind(0);
	asteroid2.drawMesh();
	asteroid2.updateSphereVars(*transform.GetPosition(), 0.5f);

	transform.SetPosition(glm::vec3(cosf(timer) * 14, sinf(timer) * 7, 0));
	transform.SetRotation(glm::vec3(0.0, timer, timer / 2));
	transform.SetScale(glm::vec3(0.15, 0.15, 0.15));
	shader.BindTexture();
	shader.Update(transform, gameCam);
	textureAsteroid.TextureBind(0);
	asteroid3.drawMesh();
	asteroid3.updateSphereVars(*transform.GetPosition(), 0.5f);

	timer = timer + 0.005f;

	glEnableClientState(GL_COLOR_ARRAY);
	glEnd();

	gameDisplay.switchBuffer();
}