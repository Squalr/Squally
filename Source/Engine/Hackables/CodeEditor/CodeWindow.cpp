﻿#include "CodeWindow.h"

#include "cocos/2d/CCLayer.h"
#include "cocos/base/CCEventDispatcher.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/ui/UIRichText.h"
#include "cocos/ui/UIScrollView.h"
#include "cocos/ui/UITextField.h"

#include "Engine/Events/HackableEvents.h"
#include "Engine/Events/LocalizationEvents.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Input/InputText.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/Utils/StrUtils.h"

#include "Strings/Generics/Empty.h"
#include "Strings/Generics/Newline.h"

using namespace cocos2d;
using namespace cocos2d::ui;

const std::string CodeWindow::Delimiters = "[],:; +-*\n\t";

const std::set<std::string> CodeWindow::Registers =
{
	// General registers
	"ax", "bx", "cx", "dx", "si", "di", "bp", "sp", "ip",
	"al", "bl", "cl", "dl", "sil", "dil", "bpl", "spl",
	"ah", "bh", "ch", "dh",
	"eax", "ebx", "ecx" ,"edx" ,"esi", "edi", "ebp", "esp",
	"r8w", "r9w", "r10w", "r11w", "r12w", "r13w", "r14w", "r15w",
	"r8b", "r9b", "r10b", "r11b", "r12b", "r13b", "r14b", "r15b",
	"r8d", "r9d", "r10d", "r11d", "r12d", "r13d", "r14d", "r15d",
	"rax", "rbx", "rcx" ,"rdx" ,"rdi", "rsi", "rbp", "rsp",
	"r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15",

	// FPU registers
	"fp0", "fp1", "fp2", "fp3", "fp4", "fp5", "fp6", "fp7",

	// FPU stack registers
	"st0", "st1", "st2", "st3", "st4", "st5", "st6", "st7",

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

const Color3B CodeWindow::DefaultColor = Color3B(255, 255, 255);
const Color3B CodeWindow::RegisterColor = Color3B(86, 156, 214);
const Color3B CodeWindow::NumberColor = Color3B(181, 206, 168);
const Color3B CodeWindow::CommentColor = Color3B(87, 166, 74);
const Color3B CodeWindow::LineNumberColor = Color3B(166, 166, 166);
const Size CodeWindow::Padding = Size(8.0f, 4.0f);
const float CodeWindow::TitleBarHeight = 48.0f;
const Color4B CodeWindow::DefaultTitleBarColor = Color4B(59, 92, 97, 255);
const Color4B CodeWindow::DefaultWindowColor = Color4B(39, 58, 61, 255);

CodeWindow* CodeWindow::create(cocos2d::Size windowSize, float marginSize)
{
	CodeWindow* instance = new CodeWindow(windowSize, marginSize);

	instance->autorelease();

	return instance;
}

CodeWindow::CodeWindow(cocos2d::Size windowSize, float marginSize)
{
	this->windowSize = windowSize;
	this->marginSize = marginSize;
	this->currentLineNumber = 1;
	this->tokenizationCallback = nullptr;
	this->onEditCallback = nullptr;
	this->lineNumberElements = std::vector<RichElement*>();

	this->lineNumbers = RichText::create();
	this->editableText = InputText::create(
		Size(windowSize.width - this->marginSize - CodeWindow::Padding.width * 2.0f, this->windowSize.height - CodeWindow::Padding.height * 2.0f),
		LocalizedLabel::FontStyle::Coding,
		LocalizedLabel::FontSize::H3
	);

	this->textElements = std::vector<std::tuple<LocalizedString*, cocos2d::Color3B>>();
	this->displayedText = RichText::create();
	this->background = LayerColor::create(CodeWindow::DefaultWindowColor, this->windowSize.width, this->windowSize.height);
	this->titleBar = LayerColor::create(CodeWindow::DefaultTitleBarColor, this->windowSize.width, CodeWindow::TitleBarHeight);
	this->windowTitle = InputText::create(
		Size(this->windowSize.width - 16.0f, CodeWindow::TitleBarHeight - 16.0f),
		LocalizedLabel::FontStyle::Main,
		LocalizedLabel::FontSize::H3
	);

	this->windowTitle->setAnchorPoint(Vec2(0.0f, 0.5f));
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

	this->addChild(this->background);
	this->addChild(this->titleBar);
	this->addChild(this->windowTitle);
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
	this->displayedText->setPosition(Vec2(this->marginSize + CodeWindow::Padding.width - this->windowSize.width / 2.0f, this->windowSize.height / 2.0f - CodeWindow::Padding.height));
	this->titleBar->setPosition(-windowSize.width / 2.0f, windowSize.height / 2.0f);
	this->windowTitle->setPosition(-windowSize.width / 2.0f + 8.0f, windowSize.height / 2 + CodeWindow::TitleBarHeight / 2.0f);

	this->lineNumbers->setPosition(Vec2(CodeWindow::Padding.width - this->windowSize.width / 2.0f, this->windowSize.height / 2.0f - CodeWindow::Padding.height));
	this->editableText->setPosition(Vec2(this->marginSize + CodeWindow::Padding.width - this->windowSize.width / 2.0f, this->windowSize.height / 2.0f - CodeWindow::Padding.height));

	this->lineNumbers->setContentSize(Size(windowSize.width - this->marginSize - CodeWindow::Padding.width * 2.0f, windowSize.height - CodeWindow::Padding.height * 2.0f));
}

void CodeWindow::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(LocalizationEvents::LocaleChangeEvent, [=](EventCustom* args)
	{
		this->rebuildText();
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(HackableEvents::HackableAttributeEditEvent, [=](EventCustom* args)
	{
		this->editableText->getHitbox()->setAllowCollisionWhenInvisible(true);
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(HackableEvents::HackableAttributeEditDoneEvent, [=](EventCustom* args)
	{
		this->editableText->getHitbox()->setAllowCollisionWhenInvisible(false);
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(HackableEvents::HackableObjectCloseEvent, [=](EventCustom* args)
	{
		this->editableText->getHitbox()->setAllowCollisionWhenInvisible(false);
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

std::string CodeWindow::getText()
{
	return this->editableText->getString();
}

std::string CodeWindow::getTitle()
{
	return this->windowTitle->getString();
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
	RichElement* lineNumberText = RichElementText::create(0, CodeWindow::LineNumberColor, 0xFF, std::to_string(this->currentLineNumber++), this->editableText->getFont(), this->editableText->getFontSize());
	RichElement* lineNumberNewLine = RichElementNewLine::create(0, CodeWindow::DefaultColor, 0xFF);

	this->lineNumberElements.push_back(lineNumberText);
	this->lineNumbers->pushBackElement(lineNumberText);
	this->lineNumberElements.push_back(lineNumberNewLine);
	this->lineNumbers->pushBackElement(lineNumberNewLine);

	LocalizedString* text = Strings::Generics_Newline::create();
	RichElement* element = RichElementNewLine::create(0, CodeWindow::DefaultColor, 0xFF);

	text->retain();
	this->textElements.push_back(std::make_tuple(text, Color3B()));
	this->displayedText->pushBackElement(element);
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
}

void CodeWindow::constructTokenizedText(std::string currentText)
{
	if (this->tokenizationCallback == nullptr)
	{
		return;
	}

	std::vector<CodeWindow::token> tokens = std::vector<CodeWindow::token>();

	// Due to RichTextBoxes being garbage, we need to split text down further if they contain newlines
	// Also split them down further if they contain comments
	std::vector<std::string> splitText = StrUtils::splitOn(currentText, ";\n");
	std::vector<std::string> textJoined = std::vector<std::string>();
	std::string currentString = "";
	bool isJoiningComment = false;

	for (auto splitTextIterator = splitText.begin(); splitTextIterator != splitText.end(); splitTextIterator++)
	{
		std::string next = *splitTextIterator;

		// Newlines end comments
		if (next == "\n")
		{
			if (!currentString.empty())
			{
				textJoined.push_back(currentString);
			}

			textJoined.push_back(next);

			isJoiningComment = false;
			currentString = "";
		}
		else if (next == ";" || isJoiningComment)
		{
			isJoiningComment = true;
			currentString += next;
		}
		else
		{
			textJoined.push_back(next);
		}
	}

	// Add final joined comment if exists
	if (isJoiningComment && !currentString.empty())
	{
		textJoined.push_back(currentString);
	}

	for (auto joinedTextIterator = textJoined.begin(); joinedTextIterator != textJoined.end(); joinedTextIterator++)
	{
		std::vector<std::string> tokenStrings;

		// Tokenize the string if it isn't a comment -- otherwise treat it as one token
		if (!StrUtils::startsWith(*joinedTextIterator, ";", false))
		{
			tokenStrings = StrUtils::tokenize(*joinedTextIterator, CodeWindow::Delimiters);
		}
		else
		{
			tokenStrings = std::vector<std::string>();
			tokenStrings.push_back(*joinedTextIterator);
		}

		// Iterate tokens
		for (auto tokenIterator = tokenStrings.begin(); tokenIterator != tokenStrings.end(); tokenIterator++)
		{
			std::string token = *tokenIterator;
			Color3B color = CodeWindow::DefaultColor;

			if (CodeWindow::Registers.find(token) != CodeWindow::Registers.end())
			{
				color = CodeWindow::RegisterColor;
			}
			else if (StrUtils::isInteger(token) || StrUtils::isFloat(token) || StrUtils::isHexNumber(token))
			{
				color = CodeWindow::NumberColor;
			}
			else if (StrUtils::startsWith(token, ";", false))
			{
				color = CodeWindow::CommentColor;
			}

			CodeWindow::token nextToken = CodeWindow::token(ConstantString::create(token), color);
			tokens.push_back(nextToken);
		}
	}

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

void CodeWindow::setWindowTitle(std::string windowTitle)
{
	this->windowTitle->setString(windowTitle);
}

void CodeWindow::insertText(LocalizedString* text, Color3B color)
{
	RichElement* element = RichElementText::create(0, color, 0xFF, text->getString(), this->editableText->getFont(), this->editableText->getFontSize());

	text->retain();
	this->textElements.push_back(std::make_tuple(text, color));
	this->displayedText->pushBackElement(element);
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
