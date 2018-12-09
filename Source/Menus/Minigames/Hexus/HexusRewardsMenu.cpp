#include "HexusRewardsMenu.h"

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
	this->goldLabel = Label::create("", Localization::getMainFont(), Localization::getFontSizeH1(Localization::getMainFont()));

	this->goldLabel->enableOutline(Color4B::BLACK, 3);
	
	Label* returnButtonLabel = Label::create("Return", Localization::getMainFont(), Localization::getFontSizeP(Localization::getMainFont()));
	Label* returnButtonLabelHover = Label::create("Return", Localization::getMainFont(), Localization::getFontSizeP(Localization::getMainFont()));
	Label* returnButtonLabelClick = Label::create("Return", Localization::getMainFont(), Localization::getFontSizeP(Localization::getMainFont()));

	returnButtonLabel->enableOutline(Color4B::BLACK, 2);
	returnButtonLabelHover->enableOutline(Color4B::BLACK, 2);
	returnButtonLabelClick->enableOutline(Color4B::BLACK, 2);

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
	this->addChild(Mouse::create());
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
