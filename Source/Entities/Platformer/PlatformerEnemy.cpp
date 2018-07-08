#include "PlatformerEnemy.h"

PlatformerEnemy::PlatformerEnemy(ValueMap* initProperties, std::string scmlResource, CategoryName categoryName, Size size, float scale, Vec2 collisionOffset)
	: PlatformerEntity(initProperties, scmlResource, categoryName, size, scale, collisionOffset)
{
}

PlatformerEnemy::~PlatformerEnemy()
{
}