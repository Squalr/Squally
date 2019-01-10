#include "CodeEditor.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Hackables/HackableObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/HackUtils.h"
#include "Engine/Utils/StrUtils.h"
#include "Engine/UI/Controls/MenuLabel.h"
#include "Engine/UI/Controls/Text/TextWindow.h"

#include "Resources/UIResources.h"

#include "Strings/Generics/Empty.h"
#include "Strings/Generics/XOverY.h"
#include "Strings/Hacking/CodeEditor/Address.h"
#include "Strings/Hacking/CodeEditor/AllocationEditor.h"
#include "Strings/Hacking/CodeEditor/Assembler.h"
#include "Strings/Hacking/CodeEditor/ByteCount.h"
#include "Strings/Hacking/CodeEditor/ByteOverflow.h"
#include "Strings/Hacking/CodeEditor/Bytes.h"
#include "Strings/Hacking/CodeEditor/ClickToEdit.h"
#include "Strings/Hacking/CodeEditor/CodeEditor.h"
#include "Strings/Hacking/CodeEditor/CompileErrors.h"
#include "Strings/Hacking/CodeEditor/CompileSuccessful.h"
#include "Strings/Hacking/CodeEditor/Error.h"
#include "Strings/Hacking/CodeEditor/FunctionHeader.h"
#include "Strings/Hacking/CodeEditor/LineNumber.h"
#include "Strings/Hacking/CodeEditor/RegisterEax.h"
#include "Strings/Hacking/CodeEditor/RegisterEbp.h"
#include "Strings/Hacking/CodeEditor/RegisterEbx.h"
#include "Strings/Hacking/CodeEditor/RegisterEcx.h"
#include "Strings/Hacking/CodeEditor/RegisterEdi.h"
#include "Strings/Hacking/CodeEditor/RegisterEdx.h"
#include "Strings/Hacking/CodeEditor/RegisterEsi.h"
#include "Strings/Hacking/CodeEditor/RegisterEsp.h"
#include "Strings/Hacking/CodeEditor/RegisterR8.h"
#include "Strings/Hacking/CodeEditor/RegisterR9.h"
#include "Strings/Hacking/CodeEditor/RegisterR10.h"
#include "Strings/Hacking/CodeEditor/RegisterR11.h"
#include "Strings/Hacking/CodeEditor/RegisterR12.h"
#include "Strings/Hacking/CodeEditor/RegisterR13.h"
#include "Strings/Hacking/CodeEditor/RegisterR14.h"
#include "Strings/Hacking/CodeEditor/RegisterR15.h"
#include "Strings/Hacking/CodeEditor/RegisterRax.h"
#include "Strings/Hacking/CodeEditor/RegisterRbp.h"
#include "Strings/Hacking/CodeEditor/RegisterRbx.h"
#include "Strings/Hacking/CodeEditor/RegisterRcx.h"
#include "Strings/Hacking/CodeEditor/RegisterRbp.h"
#include "Strings/Hacking/CodeEditor/RegisterRdi.h"
#include "Strings/Hacking/CodeEditor/RegisterRdx.h"
#include "Strings/Hacking/CodeEditor/RegisterRsi.h"
#include "Strings/Hacking/CodeEditor/RegisterRsp.h"
#include "Strings/Hacking/CodeEditor/Status.h"
#include "Strings/Hacking/CodeEditor/StatusHeader.h"
#include "Strings/Hacking/CodeEditor/UnfilledBytes.h"
#include "Strings/Menus/Accept.h"
#include "Strings/Menus/Cancel.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Events/HackableEvents.h"
#include "Engine/GlobalDirector.h"
#include "Strings/Generics/Constant.h"

using namespace cocos2d;
using namespace cocos2d::ui;

const float CodeEditor::compileDelayMaxSeconds = 0.1f;
const float CodeEditor::lineNumberMargin = 32.0f;;
const Size CodeEditor::statusSize = Size(420.0f, 1080.0f);
const Size CodeEditor::functionSize = Size(512.0f, 320.0f);
const std::string CodeEditor::delimiters = "[],:; +-*\n\t";
const Color3B CodeEditor::defaultColor = Color3B(255, 255, 255);
const Color3B CodeEditor::subtextColor = Color3B(66, 166, 166);
const Color3B CodeEditor::headerColor = Color3B(188, 188, 64);
const Color3B CodeEditor::errorColor = Color3B(196, 82, 82);
const Color3B CodeEditor::registerColor = Color3B(86, 156, 214);
const Color3B CodeEditor::numberColor = Color3B(181, 206, 168); // Color3B(78, 201, 176);
const Color3B CodeEditor::commentColor = Color3B(87, 166, 74);

const std::set<std::string> CodeEditor::registers =
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

CodeEditor* CodeEditor::instance = nullptr;

void CodeEditor::registerGlobalNode()
{
	if (CodeEditor::instance == nullptr)
	{
		CodeEditor::instance = new CodeEditor();

		CodeEditor::instance->autorelease();

		GlobalDirector::registerGlobalNode(CodeEditor::instance);
	}
}

CodeEditor::CodeEditor()
{
	this->compileDelay = CodeEditor::compileDelayMaxSeconds;
	this->activeHackableCode = nullptr;

	this->statusBackground = Sprite::create(UIResources::Menus_HackerModeMenu_SideBar);
	this->rightBarBackground = Sprite::create(UIResources::Menus_HackerModeMenu_SideBar);

	LocalizedLabel* statusTextStyle = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Generics_Empty::create());
	LocalizedLabel* functionTextStyle = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H3, Strings::Generics_Empty::create());

	this->functionWindow = EditableTextWindow::create(Strings::Hacking_CodeEditor_FunctionHeader::create(), functionTextStyle, CodeEditor::functionSize, CodeEditor::defaultColor);
	this->statusWindow = TextWindow::create(Strings::Generics_Empty::create(), statusTextStyle, CodeEditor::statusSize, CodeEditor::defaultColor);

	LocalizedLabel*	acceptLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Accept::create());
	LocalizedLabel*	acceptLabelHover = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Accept::create());

	LocalizedLabel*	cancelLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Cancel::create());
	LocalizedLabel*	cancelLabelHover = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Cancel::create());

	Size shadowSize = Size(-2.0f, -2.0f);
	int shadowBlur = 2;
	Color3B textColor = Color3B::WHITE;
	Color4B shadowColor = Color4B::BLACK;
	Color3B highlightColor = Color3B::YELLOW;
	Color4B glowColor = Color4B::ORANGE;

	acceptLabel->setColor(textColor);
	acceptLabel->enableShadow(shadowColor, shadowSize, shadowBlur);
	acceptLabel->enableGlow(shadowColor);
	cancelLabel->setColor(textColor);
	cancelLabel->enableShadow(shadowColor, shadowSize, shadowBlur);
	cancelLabel->enableGlow(shadowColor);

	acceptLabelHover->setColor(highlightColor);
	acceptLabelHover->enableShadow(shadowColor, shadowSize, shadowBlur);
	acceptLabelHover->enableGlow(glowColor);
	cancelLabelHover->setColor(highlightColor);
	cancelLabelHover->enableShadow(shadowColor, shadowSize, shadowBlur);
	cancelLabelHover->enableGlow(glowColor);

	this->acceptButton = ClickableTextNode::create(
		acceptLabel,
		acceptLabelHover,
		UIResources::Menus_Buttons_GenericHackButton,
		UIResources::Menus_Buttons_GenericHackButtonHover);

	this->cancelButton = ClickableTextNode::create(
		cancelLabel,
		cancelLabelHover,
		UIResources::Menus_Buttons_GenericHackButton,
		UIResources::Menus_Buttons_GenericHackButtonHover);

	this->acceptButtonGrayed = Node::create();
	this->acceptButtonGrayed->addChild(Sprite::create(UIResources::Menus_Buttons_GenericHackButtonGray));

	LocalizedLabel*	acceptGray = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Accept::create());
	acceptGray->setTextColor(Color4B::GRAY);
	this->acceptButtonGrayed->addChild(acceptGray);

	this->functionWindow->setTokenizationCallback(CC_CALLBACK_2(CodeEditor::tokenizeCallback, this));
	this->functionWindow->setOnEditCallback(CC_CALLBACK_1(CodeEditor::compile, this));
	this->functionWindow->setMarginSize(32.0f);

	this->statusBackground->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->statusWindow->setMarginSize(8.0f);
	this->statusWindow->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->statusWindow->toggleBackground(false);
	this->statusWindow->toggleHeader(false);

	this->rightBarBackground->setAnchorPoint(Vec2(1.0f, 0.5f));
	this->registerWindow->setMarginSize(8.0f);
	this->registerWindow->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->registerWindow->toggleBackground(false);
	this->registerWindow->toggleHeader(false);

	this->setVisible(false);

	this->addChild(this->functionWindow);
	this->addChild(this->statusBackground);
	this->addChild(this->rightBarBackground);
	this->addChild(this->statusWindow);
	this->addChild(this->registerWindow);
	this->addChild(this->cancelButton);
	this->addChild(this->acceptButton);
	this->addChild(this->acceptButtonGrayed);
}

CodeEditor::~CodeEditor()
{
}

void CodeEditor::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void CodeEditor::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->statusBackground->setPosition(Vec2(0.0f, visibleSize.height / 2.0f));
	this->statusWindow->setPosition(Vec2(CodeEditor::statusSize.width / 2.0f, visibleSize.height / 2.0f));

	this->rightBarBackground->setPosition(Vec2(visibleSize.width, visibleSize.height / 2.0f));
	this->registerWindow->setPosition(Vec2(visibleSize.width - CodeEditor::statusSize.width / 2.0f, visibleSize.height / 2.0f));

	this->acceptButton->setPosition(Vec2(visibleSize.width - 420.0f / 2.0f, visibleSize.height / 2.0f - 448.0f));
	this->cancelButton->setPosition(Vec2(visibleSize.width - 420.0f / 2.0f, visibleSize.height / 2.0f - 496.0f));
	this->acceptButtonGrayed->setPosition(this->acceptButton->getPosition());

	this->functionWindow->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f - 64.0f));
}

void CodeEditor::initializeListeners()
{
	super::initializeListeners();

	this->acceptButton->setClickCallback(CC_CALLBACK_1(CodeEditor::onAccept, this));
	this->cancelButton->setClickCallback(CC_CALLBACK_1(CodeEditor::onCancel, this));

	EventListenerCustom* hackableEditListener = EventListenerCustom::create(
		HackableEvents::HackableAttributeEditEvent, 
		[=](EventCustom* args) { this->open((HackableEvents::HackableObjectEditArgs*)args->getUserData()); }
	);

	this->addEventListenerIgnorePause(hackableEditListener);
}

void CodeEditor::open(HackableEvents::HackableObjectEditArgs* args)
{
	HackableCode* hackableCode = dynamic_cast<HackableCode*>(args->hackableAttribute);

	if (hackableCode != nullptr)
	{
		this->activeHackableCode = hackableCode;

		this->functionWindow->setTitleStringReplaceVariables(hackableCode->getName());
		this->functionWindow->setText(hackableCode->getAssemblyString());
		this->functionWindow->focus();

		this->setVisible(true);
		GameUtils::focus(this);

		this->buildRegisterWindow();
	}
}

void CodeEditor::onFunctionTextUpdate(std::string text)
{
	// Reset compile delay
	this->disableAccept();
	this->compileDelay = 0.0f;
}

void CodeEditor::onAllocationTextUpdate(std::string text)
{
	// Reset compile delay
	this->disableAccept();
	this->compileDelay = 0.0f;
}

void CodeEditor::update(float dt)
{
	// Update compile based on compile delay
	if (this->compileDelay <= CodeEditor::compileDelayMaxSeconds)
	{
		this->compileDelay += dt;

		if (this->compileDelay > CodeEditor::compileDelayMaxSeconds)
		{
			this->compile(this->functionWindow->getText());
		}
	}
}

void CodeEditor::enableAccept()
{
	this->acceptButtonGrayed->setVisible(false);
	this->acceptButton->setVisible(true);
}

void CodeEditor::disableAccept()
{
	this->acceptButtonGrayed->setVisible(true);
	this->acceptButton->setVisible(false);
}

void CodeEditor::buildRegisterWindow()
{
	if (sizeof(void*) == 4)
	{
		this->registerWindow->insertText(Strings::Hacking_CodeEditor_RegisterEax::create(), CodeEditor::headerColor);
		this->registerWindow->insertText(Strings::Hacking_CodeEditor_RegisterEbx::create(), CodeEditor::headerColor);
		this->registerWindow->insertText(Strings::Hacking_CodeEditor_RegisterEcx::create(), CodeEditor::headerColor);
		this->registerWindow->insertText(Strings::Hacking_CodeEditor_RegisterEdx::create(), CodeEditor::headerColor);
		this->registerWindow->insertText(Strings::Hacking_CodeEditor_RegisterEdi::create(), CodeEditor::headerColor);
		this->registerWindow->insertText(Strings::Hacking_CodeEditor_RegisterEsi::create(), CodeEditor::headerColor);
		this->registerWindow->insertText(Strings::Hacking_CodeEditor_RegisterEbp::create(), CodeEditor::headerColor);
		this->registerWindow->insertText(Strings::Hacking_CodeEditor_RegisterEsp::create(), CodeEditor::headerColor);
	}
	else
	{
		this->registerWindow->insertText(Strings::Hacking_CodeEditor_RegisterRax::create(), CodeEditor::headerColor);
		this->registerWindow->insertText(Strings::Hacking_CodeEditor_RegisterRbx::create(), CodeEditor::headerColor);
		this->registerWindow->insertText(Strings::Hacking_CodeEditor_RegisterRcx::create(), CodeEditor::headerColor);
		this->registerWindow->insertText(Strings::Hacking_CodeEditor_RegisterRdx::create(), CodeEditor::headerColor);
		this->registerWindow->insertText(Strings::Hacking_CodeEditor_RegisterRdi::create(), CodeEditor::headerColor);
		this->registerWindow->insertText(Strings::Hacking_CodeEditor_RegisterRsi::create(), CodeEditor::headerColor);
		this->registerWindow->insertText(Strings::Hacking_CodeEditor_RegisterR8::create(), CodeEditor::headerColor);
		this->registerWindow->insertText(Strings::Hacking_CodeEditor_RegisterR9::create(), CodeEditor::headerColor);
		this->registerWindow->insertText(Strings::Hacking_CodeEditor_RegisterR10::create(), CodeEditor::headerColor);
		this->registerWindow->insertText(Strings::Hacking_CodeEditor_RegisterR11::create(), CodeEditor::headerColor);
		this->registerWindow->insertText(Strings::Hacking_CodeEditor_RegisterR12::create(), CodeEditor::headerColor);
		this->registerWindow->insertText(Strings::Hacking_CodeEditor_RegisterR13::create(), CodeEditor::headerColor);
		this->registerWindow->insertText(Strings::Hacking_CodeEditor_RegisterR14::create(), CodeEditor::headerColor);
		this->registerWindow->insertText(Strings::Hacking_CodeEditor_RegisterR15::create(), CodeEditor::headerColor);
		this->registerWindow->insertText(Strings::Hacking_CodeEditor_RegisterRbp::create(), CodeEditor::headerColor);
		this->registerWindow->insertText(Strings::Hacking_CodeEditor_RegisterRsp::create(), CodeEditor::headerColor);
	}
}

void CodeEditor::compile(std::string assemblyText)
{
	if (this->activeHackableCode == nullptr)
	{
		return;
	}

	// Do the actual compile
	HackUtils::CompileResult compileResult = HackUtils::assemble(assemblyText, this->activeHackableCode->getCodePointer());

	this->statusWindow->clearText();

	// Build text and enable/disable the accept button
	if (!compileResult.hasError)
	{
		bool isByteOverflow = compileResult.byteCount > this->activeHackableCode->getOriginalLength();

		LocalizedString* bytesUsed = Strings::Generics_XOverY::create();

		bytesUsed->setStringReplacementVariables(
		{
			ConstantString::create(std::to_string(compileResult.byteCount)),
			ConstantString::create(std::to_string(this->activeHackableCode->getOriginalLength()))
		});
		
		this->statusWindow->insertText(Strings::Hacking_CodeEditor_Status::create(), CodeEditor::headerColor);
		this->statusWindow->insertText(Strings::Hacking_CodeEditor_CompileSuccessful::create(), CodeEditor::defaultColor);
		this->statusWindow->insertNewline();
		this->statusWindow->insertNewline();
		this->statusWindow->insertText(Strings::Hacking_CodeEditor_Address::create(), CodeEditor::headerColor);
		this->statusWindow->insertText(ConstantString::create(HackUtils::hexAddressOf(this->activeHackableCode->getCodePointer(), true, true)), CodeEditor::defaultColor);
		this->statusWindow->insertNewline();
		this->statusWindow->insertNewline();
		this->statusWindow->insertText(Strings::Hacking_CodeEditor_ByteCount::create(), CodeEditor::headerColor);
		this->statusWindow->insertText(bytesUsed, isByteOverflow ? CodeEditor::errorColor : CodeEditor::defaultColor);
		this->statusWindow->insertNewline();
		this->statusWindow->insertNewline();
		
		if (compileResult.byteCount != this->activeHackableCode->getOriginalLength())
		{
			if (isByteOverflow)
			{
				this->statusWindow->insertText(Strings::Hacking_CodeEditor_ByteOverflow::create(), CodeEditor::errorColor);
			}
			else
			{
				this->statusWindow->insertText(Strings::Hacking_CodeEditor_UnfilledBytes::create(), CodeEditor::subtextColor);
			}

			this->statusWindow->insertNewline();
			this->statusWindow->insertNewline();
		}
		
		this->statusWindow->insertText(Strings::Hacking_CodeEditor_Bytes::create(), CodeEditor::headerColor);
		this->statusWindow->insertText(ConstantString::create(HackUtils::arrayOfByteStringOf(compileResult.compiledBytes, compileResult.byteCount, compileResult.byteCount)), CodeEditor::defaultColor);
		
		if (isByteOverflow)
		{
			this->disableAccept();
		}
		else
		{
			this->enableAccept();
		}
	}
	else
	{
		this->statusWindow->insertText(Strings::Hacking_CodeEditor_Status::create(), CodeEditor::headerColor);
		this->statusWindow->insertText(Strings::Hacking_CodeEditor_CompileErrors::create(), CodeEditor::errorColor);
		this->statusWindow->insertNewline();
		this->statusWindow->insertNewline();
		this->statusWindow->insertText(Strings::Hacking_CodeEditor_Error::create(), CodeEditor::headerColor);
		this->statusWindow->insertText(compileResult.errorData.message, CodeEditor::defaultColor);
		this->statusWindow->insertNewline();
		this->statusWindow->insertNewline();
		this->statusWindow->insertText(Strings::Hacking_CodeEditor_LineNumber::create(), CodeEditor::headerColor);
		this->statusWindow->insertText(ConstantString::create(std::to_string(compileResult.errorData.lineNumber)), CodeEditor::defaultColor);
		
		this->disableAccept();
	}
}

void CodeEditor::tokenizeCallback(std::string text, std::vector<EditableTextWindow::token>& tokens)
{
	// Due to RichTextBoxes being garbage, we need to split text down further if they contain newlines
	// Also split them down further if they contain comments
	std::vector<std::string> splitText = StrUtils::splitOn(text, ";\n");
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
			tokenStrings = StrUtils::tokenize(*joinedTextIterator, CodeEditor::delimiters);
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
			Color3B color = CodeEditor::defaultColor;

			if (CodeEditor::registers.find(token) != CodeEditor::registers.end())
			{
				color = CodeEditor::registerColor;
			}
			else if (StrUtils::isInteger(token) || StrUtils::isFloat(token) || StrUtils::isHexNumber(token))
			{
				color = CodeEditor::numberColor;
			}
			else if (StrUtils::startsWith(token, ";", false))
			{
				color = CodeEditor::commentColor;
			}

			EditableTextWindow::token nextToken = EditableTextWindow::token(ConstantString::create(token), color);
			tokens.push_back(nextToken);
		}
	}
}

void CodeEditor::onAccept(ClickableNode* menuSprite)
{
	HackUtils::CompileResult compileResult = HackUtils::assemble(this->functionWindow->getText(), this->activeHackableCode->getCodePointer());

	// Sanity check that the code compiles -- it should at this point
	if (compileResult.hasError || compileResult.byteCount > this->activeHackableCode->getOriginalLength())
	{
		this->disableAccept();
		return;
	}

	// Enable hack with new assembly
	this->activeHackableCode->applyCustomCode(this->functionWindow->getText());

	this->setVisible(false);
	this->getParent()->setOpacity(0xFF);

	HackableEvents::TriggerEditHackableAttributeDone();
}

void CodeEditor::onCancel(ClickableNode* menuSprite)
{
	this->setVisible(false);

	HackableEvents::TriggerEditHackableAttributeDone();
}
