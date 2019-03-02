#include "PlatformerEnemy.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/Item.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItemDeserializer.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string PlatformerEnemy::SaveKeyIsDead = "is_dead";
const std::string PlatformerEnemy::MapKeyBattleMap = "battle_map";
const std::string PlatformerEnemy::MapKeyAlly1 = "ally-1";
const std::string PlatformerEnemy::MapKeyAlly2 = "ally-2";
const std::string PlatformerEnemy::MapKeyAlly3 = "ally-3";

PlatformerEnemy::PlatformerEnemy(
	cocos2d::ValueMap& initProperties,
	std::string scmlResource,
	std::string emblemResource,
	PlatformerCollisionType collisionType, 
	cocos2d::Size size, 
	float scale,
	cocos2d::Vec2 collisionOffset,
	int baseHealth,
	int baseSpecial)
	: super(initProperties, scmlResource, emblemResource, collisionType, size, scale, collisionOffset, baseHealth, baseSpecial)
{
	this->battleMapResource = "";
	this->combatEntityList = std::vector<std::string>();
	this->resurrectButton = ClickableNode::create(UIResources::Menus_Icons_Voodoo, UIResources::Menus_Icons_Voodoo);
	this->killButton = ClickableNode::create(UIResources::Menus_Icons_Skull, UIResources::Menus_Icons_Skull);

	if (GameUtils::keyExists(initProperties, PlatformerEnemy::MapKeyBattleMap))
	{
		this->battleMapResource = initProperties.at(PlatformerEnemy::MapKeyBattleMap).asString();
	}

	this->combatEntityList.push_back(initProperties.at(PlatformerEnemy::MapKeyName).asString());

	if (GameUtils::keyExists(initProperties, PlatformerEnemy::MapKeyAlly1))
	{
		this->combatEntityList.push_back(initProperties.at(PlatformerEnemy::MapKeyAlly1).asString());
	}

	if (GameUtils::keyExists(initProperties, PlatformerEnemy::MapKeyAlly2))
	{
		this->combatEntityList.push_back(initProperties.at(PlatformerEnemy::MapKeyAlly2).asString());
	}

	if (GameUtils::keyExists(initProperties, PlatformerEnemy::MapKeyAlly3))
	{
		this->combatEntityList.push_back(initProperties.at(PlatformerEnemy::MapKeyAlly3).asString());
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

	this->resurrectButton->setClickCallback([=](ClickableNode*, MouseEvents::MouseEventArgs*)
	{
		this->animationNode->playAnimation(SmartAnimationNode::AnimationPlayMode::ReturnToIdle, 1.25f);
		this->health = std::max(this->getMaxHealth(), 1);
	});

	this->killButton->setClickCallback([=](ClickableNode*, MouseEvents::MouseEventArgs*)
	{
		this->animationNode->playAnimation("Death", SmartAnimationNode::AnimationPlayMode::PauseOnAnimationComplete);
		this->health = 0;
	});
}

std::string PlatformerEnemy::getBattleMapResource()
{
	if (this->battleMapResource == "")
	{
		return this->battleMapResource;
	}

	return "Platformer/Maps/" + this->battleMapResource + ".tmx";
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
