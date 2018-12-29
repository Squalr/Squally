﻿#include "TextWindow.h"

#include "cocos/2d/CCNode.h"
#include "cocos/2d/CCLayer.h"
#include "cocos/ui/UIRichText.h"
#include "cocos/ui/UIScrollView.h"
#include "cocos/ui/UITextField.h"

#include "Engine/Localization/Localization.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/UI/Controls/MenuLabel.h"

using namespace cocos2d;
using namespace cocos2d::ui;

const Size TextWindow::padding = Size(8.0f, 4.0f);
const float TextWindow::titleBarHeight = 48.0f;
const Color4B TextWindow::defaultTitleBarColor = Color4B(59, 92, 97, 192);
const Color4B TextWindow::defaultWindowColor = Color4B(39, 58, 61, 192);

TextWindow* TextWindow::create(LocalizedString* windowTitle, Size initWindowSize, Color3B initFontColor)
{
	TextWindow* instance = new TextWindow(windowTitle, initWindowSize, initFontColor);

	instance->autorelease();

	return instance;
}

TextWindow::TextWindow(LocalizedString* windowTitle, Size initWindowSize, Color3B initFontColor)
{
	this->displayTextElements = std::vector<RichElement*>();

	this->marginSize = 0;
	this->windowSize = initWindowSize;

	this->windowColor = TextWindow::defaultWindowColor;
	this->titleBarColor = TextWindow::defaultTitleBarColor;

	this->scrollView = ScrollView::create();
	this->displayedText = RichText::create();
	this->background = Node::create();
	this->titleBar = Node::create();
	this->windowTitle = MenuLabel::create(LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H2, windowTitle));

	this->background->addChild(LayerColor::create(this->windowColor, this->windowSize.width, this->windowSize.height));
	this->titleBar->addChild(LayerColor::create(this->titleBarColor, this->windowSize.width, TextWindow::titleBarHeight));

	this->scrollView->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->scrollView->setDirection(ScrollView::Direction::BOTH);
	this->displayedText->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->displayedText->setWrapMode(RichText::WrapMode::WRAP_PER_CHAR);
	this->displayedText->ignoreContentAdaptWithSize(false);

	this->scrollView->addChild(this->displayedText);

	this->addChild(this->background);
	this->addChild(this->titleBar);
	this->addChild(this->windowTitle);
	this->addChild(this->scrollView);
}

TextWindow::~TextWindow()
{
}

void TextWindow::onEnter()
{
	SmartNode::onEnter();

	this->scheduleUpdate();
}

void TextWindow::initializePositions()
{
	SmartNode::initializePositions();

	this->scrollView->setContentSize(windowSize);
	this->scrollView->setInnerContainerSize(Size(windowSize.width, windowSize.height * 2));
	this->displayedText->setContentSize(Size(windowSize.width - this->marginSize - TextWindow::padding.width * 2.0f, windowSize.height - TextWindow::padding.height * 2.0f));

	this->scrollView->setPosition(Vec2(0.0f, 0.0f));
	this->background->setPosition(-this->windowSize.width / 2.0f, -this->windowSize.height / 2.0f);
	this->displayedText->setPosition(Vec2(this->marginSize + TextWindow::padding.width,this->scrollView->getInnerContainerSize().height - TextWindow::padding.height));
	this->titleBar->setPosition(-this->windowSize.width / 2.0f, this->windowSize.height / 2.0f);
	this->windowTitle->setPosition(0.0f, this->windowSize.height / 2 + TextWindow::titleBarHeight / 2.0f);
}

void TextWindow::initializeListeners()
{
	SmartNode::initializeListeners();
}

void TextWindow::setWindowColor(Color4B newWindowColor)
{
	this->windowColor = newWindowColor;
	this->background->removeAllChildren();
	this->background->addChild(LayerColor::create(this->windowColor, this->windowSize.width, this->windowSize.height));
	this->initializePositions();
}

void TextWindow::setTitleBarColor(Color4B newTitleBarColor)
{
	this->titleBarColor = newTitleBarColor;
	this->titleBar->removeAllChildren();
	this->titleBar->addChild(LayerColor::create(this->titleBarColor, this->windowSize.width,
			TextWindow::titleBarHeight));
	this->initializePositions();
}

void TextWindow::setTitle(std::string text)
{
	this->windowTitle->setText(text);
}

void TextWindow::insertText(std::string text, Color3B color)
{
	RichElement* element = RichElementText::create(0, color, 0xFF, text, Localization::getCodingFont(), Localization::getFontSizeH3(Localization::getCodingFont()));

	this->displayTextElements.push_back(element);
	this->displayedText->pushBackElement(element);
}

void TextWindow::setMarginSize(float newMarginSize)
{
	this->marginSize = newMarginSize;
	this->initializePositions();
}

void TextWindow::insertNewline()
{
	RichElement* element = RichElementNewLine::create(0, this->fontColor, 0xFF);

	this->displayTextElements.push_back(element);
	this->displayedText->pushBackElement(element);

	this->displayedText->formatText();
}

void TextWindow::clearText()
{
	for (auto iterator = this->displayTextElements.begin(); iterator != this->displayTextElements.end(); iterator++)
	{
		this->displayedText->removeElement(*iterator);
	}

	this->displayTextElements.clear();
	this->displayedText->formatText();
}

void TextWindow::update(float dt)
{
	// TODO: Dynamically set inner content size
	// this->scrollView->setInnerContainerSize(Size(windowSize.width, windowSize.height * 2));
	// this->initializePositions();
}
