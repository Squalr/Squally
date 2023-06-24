#include "LightHouseBehavior.h"

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

const std::string LightHouseBehavior::MapKey = "lighthouse";

LightHouseBehavior* LightHouseBehavior::create(GameObject* owner)
{
	LightHouseBehavior* instance = new LightHouseBehavior(owner);

	instance->autorelease();

	return instance;
}

LightHouseBehavior::LightHouseBehavior(GameObject* owner) : super(owner)
{
}

LightHouseBehavior::~LightHouseBehavior()
{
}

void LightHouseBehavior::onLoad()
{
	this->defer([=]()
	{
		this->onPuzzleSolved();
	}, 5);
}

void LightHouseBehavior::onDisable()
{
	super::onDisable();
}

void LightHouseBehavior::onPuzzleSolved()
{
	if (!SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyItemEE3Given, Value(false)).asBool())
	{
		PlatformerEvents::TriggerGiveItems(PlatformerEvents::GiveItemsArgs({ TheGoldenEagle::create() }));
		SaveManager::SaveProfileData(SaveKeys::SaveKeyItemEE3Given, Value(true));
	}
}
