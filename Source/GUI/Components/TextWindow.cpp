#include "TextWindow.h"

const float TextWindow::titleBarHeight = 48.0f;

TextWindow* TextWindow::create(std::string windowTitle, Size initWindowSize, int initFontSize, Color3B initFontColor)
{
	TextWindow* codeEditor = new TextWindow(windowTitle, initWindowSize, initFontSize, initFontColor);

	codeEditor->autorelease();

	return codeEditor;
}

TextWindow::TextWindow(std::string windowTitle, Size initWindowSize, int initFontSize, Color3B initFontColor)
{
	this->displayTextElements = new std::vector<RichElement*>();

	this->marginSize = 0;
	this->fontSize = initFontSize;
	this->windowSize = initWindowSize;

	this->scrollView = ScrollView::create();
	this->displayedText = RichText::create();
	this->background = LayerColor::create(Color4B(16, 19, 23, 192), initWindowSize.width, initWindowSize.height);
	this->titleBar = LayerColor::create(Color4B(16, 81, 56, 128), initWindowSize.width, TextWindow::titleBarHeight);
	this->windowTitle = MenuLabel::create(windowTitle, Resources::Fonts_Montserrat_Medium, this->fontSize);

	this->scrollView->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->scrollView->setDirection(SCROLLVIEW_DIR_BOTH);
	this->displayedText->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->displayedText->ignoreContentAdaptWithSize(false);

	this->scrollView->addChild(this->displayedText);

	this->addChild(this->background);
	this->addChild(this->titleBar);
	this->addChild(this->windowTitle);
	this->addChild(this->scrollView);

	this->initializePositions();
	this->initializeListeners();
	this->scheduleUpdate();
}

TextWindow::~TextWindow()
{
	delete(this->displayTextElements);
}

void TextWindow::setTitle(std::string text)
{
	this->windowTitle->setText(text);
}

void TextWindow::insertText(std::string text, Color3B color)
{
	RichElement* element = RichElementText::create(0, color, 0xFF, text, Resources::Fonts_UbuntuMono_B, this->fontSize);

	this->displayTextElements->push_back(element);
	this->displayedText->pushBackElement(element);
	this->displayedText->formatText();
}

void TextWindow::setMarginSize(float newMarginSize)
{
	this->marginSize = newMarginSize;
	this->initializePositions();
}

void TextWindow::insertNewline()
{
	RichElement* element = RichElementNewLine::create(0, this->fontColor, 0xFF);

	this->displayTextElements->push_back(element);
	this->displayedText->pushBackElement(element);

	this->displayedText->formatText();
}

void TextWindow::clearText()
{
	for (auto iterator = this->displayTextElements->begin(); iterator != this->displayTextElements->end(); iterator++)
	{
		this->displayedText->removeElement(*iterator);
	}

	this->displayTextElements->clear();
	this->displayedText->formatText();
}

void TextWindow::initializePositions()
{
	this->scrollView->setSize(windowSize);
	this->scrollView->setInnerContainerSize(Size(windowSize.width, windowSize.height * 2));
	this->displayedText->setSize(Size(windowSize.width - this->marginSize, windowSize.height));

	this->scrollView->setPosition(Vec2(0.0f, 0.0f));
	this->background->setPosition(-this->windowSize.width / 2.0f, -this->windowSize.height / 2.0f);
	this->displayedText->setPosition(Vec2(this->marginSize, this->scrollView->getInnerContainerSize().height));
	this->titleBar->setPosition(-this->titleBar->getContentSize().width / 2.0f, this->windowSize.height / 2.0f - this->titleBar->getContentSize().height / 2.0f + this->fontSize);
	this->windowTitle->setPosition(0.0f, this->windowSize.height / 2 + this->fontSize);
}

void TextWindow::initializeListeners()
{
}

void TextWindow::update(float dt)
{
	// TODO: Dynamically set inner content size
	// this->scrollView->setInnerContainerSize(Size(windowSize.width, windowSize.height * 2));
	// this->initializePositions();
}
