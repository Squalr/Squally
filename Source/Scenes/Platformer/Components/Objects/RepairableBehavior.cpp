#include "RepairableBehavior.h"

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
#include "Objects/Platformer/Interactables/InteractObject.h"
#include "Menus/CursorSets.h"
#include "Scenes/Platformer/Components/Objects/ObjectSelectionBehavior.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string RepairableBehavior::MapKey = "repair";
const std::string RepairableBehavior::SavePropertyKeyWasRepaired = "WAS_REPAIRED";
const std::string RepairableBehavior::MapKeyRepairEvent = "repair-event";

RepairableBehavior* RepairableBehavior::create(GameObject* owner)
{
	RepairableBehavior* instance = new RepairableBehavior(owner);

	instance->autorelease();

	return instance;
}

RepairableBehavior::RepairableBehavior(GameObject* owner) : super(owner)
{
	this->interactObject = dynamic_cast<InteractObject*>(owner);
	this->repairIcon = Sprite::create(UIResources::Menus_Icons_RobotArm);

	this->repairIcon->setScale(0.75f);

	if (this->interactObject == nullptr)
	{
		this->invalidate();
	}
	else
	{
		this->repairEvent = this->interactObject->getPropertyOrDefault(RepairableBehavior::MapKeyRepairEvent, Value("")).asString();
	}

	this->repairIcon->setVisible(false);

	this->addChild(this->repairIcon);
}

RepairableBehavior::~RepairableBehavior()
{
}

void RepairableBehavior::initializePositions()
{
	super::initializePositions();

	this->repairIcon->setPosition(Vec2(0.0f, -32.0f));
}

void RepairableBehavior::onLoad()
{
	if (this->wasRepaired())
	{
		this->interactObject->unlock(false);
	}
	else
	{
		this->interactObject->lock(false);
	}

	this->defer([=]()
	{
		if (this->interactObject->getComponent<ObjectSelectionBehavior>() == nullptr)
		{
			this->interactObject->attachComponent(ObjectSelectionBehavior::create(this->interactObject));
		}

		this->interactObject->watchForComponent<ObjectSelectionBehavior>([=](ObjectSelectionBehavior* selectionBehavior)
		{
			selectionBehavior->setClickModifier(InputEvents::KeyCode::KEY_SHIFT);
			selectionBehavior->setClickableCallback([=]()
			{
				return this->canRepair();
			});
			selectionBehavior->setObjectClickCallbacks([=]()
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

void RepairableBehavior::onDisable()
{
	super::onDisable();
}

void RepairableBehavior::attemptRepair()
{
	if (this->canRepair())
	{
		HelperEvents::TriggerRequestRepair(HelperEvents::RequestRepairArgs(
			this->interactObject,
			this->repairEvent,
			RepairableBehavior::SavePropertyKeyWasRepaired
		));
	}
}

bool RepairableBehavior::canRepair()
{
	return this->interactObject != nullptr && this->currentHelperName == Guano::MapKey && !this->wasRepaired();
}

bool RepairableBehavior::wasRepaired()
{
	return this->interactObject->loadObjectStateOrDefault(RepairableBehavior::SavePropertyKeyWasRepaired, Value(false)).asBool();
}

void RepairableBehavior::onRepaired()
{
	this->updateIconVisibility();
	
	this->interactObject->getComponent<ObjectSelectionBehavior>([=](ObjectSelectionBehavior* selection)
	{
		selection->clearObjectClickCallbacks();
		
		this->refreshCursorState();
	});
}

void RepairableBehavior::updateIconVisibility()
{
	this->repairIcon->setVisible(this->canRepair());
}

void RepairableBehavior::refreshCursorState()
{
	CursorSets::SetActiveCursorSet(CursorSets::Default);

	// Fire a hit test to see if any other entities are still selected. Restore the pickpocket cursor set if so.
	InputEvents::TriggerMouseHitTest(InputEvents::MouseHitTestArgs(
		Input::GetMouseEvent().mouseCoords,
		[=](Node* node)
		{
			ObjectSelectionBehavior* selection = GameUtils::GetFirstParentOfType<ObjectSelectionBehavior>(node);

			if (selection != nullptr)
			{
				selection->getOwner()->getComponent<RepairableBehavior>([](RepairableBehavior* pickPocketBehavior)
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
