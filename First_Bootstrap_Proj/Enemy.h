#pragma once
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

	void Draw(aie::Renderer2D* renderer);
	void Update(float deltaTime);


	void SetTimer(float newTimer);
	float GetTimer();

	float GetPosX();
	void SetPosX(float newPosX);

	float GetPosY();
	void SetPosY(float newPosY);

private:
	float timer = 0.0f;
	float e_posX = 0.0f;
	float e_posY = 0.0f;
	aie::Texture* e_texture;
};

 