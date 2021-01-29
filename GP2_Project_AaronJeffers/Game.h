#pragma once
#include <SDL\SDL.h>
#include <GL/glew.h>
#include "GameDisplay.h" 
#include "Shader.h"
#include "Mesh.h"
#include "ModelTexture.h"
#include "Tran.h"
#include "Audio.h";

enum class GameState {PLAY, QUIT};

class Game
{
public:
	Game();
	~Game();

	void play();

private:

	void initialiseSystems();  //Starts the game systems
	void input();  //Handles user inputs
	void gameRunLoop(); //Runs the game
	void draw();  //Draws the game
	bool collision(glm::vec3 rocketPos, float rocketRad, glm::vec3 sunPos, float sunRad, glm::vec3 astPos1, float astRad1, glm::vec3 astPos2, float astRad2, glm::vec3 astPos3, float astRad3); //Handles game collision
	void playSound(unsigned int source, glm::vec3 position); //Plays audio
	void stopSound(unsigned int source); //Stops audio
	float distance(glm::vec3 a, glm::vec3 b); //Keeps track of  distance between objects 
	string collisionObject;

	GameDisplay gameDisplay; 
	GameState gameState;
	Mesh rocket,sun,asteroid1,asteroid2,asteroid3;
	GameCam gameCam;
	ModelTexture textureRocket,textureAsteroid,textureSun;
	Shader shader;
	Sphere sphere;
	Audio audio;

	float timer;
	float rocketRot; //Rocket rotation
	float rocketSpeedX,rocketSpeedY,rocketPosX = 12,rocketPosY = 12; //Rocket speed and position variables
	float velocity = 0.03f;  //Rocket velocity
	unsigned int backGround, collisionAsteroidShip, collisionSunShip, thrust;  //Indexs for audio sources
};

