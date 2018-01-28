#include "CodeEditor.h"

const Size CodeEditor::textSize = Size(480.0f, 640.0f);
const std::string CodeEditor::delimiters = "[],; \n\t";
const Color3B CodeEditor::defaultColor = Color3B::WHITE;
const Color3B CodeEditor::registerColor = Color3B(51, 51, 212);
const Color3B CodeEditor::numberColor = Color3B(51, 212, 51);

const std::set<std::string> CodeEditor::registers =
{
	// General registers
	"ax", "bx", "cx", "dx", "si", "di", "bp", "sp",
	"r8w", "r9w", "r10w", "r11w", "r12w", "r13w", "r14w", "r15w",
	"al", "bl", "cl", "dl", "sil", "dil", "bpl", "spl",
	"r8b", "r9b", "r10b", "r11b", "r12b", "r13b", "r14b", "r15b",
	"eax", "ebx", "ecx" ,"edx" ,"esi", "edi", "ebp", "esp",
	"r8d", "r9d", "r10d", "r11d", "r12d", "r13d", "r14d", "r15d",
	"rax", "rbx", "rcx" ,"rdx" ,"rdi", "rsi", "rbp", "rsp",
	"r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15",

	// FPU registers
	"fp0", "fp1", "fp2", "fp3", "fp4", "fp5", "fp6", "fp7",

	// MMX registers
	"mm0", "mm1", "mm2", "mm3", "mm4", "mm5", "mm6", "mm7",
	"mm8", "mm9", "mm10", "mm11", "mm12", "mm13", "mm14", "mm15",
	"xmm0", "xmm1", "xmm2", "xmm3", "xmm4", "xmm5", "xmm6", "xmm7",
	"xmm8", "xmm9", "xmm10", "xmm11", "xmm12", "xmm13", "xmm14", "xmm15",
	"ymm0", "ymm1", "ymm2", "ymm3", "ymm4", "ymm5", "ymm6", "ymm7",
	"ymm8", "ymm9", "ymm10", "ymm11", "ymm12", "ymm13", "ymm14", "ymm15",

	// Segment registers
	"cs", "ds", "es", "fs", "gs", "ss",

	// Instruction pointers
	"eip", "rip"
};

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
	std::vector <std::string> * tokenStrings = StrUtils::splitOn(tokenStr, "\n");

	for (auto tokenIterator = tokenStrings->begin(); tokenIterator != tokenStrings->end(); tokenIterator++)
	{
		std::string innerToken = *tokenIterator;
		Color3B color = CodeEditor::defaultColor;

		if (CodeEditor::registers.find(innerToken) != CodeEditor::registers.end())
		{
			color = CodeEditor::registerColor;
		}
		else if (StrUtils::isInteger(innerToken) || StrUtils::isFloat(innerToken) || StrUtils::isHexNumber(innerToken))
		{
			color = CodeEditor::numberColor;
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
