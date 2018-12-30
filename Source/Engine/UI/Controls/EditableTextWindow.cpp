#include "EditableTextWindow.h"

#include "cocos/base/CCEventDispatcher.h"
#include "cocos/ui/UIRichText.h"
#include "cocos/ui/UIScrollView.h"
#include "cocos/ui/UITextField.h"

#include "Engine/Localization/Localization.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"

#include "Strings/Menus/CodeEditor/ClickToEdit.h"

using namespace cocos2d;
using namespace cocos2d::ui;

const Color3B EditableTextWindow::lineNumberColor = Color3B(166, 166, 166);

EditableTextWindow* EditableTextWindow::create(LocalizedString* windowTitle, Size initWindowSize, Color3B initFontColor)
{
	EditableTextWindow* instance = new EditableTextWindow(windowTitle, initWindowSize, initFontColor);

	instance->autorelease();

	return instance;
}

EditableTextWindow::EditableTextWindow(LocalizedString* windowTitle, Size initWindowSize, Color3B initFontColor)
	: TextWindow(windowTitle, initWindowSize, initFontColor)
{
	this->currentLineNumber = 1;
	this->tokenizationCallback = nullptr;
	this->onEditCallback = nullptr;
	this->lineNumberElements = std::vector<RichElement*>();
	this->windowSize = initWindowSize;

	this->lineNumbers = RichText::create();

	LocalizedLabel* label = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H3, LocaleStrings::ClickToEdit::create());

	this->editableText = UICCTextField::create(label->getString(), label->getFont(), label->getFontSize());

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
	TextWindow::onEnter();

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
	TextWindow::initializeListeners();
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
	RichElement* lineNumberText = RichElementText::create(0, EditableTextWindow::lineNumberColor, 0xFF, std::to_string(this->currentLineNumber++), this->referenceLabel->getFont(), this->referenceLabel->getFontSize());
	RichElement* lineNumberNewLine = RichElementNewLine::create(0, this->fontColor, 0xFF);

	this->lineNumberElements.push_back(lineNumberText);
	this->lineNumbers->pushBackElement(lineNumberText);
	this->lineNumberElements.push_back(lineNumberNewLine);
	this->lineNumbers->pushBackElement(lineNumberNewLine);

	TextWindow::insertNewline();
}

void EditableTextWindow::clearText()
{
	this->currentLineNumber = 1;

	for (auto iterator = this->lineNumberElements.begin(); iterator != this->lineNumberElements.end(); iterator++)
	{
		this->lineNumbers->removeElement(*iterator);
	}

	this->lineNumberElements.clear();

	TextWindow::clearText();
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

		if (token.tokenStr == "\n")
		{
			this->insertNewline();
		}
		else
		{
			this->insertText(token.tokenStr, token.color);
		}
	}
}
