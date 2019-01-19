﻿#include "CodeEditor.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Events/HackableEvents.h"
#include "Engine/GlobalDirector.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Hackables/CodeEditor/CodeWindow.h"
#include "Engine/Hackables/CodeEditor/ScriptEntry.h"
#include "Engine/Hackables/CodeEditor/ScriptList.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Hackables/HackableObject.h"
#include "Engine/Hackables/HackablePreview.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/HackUtils.h"
#include "Engine/Utils/StrUtils.h"
#include "Engine/UI/Controls/LabelStack.h"
#include "Engine/UI/Controls/MenuLabel.h"

#include "Resources/UIResources.h"

#include "Strings/Generics/Constant.h"
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
#include "Strings/Hacking/CodeEditor/RegisterEip.h"
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
#include "Strings/Hacking/CodeEditor/RegisterRdi.h"
#include "Strings/Hacking/CodeEditor/RegisterRdx.h"
#include "Strings/Hacking/CodeEditor/RegisterRip.h"
#include "Strings/Hacking/CodeEditor/RegisterRsi.h"
#include "Strings/Hacking/CodeEditor/RegisterRsp.h"
#include "Strings/Hacking/CodeEditor/Status.h"
#include "Strings/Hacking/CodeEditor/StatusHeader.h"
#include "Strings/Hacking/CodeEditor/UnfilledBytes.h"
#include "Strings/Hacking/CodeEditor/Unknown.h"
#include "Strings/Menus/ApplyChanges.h"
#include "Strings/Menus/Cancel.h"

using namespace cocos2d;
using namespace cocos2d::ui;

const float CodeEditor::CompileDelayMaxSeconds = 0.1f;
const float CodeEditor::LineNumberMargin = 32.0f;;
const Size CodeEditor::StatusSize = Size(420.0f, 1080.0f);
const Size CodeEditor::FunctionSize = Size(512.0f, 320.0f);
const Color4B CodeEditor::SubtextColor = Color4B(66, 166, 166, 255);
const Color4B CodeEditor::HeaderColor = Color4B(188, 188, 64, 255);
const Color4B CodeEditor::ErrorColor = Color4B(196, 82, 82, 255);
const Color4B CodeEditor::RegisterColor = Color4B(86, 156, 214, 255);

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
	this->compileDelay = CodeEditor::CompileDelayMaxSeconds;
	this->activeHackableCode = nullptr;

	this->statusBackground = Sprite::create(UIResources::Menus_HackerModeMenu_SideBar);
	this->rightBarBackground = Sprite::create(UIResources::Menus_HackerModeMenu_SideBar);
	this->radialEye = Sprite::create(UIResources::Menus_HackerModeMenu_Radial_RadialEyePupil);
	this->previewNode = Node::create();

	this->functionWindow = CodeWindow::create(Strings::Generics_Constant::create(), CodeEditor::FunctionSize);
	this->statusWindow = LabelStack::create(CodeEditor::StatusSize, 8.0f);
	this->registerWindow = LabelStack::create(CodeEditor::StatusSize, 8.0f);
	this->scriptList = ScriptList::create(CC_CALLBACK_1(CodeEditor::onScriptLoad, this));
	this->titleLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Hacking_CodeEditor_FunctionHeader::create());

	LocalizedLabel*	acceptLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_ApplyChanges::create());
	LocalizedLabel*	acceptLabelHover = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_ApplyChanges::create());

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

	this->applyChangesButton = ClickableTextNode::create(
		acceptLabel,
		acceptLabelHover,
		UIResources::Menus_Buttons_GenericHackButton,
		UIResources::Menus_Buttons_GenericHackButtonHover);

	this->cancelButton = ClickableTextNode::create(
		cancelLabel,
		cancelLabelHover,
		UIResources::Menus_Buttons_GenericHackButton,
		UIResources::Menus_Buttons_GenericHackButtonHover);

	this->applyChangesButtonGrayed = Node::create();
	this->applyChangesButtonGrayed->addChild(Sprite::create(UIResources::Menus_Buttons_GenericHackButtonGray));

	LocalizedLabel*	acceptGray = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_ApplyChanges::create());
	acceptGray->setTextColor(Color4B::GRAY);
	this->applyChangesButtonGrayed->addChild(acceptGray);

	this->titleLabel->enableOutline(Color4B::BLACK, 3);

	this->functionWindow->setTokenizationCallback(CC_CALLBACK_2(CodeEditor::tokenizeCallback, this));
	this->functionWindow->setOnEditCallback(CC_CALLBACK_1(CodeEditor::onFunctionTextUpdate, this));
	this->functionWindow->setMarginSize(32.0f);

	this->statusWindow->setPadding(Size(16.0f, 0.0f));
	this->registerWindow->setPadding(Size(16.0f, 0.0f));

	this->statusBackground->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->rightBarBackground->setAnchorPoint(Vec2(1.0f, 0.5f));
	this->statusWindow->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->registerWindow->setAnchorPoint(Vec2(0.0f, 1.0f));

	this->scriptList->setAnchorPoint(Vec2(0.0f, 1.0f));

	this->setVisible(false);

	this->addChild(this->functionWindow);
	this->addChild(this->statusBackground);
	this->addChild(this->rightBarBackground);
	this->addChild(this->radialEye);
	this->addChild(this->previewNode);
	this->addChild(this->statusWindow);
	this->addChild(this->registerWindow);
	this->addChild(this->scriptList);
	this->addChild(this->cancelButton);
	this->addChild(this->applyChangesButton);
	this->addChild(this->applyChangesButtonGrayed);
	this->addChild(this->titleLabel);
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

	const float sidebarWidth = 420.0f;

	this->statusBackground->setPosition(Vec2(0.0f, visibleSize.height / 2.0f));
	this->statusWindow->setPosition(Vec2(0.0f, visibleSize.height));
	this->scriptList->setPosition(Vec2(sidebarWidth / 2.0f, visibleSize.height / 2.0f + 128.0f));

	this->rightBarBackground->setPosition(Vec2(visibleSize.width, visibleSize.height / 2.0f));
	this->radialEye->setPosition(Vec2(visibleSize.width - sidebarWidth / 2.0f, visibleSize.height / 2.0f + 352.0f));
	this->previewNode->setPosition(Vec2(visibleSize.width - sidebarWidth / 2.0f, visibleSize.height / 2.0f + 352.0f));
	this->functionWindow->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f - 64.0f));
	this->registerWindow->setPosition(Vec2(visibleSize.width - CodeEditor::StatusSize.width, visibleSize.height / 2.0f + 144.0f));

	this->applyChangesButton->setPosition(Vec2(visibleSize.width / 2.0f + 128.0f, visibleSize.height / 2.0f - 192.0f));
	this->cancelButton->setPosition(Vec2(visibleSize.width / 2.0f - 128.0f, visibleSize.height / 2.0f - 192.0f));
	this->applyChangesButtonGrayed->setPosition(this->applyChangesButton->getPosition());

	this->titleLabel->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height - 32.0f));
}

void CodeEditor::initializeListeners()
{
	super::initializeListeners();

	this->applyChangesButton->setClickCallback(CC_CALLBACK_1(CodeEditor::onAccept, this));
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
		this->scriptList->loadScripts(hackableCode);
		this->activeHackableCode = hackableCode;

		this->previewNode->removeAllChildren();

		if (hackableCode->getHackablePreview() != nullptr)
		{
			HackablePreview* preview = hackableCode->getHackablePreview()->clone();

			preview->setAssemblyTextVisible(true);

			this->previewNode->addChild(preview);
		}

		ScriptEntry* activeScript = this->scriptList->getActiveScript();

		this->functionWindow->setText(activeScript == nullptr ? "" : activeScript->getScript());
		this->functionWindow->focus();

		this->titleLabel->setStringReplacementVariables(hackableCode->getName()->clone());

		this->setVisible(true);
		GameUtils::focus(this);

		this->buildRegisterWindow();
	}
}

void CodeEditor::onFunctionTextUpdate(std::string text)
{
	this->scriptList->setActiveScriptText(text);

	this->disableAccept();

	// This will trigger another compile after waiting the compile delay time, for performance
	this->compileDelay = 0.0f;
}

void CodeEditor::update(float dt)
{
	super::update(dt);

	ScriptEntry* activeScript = this->scriptList->getActiveScript();
	
	if (activeScript != nullptr)
	{
		activeScript->getName()->setString(this->functionWindow->getTitle());
	}

	// Update compile based on compile delay
	if (this->compileDelay <= CodeEditor::CompileDelayMaxSeconds)
	{
		this->compileDelay += dt;

		if (this->compileDelay > CodeEditor::CompileDelayMaxSeconds)
		{
			this->compile(this->functionWindow->getText());
		}
	}
}

void CodeEditor::enableAccept()
{
	this->applyChangesButtonGrayed->setVisible(false);
	this->applyChangesButton->setVisible(true);
}

void CodeEditor::disableAccept()
{
	this->applyChangesButtonGrayed->setVisible(true);
	this->applyChangesButton->setVisible(false);
}

void CodeEditor::buildRegisterWindow()
{
	if (this->activeHackableCode == nullptr)
	{
		return;
	}

	this->registerWindow->clear();

	auto getRegisterLabel = ([=](HackableCode::Register reg)
	{
		switch (reg)
		{
			default:
			case HackableCode::Register::eax:
			{
				return (LocalizedString*)Strings::Hacking_CodeEditor_RegisterEax::create();
			}
			case HackableCode::Register::ebx:
			{
				return (LocalizedString*)Strings::Hacking_CodeEditor_RegisterEbx::create();
			}
			case HackableCode::Register::ecx:
			{
				return (LocalizedString*)Strings::Hacking_CodeEditor_RegisterEcx::create();
			}
			case HackableCode::Register::edx:
			{
				return (LocalizedString*)Strings::Hacking_CodeEditor_RegisterEdx::create();
			}
			case HackableCode::Register::edi:
			{
				return (LocalizedString*)Strings::Hacking_CodeEditor_RegisterEdi::create();
			}
			case HackableCode::Register::esi:
			{
				return (LocalizedString*)Strings::Hacking_CodeEditor_RegisterEsi::create();
			}
			case HackableCode::Register::ebp:
			{
				return (LocalizedString*)Strings::Hacking_CodeEditor_RegisterEbp::create();
			}
			case HackableCode::Register::esp:
			{
				return (LocalizedString*)Strings::Hacking_CodeEditor_RegisterEsp::create();
			}
			case HackableCode::Register::eip:
			{
				return (LocalizedString*)Strings::Hacking_CodeEditor_RegisterEip::create();
			}
			case HackableCode::Register::rax:
			{
				return (LocalizedString*)Strings::Hacking_CodeEditor_RegisterRax::create();
			}
			case HackableCode::Register::rbx:
			{
				return (LocalizedString*)Strings::Hacking_CodeEditor_RegisterRbx::create();
			}
			case HackableCode::Register::rcx:
			{
				return (LocalizedString*)Strings::Hacking_CodeEditor_RegisterRcx::create();
			}
			case HackableCode::Register::rdx:
			{
				return (LocalizedString*)Strings::Hacking_CodeEditor_RegisterRdx::create();
			}
			case HackableCode::Register::rdi:
			{
				return (LocalizedString*)Strings::Hacking_CodeEditor_RegisterRdi::create();
			}
			case HackableCode::Register::rsi:
			{
				return (LocalizedString*)Strings::Hacking_CodeEditor_RegisterRsi::create();
			}
			case HackableCode::Register::rbp:
			{
				return (LocalizedString*)Strings::Hacking_CodeEditor_RegisterRbp::create();
			}
			case HackableCode::Register::rsp:
			{
				return (LocalizedString*)Strings::Hacking_CodeEditor_RegisterRsp::create();
			}
			case HackableCode::Register::rip:
			{
				return (LocalizedString*)Strings::Hacking_CodeEditor_RegisterRip::create();
			}
			case HackableCode::Register::r8:
			{
				return (LocalizedString*)Strings::Hacking_CodeEditor_RegisterR8::create();
			}
			case HackableCode::Register::r9:
			{
				return (LocalizedString*)Strings::Hacking_CodeEditor_RegisterR9::create();
			}
			case HackableCode::Register::r10:
			{
				return (LocalizedString*)Strings::Hacking_CodeEditor_RegisterR10::create();
			}
			case HackableCode::Register::r11:
			{
				return (LocalizedString*)Strings::Hacking_CodeEditor_RegisterR11::create();
			}
			case HackableCode::Register::r12:
			{
				return (LocalizedString*)Strings::Hacking_CodeEditor_RegisterR12::create();
			}
			case HackableCode::Register::r13:
			{
				return (LocalizedString*)Strings::Hacking_CodeEditor_RegisterR13::create();
			}
			case HackableCode::Register::r14:
			{
				return (LocalizedString*)Strings::Hacking_CodeEditor_RegisterR14::create();
			}
			case HackableCode::Register::r15:
			{
				return (LocalizedString*)Strings::Hacking_CodeEditor_RegisterR15::create();
			}
		}
	});

	auto tryPrintRegisterHint = [=](HackableCode::Register reg)
	{
		if (this->activeHackableCode->registerHints.find(reg) != this->activeHackableCode->registerHints.end())
		{
			LocalizedLabel* registerLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, getRegisterLabel(reg));

			registerLabel->setTextColor(CodeEditor::RegisterColor);

			this->registerWindow->insert(registerLabel);

			LocalizedLabel* registerHint = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, this->activeHackableCode->registerHints[reg]->clone());

			this->registerWindow->insert(registerHint);
		}
	};

	if (sizeof(void*) == 4)
	{
		tryPrintRegisterHint(HackableCode::Register::eax);
		tryPrintRegisterHint(HackableCode::Register::ebx);
		tryPrintRegisterHint(HackableCode::Register::ecx);
		tryPrintRegisterHint(HackableCode::Register::edx);
		tryPrintRegisterHint(HackableCode::Register::edi);
		tryPrintRegisterHint(HackableCode::Register::esi);
		tryPrintRegisterHint(HackableCode::Register::ebp);
		tryPrintRegisterHint(HackableCode::Register::esp);
		tryPrintRegisterHint(HackableCode::Register::eip);
	}
	else
	{
		tryPrintRegisterHint(HackableCode::Register::rax);
		tryPrintRegisterHint(HackableCode::Register::rbx);
		tryPrintRegisterHint(HackableCode::Register::rcx);
		tryPrintRegisterHint(HackableCode::Register::rdx);
		tryPrintRegisterHint(HackableCode::Register::rdi);
		tryPrintRegisterHint(HackableCode::Register::rsi);
		tryPrintRegisterHint(HackableCode::Register::rbp);
		tryPrintRegisterHint(HackableCode::Register::rsp);
		tryPrintRegisterHint(HackableCode::Register::rip);
		tryPrintRegisterHint(HackableCode::Register::r8);
		tryPrintRegisterHint(HackableCode::Register::r9);
		tryPrintRegisterHint(HackableCode::Register::r10);
		tryPrintRegisterHint(HackableCode::Register::r11);
		tryPrintRegisterHint(HackableCode::Register::r12);
		tryPrintRegisterHint(HackableCode::Register::r13);
		tryPrintRegisterHint(HackableCode::Register::r14);
		tryPrintRegisterHint(HackableCode::Register::r15);
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

	this->statusWindow->clear();

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

		LocalizedLabel* statusLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Hacking_CodeEditor_Status::create());
		statusLabel->setTextColor(CodeEditor::HeaderColor);

		LocalizedLabel* compileSuccessfulLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Hacking_CodeEditor_CompileSuccessful::create());

		LocalizedLabel* addressLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Hacking_CodeEditor_Address::create());
		addressLabel->setTextColor(CodeEditor::HeaderColor);

		LocalizedLabel* addressValueLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, ConstantString::create(HackUtils::hexAddressOf(this->activeHackableCode->getCodePointer(), true, true)));
		
		LocalizedLabel* byteCountLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Hacking_CodeEditor_ByteCount::create());
		byteCountLabel->setTextColor(CodeEditor::HeaderColor);

		LocalizedLabel* bytesUsedLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Generics_XOverY::create());

		bytesUsedLabel->setStringReplacementVariables
		({
			ConstantString::create(std::to_string(compileResult.byteCount)),
			ConstantString::create(std::to_string(this->activeHackableCode->getOriginalLength())),
		});

		if (isByteOverflow)
		{
			bytesUsedLabel->setTextColor(CodeEditor::ErrorColor);
		}

		this->statusWindow->insert(statusLabel);
		this->statusWindow->insert(compileSuccessfulLabel);
		this->statusWindow->insert(addressLabel);
		this->statusWindow->insert(addressValueLabel);
		this->statusWindow->insert(byteCountLabel);
		this->statusWindow->insert(bytesUsedLabel);
		
		if (compileResult.byteCount != this->activeHackableCode->getOriginalLength())
		{
			if (isByteOverflow)
			{
				LocalizedLabel* byteOverflowLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Hacking_CodeEditor_ByteOverflow::create());
				
				byteOverflowLabel->setTextColor(CodeEditor::ErrorColor);

				this->statusWindow->insert(byteOverflowLabel);
			}
			else
			{
				LocalizedLabel* byteOverflowLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Hacking_CodeEditor_UnfilledBytes::create());
				
				byteOverflowLabel->setTextColor(CodeEditor::SubtextColor);

				this->statusWindow->insert(byteOverflowLabel);
			}
		}

		LocalizedLabel* bytesLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Hacking_CodeEditor_Bytes::create());
		
		bytesLabel->setTextColor(CodeEditor::HeaderColor);

		this->statusWindow->insert(bytesLabel);

		LocalizedLabel* arrayOfBytesLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, ConstantString::create(HackUtils::arrayOfByteStringOf(compileResult.compiledBytes, compileResult.byteCount, compileResult.byteCount)));
		
		this->statusWindow->insert(arrayOfBytesLabel);
		
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
		LocalizedLabel* statusLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Hacking_CodeEditor_Status::create());
		
		statusLabel->setTextColor(CodeEditor::HeaderColor);

		this->statusWindow->insert(statusLabel);

		LocalizedLabel* compileErrorsLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Hacking_CodeEditor_CompileErrors::create());
		
		compileErrorsLabel->setTextColor(CodeEditor::ErrorColor);

		this->statusWindow->insert(compileErrorsLabel);

		LocalizedLabel* errorLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Hacking_CodeEditor_Error::create());
		
		errorLabel->setTextColor(CodeEditor::HeaderColor);

		this->statusWindow->insert(errorLabel);

		LocalizedLabel* errorMessageLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, compileResult.errorData.message);
		
		this->statusWindow->insert(errorMessageLabel);

		LocalizedLabel* lineNumberLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Hacking_CodeEditor_LineNumber::create());
		
		lineNumberLabel->setTextColor(CodeEditor::HeaderColor);

		this->statusWindow->insert(lineNumberLabel);

		LocalizedLabel* lineNumberValueLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, ConstantString::create(std::to_string(compileResult.errorData.lineNumber)));
		
		this->statusWindow->insert(lineNumberValueLabel);
		
		this->disableAccept();
	}
}

void CodeEditor::tokenizeCallback(std::string text, std::vector<CodeWindow::token>& tokens)
{
}

void CodeEditor::onScriptLoad(ScriptEntry* script)
{
	this->functionWindow->setTitleStringReplaceVariable(script->getName()->clone());
	this->functionWindow->setText(script->getScript());
}

void CodeEditor::onAccept(ClickableNode* menuSprite)
{
	this->scriptList->saveScripts();

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
	this->scriptList->saveScripts();

	this->setVisible(false);

	HackableEvents::TriggerEditHackableAttributeDone();
}
