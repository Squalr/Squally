#include "BinderMechanicalFlail.h"

#include "cocos/2d/CCDrawNode.h"
#include "cocos/base/ccTypes.h"
#include "cocos/base/CCValue.h"

#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/Traps/MechanicalFlail/MechanicalFlail.h"
#include "Objects/Platformer/MiniMap/MiniMapObject.h"

using namespace cocos2d;


BinderMechanicalFlail* BinderMechanicalFlail::create()
{
	BinderMechanicalFlail* instance = new BinderMechanicalFlail();

	instance->autorelease();

	return instance;
}

BinderMechanicalFlail::BinderMechanicalFlail() : super()
{
}

BinderMechanicalFlail::~BinderMechanicalFlail()
{
}

void BinderMechanicalFlail::bindTo(MiniMapObject* miniMapObject, GameObject* gameObject)
{
	super::bindTo(miniMapObject, gameObject);

	this->miniMapObject->drawNode->setPositionY(this->miniMapObject->drawNode->getContentSize().height / 2.0f);
	this->miniMapObject->rotatorNode->setPositionY(-this->miniMapObject->drawNode->getContentSize().height / 2.0f);
	this->mechanicalFlail = dynamic_cast<MechanicalFlail*>(gameObject);
}

void BinderMechanicalFlail::update(float dt)
{
	super::update(dt);

	if (this->mechanicalFlail == nullptr)
	{
		return;
	}

	this->miniMapObject->rotatorNode->setRotation(this->mechanicalFlail->flailChain->getRotation());
}
