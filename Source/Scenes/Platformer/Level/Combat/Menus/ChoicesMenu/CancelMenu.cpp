#include "CancelMenu.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Level/Combat/Menus/ChoicesMenu/RadialEntry.h"
#include "Scenes/Platformer/Level/Combat/Menus/ChoicesMenu/RadialScrollMenu.h"
#include "Scenes/Platformer/Level/Combat/TimelineEntry.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const float CancelMenu::Radius = 240.0f;

CancelMenu* CancelMenu::create()
{
	CancelMenu* instance = new CancelMenu();

	instance->autorelease();

	return instance;
}

CancelMenu::CancelMenu()
{
	this->cancelMenu = RadialScrollMenu::create(CancelMenu::Radius);
	this->currentMenu = CombatEvents::MenuStateArgs::CurrentMenu::Closed;
	this->previousMenu = CombatEvents::MenuStateArgs::CurrentMenu::Closed;
	this->trackTarget = nullptr;

	this->cancelButton = this->cancelMenu->addEntry(Strings::Menus_Cancel::create(), { }, UIResources::Menus_Icons_Cross, UIResources::Combat_AttackCircle, [=]()
	{
		this->onCancelClick();
	});
	
	this->cancelMenu->unfocus();

	this->addChild(this->cancelMenu);
}

CancelMenu::~CancelMenu()
{
}

void CancelMenu::onEnter()
{
	super::onEnter();

	this->cancelMenu->setVisible(false);

	this->scheduleUpdate();
}

void CancelMenu::initializePositions()
{
	super::initializePositions();
}

void CancelMenu::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventChangeMenuState, [=](EventCustom* eventCustom)
	{
		CombatEvents::MenuStateArgs* combatArgs = static_cast<CombatEvents::MenuStateArgs*>(eventCustom->getUserData());

		if (combatArgs != nullptr)
		{
			this->previousMenu = this->currentMenu;
			this->currentMenu = combatArgs->currentMenu;

			this->track(combatArgs->entry == nullptr ? nullptr : combatArgs->entry->getEntity());

			switch (this->currentMenu)
			{
				case CombatEvents::MenuStateArgs::CurrentMenu::ChooseAnyTarget:
				case CombatEvents::MenuStateArgs::CurrentMenu::ChooseAttackTarget:
				case CombatEvents::MenuStateArgs::CurrentMenu::ChooseBuffTarget:
				case CombatEvents::MenuStateArgs::CurrentMenu::ChooseResurrectionTarget:
				{
					this->cancelMenu->setVisible(true);
					this->cancelButton->enableInteraction(127);
					break;
				}
				default:
				{
					this->cancelMenu->setVisible(false);
					this->cancelButton->disableInteraction(0);
					break;
				}
			}
		}
	}));
}

void CancelMenu::update(float dt)
{
	super::update(dt);

	static const Vec2 Offset = Vec2(-64.0f, 0.0f);

	if (this->trackTarget != nullptr)
	{
		this->setPosition(GameUtils::getScreenBounds(this->trackTarget).origin + this->trackTarget->getEntityCenterPoint() + Offset);
	}
}

void CancelMenu::onCancelClick()
{
	CombatEvents::TriggerMenuStateChange(CombatEvents::MenuStateArgs(this->previousMenu, nullptr));
}

void CancelMenu::track(PlatformerEntity* trackTarget)
{
	this->trackTarget = trackTarget;
}
