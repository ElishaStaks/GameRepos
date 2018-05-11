#pragma once
#include <glm\vec2.hpp>
#include "PugBullet.h"
#include "Enemy.h"
#include <vector>

//namespace which contains the texture, input and renderer2D
namespace aie 
{
	class Renderer2D;
	class Input;
	class Texture;
};

//creating a struct for the bullets which has an onscreen bool and a bullet
struct p1_bulletMech
{
	//using 'p1_bullet allows you to access the contents of the PugBullet class which is the bullet contents
	PugBullet * p1_bullet;
	//checks if the bullet is on the screen or not
	bool onScreen;
};

//the struct frame includes a texture a delay and a struct frame of its contents
struct Frame {
	aie::Texture* m_texture;
	float m_delay;
	Frame(aie::Texture* texture, float delay) : m_texture(texture), m_delay(delay) {}
};

class Player
{
public:
	Player();
	//player constructor which passes in the players glm vec2 position
	Player(glm::vec2* pos);
	~Player();

	//adds the texture of the sprite and the delay of the animation
	void AddFrame(aie::Texture* texture, float delay);
	//this updates the player every frame and takes in the players input keys
	void Update(float deltaTime, aie::Input* input);
	//draws the players sprite and the position
	void Draw(aie::Renderer2D* renderer, glm::vec2* pos);
	//hit enemy function  which takles in the x and y axis of the enemies themseleves
	int HitEnemy(float targetX, float targetY); 
	//this fucntion clears the bullet when the player shoots whether it hits the enemies or goes out of scope and takes in a hit parameter when it hits
	void ClearKnife(int hit);
	//gets the position of the players x and y  
    glm::vec2* GetPos();

private:
	//this array allows you to access the contents of the bullet struct 
	p1_bulletMech* p1_array;
	//this creates the positioning of the player 
	glm::vec2* p1_pug;
	//this creates a vector of frames for animation
	std::vector<Frame> m_frames;
	//initialising variable ammo as an integer
	int ammo;
	//initialises the current frame for the animation as an integer
	int m_currentFrame;
	//initialises the speed of the player as a float which allows deeper detail
	float speed;
	//initialises the timer for the animation
	float m_timer;
	//creating a bool if the animation is playing or not
	bool isAnimate;
	//checks if the player is alive or not
	bool isAlive;
};