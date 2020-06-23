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
	this->languageButtons = std::vector<ClickableTextNode*>();

	for (int index = (int)LanguageType::FIRST_LANGUAGE; index <= (int)LanguageType::LAST_LANGUAGE; index++)
	{
		LanguageType language = (LanguageType)index;
		LocalizedString* nextString = Strings::Common_NativeLanguage::create();

		nextString->setOverrideLanguage(language);

		ClickableTextNode* button = this->constructLanguageButton(nextString);

		button->setMouseClickCallback([=](InputEvents::MouseEventArgs*) { Localization::setLanguage(language); });

		this->languageButtons.push_back(button);
	}

	for (auto next : this->languageButtons)
	{
		this->addChild(next);
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
		LanguageType language = (LanguageType)index;

		if (buttonIndex < int(this->languageButtons.size()))
		{
			this->languageButtons[buttonIndex]->setMouseClickCallback([=](InputEvents::MouseEventArgs*) { Localization::setLanguage(language); });
		}
	}
}

void LanguageTab::initializePositions()
{
	super::initializePositions();

	const Vec2 offset = Vec2(-240.0f, 212.0f);
	const Vec2 spacing = Vec2(224.0f, 56.0f);
	int index = 0;

	for (auto next : this->languageButtons)
	{
		float x = (float)(index / 10) * spacing.x + offset.x;
		float y = -(float)(index % 10) * spacing.y + offset.y;

		next->setPosition(Vec2(x, y));

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
