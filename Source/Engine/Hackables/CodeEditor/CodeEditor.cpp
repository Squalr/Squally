#include "CodeEditor.h"

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
#include "Engine/Hackables/Clippy.h"
#include "Engine/Hackables/CodeEditor/Lexicon/Lexicon.h"
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
#include "Strings/Hacking/CodeEditor/RegisterSt0.h"
#include "Strings/Hacking/CodeEditor/RegisterSt1.h"
#include "Strings/Hacking/CodeEditor/RegisterSt2.h"
#include "Strings/Hacking/CodeEditor/RegisterSt3.h"
#include "Strings/Hacking/CodeEditor/RegisterSt4.h"
#include "Strings/Hacking/CodeEditor/RegisterSt5.h"
#include "Strings/Hacking/CodeEditor/RegisterSt6.h"
#include "Strings/Hacking/CodeEditor/RegisterSt7.h"
#include "Strings/Hacking/CodeEditor/RegisterXmm0.h"
#include "Strings/Hacking/CodeEditor/RegisterXmm1.h"
#include "Strings/Hacking/CodeEditor/RegisterXmm2.h"
#include "Strings/Hacking/CodeEditor/RegisterXmm3.h"
#include "Strings/Hacking/CodeEditor/RegisterXmm4.h"
#include "Strings/Hacking/CodeEditor/RegisterXmm5.h"
#include "Strings/Hacking/CodeEditor/RegisterXmm6.h"
#include "Strings/Hacking/CodeEditor/RegisterXmm7.h"
#include "Strings/Hacking/CodeEditor/Status.h"
#include "Strings/Hacking/CodeEditor/StatusHeader.h"
#include "Strings/Hacking/CodeEditor/UnfilledBytes.h"
#include "Strings/Hacking/CodeEditor/Unknown.h"
#include "Strings/Hacking/Lexicon/Lexicon.h"
#include "Strings/Menus/ApplyChanges.h"
#include "Strings/Menus/Cancel.h"

using namespace cocos2d;
using namespace cocos2d::ui;

const float CodeEditor::CompileDelayMaxSeconds = 0.1f;
const float CodeEditor::LineNumberMargin = 32.0f;;
const Size CodeEditor::StatusSize = Size(420.0f, 1080.0f);
const Size CodeEditor::FunctionSize = Size(640.0f, 640.0f);
const Color4B CodeEditor::SubtextColor = Color4B(66, 166, 166, 255);
const Color4B CodeEditor::HeaderColor = Color4B(188, 188, 64, 255);
const Color4B CodeEditor::ErrorColor = Color4B(196, 82, 82, 255);
const Color4B CodeEditor::RegisterColor = Color4B(86, 156, 214, 255);

CodeEditor* CodeEditor::create()
{
	CodeEditor* instance = new CodeEditor();

	instance->autorelease();

	return instance;
}

CodeEditor::CodeEditor()
{
	this->compileDelay = CodeEditor::CompileDelayMaxSeconds;
	this->activeHackableCode = nullptr;

	this->statusBackground = Sprite::create(UIResources::Menus_HackerModeMenu_SideBar);
	this->rightBarBackground = Sprite::create(UIResources::Menus_HackerModeMenu_SideBar);
	this->radialEye = Sprite::create(UIResources::Menus_HackerModeMenu_Radial_RadialEyePupil);
	this->previewNode = Node::create();
	this->clippyNode = Node::create();

	this->functionWindow = CodeWindow::create(CodeEditor::FunctionSize);
	this->statusWindow = LabelStack::create(CodeEditor::StatusSize, 8.0f);
	this->registerWindow = LabelStack::create(CodeEditor::StatusSize, 8.0f);
	this->scriptList = ScriptList::create(CC_CALLBACK_1(CodeEditor::onScriptLoad, this));
	this->titleLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Hacking_CodeEditor_FunctionHeader::create());

	LocalizedLabel*	acceptLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_ApplyChanges::create());
	LocalizedLabel*	acceptLabelHover = acceptLabel->clone();

	LocalizedLabel*	cancelLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Cancel::create());
	LocalizedLabel*	cancelLabelHover = cancelLabel->clone();

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

	LocalizedLabel*	lexiconLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Hacking_Lexicon_Lexicon::create());
	LocalizedLabel*	lexiconLabelSelected = lexiconLabel->clone();

	lexiconLabel->enableOutline(Color4B::BLACK, 2);
	lexiconLabelSelected->enableOutline(Color4B::BLACK, 2);
	lexiconLabelSelected->setTextColor(Color4B::YELLOW);

	this->lexiconButton = ClickableTextNode::create(lexiconLabel, lexiconLabelSelected, UIResources::Menus_LexiconMenu_LexiconButton, UIResources::Menus_LexiconMenu_LexiconButtonSelected);
	this->lexicon = Lexicon::create();

	this->titleLabel->enableOutline(Color4B::BLACK, 3);
	this->lexiconButton->setTextOffset(Vec2(0.0f, -56.0f));

	this->functionWindow->setTokenizationCallback(CC_CALLBACK_2(CodeEditor::tokenizeCallback, this));
	this->functionWindow->setOnEditCallback(CC_CALLBACK_1(CodeEditor::onFunctionTextUpdate, this));

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
	this->addChild(this->lexiconButton);
	this->addChild(this->clippyNode);
	this->addChild(this->lexicon);
}

CodeEditor::~CodeEditor()
{
}

void CodeEditor::onEnter()
{
	super::onEnter();

	this->lexiconButton->setVisible(false);
	this->lexicon->setVisible(false);

	this->scheduleUpdate();
}

void CodeEditor::onExit()
{
	super::onExit();
	
	this->activeHackableCode = nullptr;
	this->clippyNode->removeAllChildren();
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
	this->clippyNode->setPosition(Vec2(visibleSize.width - sidebarWidth / 2.0f, visibleSize.height / 2.0f - 480.0f));
	this->functionWindow->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->registerWindow->setPosition(Vec2(visibleSize.width - CodeEditor::StatusSize.width, visibleSize.height / 2.0f + 144.0f));

	this->cancelButton->setPosition(this->functionWindow->getPosition() + Vec2(-160.0f, -CodeEditor::FunctionSize.height / 2.0f - 64.0f));
	this->applyChangesButton->setPosition(this->functionWindow->getPosition() + Vec2(160.0f, -CodeEditor::FunctionSize.height / 2.0f - 64.0f));
	this->applyChangesButtonGrayed->setPosition(this->applyChangesButton->getPosition());

	this->titleLabel->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height - 32.0f));
	this->lexiconButton->setPosition(Vec2(sidebarWidth / 2.0f, 88.0f));
}

void CodeEditor::initializeListeners()
{
	super::initializeListeners();

	this->applyChangesButton->setMouseClickCallback(CC_CALLBACK_0(CodeEditor::onAccept, this));
	this->cancelButton->setMouseClickCallback(CC_CALLBACK_0(CodeEditor::onCancel, this));

	this->addEventListenerIgnorePause(EventListenerCustom::create(HackableEvents::EventHackerModeDisable, [=](EventCustom* eventCustom)
	{
		if (this->isVisible())
		{
			this->onCancel();
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(HackableEvents::EventHackableAttributeEdit, [=](EventCustom* eventCustom)
	{
		HackableEvents::HackableObjectEditArgs* args = static_cast<HackableEvents::HackableObjectEditArgs*>(eventCustom->getUserData());
		
		if (args != nullptr)
		{
			this->open(args);
		}
	}));
}

void CodeEditor::open(HackableEvents::HackableObjectEditArgs* args)
{
	HackableCode* hackableCode = dynamic_cast<HackableCode*>(args->hackableAttribute);

	if (hackableCode != nullptr)
	{
		this->scriptList->loadScripts(hackableCode);
		this->activeHackableCode = hackableCode;

		this->previewNode->removeAllChildren();
		this->clippyNode->removeAllChildren();

		if (hackableCode->getHackablePreview() != nullptr)
		{
			HackablePreview* preview = hackableCode->getHackablePreview()->clone();

			preview->setAssemblyTextVisible(true);

			this->previewNode->addChild(preview);
		}

		if (hackableCode->getClippy() != nullptr)
		{
			Clippy* clippy = hackableCode->getClippy()->clone();

			this->clippyNode->addChild(clippy);
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
			case HackableCode::Register::zax:
			{
				return ((sizeof(void*) == 4 ? (LocalizedString*)Strings::Hacking_CodeEditor_RegisterEax::create() : (LocalizedString*)Strings::Hacking_CodeEditor_RegisterRax::create()));
			}
			case HackableCode::Register::zbx:
			{
				return ((sizeof(void*) == 4 ? (LocalizedString*)Strings::Hacking_CodeEditor_RegisterEbx::create() : (LocalizedString*)Strings::Hacking_CodeEditor_RegisterRbx::create()));
			}
			case HackableCode::Register::zcx:
			{
				return ((sizeof(void*) == 4 ? (LocalizedString*)Strings::Hacking_CodeEditor_RegisterEcx::create() : (LocalizedString*)Strings::Hacking_CodeEditor_RegisterRcx::create()));
			}
			case HackableCode::Register::zdx:
			{
				return ((sizeof(void*) == 4 ? (LocalizedString*)Strings::Hacking_CodeEditor_RegisterEdx::create() : (LocalizedString*)Strings::Hacking_CodeEditor_RegisterRdx::create()));
			}
			case HackableCode::Register::zdi:
			{
				return ((sizeof(void*) == 4 ? (LocalizedString*)Strings::Hacking_CodeEditor_RegisterEdi::create() : (LocalizedString*)Strings::Hacking_CodeEditor_RegisterRdi::create()));
			}
			case HackableCode::Register::zsi:
			{
				return ((sizeof(void*) == 4 ? (LocalizedString*)Strings::Hacking_CodeEditor_RegisterEsi::create() : (LocalizedString*)Strings::Hacking_CodeEditor_RegisterRsi::create()));
			}
			case HackableCode::Register::zbp:
			{
				return ((sizeof(void*) == 4 ? (LocalizedString*)Strings::Hacking_CodeEditor_RegisterEbp::create() : (LocalizedString*)Strings::Hacking_CodeEditor_RegisterRbp::create()));
			}
			case HackableCode::Register::zsp:
			{
				return ((sizeof(void*) == 4 ? (LocalizedString*)Strings::Hacking_CodeEditor_RegisterEsp::create() : (LocalizedString*)Strings::Hacking_CodeEditor_RegisterRsp::create()));
			}
			case HackableCode::Register::zip:
			{
				return ((sizeof(void*) == 4 ? (LocalizedString*)Strings::Hacking_CodeEditor_RegisterEip::create() : (LocalizedString*)Strings::Hacking_CodeEditor_RegisterRip::create()));
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
			case HackableCode::Register::st0:
			{
				return (LocalizedString*)Strings::Hacking_CodeEditor_RegisterSt0::create();
			}
			case HackableCode::Register::st1:
			{
				return (LocalizedString*)Strings::Hacking_CodeEditor_RegisterSt1::create();
			}
			case HackableCode::Register::st2:
			{
				return (LocalizedString*)Strings::Hacking_CodeEditor_RegisterSt2::create();
			}
			case HackableCode::Register::st3:
			{
				return (LocalizedString*)Strings::Hacking_CodeEditor_RegisterSt3::create();
			}
			case HackableCode::Register::st4:
			{
				return (LocalizedString*)Strings::Hacking_CodeEditor_RegisterSt4::create();
			}
			case HackableCode::Register::st5:
			{
				return (LocalizedString*)Strings::Hacking_CodeEditor_RegisterSt5::create();
			}
			case HackableCode::Register::st6:
			{
				return (LocalizedString*)Strings::Hacking_CodeEditor_RegisterSt6::create();
			}
			case HackableCode::Register::st7:
			{
				return (LocalizedString*)Strings::Hacking_CodeEditor_RegisterSt7::create();
			}
			case HackableCode::Register::xmm0:
			{
				return (LocalizedString*)Strings::Hacking_CodeEditor_RegisterXmm0::create();
			}
			case HackableCode::Register::xmm1:
			{
				return (LocalizedString*)Strings::Hacking_CodeEditor_RegisterXmm1::create();
			}
			case HackableCode::Register::xmm2:
			{
				return (LocalizedString*)Strings::Hacking_CodeEditor_RegisterXmm2::create();
			}
			case HackableCode::Register::xmm3:
			{
				return (LocalizedString*)Strings::Hacking_CodeEditor_RegisterXmm3::create();
			}
			case HackableCode::Register::xmm4:
			{
				return (LocalizedString*)Strings::Hacking_CodeEditor_RegisterXmm4::create();
			}
			case HackableCode::Register::xmm5:
			{
				return (LocalizedString*)Strings::Hacking_CodeEditor_RegisterXmm5::create();
			}
			case HackableCode::Register::xmm6:
			{
				return (LocalizedString*)Strings::Hacking_CodeEditor_RegisterXmm6::create();
			}
			case HackableCode::Register::xmm7:
			{
				return (LocalizedString*)Strings::Hacking_CodeEditor_RegisterXmm7::create();
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

	tryPrintRegisterHint(HackableCode::Register::zax);
	tryPrintRegisterHint(HackableCode::Register::zbx);
	tryPrintRegisterHint(HackableCode::Register::zcx);
	tryPrintRegisterHint(HackableCode::Register::zdx);
	tryPrintRegisterHint(HackableCode::Register::zdi);
	tryPrintRegisterHint(HackableCode::Register::zsi);
	tryPrintRegisterHint(HackableCode::Register::zbp);
	tryPrintRegisterHint(HackableCode::Register::zsp);
	tryPrintRegisterHint(HackableCode::Register::zip);

	if (sizeof(void*) == 8)
	{
		tryPrintRegisterHint(HackableCode::Register::r8);
		tryPrintRegisterHint(HackableCode::Register::r9);
		tryPrintRegisterHint(HackableCode::Register::r10);
		tryPrintRegisterHint(HackableCode::Register::r11);
		tryPrintRegisterHint(HackableCode::Register::r12);
		tryPrintRegisterHint(HackableCode::Register::r13);
		tryPrintRegisterHint(HackableCode::Register::r14);
		tryPrintRegisterHint(HackableCode::Register::r15);
	}

	tryPrintRegisterHint(HackableCode::Register::st0);
	tryPrintRegisterHint(HackableCode::Register::st1);
	tryPrintRegisterHint(HackableCode::Register::st2);
	tryPrintRegisterHint(HackableCode::Register::st3);
	tryPrintRegisterHint(HackableCode::Register::st4);
	tryPrintRegisterHint(HackableCode::Register::st5);
	tryPrintRegisterHint(HackableCode::Register::st6);
	tryPrintRegisterHint(HackableCode::Register::st7);
	tryPrintRegisterHint(HackableCode::Register::xmm0);
	tryPrintRegisterHint(HackableCode::Register::xmm1);
	tryPrintRegisterHint(HackableCode::Register::xmm2);
	tryPrintRegisterHint(HackableCode::Register::xmm3);
	tryPrintRegisterHint(HackableCode::Register::xmm4);
	tryPrintRegisterHint(HackableCode::Register::xmm5);
	tryPrintRegisterHint(HackableCode::Register::xmm6);
	tryPrintRegisterHint(HackableCode::Register::xmm7);
}

void CodeEditor::compile(std::string assemblyText)
{
	if (this->activeHackableCode == nullptr)
	{
		return;
	}

	// Do the actual compile
	HackUtils::CompileResult compileResult = HackUtils::assemble(assemblyText, this->activeHackableCode->getPointer());

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

		LocalizedLabel* addressValueLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, ConstantString::create(HackUtils::hexAddressOf(this->activeHackableCode->getPointer(), true, true)));
		
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

		LocalizedLabel* arrayOfBytesLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, ConstantString::create(HackUtils::arrayOfByteStringOf(compileResult.compiledBytes.data(), compileResult.byteCount, compileResult.byteCount)));
		
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
	this->functionWindow->setWindowTitle(script->getName()->getString());
	this->functionWindow->setText(script->getScript());
}

void CodeEditor::onAccept()
{
	this->scriptList->saveScripts();

	HackUtils::CompileResult compileResult = HackUtils::assemble(this->functionWindow->getText(), this->activeHackableCode->getPointer());

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

void CodeEditor::onCancel()
{
	this->scriptList->saveScripts();

	this->setVisible(false);

	HackableEvents::TriggerEditHackableAttributeDone();
}
