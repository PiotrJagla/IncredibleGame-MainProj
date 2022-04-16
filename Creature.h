#pragma once

class Creature
{
private:

	//Initialize private functions
protected:
	//Initialize protected functions
	void initSprite(sf::IntRect frameBounds, sf::Vector2f scale);
	void initTexture(std::string textureDirectory);

	sf::Sprite* m_sprite;
	sf::Texture* m_texture;
	sf::IntRect m_currentFrame;
	int m_HP;
	int m_movementSpeed;

public:
	//Constructors / Descructors
	Creature();
	virtual ~Creature();


	//Public functions
	virtual void update(const float& timePerFrame) = 0;
	virtual void updateMovement(const float& timePerFrame) = 0;
	virtual void moveInDirection(const float& timePerFrame, float Xdirection, float Ydirection) = 0;

	virtual void render(sf::RenderTarget* target) = 0;


	//Accesors

	//Modifiers

};