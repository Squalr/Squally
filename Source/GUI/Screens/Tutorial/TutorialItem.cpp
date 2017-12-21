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

	this->frame = Sprite::create(Resources::Menus_TutorialMenu_TutorialItem);
	this->startButton = MenuSprite::create(
		Resources::Menus_Buttons_PlayButton,
		Resources::Menus_Buttons_PlayButtonHover,
		Resources::Menus_Buttons_PlayButtonClick);

	this->startButton->SetClickCallback(CC_CALLBACK_1(TutorialItem::OnTutorialClick, this));

	this->description->setPosition(position);
	this->frame->setPosition(position);
	this->startButton->setPosition(Vec2(position.x + this->frame->getContentSize().width / 2 - this->startButton->getContentSize().width / 2, position.y));

	this->setContentSize(this->frame->getContentSize());

	this->addChild(this->frame);
	this->addChild(this->startButton);
	this->addChild(this->description);
}

TutorialItem::~TutorialItem()
{
}

void TutorialItem::OnTutorialClick(MenuSprite* tutorialItem)
{
	Director::getInstance()->replaceScene(Level::create(this->tutorialMapFile));
}

void TutorialItem::onEnter()
{
	Node::onEnter();
}

