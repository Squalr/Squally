#include "BinderPendulumBlade.h"

#include "cocos/2d/CCDrawNode.h"
#include "cocos/base/ccTypes.h"
#include "cocos/base/CCValue.h"

#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/Traps/PendulumBlade/PendulumBlade.h"
#include "Objects/Platformer/MiniMap/MiniMapObject.h"

using namespace cocos2d;


BinderPendulumBlade* BinderPendulumBlade::create()
{
	BinderPendulumBlade* instance = new BinderPendulumBlade();

	instance->autorelease();

	return instance;
}

BinderPendulumBlade::BinderPendulumBlade() : super()
{
}

BinderPendulumBlade::~BinderPendulumBlade()
{
}

void BinderPendulumBlade::bindTo(MiniMapObject* miniMapObject, GameObject* gameObject)
{
	super::bindTo(miniMapObject, gameObject);

	this->miniMapObject->drawNode->setPositionY(-this->miniMapObject->drawNode->getContentSize().height / 2.0f);
	this->miniMapObject->rotatorNode->setPositionY(this->miniMapObject->drawNode->getContentSize().height / 2.0f);
	this->pendulumBlade = dynamic_cast<PendulumBlade*>(gameObject);
}

void BinderPendulumBlade::update(float dt)
{
	super::update(dt);

	if (this->pendulumBlade == nullptr)
	{
		return;
	}

	this->miniMapObject->rotatorNode->setRotation(this->pendulumBlade->bladeChain->getRotation());
}
