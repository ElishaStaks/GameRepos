#pragma once
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

	void Draw(aie::Renderer2D* spriteBatch);

	float GetPosX();
	void SetPosX(float NewPosX);

	float GetPosY();
	void SetPosY(float NewPosY);

	void Update(float deltaTime);

private:
	float posx = 0.0f;
	float posy = 0.0f;
	aie::Texture* p2_bulletTexture;
};

