#include "Doubloon.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Platformer/Inventory/Currency/Doubloons.h"
#include "Scenes/Platformer/Inventory/PlayerCurrencyInventory.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string Doubloon::MapKeyDoubloon = "doubloon";
const std::string Doubloon::SaveKeyIsCollected = "is_collected";

Doubloon* Doubloon::create(ValueMap& initProperties)
{
	Doubloon* instance = new Doubloon(initProperties);

	instance->autorelease();

	return instance;
}

Doubloon::Doubloon(ValueMap& initProperties) : super(initProperties)
{
	this->doubloon = SmartAnimationSequenceNode::create(ObjectResources::Collectables_Doubloon_Doubloon_0000);
	this->doubloonCollision = CollisionObject::create(PhysicsBody::createBox(Size(64.0f, 64.0f)), (CollisionType)PlatformerCollisionType::Collectable, false, false);
	this->isCollected = false;

	this->doubloonCollision->addChild(this->doubloon);
	this->addChild(this->doubloonCollision);
}

Doubloon::~Doubloon()
{
}

void Doubloon::onEnter()
{
	super::onEnter();

	this->doubloon->playAnimationRepeat(ObjectResources::Collectables_Doubloon_Doubloon_0000, 0.1f);

	this->scheduleUpdate();
}

void Doubloon::initializePositions()
{
	super::initializePositions();
}

void Doubloon::initializeListeners()
{
	super::initializeListeners();

	this->doubloonCollision->whenCollidesWith({ (int)PlatformerCollisionType::Player }, [=](CollisionObject::CollisionData data)
	{
		if (!this->isCollected)
		{
			this->disableCollection();

			PlayerCurrencyInventory::getInstance()->addCurrency(Doubloons::getIdentifier(), 1);
			this->saveObjectState(Doubloon::SaveKeyIsCollected, Value(true));
		}

		return CollisionObject::CollisionResult::DoNothing;
	});
}

void Doubloon::update(float dt)
{
	super::update(dt);
}

void Doubloon::onObjectStateLoaded()
{
	super::onObjectStateLoaded();

	if (this->getObjectStateOrDefault(Doubloon::SaveKeyIsCollected, Value(false)).asBool())
	{
		this->disableCollection();
	}
}

void Doubloon::disableCollection()
{
	this->isCollected = true;
	this->doubloonCollision->setPhysicsEnabled(false);
	this->doubloonCollision->setVisible(false);
}
