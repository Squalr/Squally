#include "CodeEditor.h"

const Size CodeEditor::textSize = Size(480.0f, 640.0f);
const std::string CodeEditor::delimiters = "[],; \n\t";
const std::string CodeEditor::subDelimiters = "\n";
const Color3B CodeEditor::defaultColor = Color3B::WHITE;
const Color3B CodeEditor::registerColor = Color3B::BLUE;
const Color3B CodeEditor::integerColor = Color3B::GREEN;

CodeEditor* CodeEditor::create()
{
	CodeEditor* codeEditor = new CodeEditor();

	codeEditor->autorelease();

	return codeEditor;
}

CodeEditor::CodeEditor()
{
	this->displayTextElements = new std::vector<RichElement*>();
	this->codeEditorBackground = Sprite::create(Resources::Menus_HackerModeMenu_CodeEditMenu);
	this->closeButton = MenuSprite::create(Resources::Menus_HackerModeMenu_CloseButton, Resources::Menus_HackerModeMenu_CloseButtonHover, Resources::Menus_HackerModeMenu_CloseButtonClick);
	this->assemblyCodeText = TextField::create("<Click to Edit Assembly Code>", Resources::Fonts_UbuntuMono_B, 32);
	this->displayText = RichText::create();

	this->assemblyCodeText->setOpacity(0);
	this->assemblyCodeText->setCascadeOpacityEnabled(false);
	this->assemblyCodeText->setCursorEnabled(true);
	this->assemblyCodeText->setHighlighted(true);

	this->assemblyCodeText->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->displayText->setAnchorPoint(Vec2(0.0f, 1.0f));

	this->addChild(this->codeEditorBackground);
	this->addChild(this->closeButton);
	this->addChild(this->assemblyCodeText);
	this->addChild(this->displayText);

	this->initializePositions();
	this->initializeListeners();
	this->scheduleUpdate();
}

CodeEditor::~CodeEditor()
{
	delete(this->displayTextElements);
}

void CodeEditor::update(float dt)
{
	std::string currentText = this->assemblyCodeText->getString();

	this->assemblyCodeText->attachWithIME();

	if (this->previousAssemblyText == currentText)
	{
		return;
	}

	this->previousAssemblyText = currentText;
	this->constructRichText(currentText);
}

void CodeEditor::constructRichText(std::string rawText)
{
	// Remove existing rich text
	for (auto iterator = this->displayTextElements->begin(); iterator != this->displayTextElements->end(); iterator++)
	{
		this->displayText->removeElement(*iterator);
	}

	this->displayTextElements->clear();

	// Tokenize x86/x64 assembly
	std::vector <std::string> * tokenStrings = StrUtils::tokenize(rawText, CodeEditor::delimiters);

	for (auto iterator = tokenStrings->begin(); iterator != tokenStrings->end(); iterator++)
	{
		// Create tokens from the token string (usually this is 1:1, but can sometimes break down further due to edge cases with newlines)
		std::vector<CodeEditor::token>* tokens = this->createTokens(*iterator);

		for (auto tokenIterator = tokens->begin(); tokenIterator != tokens->end(); tokenIterator++)
		{
			CodeEditor::token token = *tokenIterator;

			RichElement* element;

			if (token.tokenStr == "\n")
			{
				// For some reason RichElementText is too fucking stupid to handle newlines -- these are their own object
				element = RichElementNewLine::create(0, CodeEditor::defaultColor, 255);
			}
			else
			{
				element = RichElementText::create(0, token.color, 255, token.tokenStr, Resources::Fonts_UbuntuMono_B, 32);

			}

			this->displayTextElements->push_back(element);
			this->displayText->pushBackElement(element);
		}

		delete(tokens);
	}

	delete(tokenStrings);

	this->displayText->formatText();
}

std::vector<CodeEditor::token>* CodeEditor::createTokens(std::string tokenStr)
{
	std::vector<CodeEditor::token>* tokens = new std::vector<CodeEditor::token>();
	std::vector <std::string> * tokenStrings = StrUtils::tokenize(tokenStr, CodeEditor::subDelimiters);

	for (auto tokenIterator = tokenStrings->begin(); tokenIterator != tokenStrings->end(); tokenIterator++)
	{
		std::string innerToken = *tokenIterator;
		Color3B color = CodeEditor::defaultColor;

		if (innerToken == "eax" || innerToken == "edx" || innerToken == "ecx" || innerToken == "edx" ||
			innerToken == "edi" || innerToken == "esi" || innerToken == "ebp" || innerToken == "esp")
		{
			color = CodeEditor::registerColor;
		}

		CodeEditor::token nextToken = CodeEditor::token(innerToken, color);
		tokens->push_back(nextToken);
	}

	delete(tokenStrings);

	return tokens;
}

void CodeEditor::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->codeEditorBackground->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->closeButton->setPosition(Vec2(visibleSize.width / 2.0f + 304.0f, visibleSize.height / 2.0f + 380.0f));
	this->assemblyCodeText->setPosition(Vec2(visibleSize.width / 2.0f - CodeEditor::textSize.width / 2, visibleSize.height / 2.0f + CodeEditor::textSize.height / 2));
	this->displayText->setPosition(Vec2(visibleSize.width / 2.0f - CodeEditor::textSize.width / 2, visibleSize.height / 2.0f + CodeEditor::textSize.height / 2));
}

void CodeEditor::initializeListeners()
{
	this->closeButton->setClickCallback(CC_CALLBACK_1(CodeEditor::onClose, this));
}

void CodeEditor::open(HackableCode* hackableCode)
{
	this->assemblyCodeText->setText(HackUtils::disassemble(hackableCode->codePointer, hackableCode->codeOriginalLength).c_str());

	this->assemblyCodeText->attachWithIME();

	this->setVisible(true);
	Utils::focus(this);
}

void CodeEditor::onClose(MenuSprite* menuSprite)
{
	this->setVisible(false);

	Utils::focus(this->getParent());
}
