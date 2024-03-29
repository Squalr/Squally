#include "SquallyWeaponCollisionBehavior.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Animations/AnimationPart.h"
#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/NavigationEvents.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/Components/Entities/Inventory/EntityInventoryBehavior.h"
#include "Scenes/Platformer/Inventory/EquipmentInventory.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"
#include "Scenes/Platformer/Level/Physics/PlatformerPhysicsTypes.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"
#include "Resources/SoundResources.h"

using namespace cocos2d;

const std::string SquallyWeaponCollisionBehavior::MapKey = "squally-weapon-collision";

SquallyWeaponCollisionBehavior* SquallyWeaponCollisionBehavior::create(GameObject* owner)
{
	SquallyWeaponCollisionBehavior* instance = new SquallyWeaponCollisionBehavior(owner);

	instance->autorelease();

	return instance;
}

SquallyWeaponCollisionBehavior::SquallyWeaponCollisionBehavior(GameObject* owner) : super(owner)
{
	this->squally = dynamic_cast<Squally*>(owner);
	this->impactSound = WorldSound::create();

	if (this->squally == nullptr)
	{
		this->invalidate();
	}

	this->addChild(this->impactSound);
}

SquallyWeaponCollisionBehavior::~SquallyWeaponCollisionBehavior()
{
}

void SquallyWeaponCollisionBehavior::onLoad()
{
	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventEquippedItemsChanged, [=](EventCustom*)
	{
		this->rebuildWeaponCollision((int)PlatformerCollisionType::PlayerWeapon, false);
	}));

	this->defer([=]()
	{
		this->squally->watchForComponent<EntityWeaponCollisionBehavior>([=](EntityWeaponCollisionBehavior* weaponBehavior)
		{
			this->onWeaponChange();

			this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventEquippedItemsChanged, [=](EventCustom*)
			{
				this->onWeaponChange();
			}));
		});
	});
}

void SquallyWeaponCollisionBehavior::onDisable()
{
	super::onDisable();
}

void SquallyWeaponCollisionBehavior::onWeaponChange()
{
	this->squally->getComponent<EntityInventoryBehavior>([=](EntityInventoryBehavior* entityInventoryBehavior)
	{
		Weapon* weapon = entityInventoryBehavior->getEquipmentInventory()->getWeapon();

		if (weapon != nullptr)
		{
			this->setWeaponCollisionSize(weapon->getWeaponCollisionSize());
			this->setWeaponCollisionOffset(weapon->getWeaponCollisionOffset());
		}
		else
		{
			const CSize NoWeaponSize = CSize(64.0f, 64.0f);
			const Vec2 NoWeaponOffset = Vec2(0.0f, 96.0f);

			this->setWeaponCollisionSize(NoWeaponSize);
			this->setWeaponCollisionOffset(NoWeaponOffset);
		}
	});

	this->rebuildWeaponCollision((int)PlatformerCollisionType::PlayerWeapon, false);

	if (this->mainhandWeaponCollision != nullptr)
	{
		this->mainhandWeaponCollision->setName("Squally weapon collision");
		
		this->mainhandWeaponCollision->whenCollidesWith({ (int)PlatformerCollisionType::Enemy }, [=](CollisionData collisionData)
		{
			if (!this->canEngage || !this->squally->getRuntimeStateOrDefaultBool(StateKeys::IsAlive, true))
			{
				return CollisionResult::DoNothing;
			}

			PlatformerEnemy* enemy = GameUtils::GetFirstParentOfType<PlatformerEnemy>(collisionData.other);

			if (enemy != nullptr && enemy->getRuntimeStateOrDefaultBool(StateKeys::IsAlive, true))
			{
				this->squally->getComponent<EntityInventoryBehavior>([=](EntityInventoryBehavior* entityInventoryBehavior)
				{
					Weapon* weapon = entityInventoryBehavior->getEquipmentInventory()->getWeapon();

					if (weapon != nullptr)
					{
						this->impactSound->setSoundResource(weapon->getWeaponImpactSound());
					}
					else
					{
						this->impactSound->setSoundResource(SoundResources::Platformer_Physical_Impact_HitSoft1);
					}

					this->impactSound->play();
				});

				// Encountered enemy w/ first-strike
				PlatformerEvents::TriggerEngageEnemy(PlatformerEvents::EngageEnemyArgs(enemy, true));

				this->canEngage = false;
			}

			return CollisionResult::DoNothing;
		});
	}
}
