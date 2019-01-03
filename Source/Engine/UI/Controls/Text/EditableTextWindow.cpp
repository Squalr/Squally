#include "EditableTextWindow.h"

#include "cocos/base/CCEventDispatcher.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/ui/UIRichText.h"
#include "cocos/ui/UIScrollView.h"
#include "cocos/ui/UITextField.h"

#include "Engine/Events/LocalizationEvents.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"

#include "Strings/Generics/Newline.h"

using namespace cocos2d;
using namespace cocos2d::ui;

const Color3B EditableTextWindow::lineNumberColor = Color3B(166, 166, 166);

EditableTextWindow* EditableTextWindow::create(LocalizedString* windowTitle, LocalizedLabel* referenceContentLabel, Size initWindowSize, Color3B initFontColor)
{
	EditableTextWindow* instance = new EditableTextWindow(windowTitle, referenceContentLabel, initWindowSize, initFontColor);

	instance->autorelease();

	return instance;
}

EditableTextWindow::EditableTextWindow(LocalizedString* windowTitle, LocalizedLabel* referenceContentLabel, Size initWindowSize, Color3B initFontColor)
	: super(windowTitle, referenceContentLabel, initWindowSize, initFontColor)
{
	this->currentLineNumber = 1;
	this->tokenizationCallback = nullptr;
	this->onEditCallback = nullptr;
	this->lineNumberElements = std::vector<RichElement*>();
	this->windowSize = initWindowSize;

	this->lineNumbers = RichText::create();
	this->editableText = UICCTextField::create(this->referenceContentLabel->getString(), this->referenceContentLabel->getFont(), this->referenceContentLabel->getFontSize());

	this->lineNumbers->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->lineNumbers->ignoreContentAdaptWithSize(false);
	this->editableText->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->editableText->setLineBreakWithoutSpace(true);
	this->editableText->setOpacity(0);
	this->editableText->setCascadeOpacityEnabled(false);
	this->editableText->setCursorEnabled(true);
	this->editableText->enableWrap(true);

	this->scrollView->addChild(this->lineNumbers);
	this->scrollView->addChild(this->editableText);
}

EditableTextWindow::~EditableTextWindow()
{
}


void EditableTextWindow::onEnter()
{
	super::onEnter();
	this->scheduleUpdate();
}

void EditableTextWindow::initializePositions()
{
	this->lineNumbers->setPosition(Vec2(TextWindow::Padding.width,
		this->scrollView->getInnerContainerSize().height - TextWindow::Padding.height));
	this->editableText->setPosition(Vec2(this->marginSize + TextWindow::Padding.width,
		this->scrollView->getInnerContainerSize().height - TextWindow::Padding.height));

	this->lineNumbers->setContentSize(Size(
		windowSize.width - this->marginSize - TextWindow::Padding.width * 2.0f,
		windowSize.height - TextWindow::Padding.height * 2.0f));
	this->editableText->setContentSize(Size(
		windowSize.width - this->marginSize - TextWindow::Padding.width * 2.0f,
		windowSize.height - TextWindow::Padding.height * 2.0f));
	this->editableText->setDimensions(
		windowSize.width - this->marginSize - TextWindow::Padding.width * 2.0f,
		windowSize.height - TextWindow::Padding.height * 2.0f);

	TextWindow::initializePositions();
}

void EditableTextWindow::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(LocalizationEvents::LocaleChangeEvent, [=](EventCustom* args)
	{
		// A bit hacky, but clearing this forces a re-building of the text
		this->previousText = "";
	}));
}

void EditableTextWindow::update(float dt)
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

		// TODO: Dynamically set inner content size
		// this->scrollView->setInnerContainerSize(Size(windowSize.width, windowSize.height * 2));
		// this->initializePositions();
	}
}

void EditableTextWindow::setTokenizationCallback(std::function<void(std::string text, std::vector<EditableTextWindow::token>&)> newTokenizationCallback)
{
	this->tokenizationCallback = newTokenizationCallback;
}

void EditableTextWindow::setOnEditCallback(std::function<void(std::string text)> newOnEditCallback)
{
	this->onEditCallback = newOnEditCallback;
}

std::string  EditableTextWindow::getText()
{
	return this->editableText->getString();
}

void EditableTextWindow::setText(std::string text)
{
	this->editableText->setString(text);
}

void EditableTextWindow::focus()
{
	this->editableText->attachWithIME();
}

void EditableTextWindow::insertNewline()
{
	RichElement* lineNumberText = RichElementText::create(0, EditableTextWindow::lineNumberColor, 0xFF, std::to_string(this->currentLineNumber++), this->referenceContentLabel->getFont(), this->referenceContentLabel->getFontSize());
	RichElement* lineNumberNewLine = RichElementNewLine::create(0, this->fontColor, 0xFF);

	this->lineNumberElements.push_back(lineNumberText);
	this->lineNumbers->pushBackElement(lineNumberText);
	this->lineNumberElements.push_back(lineNumberNewLine);
	this->lineNumbers->pushBackElement(lineNumberNewLine);

	super::insertNewline();
}

void EditableTextWindow::clearText()
{
	this->currentLineNumber = 1;

	for (auto iterator = this->lineNumberElements.begin(); iterator != this->lineNumberElements.end(); iterator++)
	{
		this->lineNumbers->removeElement(*iterator);
	}

	this->lineNumberElements.clear();

	super::clearText();
}

void EditableTextWindow::constructTokenizedText(std::string currentText)
{
	if (this->tokenizationCallback == nullptr)
	{
		return;
	}

	std::vector<EditableTextWindow::token> tokens = std::vector<EditableTextWindow::token>();
	this->tokenizationCallback(currentText, tokens);
	this->clearText();
	this->insertNewline();

	for (auto tokenIterator = tokens.begin(); tokenIterator != tokens.end(); tokenIterator++)
	{
		EditableTextWindow::token token = *tokenIterator;

		if (dynamic_cast<Strings::Generics_Newline*>(token.tokenStr) != nullptr)
		{
			this->insertNewline();
		}
		else
		{
			this->insertText(token.tokenStr, token.color);
		}
	}
}
