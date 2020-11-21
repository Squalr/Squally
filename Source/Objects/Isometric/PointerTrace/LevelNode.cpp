#include "LevelNode.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Resources/UIResources.h"

#include "Engine/Events/NavigationEvents.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/PointerTrace/PointerTraceMap.h"

using namespace cocos2d;

const std::string LevelNode::MapKey = "level-node";
const std::string LevelNode::PropertyMapFile = "map-file";
const std::string LevelNode::PropertyLevelIndex = "level-index";
const std::string LevelNode::PropertyGroupIndex = "group-index";
const std::string LevelNode::PropertyGroupFinale = "group-finale";
const std::string LevelNode::SaveKeyPrefix = "POINTER_TRACE_LEVEL_";

LevelNode* LevelNode::create(const cocos2d::ValueMap& properties)
{
	LevelNode* instance = new LevelNode(properties);

	instance->autorelease();

	return instance;
}

LevelNode::LevelNode(const cocos2d::ValueMap& properties) : super(properties)
{
	this->nodeMapFile = GameUtils::getKeyOrDefault(this->properties, LevelNode::PropertyMapFile, Value("")).asString();
	this->levelIndex = GameUtils::getKeyOrDefault(this->properties, LevelNode::PropertyLevelIndex, Value(0)).asInt();
	this->groupIndex = GameUtils::getKeyOrDefault(this->properties, LevelNode::PropertyGroupIndex, Value(0)).asInt();
	this->isGroupFinale = GameUtils::getKeyOrDefault(this->properties, LevelNode::PropertyGroupFinale, Value(false)).asBool();
	this->disabledSprite = Sprite::create(UIResources::Menus_WorldMap_MarkerCompleted);
	this->sprite = ClickableNode::create(UIResources::Menus_WorldMap_MarkerCurrent, UIResources::Menus_WorldMap_MarkerCurrentSelected);
	this->indexLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::M3, ConstantString::create(std::to_string(this->levelIndex)));

	this->setZSorted(true);
	
	this->disabledSprite->setScale(2.0f);
	this->sprite->setScale(2.0f);

	this->indexLabel->enableOutline(Color4B::BLACK, 4);

	if (this->nodeMapFile != "")
	{
		this->nodeMapFile = "Isometric/Maps/" + this->nodeMapFile + ".tmx";
	}

	this->addChild(this->disabledSprite);
	this->addChild(this->sprite);
	this->addChild(this->indexLabel);
}

LevelNode::~LevelNode()
{
}

void LevelNode::onEnter()
{
	super::onEnter();

	ObjectEvents::TriggerBindObjectToUI(RelocateObjectArgs(this->indexLabel));

	this->setLockState();
}

void LevelNode::initializePositions()
{
	super::initializePositions();

	Vec2 offset = Vec2(64.0f, 128.0f);

	this->disabledSprite->setPosition(offset);
	this->sprite->setPosition(offset);

	this->setContentSize(this->sprite->getContentSize());
}

void LevelNode::initializeListeners()
{
	super::initializeListeners();

	this->sprite->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		NavigationEvents::LoadScene(NavigationEvents::LoadSceneArgs([=]()
		{
			PointerTraceMap* map = PointerTraceMap::create(this->nodeMapFile, [=]()
			{
				SaveManager::SaveGlobalData(this->getSaveKey(), Value(true));
			});

			return map;
		}));
	});
}

std::string LevelNode::getSaveKey()
{
	if (this->isGroupFinale)
	{
		// Use a special save key for the final entry in each group
		return LevelNode::SaveKeyPrefix + std::to_string(this->groupIndex) + "_" + "FINALE";
	}

	return LevelNode::SaveKeyPrefix + std::to_string(this->groupIndex) + "_" + std::to_string(this->levelIndex);
}

std::string LevelNode::getPreviousSaveKey()
{
	if (this->groupIndex > 0 && this->levelIndex == 0)
	{
		// Previous level is the end of a group
		return  LevelNode::SaveKeyPrefix + std::to_string(this->groupIndex - 1) + "_" + "FINALE";
	}
	else if (this->levelIndex <= 0)
	{
		// No previous level
		return "";
	}

	// Standard index-based previous level in the same group
	return LevelNode::SaveKeyPrefix + std::to_string(this->groupIndex) + "_" + std::to_string(this->levelIndex - 1);
}

void LevelNode::setLockState()
{
	std::string previousSaveKey = this->getPreviousSaveKey();
	std::string saveKey = this->getSaveKey();
	
	if (previousSaveKey == ""
		|| SaveManager::GetGlobalDataOrDefault(previousSaveKey, Value(false)).asBool()
		|| SaveManager::GetGlobalDataOrDefault(saveKey, Value(false)).asBool())
	{
		this->disabledSprite->setVisible(false);
		this->sprite->setVisible(true);
	}
	else
	{
		this->disabledSprite->setVisible(true);
		this->sprite->setVisible(false);
	}
}
