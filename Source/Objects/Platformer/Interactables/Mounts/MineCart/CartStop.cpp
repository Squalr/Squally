#include "CartStop.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Physics/CollisionObject.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"
#include "Resources/SoundResources.h"

using namespace cocos2d;

const std::string CartStop::MapKey = "cart-stop";

CartStop* CartStop::create(ValueMap& properties)
{
	CartStop* instance = new CartStop(properties);

	instance->autorelease();

	return instance;
}

CartStop::CartStop(ValueMap& properties) : super(properties)
{
	this->cartStop = Sprite::create(ObjectResources::Physics_CartStop_CartStop);
	this->collision = CollisionObject::create(
		CollisionObject::createBox(Size(188.0f, 169.0f)),
		(CollisionType)PlatformerCollisionType::CartStop,
		CollisionObject::Properties(false, false)
	);
	this->colideSound = WorldSound::create();
	
	this->cartStop->setFlippedX(GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyFlipX, Value(false)).asBool());
	
	this->addChild(this->cartStop);
	this->addChild(this->collision);
	this->addChild(this->colideSound);
}

CartStop::~CartStop()
{
}
