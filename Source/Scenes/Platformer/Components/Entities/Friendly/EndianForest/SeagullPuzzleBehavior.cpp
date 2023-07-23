#include "SeagullPuzzleBehavior.h"

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

const std::string SeagullPuzzleBehavior::MapKey = "seagull-puzzle";

SeagullPuzzleBehavior* SeagullPuzzleBehavior::create(GameObject* owner)
{
	SeagullPuzzleBehavior* instance = new SeagullPuzzleBehavior(owner);

	instance->autorelease();

	return instance;
}

SeagullPuzzleBehavior::SeagullPuzzleBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

SeagullPuzzleBehavior::~SeagullPuzzleBehavior()
{
}

void SeagullPuzzleBehavior::onLoad()
{
	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);

	ObjectEvents::WatchForObject<Scrappy>(this, [=](Scrappy* scrappy)
	{
		this->scrappy = scrappy;
	}, Scrappy::MapKey);

	this->entity->listenForMapEventOnce("gull-A", [=](ValueMap)
	{
		this->entity->listenForMapEventOnce("gull-B", [=](ValueMap)
		{
			this->entity->listenForMapEventOnce("gull-C", [=](ValueMap)
			{
				this->entity->listenForMapEventOnce("gull-D", [=](ValueMap)
				{
					this->entity->listenForMapEventOnce("gull-E", [=](ValueMap)
					{
						this->entity->listenForMapEventOnce("gull-F", [=](ValueMap)
						{
							this->entity->listenForMapEventOnce("gull-G", [=](ValueMap)
							{
								this->entity->listenForMapEventOnce("gull-H", [=](ValueMap)
								{
									this->entity->listenForMapEventOnce("gull-I", [=](ValueMap)
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

void SeagullPuzzleBehavior::onDisable()
{
	super::onDisable();
}

void SeagullPuzzleBehavior::onPuzzleSolved()
{
	this->entity->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
	{
		if (SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyItemEE4Given, Value(false)).asBool())
		{
			return;
		}

		interactionBehavior->getMainDialogueSet()->addDialogueOption(DialogueOption::create(
			Strings::Platformer_Quests_EndianForest_SkyShipToTemple_Dudly_W_SolvedBirdProblem::create(),
			[=]()
			{
				DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
					Strings::Platformer_Quests_EndianForest_SkyShipToTemple_Dudly_X_LikedThoseBirds::create(),
					DialogueEvents::DialogueVisualArgs(
						DialogueBox::DialogueDock::Bottom,
						DialogueBox::DialogueAlignment::Left,
						DialogueEvents::BuildPreviewNode(&this->entity, false),
						DialogueEvents::BuildPreviewNode(&this->squally, true)
					),
					[=]()
					{
						if (!SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyItemEE4Given, Value(false)).asBool())
						{
							PlatformerEvents::TriggerGiveItems(PlatformerEvents::GiveItemsArgs({ TigersBane::create() }));
							SaveManager::SaveProfileData(SaveKeys::SaveKeyItemEE4Given, Value(true));
						}

						// Defer to avoid disposing of dialgue options in the middle of the callback of one
						this->defer([=]()
						{
							this->entity->broadcastMapEvent("refresh-dialogue", ValueMap());
						});
					},
					Voices::GetNextVoiceMedium(),
					true
				));
			}),
			0.75f
		);
	});
}
