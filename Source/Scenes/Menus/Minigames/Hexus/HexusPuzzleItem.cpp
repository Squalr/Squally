#include "HexusPuzzleItem.h"

HexusPuzzleItem* HexusPuzzleItem::create(std::string description, std::string mapFile, int index, std::function<void(HexusPuzzleItem*)> onMouseOver)
{
	HexusPuzzleItem* instance = new HexusPuzzleItem(description, mapFile, index, onMouseOver);

	instance->autorelease();

	return instance;
}

HexusPuzzleItem::HexusPuzzleItem(std::string description, std::string mapFile, int index, std::function<void(HexusPuzzleItem*)> onMouseOver)
{
	this->tutorialMapFile = mapFile;
	this->tutorialDescription = description;
	this->onMouseOverEvent = onMouseOver;
	this->levelIndex = index;
	this->page = index / HexusPuzzleItem::MaxEntriesPerPage;

	this->frame = Sprite::create(Resources::Menus_TutorialMenu_TutorialEntry);
	this->indexLabel = Label::create(std::to_string(index + 1), Localization::getMainFont(), 28.0f);

	// TODO: Load save data (steam cloud)
	this->isLevelComplete = true;

	if (this->isLevelComplete)
	{
		this->startButton = MenuSprite::create(
			Resources::Menus_TutorialMenu_TutorialEntryComplete,
			Resources::Menus_TutorialMenu_TutorialEntryCompleteSelected,
			Resources::Menus_TutorialMenu_TutorialEntryCompleteSelected);
	}
	else
	{
		this->startButton = MenuSprite::create(
			Resources::Menus_TutorialMenu_TutorialEntry,
			Resources::Menus_TutorialMenu_TutorialEntrySelected,
			Resources::Menus_TutorialMenu_TutorialEntrySelected);
	}

	this->startButton->setClickCallback(CC_CALLBACK_1(HexusPuzzleItem::onTutorialClick, this));
	this->startButton->setMouseOverCallback(CC_CALLBACK_1(HexusPuzzleItem::onTutorialMouseOver, this));
	this->setContentSize(this->frame->getContentSize());
	this->setCascadeOpacityEnabled(true);

	this->addChild(this->frame);
	this->addChild(this->startButton);
	this->addChild(this->indexLabel);
}

HexusPuzzleItem::~HexusPuzzleItem()
{
}

void HexusPuzzleItem::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// Adjust index to be relative to the current page
	int orderIndex = this->levelIndex % HexusPuzzleItem::MaxEntriesPerPage;

	// Set position based on order index
	Vec2 position = Vec2(
		origin.x + visibleSize.width / 2 - 272.0f + (orderIndex % HexusPuzzleItem::MaxEntriesPerRow) * 136.0f,
		origin.y + visibleSize.height / 2 + 104.0f + ((orderIndex / HexusPuzzleItem::MaxEntriesPerRow) * -160.0f)
	);

	this->frame->setPosition(position);
	this->startButton->setPosition(Vec2(position.x + this->frame->getContentSize().width / 2 - this->startButton->getContentSize().width / 2, position.y));
	this->indexLabel->setPosition(Vec2(position.x + this->frame->getContentSize().width / 2 - this->startButton->getContentSize().width / 2, position.y + 20));
}

void HexusPuzzleItem::onTutorialClick(MenuSprite* HexusPuzzleItem)
{
	NavigationEvents::loadMap(this->tutorialMapFile);
}

void HexusPuzzleItem::onTutorialMouseOver(MenuSprite* HexusPuzzleItem)
{
	this->onMouseOverEvent(this);
}
