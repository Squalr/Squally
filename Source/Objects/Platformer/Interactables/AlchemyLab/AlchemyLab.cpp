#include "AlchemyLab.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Inventory/Item.h"
#include "Engine/Inventory/MinMaxPool.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/ItemPools/RecipePools/RecipePoolDeserializer.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Recipe.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/ItemResources.h"
#include "Resources/FXResources.h"
#include "Resources/ObjectResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string AlchemyLab::MapKeyAlchemyLab = "alchemy-lab";

AlchemyLab* AlchemyLab::create(ValueMap& properties)
{
	AlchemyLab* instance = new AlchemyLab(properties);

	instance->autorelease();

	return instance;
}

AlchemyLab::AlchemyLab(ValueMap& properties) : super(properties, InteractObject::InteractType::Input, Size(192.0f, 440.0f))
{
	this->alchemyLab = Sprite::create(ObjectResources::Interactive_AlchemyLab_AlchemyLab);
	this->shine = Sprite::create(UIResources::HUD_EmblemGlow);
	this->potion = Sprite::create(ItemResources::Consumables_Potions_ManaFlaskAdd);
	this->floatContainer = Node::create();
	this->recipes = std::vector<Item*>();
	this->recipePoolName = GameUtils::getKeyOrDefault(this->properties, RecipePoolDeserializer::MapKeyTypeRecipePool, Value("")).asString();
	this->recipePool = nullptr;
	this->recipePoolDeserializer = RecipePoolDeserializer::create();
	
	this->floatContainer->addChild(this->shine);
	this->floatContainer->addChild(this->potion);
	this->addChild(this->alchemyLab);
	this->addChild(this->floatContainer);
	this->addChild(this->recipePoolDeserializer);
}

AlchemyLab::~AlchemyLab()
{
}

void AlchemyLab::onEnter()
{
	super::onEnter();

	this->floatContainer->runAction(RepeatForever::create(Sequence::create(
		EaseSineInOut::create(MoveTo::create(3.0f, Vec2(0.0f, 96.0f))),
		EaseSineInOut::create(MoveTo::create(3.0f, Vec2(0.0f, 160.0f))),
		nullptr
	)));

	this->loadRecipePool();
}

void AlchemyLab::initializePositions()
{
	super::initializePositions();

	this->potion->setPosition(Vec2(24.0f, 0.0f));
	this->shine->setPosition(Vec2(24.0f, 0.0f));
	this->floatContainer->setPosition(Vec2(0.0f, 160.0f));
	this->alchemyLab->setPosition(Vec2(0.0f, 0.0f));
}

void AlchemyLab::initializeListeners()
{
	super::initializeListeners();
}

void AlchemyLab::onInteract()
{
	super::onInteract();

	PlatformerEvents::TriggerOpenAlchemy(PlatformerEvents::CraftingOpenArgs(this->recipes));
}

void AlchemyLab::loadRecipePool()
{
	ValueMap valueMap = ValueMap();

	valueMap[GameObject::MapKeyType] = RecipePoolDeserializer::MapKeyTypeRecipePool;
	valueMap[GameObject::MapKeyName] = this->recipePoolName;

	ObjectDeserializer::ObjectDeserializationRequestArgs deserializeArgs = ObjectDeserializer::ObjectDeserializationRequestArgs(valueMap, [&](ObjectDeserializer::ObjectDeserializationArgs args)
	{
		this->recipePool = static_cast<MinMaxPool*>(args.gameObject);

		for (auto next : this->recipePool->getItems({ }))
		{
			this->recipes.push_back(next);

			this->addChild(next);
		}

		this->addChild(this->recipePool);
	});

	this->recipePoolDeserializer->deserialize(&deserializeArgs);
}
