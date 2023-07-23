#include "GullPuzzleBehavior.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/DialogueOption.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Save/SaveManager.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Interactables/Doors/Mayan/MayanDoor.h"
#include "Scenes/Platformer/Components/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Dialogue/DialogueSet.h"
#include "Scenes/Platformer/Dialogue/Voices.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/HexusResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string GullPuzzleBehavior::MapKey = "gull-puzzle";

GullPuzzleBehavior* GullPuzzleBehavior::create(GameObject* owner)
{
	GullPuzzleBehavior* instance = new GullPuzzleBehavior(owner);

	instance->autorelease();

	return instance;
}

GullPuzzleBehavior::GullPuzzleBehavior(GameObject* owner) : super(owner)
{
	this->pillarCollision = dynamic_cast<CollisionObject*>(owner);

	if (this->pillarCollision == nullptr)
	{
		this->invalidate();
	}
}

GullPuzzleBehavior::~GullPuzzleBehavior()
{
}

void GullPuzzleBehavior::onLoad()
{
	this->owner->listenForMapEventOnce("gull-A", [=](ValueMap)
	{
		this->owner->listenForMapEventOnce("gull-B", [=](ValueMap)
		{
			this->owner->listenForMapEventOnce("gull-C", [=](ValueMap)
			{
				this->owner->listenForMapEventOnce("gull-D", [=](ValueMap)
				{
					this->owner->listenForMapEventOnce("gull-E", [=](ValueMap)
					{
						this->owner->listenForMapEventOnce("gull-F", [=](ValueMap)
						{
							this->owner->listenForMapEventOnce("gull-G", [=](ValueMap)
							{
								this->owner->listenForMapEventOnce("gull-H", [=](ValueMap)
								{
									this->owner->listenForMapEventOnce("gull-I", [=](ValueMap)
									{
										this->onPuzzleSolved();
									});
								});
							});
						});
					});
				});
			});
		});
	});
}

void GullPuzzleBehavior::onDisable()
{
	super::onDisable();
}

void GullPuzzleBehavior::onPuzzleSolved()
{
	this->pillarCollision->setPhysicsFlagEnabled(false);
}
