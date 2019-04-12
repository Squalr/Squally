#include "CipherLevelItem.h"

#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Events/NavigationEvents.h"
#include "Scenes/Platformer/Level/PlatformerMap.h"
#include "Scenes/Hexus/Deck.h"

#include "Resources/UIResources.h"

#include "Strings/Generics/Constant.h"

using namespace cocos2d;

CipherLevelItem* CipherLevelItem::create(std::string description, std::string mapFile, int index, std::function<void(CipherLevelItem*)> onMouseOver)
{
	CipherLevelItem* instance = new CipherLevelItem(description, mapFile, index, onMouseOver);

	instance->autorelease();

	return instance;
}

CipherLevelItem::CipherLevelItem(std::string description, std::string mapFile, int index, std::function<void(CipherLevelItem*)> onMouseOver)
{
	this->tutorialMapFile = mapFile;
	this->tutorialDescription = description;
	this->onMouseOverEvent = onMouseOver;
	this->levelIndex = index;

	this->frame = Sprite::create(UIResources::Menus_TutorialMenu_TutorialEntry);
	
	// TODO: Load save data
	this->isLevelComplete = true;

	if (this->isLevelComplete)
	{
		this->startButton = ClickableNode::create(
			UIResources::Menus_TutorialMenu_TutorialEntryComplete,
			UIResources::Menus_TutorialMenu_TutorialEntryCompleteSelected);
	}
	else
	{
		this->startButton = ClickableNode::create(
			UIResources::Menus_TutorialMenu_TutorialEntry,
			UIResources::Menus_TutorialMenu_TutorialEntrySelected);
	}

	this->startButton->setMouseClickCallback(CC_CALLBACK_0(CipherLevelItem::onTutorialClick, this));
	this->startButton->setMouseOverCallback(CC_CALLBACK_0(CipherLevelItem::onTutorialMouseOver, this));
	this->setContentSize(this->frame->getContentSize());
	this->setCascadeOpacityEnabled(true);

	this->addChild(this->frame);
	this->addChild(this->startButton);
}

CipherLevelItem::~CipherLevelItem()
{
}

void CipherLevelItem::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// Adjust index to be relative to the current page
	int orderIndex = this->levelIndex % CipherLevelItem::MaxEntriesPerPage;

	// Set position based on order index
	Vec2 position = Vec2(
		origin.x + visibleSize.width / 2 - 272.0f + (orderIndex % CipherLevelItem::MaxEntriesPerRow) * 136.0f,
		origin.y + visibleSize.height / 2 + 104.0f + ((orderIndex / CipherLevelItem::MaxEntriesPerRow) * -160.0f)
	);

	this->frame->setPosition(position);
	this->startButton->setPosition(Vec2(position.x + this->frame->getContentSize().width / 2 - this->startButton->getContentSize().width / 2, position.y));
}

void CipherLevelItem::onTutorialClick()
{
	//// HexusEvents::startGame(HexusEvents::HexusGameEventArgs(deck1, deck2));
}

void CipherLevelItem::onTutorialMouseOver()
{
	this->onMouseOverEvent(this);
}
