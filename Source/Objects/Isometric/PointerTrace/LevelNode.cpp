#include "LevelNode.h"

#include "cocos/base/CCValue.h"

#include "Resources/UIResources.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/NavigationEvents.h"

using namespace cocos2d;

const std::string LevelNode::MapKeyLevelNode = "level-node";
const std::string LevelNode::MapKeyMapFile = "map-file";
const std::string LevelNode::MapKeyIndex = "index";

LevelNode* LevelNode::create(const cocos2d::ValueMap& properties)
{
	LevelNode* instance = new LevelNode(properties);

	instance->autorelease();

	return instance;
}

LevelNode::LevelNode(const cocos2d::ValueMap& properties) : super(properties)
{
	this->nodeMapFile = GameUtils::getKeyOrDefault(this->properties, LevelNode::MapKeyMapFile, Value("")).asString();
	this->mapSprite = ClickableNode::create(UIResources::Menus_WorldMap_MarkerCurrent, UIResources::Menus_WorldMap_MarkerCurrentSelected);

	this->setAnchorPoint(Vec2(0.0f, 0.0f));

	this->addChild(this->mapSprite);
}

LevelNode::~LevelNode()
{
}

void LevelNode::setLocked(bool newLocked)
{
	if (newLocked)
	{
		this->mapSprite->setVisible(false);
	}
	else
	{
		this->mapSprite->setVisible(true);
	}

	this->locked = newLocked;
}

bool LevelNode::isLocked()
{
	return this->locked;
}

void LevelNode::initializePositions()
{
	super::initializePositions();

	this->setContentSize(this->mapSprite->getContentSize());
}

void LevelNode::initializeListeners()
{
	super::initializeListeners();

	this->mapSprite->setMouseClickCallback([=](MouseEvents::MouseEventArgs*)
	{
		NavigationEvents::navigatePointerTraceMap(NavigationEvents::NavigateMapArgs(this->nodeMapFile));
	});
}
