#include "ChooseTargetMenu.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Sound/Sound.h"
#include "Events/CombatEvents.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

ChooseTargetMenu* ChooseTargetMenu::create()
{
	ChooseTargetMenu* instance = new ChooseTargetMenu();

	instance->autorelease();

	return instance;
}

ChooseTargetMenu::ChooseTargetMenu()
{
	this->background = Sprite::create(UIResources::Combat_ItemFrame);
	this->iconPreviewNode = Node::create();
	this->firstStrikeLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Platformer_Combat_ChooseATarget::create());

	this->firstStrikeLabel->enableOutline(Color4B::BLACK, 2);
	this->firstStrikeLabel->setAnchorPoint(Vec2(0.0f, 0.5f));

	this->addChild(this->background);
	this->addChild(this->iconPreviewNode);
	this->addChild(this->firstStrikeLabel);
}

ChooseTargetMenu::~ChooseTargetMenu()
{
}

void ChooseTargetMenu::onEnter()
{
	super::onEnter();
	
	this->setVisible(false);
}

void ChooseTargetMenu::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 368.0f));

	this->iconPreviewNode->setPosition(Vec2(-112.0f, 0.0f));
	this->firstStrikeLabel->setPosition(Vec2(-48.0f, 0.0f));
}

void ChooseTargetMenu::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventChangeMenuState, [=](EventCustom* args)
	{
		CombatEvents::MenuStateArgs* combatArgs = static_cast<CombatEvents::MenuStateArgs*>(args->getData());

		if (combatArgs != nullptr)
		{
			iconPreviewNode->removeAllChildren();

			switch (combatArgs->currentMenu)
			{
				case CombatEvents::MenuStateArgs::CurrentMenu::ChooseAnyTarget:
				case CombatEvents::MenuStateArgs::CurrentMenu::ChooseAttackTarget:
				case CombatEvents::MenuStateArgs::CurrentMenu::ChooseBuffTarget:
				case CombatEvents::MenuStateArgs::CurrentMenu::ChooseResurrectionTarget:
				{
					this->setVisible(true);

					switch (combatArgs->selectionMeta.choice)
					{
						case CombatEvents::MenuStateArgs::SelectionMeta::Choice::Attack:
						{
							this->setVisible(true);
							iconPreviewNode->addChild(Sprite::create(UIResources::Combat_AttackCircle));
							iconPreviewNode->addChild(Sprite::create(combatArgs->selectionMeta.iconResource));
							break;
						}
						case CombatEvents::MenuStateArgs::SelectionMeta::Choice::Item:
						{
							this->setVisible(true);
							iconPreviewNode->addChild(Sprite::create(UIResources::Combat_ItemsCircle));
							iconPreviewNode->addChild(Sprite::create(combatArgs->selectionMeta.iconResource));
							break;
						}
						default:
						{
							break;
						}
					}
					break;
				}
				default:
				{
					this->setVisible(false);
					break;
				}
			}
		}
	}));
}

void ChooseTargetMenu::show(bool playerFirstStrike)
{
}
