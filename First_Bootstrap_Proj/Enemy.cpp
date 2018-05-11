#include "Enemy.h"
#include <Renderer2D.h>
#include <Texture.h>


//constructor
Enemy::Enemy()
{
	//creates a new texture and find the location of that texture in the folder
	e_texture = new aie::Texture("../bin/textures/flameBallV2.png");
}

//deconstructor
Enemy::~Enemy()
{
	//makes the texture equal to nullptr 
	e_texture = nullptr;
	//then it deletes the texture
	delete e_texture;
}
//draw function
void Enemy::Draw(aie::Renderer2D * renderer)
{
	//takes the sprite and draws the dexture first then the position x and y then draws its size
	renderer->drawSprite(e_texture, e_posX, e_posY, 100.0f, 100.0f);
}

//update function
void Enemy::Update(float deltaTime)
{
	//takes the enemies position and moves it in the negative direction by a speed of 400 and times it to deltatime which is the update function every frame per second
	e_posX -= 400.0f * deltaTime;
}
//set timer function
void Enemy::SetTimer(float newTimer)
{
	//timer is equal to the new timer
	timer = newTimer;
}
//get timer function
float Enemy::GetTimer()
{
	//returns the timer variable
	//this timer is the rate at which it spaws and how fast it can move
	return timer;
}
//gets the position x
float Enemy::GetPosX()
{
	//it returns the position x variable 
	return e_posX;
}

//set pos x function and takes in the new pos x
void Enemy::SetPosX(float newPosX)
{
	//enemy pos x is equal to the new pos x
	e_posX = newPosX;
}

//get pos y function
float Enemy::GetPosY()
{
	//returns the initialised position y for the enemy
	return e_posY;
}

//set pos y function
void Enemy::SetPosY(float newPosY)
{
	//enemy pos y is equal to new pos y
	e_posY = newPosY;
}
