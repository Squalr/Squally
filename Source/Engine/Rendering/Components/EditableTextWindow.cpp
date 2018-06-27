#include "EditableTextWindow.h"

const Color3B EditableTextWindow::lineNumberColor = Color3B::GRAY;

EditableTextWindow* EditableTextWindow::create(std::string windowTitle, Size initWindowSize, int initFontSize, Color3B initFontColor)
{
	EditableTextWindow* codeEditor = new EditableTextWindow(windowTitle, initWindowSize, initFontSize, initFontColor);

	codeEditor->autorelease();

	return codeEditor;
}

EditableTextWindow::EditableTextWindow(std::string windowTitle, Size initWindowSize, int initFontSize, Color3B initFontColor)
	: TextWindow(windowTitle, initWindowSize, initFontSize, initFontColor)
{
	this->currentLineNumber = 1;
	this->tokenizationCallback = nullptr;
	this->onEditCallback = nullptr;
	this->lineNumberElements = new std::vector<RichElement*>();
	this->fontSize = initFontSize;
	this->windowSize = initWindowSize;

	this->lineNumbers = RichText::create();
	this->editableText = UICCTextField::create("<Click to Edit>", Resources::Fonts_UbuntuMono_Bold, this->fontSize);

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

	this->initializePositions();
	this->initializeListeners();
	this->scheduleUpdate();
}

EditableTextWindow::~EditableTextWindow()
{
	delete(this->lineNumberElements);
}

void EditableTextWindow::setTokenizationCallback(std::function<void(std::string text, std::vector<EditableTextWindow::token>*)> newTokenizationCallback)
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

void EditableTextWindow::initializePositions()
{
	this->lineNumbers->setPosition(Vec2(TextWindow::padding.width, this->scrollView->getInnerContainerSize().height - TextWindow::padding.height));
	this->editableText->setPosition(Vec2(this->marginSize + TextWindow::padding.width, this->scrollView->getInnerContainerSize().height - TextWindow::padding.height));

	this->lineNumbers->setSize(Size(windowSize.width - this->marginSize - TextWindow::padding.width * 2.0f, windowSize.height - TextWindow::padding.height * 2.0f));
	this->editableText->setContentSize(Size(windowSize.width - this->marginSize - TextWindow::padding.width * 2.0f, windowSize.height - TextWindow::padding.height * 2.0f));
	this->editableText->setDimensions(windowSize.width - this->marginSize - TextWindow::padding.width * 2.0f, windowSize.height - TextWindow::padding.height * 2.0f);

	TextWindow::initializePositions();
}

void EditableTextWindow::initializeListeners()
{
	this->getEventDispatcher()->removeEventListenersForTarget(this);
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

void EditableTextWindow::insertNewline()
{
	RichElement* lineNumberText = RichElementText::create(0, EditableTextWindow::lineNumberColor, 0xFF, to_string(this->currentLineNumber++), Resources::Fonts_UbuntuMono_Bold, this->fontSize);
	RichElement* lineNumberNewLine = RichElementNewLine::create(0, this->fontColor, 0xFF);

	this->lineNumberElements->push_back(lineNumberText);
	this->lineNumbers->pushBackElement(lineNumberText);
	this->lineNumberElements->push_back(lineNumberNewLine);
	this->lineNumbers->pushBackElement(lineNumberNewLine);

	TextWindow::insertNewline();
}

void EditableTextWindow::clearText()
{
	this->currentLineNumber = 1;

	for (auto iterator = this->lineNumberElements->begin(); iterator != this->lineNumberElements->end(); iterator++)
	{
		this->lineNumbers->removeElement(*iterator);
	}

	this->lineNumberElements->clear();

	TextWindow::clearText();
}

void EditableTextWindow::constructTokenizedText(std::string currentText)
{
	if (this->tokenizationCallback == nullptr)
	{
		return;
	}

	std::vector<EditableTextWindow::token>* tokens = new std::vector<EditableTextWindow::token>();
	this->tokenizationCallback(currentText, tokens);
	this->clearText();
	this->insertNewline();

	for (auto tokenIterator = tokens->begin(); tokenIterator != tokens->end(); tokenIterator++)
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

	delete(tokens);
}
