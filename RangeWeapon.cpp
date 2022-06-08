#include "headers.h"
#include "RangeWeapon.h"

RangeWeapon::RangeWeapon(sf::Texture* texture) 
	: Item{texture}
{


}

RangeWeapon::~RangeWeapon()
{
}

void RangeWeapon::update(const float& timePerFrame)
{


}

void RangeWeapon::render(sf::RenderTarget* target)
{

	target->draw(*m_item);
}

