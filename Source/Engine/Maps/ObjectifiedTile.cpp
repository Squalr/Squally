#include "ObjectifiedTile.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

ObjectifiedTile* ObjectifiedTile::create(Sprite* sprite, ValueMap properties)
{
	ObjectifiedTile* instance = new ObjectifiedTile(sprite, properties);

	instance->autorelease();

	return instance;
}

ObjectifiedTile::ObjectifiedTile(Sprite* sprite, ValueMap properties) : super(properties)
{
	if (sprite != nullptr && sprite->getTexture() != nullptr)
	{
		this->innerSprite = Sprite::create(sprite->getTexture()->getPath(), sprite->getTextureRect());

		// Transfer position from sprite to this object
		Vec2 spritePosition = sprite->getPosition();
		this->setPosition(spritePosition);
		innerSprite->setPosition(Vec2::ZERO);

		this->setZSorted(true);

		this->addChild(this->innerSprite);
	}
}

ObjectifiedTile::~ObjectifiedTile()
{
}
