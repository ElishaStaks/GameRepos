#pragma once
#include <Texture.h>
#include "Input.h"
#include <Renderer2D.h>



class InfiniteBackground
{
public:
	InfiniteBackground();
	~InfiniteBackground();
	//updates the time every frame
	void Update(float time);
	//draws the sprite 
	void Draw(aie::Renderer2D* spriteBatch);

private:
	//creating a struct which has a position and a texture
	struct BGNode
	{
		float m_pos;
		aie::Texture* m_texture;
	};
	//creating a array of struct BGNODE
	//using 'm_array' will allow you to a access all the contents in the struct 
	BGNode* m_array;
};

