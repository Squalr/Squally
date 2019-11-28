#include "AgroBehavior.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string AgroBehavior::MapKeyAttachedBehavior = "agro";
const float AgroBehavior::AgroRangeX = 640.0f;
const float AgroBehavior::AgroRangeY = 512.0f;
const float AgroBehavior::EngageCooldownMax = 1.0f;

AgroBehavior* AgroBehavior::create(GameObject* owner)
{
	AgroBehavior* instance = new AgroBehavior(owner);

	instance->autorelease();

	return instance;
}

AgroBehavior::AgroBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);
	this->exclamation = Sprite::create(UIResources::Platformer_Exclamation);
	this->isAgrod = false;
	this->engageCooldown = 0.f;

	if (this->entity == nullptr)
	{
		this->invalidate();
	}

	this->exclamation->setVisible(false);

	this->squally = nullptr;

	this->addChild(this->exclamation);
}

AgroBehavior::~AgroBehavior()
{
}

void AgroBehavior::initializePositions()
{
	super::initializePositions();

	if (this->entity != nullptr)
	{
		Vec2 offset = this->entity->getCollisionOffset() + Vec2(0.0f, this->entity->getEntitySize().height + this->entity->getHoverHeight() / 2.0f + 64.0f);

		this->exclamation->setPosition(offset);
	}
}

void AgroBehavior::onLoad()
{
	ObjectEvents::watchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKeySqually);
}

void AgroBehavior::update(float dt)
{
	super::update(dt);

	if (this->squally == nullptr || this->entity == nullptr)
	{
		return;
	}

	if (!this->entity->getStateOrDefault(StateKeys::IsAlive, Value(true)).asBool())
	{
		return;
	}

	Vec2 squallyPosition = GameUtils::getWorldCoords(this->squally);
	Vec2 entityPosition = GameUtils::getWorldCoords(this->entity);
	
	if (!this->isAgrod)
	{
		if (std::abs(squallyPosition.x - entityPosition.x) <= AgroBehavior::AgroRangeX &&
			std::abs(squallyPosition.y - entityPosition.y) <= AgroBehavior::AgroRangeY)
		{
			this->isAgrod = true;
			this->engageCooldown = AgroBehavior::EngageCooldownMax;
			this->exclamation->setVisible(true);
			this->entity->getAnimations()->setFlippedX(squallyPosition.x < entityPosition.x);
		}
	}

	if (this->isAgrod)
	{
		if (this->engageCooldown <= 0.0f)
		{
			this->exclamation->setVisible(false);
			
			if (std::abs(squallyPosition.x - entityPosition.x) <= AgroBehavior::AgroRangeX &&
				std::abs(squallyPosition.y - entityPosition.y) <= AgroBehavior::AgroRangeY)
			{
				this->entity->setState(StateKeys::PatrolDestinationX, Value(squallyPosition.x));
			}
			else
			{
				this->isAgrod = false;
			}
		}
		else
		{
			this->engageCooldown -= dt;
		}
	}
}
