#include "TutorialItem.h"

TutorialItem* TutorialItem::create(std::string description, std::string mapFile, Vec2 position)
{
	TutorialItem* tutorialItem = new TutorialItem(description, mapFile, position);

	tutorialItem->autorelease();

	return tutorialItem;
}

TutorialItem::TutorialItem(std::string description, std::string mapFile, Vec2 position)
{
	this->tutorialDescription = description;
	this->tutorialMapFile = mapFile;
	this->description = Label::create(description, Resources::Fonts_Montserrat_Medium, 14.0f);

	this->sprite = MenuSprite::create(
		Resources::Menus_TutorialMenu_TutorialItem,
		Resources::Menus_TutorialMenu_TutorialItemHover,
		Resources::Menus_TutorialMenu_TutorialItemClick);

	this->sprite->SetClickCallback(CC_CALLBACK_1(TutorialItem::OnTutorialClick, this));

	this->description->setPosition(position);
	this->sprite->setPosition(position);

	this->setContentSize(this->sprite->getContentSize());

	this->addChild(this->sprite);
	this->addChild(this->description);
}

TutorialItem::~TutorialItem()
{
}

void TutorialItem::OnTutorialClick(MenuSprite* tutorialItem)
{
	Director::getInstance()->replaceScene(new Level(this->tutorialMapFile));
}

void TutorialItem::onEnter()
{
	Node::onEnter();
}

