#include "EntityPetrificationBehavior.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Animations/AnimationPart.h"
#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Inventory/Inventory.h"
#include "Engine/Particles/SmartParticles.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Interactables/InteractObject.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Inventory/EntityInventoryBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Stats/EntityHealthBehavior.h"
#include "Scenes/Platformer/Inventory/Items/Misc/Keys/UnderflowRuins/MedusaMirror.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"
#include "Resources/ObjectResources.h"
#include "Resources/ParticleResources.h"

using namespace cocos2d;

const std::string EntityPetrificationBehavior::MapKey = "petrified";
const std::string EntityPetrificationBehavior::SaveKeyCured = "SAVE_KEY_PETRIFICATION_CURED";

EntityPetrificationBehavior* EntityPetrificationBehavior::create(GameObject* owner)
{
	EntityPetrificationBehavior* instance = new EntityPetrificationBehavior(owner);

	instance->autorelease();

	return instance;
}

EntityPetrificationBehavior::EntityPetrificationBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);
	this->petrifiedSprite = nullptr;
	this->displayOffset = Vec2::ZERO;
	this->inventory = nullptr;
	this->cureInteraction = nullptr;
	this->unpetrifyParticles = SmartParticles::create(ParticleResources::Objects_StatueBreak, SmartParticles::CullInfo(Size(113.0f, 160.0f)));

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
	else
	{
		this->cureInteraction = InteractObject::create(InteractObject::InteractType::Input, this->entity->getEntitySize());

		this->cureInteraction->disable();

		if (this->entity->getEntityKey() == "ajax")
		{
			this->petrifiedSprite = Sprite::create(EntityResources::Npcs_UnderflowRuins_Ajax_Petrified);
			this->displayOffset = Vec2(58.0f, 0.0f);
		}
		else if (this->entity->getEntityKey() == "griffin")
		{
			this->petrifiedSprite = Sprite::create(EntityResources::Npcs_UnderflowRuins_Griffin_Petrified);
			this->displayOffset = Vec2(40.0f, -2.0f);
		}
		else if (this->entity->getEntityKey() == "geryon")
		{
			this->petrifiedSprite = Sprite::create(EntityResources::Npcs_UnderflowRuins_Geryon_Petrified);
			this->displayOffset = Vec2(28.0f, -4.0f);
		}
		else if (this->entity->getEntityKey() == "athena")
		{
			this->petrifiedSprite = Sprite::create(EntityResources::Npcs_UnderflowRuins_Athena_Petrified);
			this->displayOffset = Vec2(30.0f, -7.0f);
		}
		else if (this->entity->getEntityKey() == "thor")
		{
			this->petrifiedSprite = Sprite::create(EntityResources::Npcs_UnderflowRuins_Thor_Petrified);
			this->displayOffset = Vec2(34.0f, -6.0f);
		}
		else if (this->entity->getEntityKey() == "ares")
		{
			this->petrifiedSprite = Sprite::create(EntityResources::Npcs_UnderflowRuins_Ares_Petrified);
			this->displayOffset = Vec2(34.0f, 0.0f);
		}
		else
		{
			this->petrifiedSprite = Sprite::create(EntityResources::Npcs_UnderflowRuins_Aphrodite_Petrified);
			this->displayOffset = Vec2(2.0f, 0.0f);
		}

		this->petrifiedSprite->setVisible(false);
		this->petrifiedSprite->setAnchorPoint(Vec2(0.5f, 0.0f));

		this->addChild(this->petrifiedSprite);
		this->addChild(this->cureInteraction);
	}

	this->addChild(this->unpetrifyParticles);
}

EntityPetrificationBehavior::~EntityPetrificationBehavior()
{
}

void EntityPetrificationBehavior::onLoad()
{
	if (this->entity->loadObjectStateOrDefault(EntityPetrificationBehavior::SaveKeyCured, Value(false)).asBool())
	{
		return;
	}

	this->cureInteraction->setInteractCallback([=]()
	{
		return this->tryCure();
	});

	this->unpetrifyParticles->setPosition(this->entity->getEntityCenterPoint());
	this->cureInteraction->setPosition(this->entity->getEntityCenterPoint());

	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		squally->watchForAttachedBehavior<EntityInventoryBehavior>([&](EntityInventoryBehavior* entityInventoryBehavior)
		{
			this->inventory = entityInventoryBehavior->getInventory();

			if (this->inventory->hasItemOfType<MedusaMirror>())
			{
				this->cureInteraction->enable();
			}
		});
	}, Squally::MapKey);

	this->petrifiedSprite->setVisible(true);
	this->petrifiedSprite->setFlippedX(this->entity->isFlippedX());
	this->petrifiedSprite->setPosition(this->petrifiedSprite->isFlippedX() ? Vec2(-this->displayOffset.x, this->displayOffset.y) : this->displayOffset);
	
	// How we achieve the magic of petrification -- mark the entity as dead. All other loaded behaviors should respect this.
	this->entity->watchForAttachedBehavior<EntityHealthBehavior>([=](EntityHealthBehavior* healthBehavior)
	{
		healthBehavior->kill();
	});
	
	this->entity->getAnimations()->setVisible(false);
}

void EntityPetrificationBehavior::onDisable()
{
	super::onDisable();

	this->unpetrify();
}

bool EntityPetrificationBehavior::tryCure()
{
	if (this->inventory == nullptr)
	{
		return false;
	}

	Item* mirror = this->inventory->getItemOfType<MedusaMirror>();

	PlatformerEvents::TriggerDiscoverItem(PlatformerEvents::ItemDiscoveryArgs(mirror));

	this->entity->saveObjectState(EntityPetrificationBehavior::SaveKeyCured, Value(true));
	this->unpetrify();

	this->cureInteraction->disable();
	this->unpetrifyParticles->start();

	return true;
}

void EntityPetrificationBehavior::unpetrify()
{
	if (this->petrifiedSprite != nullptr)
	{
		this->petrifiedSprite->setVisible(false);
	}

	if (this->entity != nullptr)
	{
		this->entity->getAnimations()->setVisible(true);

		this->entity->watchForAttachedBehavior<EntityHealthBehavior>([=](EntityHealthBehavior* healthBehavior)
		{
			healthBehavior->revive();
		});
	}
}
