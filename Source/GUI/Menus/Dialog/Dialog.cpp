#include "Dialog.h"

Dialog* Dialog::create(Portrait portraitLeft, Portrait portraitRight, Speaker speaker, TextMood textMood, std::string text)
{
	Dialog* dialog = new Dialog(portraitLeft, portraitRight, speaker, textMood, text);

	dialog->autorelease();

	return dialog;
}

Dialog::Dialog(Portrait portraitLeft, Portrait portraitRight, Speaker speaker, TextMood textMood, std::string text)
{
	this->children = new std::map<std::string, Dialog*>();
	this->spriteLeft = this->getSprite(portraitLeft);
	this->spriteRight = this->getSprite(portraitRight);
	this->spriteRight->setFlippedX(true);

	this->dialogText = Label::create(text, Resources::Fonts_Montserrat_Medium, 24);
	this->dialogText->enableWrap(true);
	this->dialogText->setDimensions(1024.0f, 224.0f);

	switch (speaker)
	{
	case Speaker::NoSpeaker:
		this->dialogText->setAlignment(TextHAlignment::CENTER);
		break;
	case Speaker::Left:
		this->dialogText->setAlignment(TextHAlignment::LEFT);
		break;
	case Speaker::Right:
		this->dialogText->setAlignment(TextHAlignment::RIGHT);
		break;
	}

	switch (textMood)
	{
	case TextMood::Normal:
		this->dialogText->setColor(Color3B::WHITE);
		break;
	case TextMood::Calm:
		this->dialogText->setColor(Color3B(0x91, 0xb6, 0xd8));
		break;
	case TextMood::Angry:
		this->dialogText->setColor(Color3B(0xcd, 0x4f, 0x39));
		break;
	}

	this->initializePositions();

	this->addChild(this->spriteLeft);
	this->addChild(this->spriteRight);
	this->addChild(this->dialogText);
}

Dialog::~Dialog()
{
	delete(this->children);
}

void Dialog::push(Dialog* dialog)
{
	this->push(dialog, "");
}

void Dialog::push(Dialog* dialog, std::string choice)
{
	this->children->insert_or_assign(choice, dialog);
}

void Dialog::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->spriteLeft->setPosition(Vec2(visibleSize.width / 2 - 732, 16));
	this->spriteRight->setPosition(Vec2(visibleSize.width / 2 + 732, 16));
	this->dialogText->setPosition(Vec2(visibleSize.width / 2, -16));
}

Sprite* Dialog::getSprite(Portrait portrait)
{
	switch (portrait)
	{
	case Portrait::Player:
		return Sprite::create(Resources::Menus_DialogMenu_PlayerPortrait);
	case Portrait::NoPortrait:
	default:
		return Sprite::create();
	}
}
