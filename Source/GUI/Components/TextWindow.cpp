#include "TextWindow.h"

const float TextWindow::lineNumberMargin = 32.0f;;
const Size TextWindow::textSize = Size(448.0f, 640.0f);
const Color3B TextWindow::defaultColor = Color3B::WHITE;
const Color3B TextWindow::subtextColor = Color3B::GRAY;
const Color3B TextWindow::headerColor = Color3B(188, 188, 64);
const Color3B TextWindow::errorColor = Color3B(196, 82, 82);
const Color3B TextWindow::registerColor = Color3B(86, 156, 214);
const Color3B TextWindow::numberColor = Color3B(181, 206, 168); // Color3B(78, 201, 176);
const Color3B TextWindow::commentColor = Color3B(87, 166, 74);

TextWindow* TextWindow::create(std::string windowTitle)
{
	TextWindow* codeEditor = new TextWindow(windowTitle);

	codeEditor->autorelease();

	return codeEditor;
}

TextWindow::TextWindow(std::string windowTitle)
{
	this->tokenizationCallback = nullptr;
	this->displayTextElements = new std::vector<RichElement*>();
	this->lineNumberElements = new std::vector<RichElement*>();

	this->scrollView = ScrollView::create();
	this->editableText = TextField::create("<Click to Edit>", Resources::Fonts_UbuntuMono_B, 32);
	this->lineNumbers = RichText::create();
	this->displayedText = RichText::create();
	this->windowTitle = MenuLabel::create(windowTitle, Resources::Fonts_Montserrat_Medium, 32);

	//this->scrollView->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->scrollView->setSize(TextWindow::textSize);
	this->scrollView->setDirection(SCROLLVIEW_DIR_BOTH);
	this->scrollView->setInnerContainerSize(Size(TextWindow::textSize.width, TextWindow::textSize.height * 2));
	//this->displayedText->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->displayedText->setSize(TextWindow::textSize);
	this->displayedText->ignoreContentAdaptWithSize(false);
	//this->editableText->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->editableText->setOpacity(0);
	this->editableText->setCascadeOpacityEnabled(false);
	this->editableText->setCursorEnabled(true);
	this->editableText->setHighlighted(true);
	this->editableText->setSize(TextWindow::textSize);
	this->editableText->ignoreContentAdaptWithSize(false);
	//this->lineNumbers->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->lineNumbers->setSize(TextWindow::textSize);
	this->lineNumbers->ignoreContentAdaptWithSize(false);

	this->addChild(this->windowTitle);
	this->addChild(this->scrollView);
	this->addChild(this->lineNumbers);
	this->addChild(this->displayedText);
	this->addChild(this->editableText);

	this->initializePositions();
	this->initializeListeners();
	this->scheduleUpdate();
}

TextWindow::~TextWindow()
{
	delete(this->displayTextElements);
	delete(this->lineNumberElements);
}

void TextWindow::setTokenizationCallback(std::function<std::vector<TextWindow::token>*(std::string text)> newTokenizationCallback)
{
	this->tokenizationCallback = newTokenizationCallback;
}

void TextWindow::setTitle(std::string text)
{
	this->windowTitle->setText(text);
}

void TextWindow::setText(std::string text)
{
	this->editableText->setString(text);
}

void TextWindow::focus()
{
	this->editableText->attachWithIME();
}

void TextWindow::initializePositions()
{
	this->scrollView->setPosition(Vec2(0.0f, 0.0f));
	this->lineNumbers->setPosition(Vec2(0.0f, 0.0f));
	this->editableText->setPosition(Vec2(TextWindow::lineNumberMargin, 0.0f));
	this->displayedText->setPosition(this->editableText->getPosition());
	this->windowTitle->setPosition(0.0f, 340.0f);
}

void TextWindow::initializeListeners()
{
}

void TextWindow::update(float dt)
{
	std::string currentText = this->editableText->getString();

	if (this->previousAssemblyText != currentText)
	{
		this->previousAssemblyText = currentText;
		this->constructCodeRichText(currentText);

		// TODO: OnEdit callback
	}
}

void TextWindow::constructCodeRichText(std::string currentText)
{
	if (this->tokenizationCallback == nullptr)
	{
		return;
	}

	// Remove existing rich text
	for (auto iterator = this->displayTextElements->begin(); iterator != this->displayTextElements->end(); iterator++)
	{
		this->displayedText->removeElement(*iterator);
	}

	for (auto iterator = this->lineNumberElements->begin(); iterator != this->lineNumberElements->end(); iterator++)
	{
		this->lineNumbers->removeElement(*iterator);
	}

	this->displayTextElements->clear();
	this->lineNumberElements->clear();

	std::vector<TextWindow::token>* tokens = this->tokenizationCallback(currentText);
	int lineNumber = 1;
	bool insertLineNumber = false;

	this->insertLineNumber(lineNumber++);

	for (auto tokenIterator = tokens->begin(); tokenIterator != tokens->end(); tokenIterator++)
	{
		TextWindow::token token = *tokenIterator;

		RichElement* element;

		if (token.tokenStr == "\n")
		{
			// For some reason RichElementText is too fucking stupid to handle newlines -- these are their own object
			element = RichElementNewLine::create(0, TextWindow::defaultColor, 0xFF);
			insertLineNumber = true;
		}
		else
		{
			element = RichElementText::create(0, token.color, 0xFF, token.tokenStr, Resources::Fonts_UbuntuMono_B, 32);
		}

		if (insertLineNumber)
		{
			this->insertLineNumber(lineNumber++);

			insertLineNumber = false;
		}

		this->displayTextElements->push_back(element);
		this->displayedText->pushBackElement(element);
	}

	delete(tokens);

	this->displayedText->formatText();
	this->lineNumbers->formatText();
}

void TextWindow::insertLineNumber(int lineNumber)
{
	RichElement* lineNumberText = RichElementText::create(0, TextWindow::subtextColor, 0xFF, to_string(lineNumber), Resources::Fonts_UbuntuMono_B, 32);
	RichElement* lineNumberNewLine = RichElementNewLine::create(0, TextWindow::defaultColor, 0xFF);

	this->lineNumberElements->push_back(lineNumberText);
	this->lineNumbers->pushBackElement(lineNumberText);
	this->lineNumberElements->push_back(lineNumberNewLine);
	this->lineNumbers->pushBackElement(lineNumberNewLine);
}
