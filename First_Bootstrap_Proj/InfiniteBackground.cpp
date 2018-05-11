#include "InfiniteBackground.h"

InfiniteBackground::InfiniteBackground()
{
	m_array = new BGNode[2];

	for (int i = 0; i < 2; ++i)
	{
		m_array[i].m_texture = new aie::Texture("../bin/textures/BG/EmptyStarfield.jpg");
		m_array[i].m_pos = 640.0f + (4096.0f * i);     	
	}
}


InfiniteBackground::~InfiniteBackground()
{
	for (int i = 0; i < 2; ++i)
	{
		delete m_array[i].m_texture;
	}

	delete[] m_array;
}

void InfiniteBackground::Update(float time)
{
	//1
	m_array[0].m_pos -= 300.0f * time;

	if (m_array[0].m_pos < -2048)
	{
		m_array[0].m_pos += 4096 * 2;
	}

	//2
	m_array[1].m_pos -= 300.0f * time;

	if (m_array[1].m_pos < -2048)
	{
		m_array[1].m_pos += 4096 * 2;
	}


}

void InfiniteBackground::Draw(aie::Renderer2D * spriteBatch)
{
	spriteBatch->drawSprite(m_array[0].m_texture, m_array[0].m_pos, 2048);
	spriteBatch->drawSprite(m_array[1].m_texture, m_array[1].m_pos, 2048);
	
}
