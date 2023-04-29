#include "Crack.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/NavigationEvents.h"
#include "Engine/Inventory/Item.h"
#include "Engine/Inventory/MinMaxPool.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/DialogueEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/ItemPools/RecipePools/RecipePoolDeserializer.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Recipe.h"
#include "Scenes/Platformer/Level/PlatformerMap.h"
#include "Scenes/Platformer/Objectives/ObjectiveKeys.h"
#include "Scenes/Platformer/Objectives/Objectives.h"
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
	this->crackSize = GameUtils::getKeyOrDefault(this->properties, Crack::MapPropertyCrackSize, Value("")).asString();

	if (this->crackSize == "small")
	{
		this->crack = Sprite::create(ObjectResources::Interactive_Cracks_CrackSmallWhite);
	}
	else if (this->crackSize == "medium")
	{
		this->crack = Sprite::create(ObjectResources::Interactive_Cracks_CrackMediumWhite);
	}
	else if (this->crackSize == "large")
	{
		this->crack = Sprite::create(ObjectResources::Interactive_Cracks_CrackLargeWhite);
	}
	
	this->addChild(this->crack);
}

Crack::~Crack()
{
}

void Crack::initializePositions()
{
	super::initializePositions();

	if (this->crackSize == "small")
	{
		this->crack->setPosition(Vec2(96.0f, 0.0f));
	}
	else if (this->crackSize == "medium")
	{
		this->crack->setPosition(Vec2(96.0f, 0.0f));
	}
	else if (this->crackSize == "large")
	{
		this->crack->setPosition(Vec2(96.0f, 0.0f));
	}
}

void Crack::onInteract(PlatformerEntity* interactingEntity)
{
	super::onInteract(interactingEntity);
}
