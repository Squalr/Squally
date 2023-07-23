#include "GarinBehavior.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Save/SaveManager.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/DialogueEvents.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/Components/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Dialogue/DialogueSet.h"
#include "Scenes/Platformer/Dialogue/Voices.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/HexusResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string GarinBehavior::MapKey = "garin";

GarinBehavior* GarinBehavior::create(GameObject* owner)
{
	GarinBehavior* instance = new GarinBehavior(owner);

	instance->autorelease();

	return instance;
}

GarinBehavior::GarinBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

GarinBehavior::~GarinBehavior()
{
}

void GarinBehavior::onLoad()
{
	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);

	ObjectEvents::WatchForObject<Scrappy>(this, [=](Scrappy* scrappy)
	{
		this->scrappy = scrappy;
	}, Scrappy::MapKey);

	this->setPostText();
}

void GarinBehavior::onDisable()
{
	super::onDisable();
}

void GarinBehavior::setPostText()
{
	if (this->entity == nullptr)
	{
		return;
	}

	this->entity->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
	{
		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_CastleValgrind_Gossip_Garin_A_Train::create()->setStringReplacementVariables({
				Strings::Platformer_MapNames_CastleValgrind_CastleValgrind::create(),
				Strings::Platformer_MapNames_DataMines_Drammol::create()
			}),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Right,
				DialogueEvents::BuildPreviewNode(&this->squally, false),
				DialogueEvents::BuildPreviewNode(&this->entity, true)
			),
			[=]()
			{
				this->defer([=]()
				{
					this->setPostText();
				});
			},
			Voices::GetNextVoiceLong(),
			true
		));
	});
}
