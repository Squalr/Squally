#include "DefeatMenu.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Events/ObjectEvents.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/Item.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Sound/Sound.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Events/CombatEvents.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

DefeatMenu* DefeatMenu::create()
{
	DefeatMenu* instance = new DefeatMenu();

	instance->autorelease();

	return instance;
}

DefeatMenu::DefeatMenu()
{
	this->defeatBanner = Sprite::create(UIResources::Combat_DefeatMenu);
	this->defeatLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Platformer_Combat_Defeat::create());
	this->defeatSound = Sound::create(SoundResources::Platformer_Combat_Defeat);

	LocalizedLabel*	returnLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Return::create());
	LocalizedLabel*	returnLabelHover = returnLabel->clone();

	returnLabel->enableOutline(Color4B::BLACK, 2);
	returnLabelHover->enableOutline(Color4B::BLACK, 2);

	this->returnButton = ClickableTextNode::create(returnLabel, returnLabelHover, Sprite::create(UIResources::Menus_Buttons_WoodButton), Sprite::create(UIResources::Menus_Buttons_WoodButtonSelected));

	this->defeatLabel->enableOutline(Color4B::BLACK, 2);

	this->addChild(this->defeatBanner);
	this->addChild(this->defeatLabel);
	this->addChild(this->returnButton);
	this->addChild(this->defeatSound);
}

DefeatMenu::~DefeatMenu()
{
}

void DefeatMenu::onEnter()
{
	super::onEnter();

	this->setOpacity(0);
}

void DefeatMenu::initializePositions()
{
	super::initializePositions();

	this->defeatBanner->setPosition(Vec2(16.0f, 0.0f));
	this->defeatLabel->setPosition(Vec2(0.0f, 176.0f));
	this->returnButton->setPosition(Vec2(0.0f, -160.0f));
}

void DefeatMenu::initializeListeners()
{
	super::initializeListeners();

	this->returnButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		CombatEvents::TriggerBeforeReturnToMap(CombatEvents::BeforeReturnToMapArgs(true));
		CombatEvents::TriggerReturnToMapRespawn();
	});

	this->whenKeyPressed({ InputEvents::KeyCode::KEY_SPACE }, [=](InputEvents::KeyboardEventArgs* args)
	{
		if (!GameUtils::isVisible(this))
		{
			return;
		}
		
		CombatEvents::TriggerBeforeReturnToMap(CombatEvents::BeforeReturnToMapArgs(true));
		CombatEvents::TriggerReturnToMapRespawn();
	});
}

void DefeatMenu::show()
{
	this->runAction(FadeTo::create(1.0f, 255));
	this->defeatSound->play();
}
