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
	float m_speed;
	

	bool m_isInHand;
	bool m_isOnGround;
public:
	Item(sf::Texture* texture = nullptr);
	virtual ~Item();

	virtual void update(const float& timePerFrame) = 0;
	void updateItemPosition(const sf::Vector2i& mousePosition,
		const sf::Vector2f& position, const sf::Vector2f& creatureSize);
	void inHandRotation(sf::Vector2i mousePosition);

	virtual void render(sf::RenderTarget* target) = 0;

	void setScale(float scaleX, float scaleY);
	void setItemPosition(sf::Vector2f position);

	void dragItemDown();
	void itemGroundCollision(Tile& collisionTile);

	const bool isItemOnGround() const;

	const sf::Vector2f getPosition() const;

};

