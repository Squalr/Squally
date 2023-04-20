#include "EntitySoulBehavior.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Input/Input.h"
#include "Engine/Inventory/MinMaxPool.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Physics/EnginePhysicsTypes.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/UI/Mouse.h"
#include "Engine/UI/UIBoundObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/Helpers/CastleValgrind/Grim.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/HelperEvents.h"
#include "Objects/Platformer/ItemPools/PocketPools/PocketPoolDeserializer.h"
#include "Objects/Platformer/ItemPools/ErrorPool.h"
#include "Menus/CursorSets.h"
#include "Scenes/Platformer/Components/Entities/EntitySelectionBehavior.h"
#include "Scenes/Platformer/Components/Entities/Haunted/EntityHauntedBehavior.h"
#include "Scenes/Platformer/Level/Physics/PlatformerPhysicsTypes.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string EntitySoulBehavior::MapKey = "soul";
const std::string EntitySoulBehavior::SavePropertyKeyWasSoulHarvested = "WAS_SOUL_HARVESTED";

EntitySoulBehavior* EntitySoulBehavior::create(GameObject* owner)
{
	EntitySoulBehavior* instance = new EntitySoulBehavior(owner);

	instance->autorelease();

	return instance;
}

EntitySoulBehavior::EntitySoulBehavior(GameObject* owner) : super(owner)
{
	this->soulHarvestIcon = Sprite::create(UIResources::Menus_Icons_AngelFigurine);
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	this->soulHarvestIcon->setScale(0.75f);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}

	this->soulHarvestIcon->setVisible(false);

	this->addChild(this->soulHarvestIcon);
}

EntitySoulBehavior::~EntitySoulBehavior()
{
}

void EntitySoulBehavior::initializePositions()
{
	super::initializePositions();

	this->soulHarvestIcon->setPosition(Vec2(0.0f, -32.0f));
}

void EntitySoulBehavior::onLoad()
{
	this->defer([=]()
	{
		if (this->entity->getComponent<EntitySelectionBehavior>() == nullptr)
		{
			this->entity->attachComponent(EntitySelectionBehavior::create(this->entity));
		}

		this->entity->listenForStateWrite(StateKeys::IsAlive, [=](Value value)
		{
			this->updateIconVisibility();
		});

		this->entity->watchForComponent<EntitySelectionBehavior>([=](EntitySelectionBehavior* selectionBehavior)
		{
			selectionBehavior->setClickModifier(InputEvents::KeyCode::KEY_SHIFT);
			selectionBehavior->setClickableCallback([=]()
			{
				return this->canSoulHarvest();
			});
			selectionBehavior->setEntityClickCallbacks([=]()
			{
				this->attemptSoulHarvest();
			},
			[=]()
			{
				if (this->currentHelperName == Grim::MapKey && this->canSoulHarvest())
				{
					CursorSets::SetActiveCursorSet(CursorSets::SoulHarvest);
				}
			},
			[=]()
			{
				CursorSets::SetActiveCursorSet(CursorSets::Default);
			});
		});

		ObjectEvents::TriggerBindObjectToUI(RelocateObjectArgs(this->soulHarvestIcon));
	});
	
	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
		this->currentHelperName = SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyHelperName, Value("")).asString();
		this->soulHarvestIcon->setVisible(this->canSoulHarvest());

		this->squally->listenForStateWrite(StateKeys::CurrentHelper, [=](Value value)
		{
			this->currentHelperName = value.asString();
			this->soulHarvestIcon->setVisible(this->canSoulHarvest());
		});
	}, Squally::MapKey);
}

void EntitySoulBehavior::onDisable()
{
	super::onDisable();
}

void EntitySoulBehavior::attemptSoulHarvest()
{
	if (this->canSoulHarvest())
	{
		HelperEvents::TriggerRequestSoulHarvest(HelperEvents::RequestSoulHarvestArgs(
			this->entity,
			[=]()
			{
				this->onSoulHarvested();
			},
			EntitySoulBehavior::SavePropertyKeyWasSoulHarvested
		));
	}
}

bool EntitySoulBehavior::canSoulHarvest()
{
	return this->entity != nullptr && this->currentHelperName == Grim::MapKey && !this->entity->getRuntimeStateOrDefaultBool(StateKeys::IsAlive, true) && !this->wasSoulHarvested();
}

bool EntitySoulBehavior::wasSoulHarvested()
{
	return this->entity->loadObjectStateOrDefault(EntitySoulBehavior::SavePropertyKeyWasSoulHarvested, Value(false)).asBool();
}

void EntitySoulBehavior::onSoulHarvested()
{
	this->updateIconVisibility();
	
	this->entity->getComponent<EntitySelectionBehavior>([=](EntitySelectionBehavior* selection)
	{
		selection->clearEntityClickCallbacks();
		
		this->refreshCursorState();
	});

	// Lazy way to update the quest. Correct way would be to fire an event, but I don't want to do that.
	this->entity->getComponent<EntityHauntedBehavior>([=](EntityHauntedBehavior* entityHauntedBehavior)
	{
		entityHauntedBehavior->onSoulHarvested();
	});
}

void EntitySoulBehavior::updateIconVisibility()
{
	this->soulHarvestIcon->setVisible(this->canSoulHarvest());
}

void EntitySoulBehavior::refreshCursorState()
{
	CursorSets::SetActiveCursorSet(CursorSets::Default);

	// Fire a hit test to see if any other entities are still selected. Restore the pickpocket cursor set if so.
	InputEvents::TriggerMouseHitTest(InputEvents::MouseHitTestArgs(
		Input::GetMouseEvent().mouseCoords,
		[=](Node* node)
		{
			EntitySelectionBehavior* selection = GameUtils::GetFirstParentOfType<EntitySelectionBehavior>(node);

			if (selection != nullptr)
			{
				selection->getOwner()->getComponent<EntitySoulBehavior>([](EntitySoulBehavior* pickPocketBehavior)
				{
					if (pickPocketBehavior->canSoulHarvest())
					{
						CursorSets::SetActiveCursorSet(CursorSets::SoulHarvest);
					}
				});
			}
		}, false, false)
	);

	InputEvents::TriggerMouseRequestRefresh();
}
