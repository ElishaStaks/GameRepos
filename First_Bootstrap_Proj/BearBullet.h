#pragma once
//namespace which contains the texture, input and renderer2D
namespace aie
{
	class Texture;
	class Input;
	class Renderer2D;
}

class BearBullet
{
public:
	BearBullet();
	~BearBullet();
	//draws the sprite of the bear bullet
	void Draw(aie::Renderer2D* spriteBatch);
	//gets the position x of the bullet
	float GetPosX();
	//sets the position of x for the bullet and takes in a new position of float
	void SetPosX(float NewPosX);
	//gets the position y of the bullet
	float GetPosY();
	//sets the position of y axis and takes in a float of new position y
	void SetPosY(float NewPosY);

	//updates the bullet every frame
	void Update(float deltaTime);

private:
	//initialise posx as a float 0.0f
	float posx = 0.0f;
	//initialise posy as a float as well 
	float posy = 0.0f;
	//create a texture using the aie namespace
	aie::Texture* p2_bulletTexture;
};

