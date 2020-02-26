#include "CodeHud.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCDirector.h"
#include "cocos/platform/CCApplication.h"

#include "Engine/Events/HackableEvents.h"
#include "Engine/Events/SceneEvents.h"
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
#include "Menus/Confirmation/ConfirmationMenu.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;
using namespace cocos2d::ui;

const float CodeHud::CompileDelayMaxSeconds = 0.1f;
const float CodeHud::LineNumberMargin = 32.0f;
const Size CodeHud::StatusSize = Size(420.0f, 1080.0f);
const Size CodeHud::FunctionSize = Size(640.0f, 640.0f);
const Color4B CodeHud::SubtextColor = Color4B(66, 166, 166, 255);
const Color4B CodeHud::HeaderColor = Color4B(188, 188, 64, 255);
const Color4B CodeHud::ErrorColor = Color4B(196, 82, 82, 255);
const Color4B CodeHud::RegisterColor = Color4B(86, 156, 214, 255);

CodeHud* CodeHud::create()
{
	CodeHud* instance = new CodeHud();

	instance->autorelease();

	return instance;
}

CodeHud::CodeHud()
{
	this->timeSinceLastCompile = CodeHud::CompileDelayMaxSeconds;
	this->activeHackableCode = nullptr;
	this->lexicon = nullptr;

	this->statusBackground = Sprite::create(UIResources::Menus_HackerModeMenu_SideBar);
	this->rightBarBackground = Sprite::create(UIResources::Menus_HackerModeMenu_SideBar);
	this->radialEye = Sprite::create(UIResources::Menus_HackerModeMenu_Radial_RadialEyePupil);
	this->previewNode = Node::create();
	this->clippyNode = Node::create();

	this->functionWindow = CodeWindow::create(CodeHud::FunctionSize);
	this->statusWindow = LabelStack::create(CodeHud::StatusSize, 8.0f);
	this->registerWindow = LabelStack::create(CodeHud::StatusSize, 8.0f);
	this->confirmationMenu = ConfirmationMenu::create();
	this->scriptList = ScriptList::create(this->confirmationMenu, [=](ScriptEntry* scriptEntry) { this->functionWindow->openScript(scriptEntry); });
	this->titleLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Menus_Hacking_CodeEditor_FunctionHeader::create());

	LocalizedLabel*	acceptLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Apply::create());
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

	LocalizedLabel*	acceptGray = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Apply::create());
	acceptGray->setTextColor(Color4B::GRAY);
	this->applyChangesButtonGrayed->addChild(acceptGray);

	LocalizedLabel*	lexiconLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Hacking_Lexicon_Lexicon::create());
	LocalizedLabel*	lexiconLabelSelected = lexiconLabel->clone();

	lexiconLabel->enableOutline(Color4B::BLACK, 2);
	lexiconLabelSelected->enableOutline(Color4B::BLACK, 2);
	lexiconLabelSelected->setTextColor(Color4B::YELLOW);

	this->lexiconButton = ClickableTextNode::create(lexiconLabel, lexiconLabelSelected, UIResources::Menus_LexiconMenu_LexiconButton, UIResources::Menus_LexiconMenu_LexiconButtonSelected);

	LocalizedLabel*	stuckLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Hacking_CodeEditor_Stuck::create());
	LocalizedLabel*	stuckLabelSelected = stuckLabel->clone();

	stuckLabel->enableOutline(Color4B::BLACK, 2);
	stuckLabelSelected->enableOutline(Color4B::BLACK, 2);
	stuckLabelSelected->setTextColor(Color4B::YELLOW);

	this->stuckButton = ClickableTextNode::create(stuckLabel, stuckLabelSelected, UIResources::Menus_HackerModeMenu_DiscordButton, UIResources::Menus_HackerModeMenu_DiscordButtonSelected);

	this->titleLabel->enableOutline(Color4B::BLACK, 3);
	this->lexiconButton->setTextOffset(Vec2(0.0f, -56.0f));
	this->stuckButton->setTextOffset(Vec2(0.0f, -56.0f));

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
	this->addChild(this->stuckButton);
	this->addChild(this->clippyNode);
	this->addChild(this->confirmationMenu);
}

CodeHud::~CodeHud()
{
}

void CodeHud::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void CodeHud::initializePositions()
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
	this->registerWindow->setPosition(Vec2(visibleSize.width - CodeHud::StatusSize.width, visibleSize.height / 2.0f + 144.0f));

	this->cancelButton->setPosition(this->functionWindow->getPosition() + Vec2(-160.0f, -CodeHud::FunctionSize.height / 2.0f - 64.0f));
	this->applyChangesButton->setPosition(this->functionWindow->getPosition() + Vec2(160.0f, -CodeHud::FunctionSize.height / 2.0f - 64.0f));
	this->applyChangesButtonGrayed->setPosition(this->applyChangesButton->getPosition());

	this->titleLabel->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height - 32.0f));
	this->lexiconButton->setPosition(Vec2(sidebarWidth / 2.0f + 96.0f, 88.0f));
	this->stuckButton->setPosition(Vec2(sidebarWidth / 2.0f - 112.0f, 88.0f));
}

void CodeHud::initializeListeners()
{
	super::initializeListeners();

	this->applyChangesButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->onAccept();
	});

	this->cancelButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->onCancel();
	});

	this->addEventListenerIgnorePause(EventListenerCustom::create(SceneEvents::EventBeforeSceneChange, [=](EventCustom* eventCustom)
	{
		this->activeHackableCode = nullptr;
		this->clippyNode->removeAllChildren();
	}));

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
	
	this->lexiconButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->functionWindow->unfocus();
		this->getLexicon()->open();
	});
	
	this->stuckButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		Application::getInstance()->openURL("https://discord.gg/3maVXN5");
	});
}

void CodeHud::open(HackableEvents::HackableObjectEditArgs* args)
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

		if (hackableCode->getClippy() != nullptr && hackableCode->getClippy()->getIsEnabled())
		{
			Clippy* clippy = hackableCode->getClippy()->clone();

			clippy->setVisible(true);

			this->clippyNode->addChild(clippy);
		}

		this->functionWindow->openScript(this->scriptList->getActiveScript());

		this->titleLabel->setStringReplacementVariables(hackableCode->getName()->clone());

		this->setVisible(true);
		GameUtils::focus(this);

		this->buildRegisterWindow();
	}
}

void CodeHud::update(float dt)
{
	super::update(dt);

	// Compile on a delay as a performance boost
	if (this->functionWindow->hasChanges() && this->timeSinceLastCompile >= CodeHud::CompileDelayMaxSeconds)
	{
		this->timeSinceLastCompile = 0.0f;
		this->functionWindow->clearHasChanges();
		this->compile(this->functionWindow->getText());
	}
	
	if (this->timeSinceLastCompile <= CodeHud::CompileDelayMaxSeconds)
	{
		this->timeSinceLastCompile += dt;
	}
}

void CodeHud::enableAccept()
{
	this->applyChangesButtonGrayed->setVisible(false);
	this->applyChangesButton->setVisible(true);
}

void CodeHud::disableAccept()
{
	this->applyChangesButtonGrayed->setVisible(true);
	this->applyChangesButton->setVisible(false);
}

void CodeHud::buildRegisterWindow()
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
				return ((sizeof(void*) == 4 ? (LocalizedString*)Strings::Menus_Hacking_CodeEditor_RegisterEax::create() : (LocalizedString*)Strings::Menus_Hacking_CodeEditor_RegisterRax::create()));
			}
			case HackableCode::Register::zbx:
			{
				return ((sizeof(void*) == 4 ? (LocalizedString*)Strings::Menus_Hacking_CodeEditor_RegisterEbx::create() : (LocalizedString*)Strings::Menus_Hacking_CodeEditor_RegisterRbx::create()));
			}
			case HackableCode::Register::zcx:
			{
				return ((sizeof(void*) == 4 ? (LocalizedString*)Strings::Menus_Hacking_CodeEditor_RegisterEcx::create() : (LocalizedString*)Strings::Menus_Hacking_CodeEditor_RegisterRcx::create()));
			}
			case HackableCode::Register::zdx:
			{
				return ((sizeof(void*) == 4 ? (LocalizedString*)Strings::Menus_Hacking_CodeEditor_RegisterEdx::create() : (LocalizedString*)Strings::Menus_Hacking_CodeEditor_RegisterRdx::create()));
			}
			case HackableCode::Register::zdi:
			{
				return ((sizeof(void*) == 4 ? (LocalizedString*)Strings::Menus_Hacking_CodeEditor_RegisterEdi::create() : (LocalizedString*)Strings::Menus_Hacking_CodeEditor_RegisterRdi::create()));
			}
			case HackableCode::Register::zsi:
			{
				return ((sizeof(void*) == 4 ? (LocalizedString*)Strings::Menus_Hacking_CodeEditor_RegisterEsi::create() : (LocalizedString*)Strings::Menus_Hacking_CodeEditor_RegisterRsi::create()));
			}
			case HackableCode::Register::zbp:
			{
				return ((sizeof(void*) == 4 ? (LocalizedString*)Strings::Menus_Hacking_CodeEditor_RegisterEbp::create() : (LocalizedString*)Strings::Menus_Hacking_CodeEditor_RegisterRbp::create()));
			}
			case HackableCode::Register::zsp:
			{
				return ((sizeof(void*) == 4 ? (LocalizedString*)Strings::Menus_Hacking_CodeEditor_RegisterEsp::create() : (LocalizedString*)Strings::Menus_Hacking_CodeEditor_RegisterRsp::create()));
			}
			case HackableCode::Register::zip:
			{
				return ((sizeof(void*) == 4 ? (LocalizedString*)Strings::Menus_Hacking_CodeEditor_RegisterEip::create() : (LocalizedString*)Strings::Menus_Hacking_CodeEditor_RegisterRip::create()));
			}
			case HackableCode::Register::r8:
			{
				return (LocalizedString*)Strings::Menus_Hacking_CodeEditor_RegisterR8::create();
			}
			case HackableCode::Register::r9:
			{
				return (LocalizedString*)Strings::Menus_Hacking_CodeEditor_RegisterR9::create();
			}
			case HackableCode::Register::r10:
			{
				return (LocalizedString*)Strings::Menus_Hacking_CodeEditor_RegisterR10::create();
			}
			case HackableCode::Register::r11:
			{
				return (LocalizedString*)Strings::Menus_Hacking_CodeEditor_RegisterR11::create();
			}
			case HackableCode::Register::r12:
			{
				return (LocalizedString*)Strings::Menus_Hacking_CodeEditor_RegisterR12::create();
			}
			case HackableCode::Register::r13:
			{
				return (LocalizedString*)Strings::Menus_Hacking_CodeEditor_RegisterR13::create();
			}
			case HackableCode::Register::r14:
			{
				return (LocalizedString*)Strings::Menus_Hacking_CodeEditor_RegisterR14::create();
			}
			case HackableCode::Register::r15:
			{
				return (LocalizedString*)Strings::Menus_Hacking_CodeEditor_RegisterR15::create();
			}
			case HackableCode::Register::st0:
			{
				return (LocalizedString*)Strings::Menus_Hacking_CodeEditor_RegisterSt0::create();
			}
			case HackableCode::Register::st1:
			{
				return (LocalizedString*)Strings::Menus_Hacking_CodeEditor_RegisterSt1::create();
			}
			case HackableCode::Register::st2:
			{
				return (LocalizedString*)Strings::Menus_Hacking_CodeEditor_RegisterSt2::create();
			}
			case HackableCode::Register::st3:
			{
				return (LocalizedString*)Strings::Menus_Hacking_CodeEditor_RegisterSt3::create();
			}
			case HackableCode::Register::st4:
			{
				return (LocalizedString*)Strings::Menus_Hacking_CodeEditor_RegisterSt4::create();
			}
			case HackableCode::Register::st5:
			{
				return (LocalizedString*)Strings::Menus_Hacking_CodeEditor_RegisterSt5::create();
			}
			case HackableCode::Register::st6:
			{
				return (LocalizedString*)Strings::Menus_Hacking_CodeEditor_RegisterSt6::create();
			}
			case HackableCode::Register::st7:
			{
				return (LocalizedString*)Strings::Menus_Hacking_CodeEditor_RegisterSt7::create();
			}
			case HackableCode::Register::xmm0:
			{
				return (LocalizedString*)Strings::Menus_Hacking_CodeEditor_RegisterXmm0::create();
			}
			case HackableCode::Register::xmm1:
			{
				return (LocalizedString*)Strings::Menus_Hacking_CodeEditor_RegisterXmm1::create();
			}
			case HackableCode::Register::xmm2:
			{
				return (LocalizedString*)Strings::Menus_Hacking_CodeEditor_RegisterXmm2::create();
			}
			case HackableCode::Register::xmm3:
			{
				return (LocalizedString*)Strings::Menus_Hacking_CodeEditor_RegisterXmm3::create();
			}
			case HackableCode::Register::xmm4:
			{
				return (LocalizedString*)Strings::Menus_Hacking_CodeEditor_RegisterXmm4::create();
			}
			case HackableCode::Register::xmm5:
			{
				return (LocalizedString*)Strings::Menus_Hacking_CodeEditor_RegisterXmm5::create();
			}
			case HackableCode::Register::xmm6:
			{
				return (LocalizedString*)Strings::Menus_Hacking_CodeEditor_RegisterXmm6::create();
			}
			case HackableCode::Register::xmm7:
			{
				return (LocalizedString*)Strings::Menus_Hacking_CodeEditor_RegisterXmm7::create();
			}
		}
	});

	auto tryPrintRegisterHint = [=](HackableCode::Register reg)
	{
		if (this->activeHackableCode->registerHints.find(reg) != this->activeHackableCode->registerHints.end())
		{
			LocalizedLabel* registerLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, getRegisterLabel(reg));

			registerLabel->setTextColor(CodeHud::RegisterColor);

			this->registerWindow->insert(registerLabel);

			LocalizedString* strRef = this->activeHackableCode->registerHints[reg];
			LocalizedString* strCopy = strRef == nullptr ? nullptr : strRef->clone();
			LocalizedLabel* registerHint = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, strCopy);

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

void CodeHud::compile(std::string assemblyText)
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

		LocalizedString* bytesUsed = Strings::Common_XOverY::create();

		bytesUsed->setStringReplacementVariables(
		{
			ConstantString::create(std::to_string(compileResult.byteCount)),
			ConstantString::create(std::to_string(this->activeHackableCode->getOriginalLength()))
		});

		LocalizedLabel* statusLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Hacking_CodeEditor_Status::create());
		statusLabel->setTextColor(CodeHud::HeaderColor);

		LocalizedLabel* compileSuccessfulLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Hacking_CodeEditor_CompileSuccessful::create());

		LocalizedLabel* addressLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Hacking_CodeEditor_Address::create());
		addressLabel->setTextColor(CodeHud::HeaderColor);

		LocalizedLabel* addressValueLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, ConstantString::create(HackUtils::hexAddressOf(this->activeHackableCode->getPointer(), true, true)));
		
		LocalizedLabel* byteCountLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Hacking_CodeEditor_ByteCount::create());
		byteCountLabel->setTextColor(CodeHud::HeaderColor);

		LocalizedLabel* bytesUsedLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Common_XOverY::create());

		bytesUsedLabel->setStringReplacementVariables
		({
			ConstantString::create(std::to_string(compileResult.byteCount)),
			ConstantString::create(std::to_string(this->activeHackableCode->getOriginalLength())),
		});

		if (isByteOverflow)
		{
			bytesUsedLabel->setTextColor(CodeHud::ErrorColor);
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
				LocalizedLabel* byteOverflowLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Hacking_CodeEditor_ByteOverflow::create());
				
				byteOverflowLabel->setTextColor(CodeHud::ErrorColor);

				this->statusWindow->insert(byteOverflowLabel);
			}
			else
			{
				LocalizedLabel* byteOverflowLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Hacking_CodeEditor_UnfilledBytes::create());
				
				byteOverflowLabel->setTextColor(CodeHud::SubtextColor);

				this->statusWindow->insert(byteOverflowLabel);
			}
		}

		LocalizedLabel* bytesLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Hacking_CodeEditor_Bytes::create());
		
		bytesLabel->setTextColor(CodeHud::HeaderColor);

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
		LocalizedLabel* statusLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Hacking_CodeEditor_Status::create());
		
		statusLabel->setTextColor(CodeHud::HeaderColor);

		this->statusWindow->insert(statusLabel);

		LocalizedLabel* compileErrorsLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Hacking_CodeEditor_CompileErrors::create());
		
		compileErrorsLabel->setTextColor(CodeHud::ErrorColor);

		this->statusWindow->insert(compileErrorsLabel);

		LocalizedLabel* errorLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Hacking_CodeEditor_Error::create());
		
		errorLabel->setTextColor(CodeHud::HeaderColor);

		this->statusWindow->insert(errorLabel);

		LocalizedLabel* errorMessageLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, compileResult.errorData.message);
		
		this->statusWindow->insert(errorMessageLabel);

		LocalizedLabel* lineNumberLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Hacking_CodeEditor_LineNumber::create());
		
		lineNumberLabel->setTextColor(CodeHud::HeaderColor);

		this->statusWindow->insert(lineNumberLabel);

		LocalizedLabel* lineNumberValueLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, ConstantString::create(std::to_string(compileResult.errorData.lineNumber)));
		
		this->statusWindow->insert(lineNumberValueLabel);
		
		this->disableAccept();
	}
}

void CodeHud::onAccept()
{
	if (this->lexicon != nullptr)
	{
		this->lexicon->close();
	}

	this->functionWindow->unfocus();
	this->scriptList->saveScripts();

	std::string scriptText = this->functionWindow->getText();
	HackUtils::CompileResult compileResult = HackUtils::assemble(scriptText, this->activeHackableCode->getPointer());

	// Sanity check that the code compiles -- it should at this point
	if (compileResult.hasError || compileResult.byteCount > this->activeHackableCode->getOriginalLength())
	{
		this->disableAccept();
		return;
	}

	// Enable hack with new assembly
	this->activeHackableCode->applyCustomCode(scriptText);

	this->setVisible(false);
	this->getParent()->setOpacity(0xFF);

	HackableEvents::TriggerEditHackableAttributeDone();
}

void CodeHud::onCancel()
{
	if (this->lexicon != nullptr)
	{
		this->getLexicon()->close();
	}

	this->functionWindow->unfocus();
	this->scriptList->saveScripts();

	this->setVisible(false);

	HackableEvents::TriggerEditHackableAttributeDone();
}

Lexicon* CodeHud::getLexicon()
{
	// Lazy initialization for lexicon since it is a little bit resource intensive (several sprites, buttons)
	if (this->lexicon == nullptr)
	{
		this->lexicon = Lexicon::create();

		this->lexicon->setCloseCallBack([=]()
		{
			GameUtils::focus(this);
			this->functionWindow->focus();
		});

		this->lexicon->setVisible(false);

		this->addChild(this->lexicon);
	}

	return this->lexicon;
}
