#include "RepairableBehavior.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Input/Input.h"
#include "Engine/Inventory/MinMaxPool.h"
#include "Engine/Particles/SmartParticles.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Physics/EnginePhysicsTypes.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/UI/Mouse.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/Helpers/DataMines/Gecky.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/HelperEvents.h"
#include "Objects/Platformer/Interactables/InteractObject.h"
#include "Menus/CursorSets.h"
#include "Scenes/Platformer/Components/Objects/ObjectSelectionBehavior.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/ParticleResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string RepairableBehavior::MapKey = "repairable";
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
	this->iconGlow = Sprite::create(UIResources::HUD_EmblemGlow);
	this->smokeParticles = SmartParticles::create(ParticleResources::Objects_Smoke, SmartParticles::CullInfo(CSize(256.0f, 256.0f)));

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

	this->addChild(this->smokeParticles);
	this->addChild(this->iconGlow);
	this->addChild(this->repairIcon);
}

RepairableBehavior::~RepairableBehavior()
{
}

void RepairableBehavior::initializePositions()
{
	super::initializePositions();
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
		this->updateIconVisibility();

		if (this->interactObject->getComponent<ObjectSelectionBehavior>() == nullptr)
		{
			this->interactObject->attachComponent(ObjectSelectionBehavior::create(this->interactObject));
		}

		this->interactObject->watchForComponent<ObjectSelectionBehavior>([=](ObjectSelectionBehavior* selectionBehavior)
		{
			this->repairIcon->setPosition(Vec2(0.0f, -selectionBehavior->getObjectSize().height / 2.0f - 32.0f));
			this->iconGlow->setPosition(this->repairIcon->getPosition());

			selectionBehavior->setClickModifier(InputEvents::KeyCode::KEY_SHIFT);
			selectionBehavior->setClickableCallback([=]()
			{
				return this->canRepair(true);
			});
			selectionBehavior->setObjectClickCallbacks([=]()
			{
				this->attemptRepair();
			},
			[=]()
			{
				if (this->currentHelperName == Gecky::MapKey && this->canRepair(true))
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
		this->updateIconVisibility();

		this->squally->listenForStateWrite(StateKeys::CurrentHelper, [=](Value value)
		{
			this->currentHelperName = value.asString();
			this->updateIconVisibility();
		});
	}, Squally::MapKey);

	this->updateIconVisibility();
}

void RepairableBehavior::onDisable()
{
	super::onDisable();
}

void RepairableBehavior::attemptRepair()
{
	if (this->canRepair(true))
	{
		HelperEvents::TriggerRequestRepair(HelperEvents::RequestRepairArgs(
			this->interactObject,
			[=]()
			{
				this->updateIconVisibility();	
			},
			this->repairEvent,
			RepairableBehavior::SavePropertyKeyWasRepaired
		));
	}
}

bool RepairableBehavior::canRepair(bool checkZ)
{
	bool isHelperZAligned = true;

	if (checkZ)
	{
		ObjectEvents::QueryObjects<PlatformerHelper>([&](PlatformerHelper* helper)
		{
			if (std::abs(GameUtils::getDepth(helper) - GameUtils::getDepth(interactObject)) > 16.0f)
			{
				isHelperZAligned = false;
			}
		}, Squally::TeamTag);
	}

	return this->interactObject != nullptr
		&& !this->isInvalidated()
		&& isHelperZAligned
		&& this->currentHelperName == Gecky::MapKey
		&& !this->wasRepaired();
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
	this->repairIcon->setVisible(this->canRepair(false));
	this->iconGlow->setVisible(this->canRepair(false));

	if (this->canRepair(false))
	{
		this->smokeParticles->start();
	}
	else
	{
		this->smokeParticles->stop();
	}
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
					if (pickPocketBehavior->canRepair(true))
					{
						CursorSets::SetActiveCursorSet(CursorSets::Repair);
					}
				});
			}
		}, false, false)
	);

	InputEvents::TriggerMouseRequestRefresh();
}
