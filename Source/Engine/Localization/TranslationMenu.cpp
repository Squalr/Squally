#include "TranslationMenu.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCDirector.h"
#include "cocos/ui/UITextField.h"

#include "Engine/Analytics/Analytics.h"
#include "Engine/GlobalDirector.h"
#include "Engine/Localization/Localization.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/UI/Controls/TextMenuSprite.h"

#include "Resources/UIResources.h"

#include "Strings/Generics/Empty.h"
#include "Strings/Menus/Cancel.h"
#include "Strings/Menus/Submit.h"
#include "Strings/Menus/TranslationEditor/CurrentTranslation.h"
#include "Strings/Menus/TranslationEditor/NewTranslation.h"
#include "Strings/Menus/TranslationEditor/OriginalTextInEnglish.h"
#include "Strings/Menus/TranslationEditor/TranslationEditor.h"

using namespace cocos2d;
using namespace cocos2d::ui;

TranslationMenu* TranslationMenu::instance = nullptr;
const cocos2d::Size TranslationMenu::PreviousTranslationSize = Size(480.0f, 0.0f);
const cocos2d::Size TranslationMenu::InputSize = Size(512.0f, 512.0f);

void TranslationMenu::registerGlobalNode()
{
	if (TranslationMenu::instance == nullptr)
	{
		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->registerGlobalNode(TranslationMenu::getInstance());
	}
}

TranslationMenu* TranslationMenu::getInstance()
{
	if (TranslationMenu::instance == nullptr)
	{
		TranslationMenu::instance = new TranslationMenu();

		TranslationMenu::instance->autorelease();
	}

	return TranslationMenu::instance;
}

TranslationMenu::TranslationMenu()
{
	this->menuBackground = Sprite::create(UIResources::Menus_TranslateMenu_TranslateMenu);
	this->title = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H2, Strings::Menus_TranslationEditor_TranslationEditor::create());
	this->englishTitle = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_TranslationEditor_OriginalTextInEnglish::create());
	this->englishTranslation = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Generics_Empty::create(), TranslationMenu::PreviousTranslationSize);
	this->nativeTitle = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_TranslationEditor_CurrentTranslation::create());
	this->oldTranslation = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Generics_Empty::create(), TranslationMenu::PreviousTranslationSize);
	this->newTranslationTitle = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_TranslationEditor_NewTranslation::create());
	this->newTranslation = UICCTextField::create("", this->oldTranslation->getFont(), this->oldTranslation->getFontSize());

	this->newTranslation->setLineBreakWithoutSpace(true);
	this->newTranslation->setCascadeOpacityEnabled(false);
	this->newTranslation->setCursorEnabled(true);
	this->newTranslation->enableWrap(true);
	this->newTranslation->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->englishTranslation->setAlignment(TextHAlignment::LEFT);
	this->englishTranslation->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->oldTranslation->setAlignment(TextHAlignment::LEFT);
	this->oldTranslation->setAnchorPoint(Vec2(0.0f, 1.0f));

	this->oldTranslation->setTextColor(Color4B::RED);

	// Disallow editing anything on this page -- this is a bit too meta
	this->title->toggleAllowTranslationEdit(false);
	this->englishTitle->toggleAllowTranslationEdit(false);
	this->englishTranslation->toggleAllowTranslationEdit(false);
	this->nativeTitle->toggleAllowTranslationEdit(false);
	this->oldTranslation->toggleAllowTranslationEdit(false);
	this->newTranslationTitle->toggleAllowTranslationEdit(false);

	LocalizedLabel* cancelLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Cancel::create());
	LocalizedLabel* cancelLabelSelected = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Cancel::create());

	cancelLabel->toggleAllowTranslationEdit(false);
	cancelLabelSelected->toggleAllowTranslationEdit(false);

	this->cancelButton = TextMenuSprite::create(cancelLabel, cancelLabelSelected, UIResources::Menus_Buttons_GenericButton, UIResources::Menus_Buttons_GenericButtonHover);

	LocalizedLabel* label = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Submit::create());
	LocalizedLabel* labelSelected = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Submit::create());

	label->toggleAllowTranslationEdit(false);
	labelSelected->toggleAllowTranslationEdit(false);

	this->submitButton = TextMenuSprite::create(label, labelSelected, UIResources::Menus_Buttons_GenericButton, UIResources::Menus_Buttons_GenericButtonHover);

	this->setVisible(false);

	this->addChild(this->menuBackground);
	this->addChild(this->title);
	this->addChild(this->englishTranslation);
	this->addChild(this->oldTranslation);
	this->addChild(this->newTranslationTitle);
	this->addChild(this->newTranslation);
	this->addChild(this->englishTitle);
	this->addChild(this->nativeTitle);
	this->addChild(this->cancelButton);
	this->addChild(this->submitButton);
}

TranslationMenu::~TranslationMenu()
{
}

void TranslationMenu::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->menuBackground->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->title->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 372.0f));
	this->englishTitle->setPosition(Vec2(visibleSize.width / 2.0f - 272.0f, visibleSize.height / 2.0f + 256.0f));
	this->nativeTitle->setPosition(Vec2(visibleSize.width / 2.0f - 272.0f, visibleSize.height / 2.0f - 48.0f));
	this->englishTranslation->setPosition(Vec2(visibleSize.width / 2.0f - 272.0f - TranslationMenu::PreviousTranslationSize.width / 2.0f, visibleSize.height / 2.0f + 212.0f));
	this->oldTranslation->setPosition(Vec2(visibleSize.width / 2.0f - 272.0f - TranslationMenu::PreviousTranslationSize.width / 2.0f, visibleSize.height / 2.0f - 88.0f));
	this->newTranslationTitle->setPosition(Vec2(visibleSize.width / 2.0f + 272.0f, visibleSize.height / 2.0f + 256.0f));
	this->newTranslation->setPosition(Vec2(visibleSize.width / 2.0f + 272.0f - TranslationMenu::InputSize.width / 2.0f, visibleSize.height / 2.0f + 212.0f));
	this->cancelButton->setPosition(Vec2(visibleSize.width / 2.0f - 256.0f, visibleSize.height / 2.0f - 348.0f));
	this->submitButton->setPosition(Vec2(visibleSize.width / 2.0f + 256.0f, visibleSize.height / 2.0f - 348.0f));

	this->newTranslation->setContentSize(TranslationMenu::InputSize);
	this->newTranslation->setDimensions(TranslationMenu::InputSize.width, TranslationMenu::InputSize.height);
}

void TranslationMenu::initializeListeners()
{
	super::initializeListeners();

	this->addGlobalEventListener(EventListenerCustom::create(LocalizationEvents::TranslationBeginEdit, [=](EventCustom* eventArgs)
	{
		this->onTranslationMenuOpen(static_cast<LocalizationEvents::TranslationBeginEditArgs*>(eventArgs->getUserData()));
	}));

	cancelButton->setClickCallback([=](MenuSprite*, MouseEvents::MouseEventArgs*) { this->onCancelClick(); });
	submitButton->setClickCallback([=](MenuSprite*, MouseEvents::MouseEventArgs*) { this->onSubmitClick(); });
}

void TranslationMenu::onTranslationMenuOpen(LocalizationEvents::TranslationBeginEditArgs* args)
{
	this->previousFocus = GameUtils::getFocusedNode();

	if (this->previousFocus == this)
	{
		return;
	}

	this->editTarget = args->localizedString;
	LocalizedString* englishString = this->editTarget->clone();

	englishString->setOverrideLanguage(LanguageType::ENGLISH);

	this->englishTranslation->setLocalizedString(englishString);
	this->oldTranslation->setLocalizedString(this->editTarget->clone());
	this->newTranslation->initWithTTF(this->oldTranslation->getString(), this->oldTranslation->getFont(), this->oldTranslation->getFontSize(), this->newTranslation->getDimensions());
	this->newTranslation->attachWithIME();

	GameUtils::focus(this);
	this->setVisible(true);
}

void TranslationMenu::onCancelClick()
{
	this->setVisible(false);
	GameUtils::focus(this->previousFocus);
}

void TranslationMenu::onSubmitClick()
{
	if (this->editTarget != nullptr && this->oldTranslation->getString() != this->newTranslation->getString())
	{
		Analytics::sendEvent("TRANSLATION_EDIT", this->editTarget->getStringIdentifier(), this->newTranslation->getString(), (int)Localization::getLanguage());
	}
		
	this->setVisible(false);
	GameUtils::focus(this->previousFocus);
}
