#include "IOU.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Platformer/Inventory/PlayerCurrencyInventory.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"

#include "Strings/Items/Currency/IOUs.h"

using namespace cocos2d;

const std::string IOU::MapKeyIOU = "iou";
const std::string IOU::SaveKeyIsCollected = "is_collected";

IOU* IOU::create(ValueMap& initProperties)
{
	IOU* instance = new IOU(initProperties);

	instance->autorelease();

	return instance;
}

IOU::IOU(ValueMap& initProperties) : super(initProperties)
{
	this->iou = Sprite::create(ObjectResources::Items_Consumables_IOU);
	this->iouCollision = CollisionObject::create(PhysicsBody::createBox(Size(64.0f, 64.0f)), (CollisionType)PlatformerCollisionType::Collectable, true, false);
	this->isCollected = false;

	this->iouCollision->addChild(this->iou);
	this->addChild(this->iouCollision);
}

IOU::~IOU()
{
}

void IOU::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void IOU::initializePositions()
{
	super::initializePositions();
}

void IOU::initializeListeners()
{
	super::initializeListeners();

	this->iouCollision->whenCollidesWith({ (int)PlatformerCollisionType::Solid, (int)PlatformerCollisionType::PassThrough  }, [=](CollisionObject::CollisionData data)
	{
		return CollisionObject::CollisionResult::CollideWithPhysics;
	});

	this->iouCollision->whenCollidesWith({ (int)PlatformerCollisionType::Player, (int)PlatformerCollisionType::PlayerWeapon, (int)PlatformerCollisionType::PlayerHover }, [=](CollisionObject::CollisionData data)
	{
		if (!this->isCollected)
		{
			this->disableCollection();

			PlayerCurrencyInventory::getInstance()->addCurrency(IOU::getIdentifier(), 1);
			this->saveObjectState(IOU::SaveKeyIsCollected, Value(true));
		}

		return CollisionObject::CollisionResult::DoNothing;
	});
}

void IOU::update(float dt)
{
	super::update(dt);
}

void IOU::onObjectStateLoaded()
{
	super::onObjectStateLoaded();

	if (this->getObjectStateOrDefault(IOU::SaveKeyIsCollected, Value(false)).asBool())
	{
		this->disableCollection();
	}
}

void IOU::disableCollection()
{
	this->isCollected = true;
	this->iouCollision->setPhysicsEnabled(false);
	this->iouCollision->setVisible(false);
}

std::string IOU::getIdentifier()
{
	return "IOU";
}

std::string IOU::getIconResource()
{
	return ObjectResources::Items_Consumables_IOU;
}

LocalizedString* IOU::getString()
{
	return Strings::Items_Currency_IOUs::create();
}
