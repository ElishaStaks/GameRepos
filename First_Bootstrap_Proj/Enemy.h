#pragma once

//namespace which contains the texture and renderer2D
namespace aie
{
	class Renderer2D;
	class Texture;

}

class Enemy
{
public:
	Enemy();
	~Enemy();
	//draws the sprite
	void Draw(aie::Renderer2D* renderer);
	//updates the sprite every frame
	void Update(float deltaTime);

	//sets the enemies timer which takes in a new timer
	void SetTimer(float newTimer);
	//gets the setted time of the enemy
	float GetTimer();
	//gets the position x of the enemy
	float GetPosX();
	//sets the x position of the enemy and takes in a new position in the parameters
	void SetPosX(float newPosX);
	//gets the y position of the enemy
	float GetPosY();
	//sets the position y of the enemy and takes in a new y position
	void SetPosY(float newPosY);

private:
	//initialise the variable timer as a float to start at 0.0f
	float timer = 0.0f;
	//initialises the enemies position x and sets it to 0.0f
	float e_posX = 0.0f;
	//initialises the enemies position y amnd sets it to 0.0f
	float e_posY = 0.0f;
	//creates a enemy texture using the aie namespace we made at the top
	aie::Texture* e_texture;
};

 