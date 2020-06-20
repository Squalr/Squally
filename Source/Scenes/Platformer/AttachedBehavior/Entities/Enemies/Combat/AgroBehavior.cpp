#include "AgroBehavior.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/AnimationPart.h"
#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Objects/Platformer/Projectiles/Projectile.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string AgroBehavior::MapKey = "agro";
const float AgroBehavior::AgroRangeX = 720.0f;
const float AgroBehavior::AgroRangeY = 512.0f;
const float AgroBehavior::AgroRangeZ = 24.0f;
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
	this->exclamation = Sprite::create(UIResources::Combat_Exclamation);
	this->chaseOnAgro = true;
	this->warnOnAgro = true;
	this->isAgrod = false;
	this->isEnabled = true;
	this->engageCooldown = 0.0f;
	this->initCooldown = 0.0f;
	this->agroRangeX = AgroBehavior::AgroRangeX;
	this->agroRangeY = AgroBehavior::AgroRangeY;
	this->agroRangeZ = AgroBehavior::AgroRangeZ;
	this->agroBeep = WorldSound::create(SoundResources::Platformer_Entities_Generic_AgroBeep2);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}

	this->exclamation->setVisible(false);

	this->squally = nullptr;

	this->addChild(this->exclamation);
	this->addChild(this->agroBeep);
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
	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);

	// Prevent agro for a small amount of time. This gives time for entities to properly load/warp.
	this->initCooldown = 0.25f;
	
	this->scheduleUpdate();
}

void AgroBehavior::onDisable()
{
	super::onDisable();
}

void AgroBehavior::enable()
{
	this->isEnabled = true;
}

void AgroBehavior::disable()
{
	this->isEnabled = false;
}

bool AgroBehavior::hasAgro()
{
	return this->isAgrod;
}

PlatformerEntity* AgroBehavior::getAgroTarget()
{
	return this->squally;
}

void AgroBehavior::toggleChaseOnAgro(bool chaseOnAgro)
{
	this->chaseOnAgro = chaseOnAgro;
}

void AgroBehavior::toggleWarnOnAgro(bool warnOnAgro)
{
	this->warnOnAgro = warnOnAgro;
}

void AgroBehavior::setAgroRangeX(float agroRange)
{
	this->agroRangeX = agroRange;
}

void AgroBehavior::setAgroRangeY(float agroRange)
{
	this->agroRangeY = agroRange;
}

void AgroBehavior::update(float dt)
{
	super::update(dt);

	if (!this->isEnabled || this->squally == nullptr || this->entity == nullptr || !this->entity->getRuntimeStateOrDefault(StateKeys::IsAlive, Value(true)).asBool())
	{
		this->exclamation->setVisible(false);
		return;
	}

	if (this->initCooldown > 0.0f)
	{
		this->initCooldown -= dt;
		return;
	}

	Vec3 squallyPosition = GameUtils::getWorldCoords3D(this->squally);
	Vec3 entityPosition = GameUtils::getWorldCoords3D(this->entity);
	
	if (!this->isAgrod)
	{
		if (std::abs(squallyPosition.x - entityPosition.x) <= this->agroRangeX &&
			std::abs(squallyPosition.y - entityPosition.y) <= this->agroRangeY &&
			std::abs(squallyPosition.z - entityPosition.z) <= this->agroRangeZ)
		{
			this->isAgrod = true;

			if (this->warnOnAgro)
			{
				this->engageCooldown = AgroBehavior::EngageCooldownMax;
				this->exclamation->setVisible(true);
				this->agroBeep->play();
			}
			else
			{
				this->engageCooldown = 0.0f;
			}

			this->entity->getAnimations()->setFlippedX(squallyPosition.x < entityPosition.x);
		}
	}

	if (this->isAgrod)
	{
		if (this->engageCooldown <= 0.0f)
		{
			this->exclamation->setVisible(false);
			
			if (std::abs(squallyPosition.x - entityPosition.x) <= this->agroRangeX &&
				std::abs(squallyPosition.y - entityPosition.y) <= this->agroRangeY &&
				std::abs(squallyPosition.z - entityPosition.z) <= this->agroRangeZ)
			{
				if (this->chaseOnAgro)
				{
					this->entity->setState(StateKeys::PatrolDestinationX, Value(squallyPosition.x));
				}
				else
				{
					// Look at target if not able to chase
					this->entity->getAnimations()->setFlippedX(squallyPosition.x < entityPosition.x);
				}
			}
			else
			{
				this->isAgrod = false;
				this->entity->clearState(StateKeys::PatrolDestinationX);
			}
		}
		else
		{
			this->engageCooldown -= dt;
		}
	}
}
