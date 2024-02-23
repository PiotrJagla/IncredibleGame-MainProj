#pragma once

class Item
{
public:
	enum class Type
	{
		Rifle
	};

private:

	void initSprite(sf::Texture* texture);
	void initVariables();
protected:
	sf::Sprite* m_item;
	sf::Vector2f m_itemPosition;
	float m_speed;

	Type m_itemType;
	
	sf::Vector2i* m_mousePositionMapPtr;

	bool m_isInHand;
	bool m_isOnGround;
public:
	Item(sf::Texture* texture = nullptr);
	virtual ~Item();

	virtual void update(const float& timePerFrame) = 0;
	void updateItemPosition(const sf::Vector2i& mousePosition,
		const sf::Vector2f& position, const sf::Vector2f& creatureSize);
	void inHandRotation(const sf::Vector2i& mousePosition);

	virtual void render(sf::RenderTarget* target) = 0;

	void setItemPosition(sf::Vector2f position);

	void dragItemDown();
	void itemGroundCollision(Tile& collisionTile);

	const bool& isItemOnGround() const;
	const bool& isItemEquiped() const;
	const sf::Vector2f getPosition() const;
	const Type& itemType() const;

	void setPointerToMousePosition(sf::Vector2i& mousePositionMap);
	void setItemType(Type itemType);
	void setScale(float scaleX, float scaleY);
};

