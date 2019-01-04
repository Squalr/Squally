#include "LanguageTab.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Config/ConfigManager.h"
#include "Engine/Sound/SoundManager.h"
#include "Engine/UI/Controls/CCheckbox.h"
#include "Engine/UI/Controls/CSlider.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/Utils/GameUtils.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

LanguageTab* LanguageTab::create()
{
	LanguageTab* instance = new LanguageTab();

	instance->autorelease();

	return instance;
}

LanguageTab::LanguageTab()
{
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
}

void LanguageTab::initializePositions()
{
	super::initializePositions();
}
