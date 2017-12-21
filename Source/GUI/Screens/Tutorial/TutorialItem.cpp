#include "TutorialItem.h"

TutorialItem* TutorialItem::create(std::string description, std::string mapFile, int index, std::function<void(TutorialItem*)> onMouseOver)
{
	TutorialItem* tutorialItem = new TutorialItem(description, mapFile, index, onMouseOver);

	tutorialItem->autorelease();

	return tutorialItem;
}

TutorialItem::TutorialItem(std::string description, std::string mapFile, int index, std::function<void(TutorialItem*)> onMouseOver)
{
	this->tutorialMapFile = mapFile;
	this->tutorialDescription = description;
	this->onMouseOverEvent = onMouseOver;
	this->page = index / TutorialItem::MaxEntriesPerPage;

	// Adjust index to be relative to the current page
	int orderIndex = index % TutorialItem::MaxEntriesPerPage;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->frame = Sprite::create(Resources::Menus_TutorialMenu_TutorialEntry);
	this->indexLabel = Label::create(std::to_string(index + 1), Resources::Fonts_Montserrat_Medium, 28);

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

	// Set position based on order index
	Vec2 position = Vec2(
		origin.x + visibleSize.width / 2 - 256.0f + (orderIndex % TutorialItem::MaxEntriesPerRow) * 128.0f,
		origin.y + visibleSize.height / 2 + 128.0f + ((orderIndex / TutorialItem::MaxEntriesPerRow) * -160.0f)
	);

	this->startButton->SetClickCallback(CC_CALLBACK_1(TutorialItem::OnTutorialClick, this));
	this->startButton->SetMouseOverCallback(CC_CALLBACK_1(TutorialItem::OnTutorialMouseOver, this));

	this->frame->setPosition(position);
	this->startButton->setPosition(Vec2(position.x + this->frame->getContentSize().width / 2 - this->startButton->getContentSize().width / 2, position.y));
	this->indexLabel->setPosition(Vec2(position.x + this->frame->getContentSize().width / 2 - this->startButton->getContentSize().width / 2, position.y + 20));

	this->setContentSize(this->frame->getContentSize());

	this->addChild(this->frame);
	this->addChild(this->startButton);
	this->addChild(this->indexLabel);
}

TutorialItem::~TutorialItem()
{
}

void TutorialItem::OnTutorialClick(MenuSprite* tutorialItem)
{
	Director::getInstance()->replaceScene(Level::create(this->tutorialMapFile));
}

void TutorialItem::OnTutorialMouseOver(MenuSprite* tutorialItem)
{
	this->onMouseOverEvent(this);
}

void TutorialItem::onEnter()
{
	Node::onEnter();
}

