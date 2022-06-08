#pragma once
class Item
{
public:
	class Type
	{
	public:
		enum class Weapon
		{
			Rifle
		};
	};
private:

	void initSprite(sf::Texture* texture);
	void initVariables();
protected:
	sf::Sprite* m_item;
	sf::Vector2f m_itemPosition;
	float m_oscilationSpeed;
	

	bool m_isOnGround;
	bool m_isInHand;
public:
	Item(sf::Texture* texture = nullptr);
	virtual ~Item();

	virtual void update(const float& timePerFrame) = 0;
	void updateItemPosition(
		const sf::Vector2f& position, const sf::Vector2f& creatureSize);
	void inHandRotation(sf::Vector2f mousePosition);
	void onGroundOscilation();

	virtual void render(sf::RenderTarget* target) = 0;

	void setScale(float scaleX, float scaleY);
	void setItemPosition(sf::Vector2f position);

};

