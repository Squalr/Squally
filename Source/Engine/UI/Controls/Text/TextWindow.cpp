#include "TextWindow.h"

#include "cocos/2d/CCNode.h"
#include "cocos/2d/CCLayer.h"
#include "cocos/ui/UIRichText.h"
#include "cocos/ui/UIScrollView.h"
#include "cocos/ui/UITextField.h"

#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/UI/Controls/MenuLabel.h"

#include "Strings/Generics/Newline.h"

using namespace cocos2d;
using namespace cocos2d::ui;

const Size TextWindow::Padding = Size(8.0f, 4.0f);
const float TextWindow::TitleBarHeight = 48.0f;
const Color4B TextWindow::DefaultTitleBarColor = Color4B(59, 92, 97, 192);
const Color4B TextWindow::DefaultWindowColor = Color4B(39, 58, 61, 192);

TextWindow* TextWindow::create(LocalizedString* windowTitle, LocalizedLabel* referenceContentLabel, Size windowSize, Color3B fontColor)
{
	TextWindow* instance = new TextWindow(windowTitle, referenceContentLabel, windowSize, fontColor);

	instance->autorelease();

	return instance;
}

TextWindow::TextWindow(LocalizedString* windowTitle, LocalizedLabel* referenceContentLabel, Size windowSize, Color3B fontColor)
{
	this->referenceContentLabel = referenceContentLabel;

	this->marginSize = 0;

	this->textElements = std::vector<std::tuple<LocalizedString*, cocos2d::Color3B>>();
	this->scrollView = ScrollView::create();
	this->displayedText = RichText::create();
	this->background = LayerColor::create(TextWindow::DefaultWindowColor, windowSize.width, windowSize.height);
	this->titleBar = LayerColor::create(TextWindow::DefaultTitleBarColor, windowSize.width, TextWindow::TitleBarHeight);
	this->windowTitle = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H2, windowTitle);

	this->scrollView->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->scrollView->setDirection(ScrollView::Direction::BOTH);
	this->displayedText->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->displayedText->setWrapMode(RichText::WrapMode::WRAP_PER_CHAR);
	this->displayedText->ignoreContentAdaptWithSize(false);

	this->scrollView->addChild(this->displayedText);

	this->addChild(this->referenceContentLabel);
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
	super::onEnter();
}

void TextWindow::initializePositions()
{
	super::initializePositions();

	Size windowSize = this->background->getContentSize();

	this->scrollView->setContentSize(windowSize);
	this->scrollView->setInnerContainerSize(Size(windowSize.width, windowSize.height * 2));
	this->displayedText->setContentSize(Size(windowSize.width - this->marginSize - TextWindow::Padding.width * 2.0f, windowSize.height - TextWindow::Padding.height * 2.0f));

	this->scrollView->setPosition(Vec2(0.0f, 0.0f));
	this->background->setPosition(-windowSize.width / 2.0f, -windowSize.height / 2.0f);
	this->displayedText->setPosition(Vec2(this->marginSize + TextWindow::Padding.width,this->scrollView->getInnerContainerSize().height - TextWindow::Padding.height));
	this->titleBar->setPosition(-windowSize.width / 2.0f, windowSize.height / 2.0f);
	this->windowTitle->setPosition(0.0f, windowSize.height / 2 + TextWindow::TitleBarHeight / 2.0f);
}

void TextWindow::initializeListeners()
{
	super::initializeListeners();
}

void TextWindow::setWindowColor(Color4B windowColor)
{
	Size windowSize = this->background->getContentSize();

	this->background->initWithColor(windowColor, windowSize.width, windowSize.height);

	this->initializePositions();
}

void TextWindow::setTitleBarColor(Color4B titleBarColor)
{
	Size titleSize = this->titleBar->getContentSize();

	this->titleBar->initWithColor(titleBarColor, titleSize.width, titleSize.height);

	this->initializePositions();
}

void TextWindow::setTitleStringReplaceVariables(LocalizedString* stringReplaceVariables)
{
	this->windowTitle->setStringReplacementVariables(stringReplaceVariables);
}

void TextWindow::setTitleStringReplaceVariables(std::vector<LocalizedString*> stringReplaceVariables)
{
	this->windowTitle->setStringReplacementVariables(stringReplaceVariables);
}

void TextWindow::insertText(LocalizedString* text, Color3B color)
{
	RichElement* element = RichElementText::create(0, color, 0xFF, text->getString(), this->referenceContentLabel->getFont(), this->referenceContentLabel->getFontSize());

	this->addChild(text); // Retain the element
	this->textElements.push_back(std::make_tuple(text, color));
	this->displayedText->pushBackElement(element);
}

void TextWindow::setMarginSize(float newMarginSize)
{
	this->marginSize = newMarginSize;
	this->initializePositions();
}

void TextWindow::insertNewline()
{
	LocalizedString* text = Strings::Generics_Newline::create();
	RichElement* element = RichElementNewLine::create(0, this->fontColor, 0xFF);

	this->addChild(text); // Retain the element
	this->textElements.push_back(std::make_tuple(text, Color3B()));
	this->displayedText->pushBackElement(element);
	this->displayedText->formatText();
}

void TextWindow::clearText()
{
	for (auto it = this->textElements.begin(); it != this->textElements.end(); it++)
	{
		this->removeChild(std::get<0>(*it));
	}

	this->textElements.clear();
	this->displayedText->clearElements();
	this->displayedText->formatText();
}

void TextWindow::rebuildText()
{
	std::vector<std::tuple<LocalizedString*, cocos2d::Color3B>> elements = this->textElements;

	this->clearText();

	for (auto it = elements.begin(); it != elements.end(); it++)
	{
		if (dynamic_cast<Strings::Generics_Newline*>(std::get<0>(*it)) != nullptr)
		{
			this->insertNewline();
		}
		else
		{
			this->insertText(std::get<0>(*it), std::get<1>(*it));
		}
	}
}
