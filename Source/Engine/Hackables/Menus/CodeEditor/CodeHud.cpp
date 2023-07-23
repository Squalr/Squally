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
#include "Engine/Optimization/LazyNode.h"
#include "Engine/Hackables/Menus/Clippy.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Lexicon.h"
#include "Engine/Hackables/Menus/CodeEditor/CodeWindow.h"
#include "Engine/Hackables/Menus/CodeEditor/ScriptEntry.h"
#include "Engine/Hackables/Menus/CodeEditor/ScriptList.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Hackables/HackableObject.h"
#include "Engine/Hackables/Menus/CodeEditor/CodeWindow.h"
#include "Engine/Hackables/Menus/HackablePreview.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/HackUtils.h"
#include "Engine/Utils/StrUtils.h"
#include "Engine/UI/Controls/LabelStack.h"
#include "Menus/Confirmation/ConfirmationMenu.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;
using namespace cocos2d::ui;

const float CodeHud::CompileDelayMaxSeconds = 0.1f;
const float CodeHud::LineNumberMargin = 32.0f;
const CSize CodeHud::StatusSize = CSize(420.0f, 1080.0f);
const CSize CodeHud::FunctionSize = CSize(912.0f, 800.0f);
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
	this->lexicon = LazyNode<Lexicon>::create(CC_CALLBACK_0(CodeHud::buildLexicon, this));

	this->statusBackground = Sprite::create(UIResources::Menus_HackerModeMenu_SideBar);
	this->rightBarBackground = Sprite::create(UIResources::Menus_HackerModeMenu_SideBar);
	this->radialEye = Sprite::create(UIResources::Menus_HackerModeMenu_Radial_RadialEyePupil);
	this->previewNode = Node::create();
	this->clippyNode = Node::create();

	this->functionWindow = CodeWindow::create(CodeHud::FunctionSize);
	this->statusWindow = LabelStack::create(CodeHud::StatusSize, 4.0f);
	this->registerWindow = LabelStack::create(CodeHud::StatusSize, 8.0f);
	this->confirmationMenu = ConfirmationMenu::create();
	this->scriptList = ScriptList::create(this->confirmationMenu, [=](ScriptEntry* scriptEntry) { this->functionWindow->openScript(scriptEntry); });
	this->titleLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Menus_Hacking_CodeEditor_FunctionHeader::create());

	LocalizedLabel*	acceptLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Apply::create());
	LocalizedLabel*	acceptLabelHover = acceptLabel->clone();

	LocalizedLabel*	cancelLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Cancel::create());
	LocalizedLabel*	cancelLabelHover = cancelLabel->clone();

	CSize shadowSize = CSize(-2.0f, -2.0f);
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

	this->statusWindow->setPadding(CSize(16.0f, 0.0f));
	this->registerWindow->setPadding(CSize(16.0f, 0.0f));

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
	this->addChild(this->lexicon);
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

	CSize visibleSize = Director::getInstance()->getVisibleSize();

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

	this->addEventListenerIgnorePause(EventListenerCustom::create(HackableEvents::EventHackableBaseEdit, [=](EventCustom* eventCustom)
	{
		HackableObjectEditArgs* args = static_cast<HackableObjectEditArgs*>(eventCustom->getData());
		
		if (args != nullptr)
		{
			this->open(args);
		}
	}));
	
	this->lexiconButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->functionWindow->unfocus();
		this->lexicon->lazyGet()->open();
	});
	
	this->stuckButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		Application::getInstance()->openURL("https://discord.gg/3maVXN5");
	});
}

void CodeHud::open(HackableObjectEditArgs* args)
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
			HackablePreview* preview = hackableCode->getHackablePreview()->lazyClone();

			if (preview != nullptr)
			{
				preview->setAssemblyTextVisible(true);

				this->previewNode->addChild(preview);
			}
		}

		this->clippyNode->removeAllChildren();

		if (args->hackableObject != nullptr && args->hackableObject->clippyMap.find(hackableCode->getHackableIdentifier()) != args->hackableObject->clippyMap.end())
		{
			Clippy* clippy = args->hackableObject->clippyMap[hackableCode->getHackableIdentifier()]();

			if (clippy != nullptr)
			{
				this->clippyNode->addChild(clippy);
				
				clippy->startDialogue();
			}
		}

		this->functionWindow->openScript(this->scriptList->getActiveScript());

		LocalizedString* functionName = hackableCode->getName();
		this->titleLabel->setStringReplacementVariables(functionName == nullptr ? nullptr : functionName->clone());

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

	for (const HackableCode::RegisterHintInfo& registerHint : this->activeHackableCode->registerHints)
	{
		LocalizedString* registerString = nullptr;
		
		if (registerHint.isPointer)
		{
			if (registerHint.pointerOffset == 0)
			{
				registerString = Strings::Common_Pointer::create()->setStringReplacementVariables(HackableCode::registerToLocalizedString(registerHint.reg));
			}
			else
			{
				registerString = Strings::Common_PlusPointerOffset::create()->setStringReplacementVariables(
				{
					HackableCode::registerToLocalizedString(registerHint.reg),
					ConstantString::create(std::to_string(registerHint.pointerOffset))
				});
			}
		}
		else
		{
			registerString = HackableCode::registerToLocalizedString(registerHint.reg);
		}

		LocalizedLabel* registerLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, registerString);
		registerLabel->setTextColor(CodeHud::RegisterColor);

		this->registerWindow->insert(registerLabel);

		LocalizedString* strRef = registerHint.hint;
		LocalizedString* strCopy = strRef == nullptr ? nullptr : strRef->clone();
		LocalizedLabel* registerHintLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, strCopy);

		this->registerWindow->insert(registerHintLabel);
	}
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
	if (this->lexicon->isBuilt())
	{
		this->lexicon->lazyGet()->close();
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
	GameUtils::focus(nullptr);
	this->getParent()->setOpacity(0xFF);

	HackableEvents::TriggerEditHackableBaseDone();
}

void CodeHud::onCancel()
{
	if (this->lexicon->isBuilt())
	{
		this->lexicon->lazyGet()->close();
	}

	this->functionWindow->unfocus();
	this->scriptList->saveScripts();

	this->setVisible(false);
	GameUtils::focus(nullptr);

	HackableEvents::TriggerEditHackableBaseDone();
}

Lexicon* CodeHud::buildLexicon()
{
	Lexicon* instance = Lexicon::create();

	instance->setCloseCallBack([=]()
	{
		GameUtils::focus(this);
		this->functionWindow->focus();
	});

	return instance;
}
