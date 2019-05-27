#include "PlatformerEnemy.h"

#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/Item.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/StrUtils.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItemDeserializer.h"

#include "Resources/MapResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string PlatformerEnemy::SaveKeyIsDead = "is-dead";
const std::string PlatformerEnemy::MapKeyBattleArgs = "battle-args";
const std::string PlatformerEnemy::MapKeyBattleMap = "battle-map";
const std::string PlatformerEnemy::MapKeyAlly1 = "ally-1";
const std::string PlatformerEnemy::MapKeyAlly2 = "ally-2";
const std::string PlatformerEnemy::MapKeyAlly3 = "ally-3";

PlatformerEnemy::PlatformerEnemy(
	cocos2d::ValueMap& properties,
	std::string scmlResource,
	std::string emblemResource,
	PlatformerCollisionType collisionType, 
	cocos2d::Size size, 
	float scale,
	cocos2d::Vec2 collisionOffset,
	int baseHealth,
	int baseSpecial)
	: super(properties, scmlResource, emblemResource, collisionType, size, scale, collisionOffset, baseHealth, baseSpecial)
{
	this->combatEntityList = std::vector<std::string>();
	this->resurrectButton = ClickableNode::create(UIResources::Menus_Icons_Voodoo, UIResources::Menus_Icons_Voodoo);
	this->killButton = ClickableNode::create(UIResources::Menus_Icons_Skull, UIResources::Menus_Icons_Skull);
	this->battleMapArgs = GameUtils::getKeyOrDefault(this->properties, PlatformerEnemy::MapKeyBattleArgs, Value("")).asString();
	this->battleMapResource = GameUtils::getKeyOrDefault(this->properties, PlatformerEnemy::MapKeyBattleMap, Value(MapResources::EndianForest_Battlegrounds)).asString();

	this->combatEntityList.push_back(this->properties.at(PlatformerEnemy::MapKeyName).asString());

	if (GameUtils::keyExists(this->properties, PlatformerEnemy::MapKeyAlly1))
	{
		this->combatEntityList.push_back(this->properties.at(PlatformerEnemy::MapKeyAlly1).asString());
	}

	if (GameUtils::keyExists(this->properties, PlatformerEnemy::MapKeyAlly2))
	{
		this->combatEntityList.push_back(this->properties.at(PlatformerEnemy::MapKeyAlly2).asString());
	}

	if (GameUtils::keyExists(this->properties, PlatformerEnemy::MapKeyAlly3))
	{
		this->combatEntityList.push_back(this->properties.at(PlatformerEnemy::MapKeyAlly3).asString());
	}

	this->resurrectButton->setVisible(false);
	this->killButton->setVisible(false);

	this->addChild(this->resurrectButton);
	this->addChild(this->killButton);
}

PlatformerEnemy::~PlatformerEnemy()
{
}

void PlatformerEnemy::onEnter()
{
	super::onEnter();

	this->buildDropInventory();
}

void PlatformerEnemy::onDeveloperModeEnable()
{
	super::onDeveloperModeEnable();

	this->resurrectButton->setVisible(true);
	this->killButton->setVisible(true);
}

void PlatformerEnemy::onDeveloperModeDisable()
{
	super::onDeveloperModeDisable();

	this->resurrectButton->setVisible(false);
	this->killButton->setVisible(false);
}

void PlatformerEnemy::initializePositions()
{
	super::initializePositions();

	this->killButton->setPosition(Vec2(-64.0f, this->getEntitySize().height + 32.0f));
	this->resurrectButton->setPosition(Vec2(64.0f, this->getEntitySize().height + 32.0f));
}

void PlatformerEnemy::initializeListeners()
{
	super::initializeListeners();

	this->resurrectButton->setMouseClickCallback([=](MouseEvents::MouseEventArgs*)
	{
		this->saveObjectState(PlatformerEnemy::SaveKeyIsDead, Value(false));
		this->animationNode->playAnimation(SmartAnimationNode::AnimationPlayMode::ReturnToIdle, 1.25f);
		this->health = std::max(this->getMaxHealth(), 1);
	});

	this->killButton->setMouseClickCallback([=](MouseEvents::MouseEventArgs*)
	{
		this->animationNode->playAnimation("Death", SmartAnimationNode::AnimationPlayMode::PauseOnAnimationComplete);
		this->health = 0;

		if (!this->mapEvent.empty())
		{
			ObjectEvents::TriggerBroadCastMapObjectState(this->mapEvent, ValueMap());
		}
	});
}

std::string PlatformerEnemy::getBattleMapResource()
{
	if (this->battleMapResource == "")
	{
		return this->battleMapResource;
	}

	if (StrUtils::endsWith(this->battleMapResource, ".tmx", true))
	{
		return this->battleMapResource;
	}

	return "Platformer/Maps/" + this->battleMapResource + ".tmx";
}

std::string PlatformerEnemy::getBattleMapArgs()
{
	return this->battleMapArgs;
}

std::vector<std::string> PlatformerEnemy::getCombatEntityList()
{
	return this->combatEntityList;
}

void PlatformerEnemy::onObjectStateLoaded()
{
	super::onObjectStateLoaded();

	if (this->getObjectStateOrDefault(PlatformerEnemy::SaveKeyIsDead, Value(false)).asBool())
	{
		this->animationNode->playAnimation("Dead", SmartAnimationNode::AnimationPlayMode::PauseOnAnimationComplete);
		this->health = 0;

		if (!this->mapEvent.empty())
		{
			ObjectEvents::TriggerBroadCastMapObjectState(this->mapEvent, ValueMap());
		}
	}
}

void PlatformerEnemy::buildDropInventory()
{
	for (auto it = this->dropTable.begin(); it != this->dropTable.end(); it++)
	{
		if (RandomHelper::random_real(0.0f, 1.0f) <= it->second)
		{
			PlatformerItemDeserializer::onDeserializationRequest(InventoryEvents::RequestItemDeserializationArgs(it->first, [=](Item* item)
			{
				this->getInventory()->forceInsert(item);
			}));
		}
	}
}
