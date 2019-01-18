#include "CodeWindow.h"

#include "cocos/2d/CCLayer.h"
#include "cocos/base/CCEventDispatcher.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/ui/UIRichText.h"
#include "cocos/ui/UIScrollView.h"
#include "cocos/ui/UITextField.h"

#include "Engine/Events/LocalizationEvents.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"

#include "Strings/Generics/Newline.h"
#include "Strings/Generics/Constant.h"

using namespace cocos2d;
using namespace cocos2d::ui;

const Color3B CodeWindow::lineNumberColor = Color3B(166, 166, 166);
const Size CodeWindow::Padding = Size(8.0f, 4.0f);
const float CodeWindow::TitleBarHeight = 48.0f;
const Color4B CodeWindow::DefaultTitleBarColor = Color4B(59, 92, 97, 255);
const Color4B CodeWindow::DefaultWindowColor = Color4B(39, 58, 61, 255);

CodeWindow* CodeWindow::create(LocalizedString* windowTitle, Size initWindowSize, Color3B initFontColor)
{
	CodeWindow* instance = new CodeWindow(windowTitle, initWindowSize, initFontColor);

	instance->autorelease();

	return instance;
}

CodeWindow::CodeWindow(LocalizedString* windowTitle, Size initWindowSize, Color3B initFontColor)
{
	this->currentLineNumber = 1;
	this->tokenizationCallback = nullptr;
	this->onEditCallback = nullptr;
	this->lineNumberElements = std::vector<RichElement*>();
	this->windowSize = initWindowSize;
	this->referenceContentLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Generics_Constant::create());

	this->lineNumbers = RichText::create();
	this->editableText = UICCTextField::create(this->referenceContentLabel->getString(), this->referenceContentLabel->getFont(), this->referenceContentLabel->getFontSize());

	this->marginSize = 0;

	this->textElements = std::vector<std::tuple<LocalizedString*, cocos2d::Color3B>>();
	this->displayedText = RichText::create();
	this->background = LayerColor::create(CodeWindow::DefaultWindowColor, windowSize.width, windowSize.height);
	this->titleBar = LayerColor::create(CodeWindow::DefaultTitleBarColor, windowSize.width, CodeWindow::TitleBarHeight);
	this->windowTitle = windowTitle;
	this->editableWindowTitle = UICCTextField::create(this->referenceContentLabel->getString(), this->referenceContentLabel->getFont(), this->referenceContentLabel->getFontSize());
	this->editableWindowTitle->insertText(this->windowTitle->getString().c_str(), this->windowTitle->getString().size());

	this->editableWindowTitle->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->displayedText->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->displayedText->setWrapMode(RichText::WrapMode::WRAP_PER_CHAR);
	this->displayedText->ignoreContentAdaptWithSize(false);

	this->lineNumbers->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->lineNumbers->ignoreContentAdaptWithSize(false);
	this->editableText->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->editableText->setLineBreakWithoutSpace(true);
	this->editableText->setTextColor(Color4B::WHITE);
	this->editableText->setCascadeOpacityEnabled(false);
	this->editableText->setCursorEnabled(true);
	this->editableText->enableWrap(true);
	this->editableText->setOpacity(0);

	this->addChild(this->referenceContentLabel);
	this->addChild(this->background);
	this->addChild(this->titleBar);
	this->addChild(this->windowTitle);
	this->addChild(this->editableWindowTitle);
	this->addChild(this->lineNumbers);
	this->addChild(this->editableText);
	this->addChild(this->displayedText);
}

CodeWindow::~CodeWindow()
{
}


void CodeWindow::onEnter()
{
	super::onEnter();
	this->scheduleUpdate();
	this->editableText->scheduleUpdate();
}

void CodeWindow::initializePositions()
{
	super::initializePositions();

	Size windowSize = this->background->getContentSize();

	this->displayedText->setContentSize(Size(windowSize.width - this->marginSize - CodeWindow::Padding.width * 2.0f, windowSize.height - CodeWindow::Padding.height * 2.0f));

	this->background->setPosition(-windowSize.width / 2.0f, -windowSize.height / 2.0f);
	this->displayedText->setPosition(Vec2(this->marginSize + CodeWindow::Padding.width, - CodeWindow::Padding.height));
	this->titleBar->setPosition(-windowSize.width / 2.0f, windowSize.height / 2.0f);
	this->editableWindowTitle->setPosition(-windowSize.width / 2.0f + 8.0f, windowSize.height / 2 + CodeWindow::TitleBarHeight / 2.0f);

	this->lineNumbers->setPosition(Vec2(CodeWindow::Padding.width - this->windowSize.width / 2.0f, CodeWindow::Padding.height));
	this->editableText->setPosition(Vec2(this->marginSize + CodeWindow::Padding.width - this->windowSize.width / 2.0f, CodeWindow::Padding.height));

	this->lineNumbers->setContentSize(Size(
		windowSize.width - this->marginSize - CodeWindow::Padding.width * 2.0f,
		windowSize.height - CodeWindow::Padding.height * 2.0f));
	this->editableText->setContentSize(Size(
		windowSize.width - this->marginSize - CodeWindow::Padding.width * 2.0f,
		windowSize.height - CodeWindow::Padding.height * 2.0f));
	this->editableText->setDimensions(
		windowSize.width - this->marginSize - CodeWindow::Padding.width * 2.0f,
		windowSize.height - CodeWindow::Padding.height * 2.0f);

}

void CodeWindow::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(LocalizationEvents::LocaleChangeEvent, [=](EventCustom* args)
	{
		this->rebuildText();
	}));
}

void CodeWindow::update(float dt)
{
	std::string currentText = this->editableText->getString();

	if (this->previousText != currentText)
	{
		this->previousText = currentText;
		this->constructTokenizedText(currentText);

		if (this->onEditCallback != nullptr)
		{
			this->onEditCallback(currentText);
		}
	}
}

void CodeWindow::setTokenizationCallback(std::function<void(std::string text, std::vector<CodeWindow::token>&)> newTokenizationCallback)
{
	this->tokenizationCallback = newTokenizationCallback;
}

void CodeWindow::setOnEditCallback(std::function<void(std::string text)> newOnEditCallback)
{
	this->onEditCallback = newOnEditCallback;
}

std::string  CodeWindow::getText()
{
	return this->editableText->getString();
}

void CodeWindow::setText(std::string text)
{
	this->editableText->setString(text);
}

void CodeWindow::focus()
{
	this->editableText->attachWithIME();
}

void CodeWindow::insertNewline()
{
	RichElement* lineNumberText = RichElementText::create(0, CodeWindow::lineNumberColor, 0xFF, std::to_string(this->currentLineNumber++), this->referenceContentLabel->getFont(), this->referenceContentLabel->getFontSize());
	RichElement* lineNumberNewLine = RichElementNewLine::create(0, this->fontColor, 0xFF);

	this->lineNumberElements.push_back(lineNumberText);
	this->lineNumbers->pushBackElement(lineNumberText);
	this->lineNumberElements.push_back(lineNumberNewLine);
	this->lineNumbers->pushBackElement(lineNumberNewLine);

	LocalizedString* text = Strings::Generics_Newline::create();
	RichElement* element = RichElementNewLine::create(0, this->fontColor, 0xFF);

	text->retain();
	this->textElements.push_back(std::make_tuple(text, Color3B()));
	this->displayedText->pushBackElement(element);
	this->displayedText->formatText();
}

void CodeWindow::clearText()
{
	this->currentLineNumber = 1;

	for (auto iterator = this->lineNumberElements.begin(); iterator != this->lineNumberElements.end(); iterator++)
	{
		this->lineNumbers->removeElement(*iterator);
	}

	this->lineNumberElements.clear();

	for (auto it = this->textElements.begin(); it != this->textElements.end(); it++)
	{
		std::get<0>(*it)->release();
	}

	this->textElements.clear();
	this->displayedText->clearElements();
	this->displayedText->formatText();
}

void CodeWindow::constructTokenizedText(std::string currentText)
{
	if (this->tokenizationCallback == nullptr)
	{
		return;
	}

	std::vector<CodeWindow::token> tokens = std::vector<CodeWindow::token>();
	this->tokenizationCallback(currentText, tokens);
	this->clearText();
	this->insertNewline();

	for (auto tokenIterator = tokens.begin(); tokenIterator != tokens.end(); tokenIterator++)
	{
		CodeWindow::token token = *tokenIterator;

		if (token.tokenStr->getString() == "\n")
		{
			this->insertNewline();
		}
		else
		{
			this->insertText(token.tokenStr, token.color);
		}
	}
}

void CodeWindow::setTitleStringReplaceVariables(LocalizedString* stringReplaceVariables)
{
	this->windowTitle->setStringReplacementVariables(stringReplaceVariables);
}

void CodeWindow::setTitleStringReplaceVariables(std::vector<LocalizedString*> stringReplaceVariables)
{
	this->windowTitle->setStringReplacementVariables(stringReplaceVariables);
}

void CodeWindow::insertText(LocalizedString* text, Color3B color)
{
	RichElement* element = RichElementText::create(0, color, 0xFF, text->getString(), this->referenceContentLabel->getFont(), this->referenceContentLabel->getFontSize());

	text->retain();
	this->textElements.push_back(std::make_tuple(text, color));
	this->displayedText->pushBackElement(element);
}

void CodeWindow::setMarginSize(float newMarginSize)
{
	this->marginSize = newMarginSize;
	this->initializePositions();
}

void CodeWindow::toggleHeader(bool isVisible)
{
	this->titleBar->setVisible(isVisible);
	this->windowTitle->setVisible(isVisible);
}

void CodeWindow::toggleBackground(bool isVisible)
{
	this->background->setVisible(isVisible);
}

void CodeWindow::enableWrapByChar()
{
	this->displayedText->setWrapMode(RichText::WrapMode::WRAP_PER_CHAR);
}

void CodeWindow::enableWrapByWord()
{
	this->displayedText->setWrapMode(RichText::WrapMode::WRAP_PER_WORD);
}

void CodeWindow::rebuildText()
{
	std::vector<std::tuple<LocalizedString*, cocos2d::Color3B>> elements = std::vector<std::tuple<LocalizedString*, cocos2d::Color3B>>();

	for (auto it = this->textElements.begin(); it != this->textElements.end(); it++)
	{
		elements.push_back(std::make_tuple(std::get<0>(*it)->clone(), std::get<1>(*it)));
	}

	this->clearText();

	for (auto it = elements.begin(); it != elements.end(); it++)
	{
		if (std::get<0>(*it)->getString() == "\n")
		{
			this->insertNewline();
		}
		else
		{
			this->insertText(std::get<0>(*it), std::get<1>(*it));
		}
	}
}
