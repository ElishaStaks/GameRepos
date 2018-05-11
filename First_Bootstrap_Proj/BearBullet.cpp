#include "BearBullet.h"
#include <Texture.h>
#include "Input.h"
#include <Renderer2D.h>


//constructor
BearBullet::BearBullet()
{
	//creating a new texture with the location of the texture in my folders
	p2_bulletTexture = new aie::Texture("../bin/textures/Bullet_004.png");
}

//deconstructor
BearBullet::~BearBullet()
{
	//deletes every texture as it creates a new one 
	delete p2_bulletTexture;
}

//draw function
void BearBullet::Draw(aie::Renderer2D * spriteBatch)
{
	//takes the sprite amd draws the texture first, then the position x and y and it creates the size of the sprite
	spriteBatch->drawSprite(p2_bulletTexture, posx, posy, 100, 70);
}

//get pos x function
float BearBullet::GetPosX()
{
	//returns the posx variable
	return posx;
}

//set x position function
void BearBullet::SetPosX(float NewPosX)
{
	//position x is equla to the new position x
	posx = NewPosX;
}

//gets the position y
float BearBullet::GetPosY()
{
	//returns the pos y variable
	return posy;
}
//sets the pos y function
void BearBullet::SetPosY(float NewPosY)
{
	//pos y is equal to the new pos y
	posy = NewPosY;
}

//update function which updates every frame per second
void BearBullet::Update(float deltaTime)
{
	//adds 200 float times the update deltatime to the x position of the bullet which allows it to move
	//the 200 is the speed at which the bullet moves in the positive x position
	posx += 200.0f * deltaTime;
}
