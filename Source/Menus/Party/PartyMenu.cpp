#include "PartyMenu.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventListenerKeyboard.h"

#include "Engine/Events/ObjectEvents.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/PlatformerHelper.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/NotificationEvents.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/Level/Huds/Components/StatsBars.h"
#include "Scenes/Platformer/Level/PlatformerMap.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

PartyMenu* PartyMenu::create()
{
	PartyMenu* instance = new PartyMenu();

	instance->autorelease();

	return instance;
}

PartyMenu::PartyMenu()
{
	this->partyWindow = Sprite::create(UIResources::Menus_Generic_LargeMenu);
	this->closeButton = ClickableNode::create(UIResources::Menus_IngameMenu_CloseButton, UIResources::Menus_IngameMenu_CloseButtonSelected);
	this->partyLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Menus_Party_Party::create());
	this->statsBarsNode = Node::create();
	this->returnClickCallback = nullptr;
	this->partyStatsBars = std::vector<StatsBars*>();

	LocalizedLabel*	returnLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Return::create());
	LocalizedLabel*	returnLabelSelected = returnLabel->clone();

	returnLabel->enableOutline(Color4B::BLACK, 2);
	returnLabel->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	returnLabel->enableGlow(Color4B::BLACK);
	returnLabelSelected->enableOutline(Color4B::BLACK, 2);
	returnLabelSelected->setTextColor(Color4B::YELLOW);
	returnLabelSelected->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	returnLabelSelected->enableGlow(Color4B::ORANGE);

	this->returnButton = ClickableTextNode::create(
		returnLabel,
		returnLabelSelected,
		UIResources::Menus_Buttons_WoodButton,
		UIResources::Menus_Buttons_WoodButtonSelected);

	LocalizedLabel*	stuckLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Party_Stuck::create());
	LocalizedLabel*	stuckLabelSelected = stuckLabel->clone();

	stuckLabel->enableOutline(Color4B::BLACK, 2);
	stuckLabel->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	stuckLabel->enableGlow(Color4B::BLACK);
	stuckLabelSelected->enableOutline(Color4B::BLACK, 2);
	stuckLabelSelected->setTextColor(Color4B::YELLOW);
	stuckLabelSelected->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	stuckLabelSelected->enableGlow(Color4B::ORANGE);

	this->stuckButton = ClickableTextNode::create(
		stuckLabel,
		stuckLabelSelected,
		UIResources::Menus_Buttons_SmallGenericButton,
		UIResources::Menus_Buttons_SmallGenericButtonSelected);

	this->partyLabel->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	this->partyLabel->enableGlow(Color4B::BLACK);

	this->addChild(this->partyWindow);
	this->addChild(this->partyLabel);
	this->addChild(this->statsBarsNode);
	this->addChild(this->closeButton);
	this->addChild(this->stuckButton);
	this->addChild(this->returnButton);
}

PartyMenu::~PartyMenu()
{
}

void PartyMenu::onEnter()
{
	super::onEnter();

	float delay = 0.1f;
	float duration = 0.25f;

	GameUtils::fadeInObject(this->partyWindow, delay, duration);
	GameUtils::fadeInObject(this->partyLabel, delay, duration);
	GameUtils::fadeInObject(this->closeButton, delay, duration);
	GameUtils::fadeInObject(this->returnButton, delay, duration);
}

void PartyMenu::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->partyWindow->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->statsBarsNode->setPosition(Vec2(visibleSize.width / 2.0f - 460.0f, visibleSize.height / 2.0f + 160.0f));
	this->partyLabel->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 380.0f));
	this->closeButton->setPosition(Vec2(visibleSize.width / 2.0f + 580.0f, visibleSize.height / 2.0f + 368.0f));
	this->stuckButton->setPosition(Vec2(visibleSize.width / 2.0f + 384.0f, visibleSize.height / 2.0f - 288.0f));
	this->returnButton->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f - 472.0f));
}

void PartyMenu::initializeListeners()
{
	super::initializeListeners();

	this->stuckButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		NotificationEvents::TriggerConfirmation(NotificationEvents::ConfirmationArgs(
			Strings::Menus_Party_StuckConfirm::create(),
			[=]()
			{
				PlatformerEvents::TriggerUnstuck();

				return true;
			},
			[=]()
			{
				return false;
			}
		));
	});

	this->returnButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		if (this->returnClickCallback != nullptr)
		{
			this->returnClickCallback();
		}
	});

	this->closeButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		if (this->returnClickCallback != nullptr)
		{
			this->returnClickCallback();
		}
	});
	this->closeButton->setClickSound(SoundResources::Menus_ClickBack1);

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_ESCAPE }, [=](InputEvents::InputArgs* args)
	{
		if (!GameUtils::isVisible(this))
		{
			return;
		}
		
		args->handle();

		if (this->returnClickCallback != nullptr)
		{
			this->returnClickCallback();
		}
	});
}

void PartyMenu::disableUnstuck()
{
	this->stuckButton->disableInteraction(127);
}

void PartyMenu::open()
{
	this->partyStatsBars.clear();
	this->statsBarsNode->removeAllChildren();

	ObjectEvents::QueryObjects(QueryObjectsArgs<Squally>([&](Squally* entity)
	{
		StatsBars* statsBars = StatsBars::create();

		statsBars->setStatsTarget(entity);

		this->statsBarsNode->addChild(statsBars);
		this->partyStatsBars.push_back(statsBars);
	}));

	ObjectEvents::QueryObjects(QueryObjectsArgs<PlatformerHelper>([&](PlatformerHelper* entity)
	{
		StatsBars* statsBars = StatsBars::create();

		statsBars->setStatsTarget(entity);

		this->statsBarsNode->addChild(statsBars);
		this->partyStatsBars.push_back(statsBars);
	}));

	for (int index = 0; index < int(this->partyStatsBars.size()); index++)
	{
		this->partyStatsBars[index]->setPositionY((float)index * -160.0f);
	}
}

void PartyMenu::setReturnClickCallback(std::function<void()> returnClickCallback)
{
	this->returnClickCallback = returnClickCallback;
}
