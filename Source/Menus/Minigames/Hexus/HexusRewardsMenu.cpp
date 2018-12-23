#include "HexusRewardsMenu.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/GlobalDirector.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Sound/SoundManager.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Engine/UI/Controls/TextMenuSprite.h"
#include "Engine/UI/Mouse.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Events/NavigationEvents.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardRow.h"
#include "Scenes/Hexus/CardStorage.h"

#include "Resources/SoundResources.h"

#include "Strings/Menus/Return.h"

using namespace cocos2d;

const std::string HexusRewardsMenu::KeyScheduleHexusGoldTick = "KEY_SCHEDULE_HEXUS_GOLD_TICK";

HexusRewardsMenu* HexusRewardsMenu::instance;

void HexusRewardsMenu::registerGlobalScene()
{
	if (HexusRewardsMenu::instance == nullptr)
	{
		HexusRewardsMenu::instance = new HexusRewardsMenu();

		HexusRewardsMenu::instance->autorelease();
		HexusRewardsMenu::instance->initializeListeners();
	}

	GlobalDirector::registerGlobalScene(HexusRewardsMenu::instance);
}

HexusRewardsMenu::HexusRewardsMenu()
{
	this->background = Sprite::create(UIResources::Menus_MinigamesMenu_Hexus_WoodBackground);
	this->goldSprite = Sprite::create(UIResources::Menus_Objects_GOLD_2);
	this->goldSpriteLesser = Sprite::create(UIResources::Menus_Objects_GOLD_1);
	this->goldLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1);

	this->goldLabel->enableOutline(Color4B::BLACK, 3);
	
	LocalizedLabel* returnButtonLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, LocaleStrings::Return::create());
	LocalizedLabel* returnButtonLabelHover = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, LocaleStrings::Return::create());

	returnButtonLabel->enableOutline(Color4B::BLACK, 2);
	returnButtonLabelHover->enableOutline(Color4B::BLACK, 2);

	this->returnButton = TextMenuSprite::create(
		returnButtonLabel,
		returnButtonLabelHover,
		UIResources::Menus_Buttons_WoodButton,
		UIResources::Menus_Buttons_WoodButtonSelected
	);
	
	this->addChild(this->background);
	this->addChild(this->goldSprite);
	this->addChild(this->goldSpriteLesser);
	this->addChild(this->goldLabel);
	this->addChild(this->returnButton);
}

HexusRewardsMenu::~HexusRewardsMenu()
{
}

void HexusRewardsMenu::onEnter()
{
	GlobalScene::onEnter();

	float delay = 0.25f;
	float duration = 0.35f;

	SoundManager::playSoundResource(SoundResources::Hexus_Reward);
}

void HexusRewardsMenu::initializeListeners()
{
	GlobalScene::initializeListeners();

	HexusRewardsMenu::instance->addGlobalEventListener(EventListenerCustom::create(NavigationEvents::EventNavigateHexusRewards, [](EventCustom* args)
	{
		NavigationEvents::NavigateHexusRewardArgs* rewardsArgs = static_cast<NavigationEvents::NavigateHexusRewardArgs*>(args->getUserData());

		if (rewardsArgs != nullptr)
		{
			GlobalDirector::loadScene(HexusRewardsMenu::instance);
			HexusRewardsMenu::instance->onRewardsOpen(rewardsArgs->reward, rewardsArgs->isRewardReduced);
		}
	}));

	this->returnButton->setClickCallback(CC_CALLBACK_1(HexusRewardsMenu::onReturnClick, this));
}

void HexusRewardsMenu::initializePositions()
{
	GlobalScene::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->background->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->goldSprite->setPosition(Vec2(visibleSize.width / 2.0f - 48.0f, visibleSize.height / 2.0f));
	this->goldSpriteLesser->setPosition(Vec2(visibleSize.width / 2.0f - 48.0f, visibleSize.height / 2.0f));
	this->goldLabel->setPosition(Vec2(visibleSize.width / 2.0f + 48.0f, visibleSize.height / 2.0f));
	this->returnButton->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f - 128.0f));
}

void HexusRewardsMenu::onRewardsOpen(int reward, bool isRewardReduced)
{
	if (isRewardReduced)
	{
		this->goldSpriteLesser->setVisible(true);
		this->goldSprite->setVisible(false);
	}
	else
	{
		this->goldSpriteLesser->setVisible(false);
		this->goldSprite->setVisible(true);
	}

	CardStorage::addGold(reward);

	const int ticks = 15;
	const float interval = 0.05f;
	const float delay = 0.0f;

	static int currentTick = 0;

	currentTick = 0;

	this->goldLabel->schedule([=](float dt)
	{
		float progress = MathUtils::clamp(((float)currentTick / (float)ticks), 0.0f, 1.0f);

		this->goldLabel->setString("+" + std::to_string((int)(reward * progress)));

		currentTick++;

	}, interval, ticks, delay, HexusRewardsMenu::KeyScheduleHexusGoldTick);
}

void HexusRewardsMenu::onReturnClick(MenuSprite* menuSprite)
{
	NavigationEvents::navigateBack(2);
}
