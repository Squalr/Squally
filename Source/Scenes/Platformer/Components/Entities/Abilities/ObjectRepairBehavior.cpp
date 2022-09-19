#include "ObjectRepairBehavior.h"

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
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/Helpers/EndianForest/Guano.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/HelperEvents.h"
#include "Objects/Platformer/ItemPools/PocketPools/PocketPoolDeserializer.h"
#include "Objects/Platformer/ItemPools/ErrorPool.h"
#include "Menus/CursorSets.h"
#include "Scenes/Platformer/Components/Entities/EntitySelectionBehavior.h"
#include "Scenes/Platformer/Level/Physics/PlatformerPhysicsTypes.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string ObjectRepairBehavior::MapKey = "repair";
const std::string ObjectRepairBehavior::SavePropertyKeyWasRepaired = "WAS_REPAIRED";
const std::string ObjectRepairBehavior::MapKeyRepairEvent = "repair-event";

ObjectRepairBehavior* ObjectRepairBehavior::create(GameObject* owner)
{
	ObjectRepairBehavior* instance = new ObjectRepairBehavior(owner);

	instance->autorelease();

	return instance;
}

ObjectRepairBehavior::ObjectRepairBehavior(GameObject* owner) : super(owner)
{
	this->repairIcon = Sprite::create(UIResources::Menus_Icons_RobotArm);

	this->repairIcon->setScale(0.75f);

	if (this->owner == nullptr)
	{
		this->invalidate();
	}
	else
	{
		this->repairEvent = this->owner->getPropertyOrDefault(ObjectRepairBehavior::MapKeyRepairEvent, Value("")).asString();
	}

	this->repairIcon->setVisible(false);

	this->addChild(this->repairIcon);
}

ObjectRepairBehavior::~ObjectRepairBehavior()
{
}

void ObjectRepairBehavior::initializePositions()
{
	super::initializePositions();

	this->repairIcon->setPosition(Vec2(0.0f, -32.0f));
}

void ObjectRepairBehavior::onLoad()
{
	this->defer([=]()
	{
		if (this->owner->getComponent<EntitySelectionBehavior>() == nullptr)
		{
			this->owner->attachComponent(EntitySelectionBehavior::create(this->owner));
		}

		this->owner->watchForComponent<EntitySelectionBehavior>([=](EntitySelectionBehavior* selectionBehavior)
		{
			selectionBehavior->setClickModifier(InputEvents::KeyCode::KEY_SHIFT);
			selectionBehavior->setClickableCallback([=]()
			{
				return this->canRepair();
			});
			selectionBehavior->setEntityClickCallbacks([=]()
			{
				this->attemptRepair();
			},
			[=]()
			{
				if (this->currentHelperName == Guano::MapKey && this->canRepair())
				{
					CursorSets::SetActiveCursorSet(CursorSets::Repair);
				}
			},
			[=]()
			{
				CursorSets::SetActiveCursorSet(CursorSets::Default);
			});
		});
	});
	
	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
		this->currentHelperName = SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyHelperName, Value("")).asString();
		this->repairIcon->setVisible(this->canRepair());

		this->squally->listenForStateWrite(StateKeys::CurrentHelper, [=](Value value)
		{
			this->currentHelperName = value.asString();
			this->repairIcon->setVisible(this->canRepair());
		});
	}, Squally::MapKey);
}

void ObjectRepairBehavior::onDisable()
{
	super::onDisable();
}

void ObjectRepairBehavior::attemptRepair()
{
	if (this->canRepair())
	{
		HelperEvents::TriggerRequestRepair(HelperEvents::RequestRepairArgs(
			this->owner,
			this->repairEvent,
			ObjectRepairBehavior::SavePropertyKeyWasRepaired
		));
	}
}

bool ObjectRepairBehavior::canRepair()
{
	return this->owner != nullptr && this->currentHelperName == Guano::MapKey && !this->wasRepaired();
}

bool ObjectRepairBehavior::wasRepaired()
{
	return this->owner->loadObjectStateOrDefault(ObjectRepairBehavior::SavePropertyKeyWasRepaired, Value(false)).asBool();
}

void ObjectRepairBehavior::onRepaired()
{
	this->updateIconVisibility();
	
	this->owner->getComponent<EntitySelectionBehavior>([=](EntitySelectionBehavior* selection)
	{
		selection->clearEntityClickCallbacks();
		
		this->refreshCursorState();
	});
}

void ObjectRepairBehavior::updateIconVisibility()
{
	this->repairIcon->setVisible(this->canRepair());
}

void ObjectRepairBehavior::refreshCursorState()
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
				selection->getOwner()->getComponent<ObjectRepairBehavior>([](ObjectRepairBehavior* pickPocketBehavior)
				{
					if (pickPocketBehavior->canRepair())
					{
						CursorSets::SetActiveCursorSet(CursorSets::Repair);
					}
				});
			}
		}, false, false)
	);

	InputEvents::TriggerMouseRequestRefresh();
}
