#include "LanguageTab.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Config/ConfigManager.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"
#include "Engine/Localization/Localization.h"

using namespace cocos2d;

LanguageTab* LanguageTab::create()
{
	LanguageTab* instance = new LanguageTab();

	instance->autorelease();

	return instance;
}

LanguageTab::LanguageTab()
{
	for (int index = (int)LanguageType::FIRST_LANGUAGE; index <= (int)LanguageType::LAST_LANGUAGE; index++)
	{
		LanguageType languageType = (LanguageType)index;
		
		// Support for arabic removed due to poor cocos2d-x support https://github.com/cocos2d/cocos2d-x/issues/15321
		if (languageType == LanguageType::ARABIC)
		{
			continue;
		}

		LocalizedString* nextString = Strings::Common_NativeLanguage::create();

		nextString->setOverrideLanguage(languageType);

		ClickableTextNode* button = this->constructLanguageButton(nextString);

		button->setMouseClickCallback([=](InputEvents::MouseEventArgs*) { Localization::setLanguage(languageType); });

		this->languageButtons[languageType] = button;
		this->addChild(button);
	}
}

LanguageTab::~LanguageTab()
{
}

void LanguageTab::onEnter()
{
	super::onEnter();

	float delay = 0.1f;
	float duration = 0.25f;
}

void LanguageTab::initializeListeners()
{
	super::initializeListeners();

	int buttonIndex = 0;

	for (int index = (int)LanguageType::FIRST_LANGUAGE; index <= (int)LanguageType::LAST_LANGUAGE; index++, buttonIndex++)
	{
		LanguageType languageType = (LanguageType)index;

		if (this->languageButtons.find(languageType) != this->languageButtons.end())
		{
			this->languageButtons[languageType]->setMouseClickCallback([=](InputEvents::MouseEventArgs*) { Localization::setLanguage(languageType); });
		}
	}
}

void LanguageTab::initializePositions()
{
	super::initializePositions();

	const Vec2 offset = Vec2(-240.0f, 212.0f);
	const Vec2 spacing = Vec2(224.0f, 56.0f);
	int index = 0;

	for (const auto& next : this->languageButtons)
	{
		float x = (float)(index / 10) * spacing.x + offset.x;
		float y = -(float)(index % 10) * spacing.y + offset.y;

		next.second->setPosition(Vec2(x, y));

		index++;
	}
}

ClickableTextNode* LanguageTab::constructLanguageButton(LocalizedString* string)
{
	LocalizedLabel* label = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, string);
	LocalizedLabel* labelHover = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, string->clone());

	ClickableTextNode* button = ClickableTextNode::create(label, labelHover, UIResources::Menus_OptionsMenu_DarkButton, UIResources::Menus_OptionsMenu_DarkButtonSelected);

	return button;
}
