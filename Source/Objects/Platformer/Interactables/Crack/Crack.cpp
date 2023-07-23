#include "Crack.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/NavigationEvents.h"
#include "Engine/Inventory/Item.h"
#include "Engine/Inventory/MinMaxPool.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/DialogueEvents.h"
#include "Events/PlatformerEvents.h"
#include "Menus/Cutscenes/CutscenesMenu.h"
#include "Objects/Platformer/ItemPools/RecipePools/RecipePoolDeserializer.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Recipe.h"
#include "Scenes/Platformer/Level/PlatformerMap.h"
#include "Scenes/Platformer/Objectives/ObjectiveKeys.h"
#include "Scenes/Platformer/Objectives/Objectives.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/ObjectResources.h"
#include "Resources/MapResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Crack::MapKey = "crack";
const std::string Crack::MapPropertyCrackSize = "crack-size";

Crack* Crack::create(ValueMap& properties)
{
	Crack* instance = new Crack(properties);

	instance->autorelease();

	return instance;
}

Crack::Crack(ValueMap& properties) : super(properties, InteractObject::InteractType::Input, CSize(525.0f, 1193.0f))
{
	std::string crackSizeStr = GameUtils::getKeyOrDefault(this->properties, Crack::MapPropertyCrackSize, Value("")).asString();

	if (crackSizeStr == "small")
	{
		this->crack = Sprite::create(ObjectResources::Interactive_Cracks_CrackSmallWhite);
		this->crackSize = CrackSize::Small;
	}
	else if (crackSizeStr == "medium")
	{
		this->crack = Sprite::create(ObjectResources::Interactive_Cracks_CrackMediumWhite);
		this->crackSize = CrackSize::Medium;
	}
	else if (crackSizeStr == "large")
	{
		this->crack = Sprite::create(ObjectResources::Interactive_Cracks_CrackLargeWhite);
		this->crackSize = CrackSize::Large;
	}
	
	this->addChild(this->crack);
}

Crack::~Crack()
{
}

void Crack::onEnterTransitionDidFinish()
{
	super::onEnterTransitionDidFinish();

	// Prime cache for the corresponding cutscene
	// NOTE: does not actually play the cutscene. Event is poorly named, we're just priming with a parameter.
	switch(this->crackSize)
	{
		case CrackSize::Small:
		{
			if (SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyViewCrackSmall, Value(false)).asBool())
			{
				this->disable();
			}
			else
			{
				PlatformerEvents::TriggerPlayCutscene(PlatformerEvents::CutsceneArgs(Cutscene::CrackSmall, true));
			}
			break;
		}
		case CrackSize::Medium:
		{
			if (SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyViewCrackMedium, Value(false)).asBool())
			{
				this->disable();
			}
			else
			{
				PlatformerEvents::TriggerPlayCutscene(PlatformerEvents::CutsceneArgs(Cutscene::CrackMedium, true));
			}
			break;
		}
		case CrackSize::Large:
		{
			if (SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyViewCrackLarge, Value(false)).asBool())
			{
				this->disable();
			}
			else
			{
				PlatformerEvents::TriggerPlayCutscene(PlatformerEvents::CutsceneArgs(Cutscene::CrackLarge, true));
			}
			break;
		}
	}
}

void Crack::initializePositions()
{
	super::initializePositions();

	switch(this->crackSize)
	{
		case CrackSize::Small:
		{
			this->crack->setPosition(Vec2(112.0f, 0.0f));
			break;
		}
		case CrackSize::Medium:
		{
			this->crack->setPosition(Vec2(112.0f, 0.0f));
			break;
		}
		case CrackSize::Large:
		{
			this->crack->setPosition(Vec2(112.0f, 0.0f));
			break;
		}
	}
}

void Crack::onInteract(PlatformerEntity* interactingEntity)
{
	super::onInteract(interactingEntity);

	switch(this->crackSize)
	{
		case CrackSize::Small:
		{
			SaveManager::SoftSaveProfileData(SaveKeys::SaveKeyViewCrackSmall, Value(true));
			PlatformerEvents::TriggerPlayCutscene(PlatformerEvents::CutsceneArgs(Cutscene::CrackSmall, false));
			break;
		}
		case CrackSize::Medium:
		{
			SaveManager::SoftSaveProfileData(SaveKeys::SaveKeyViewCrackMedium, Value(true));
			PlatformerEvents::TriggerPlayCutscene(PlatformerEvents::CutsceneArgs(Cutscene::CrackMedium, false));
			break;
		}
		case CrackSize::Large:
		{
			SaveManager::SoftSaveProfileData(SaveKeys::SaveKeyViewCrackLarge, Value(true));
			PlatformerEvents::TriggerPlayCutscene(PlatformerEvents::CutsceneArgs(Cutscene::CrackLarge, false));
			break;
		}
	}

	this->setInteractType(InteractType::None);
}
