#include "HexusRewardsMenu.h"

const std::string HexusRewardsMenu::KeyScheduleHexusGoldTick = "KEY_SCHEDULE_HEXUS_GOLD_TICK";

HexusRewardsMenu * HexusRewardsMenu::create()
{
	HexusRewardsMenu* instance = new HexusRewardsMenu();

	instance->autorelease();

	return instance;
}

HexusRewardsMenu::HexusRewardsMenu()
{
	this->background = Sprite::create(Resources::Menus_MinigamesMenu_Hexus_WoodBackground);
	this->goldSprite = Sprite::create(Resources::Menus_Objects_GOLD_2);
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
		returnButtonLabelClick,
		Resources::Minigames_Hexus_ButtonPlank,
		Resources::Minigames_Hexus_ButtonPlankHover,
		Resources::Minigames_Hexus_ButtonPlankClick
	);
	
	this->addChild(this->background);
	this->addChild(this->goldSprite);
	this->addChild(this->goldLabel);
	this->addChild(this->returnButton);
	this->addChild(Mouse::create());
}

HexusRewardsMenu::~HexusRewardsMenu()
{
}

void HexusRewardsMenu::onEnter()
{
	FadeScene::onEnter();

	float delay = 0.25f;
	float duration = 0.35f;
}

void HexusRewardsMenu::initializeListeners()
{
	FadeScene::initializeListeners();
}

void HexusRewardsMenu::initializePositions()
{
	FadeScene::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->background->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->goldSprite->setPosition(Vec2(visibleSize.width / 2.0f - 48.0f, visibleSize.height / 2.0f));
	this->goldLabel->setPosition(Vec2(visibleSize.width / 2.0f + 48.0f, visibleSize.height / 2.0f));
	this->returnButton->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f - 128.0f));
}

void HexusRewardsMenu::onRewardsOpen(EventCustom* eventCustom)
{
	HexusEvents::HexusRewardArgs* args = (HexusEvents::HexusRewardArgs*)(eventCustom->getUserData());

	this->returnButton->setClickCallback(CC_CALLBACK_1(HexusRewardsMenu::onReturnClick, this, args->backToChapterSelect));

	int reward = args->opponentData->reward;

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

	NavigationEvents::navigate(NavigationEvents::GameScreen::Minigames_Hexus_Rewards);
}

void HexusRewardsMenu::onReturnClick(MenuSprite* menuSprite, bool backToChapterSelect)
{
	NavigationEvents::navigateBack(backToChapterSelect ? 3 : 2);
}
