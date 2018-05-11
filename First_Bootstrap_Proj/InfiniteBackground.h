#pragma once
#include <Texture.h>
#include "Input.h"
#include <Renderer2D.h>



class InfiniteBackground
{
public:
	InfiniteBackground();
	~InfiniteBackground();

	void Update(float time);
	void Draw(aie::Renderer2D* spriteBatch);

private:
	struct BGNode
	{
		float m_pos;
		aie::Texture* m_texture;
	};
	
	BGNode* m_array;
};

