#include "HexusRewardsMenu.h"

HexusRewardsMenu * HexusRewardsMenu::create()
{
	HexusRewardsMenu* instance = new HexusRewardsMenu();

	instance->autorelease();

	return instance;
}

HexusRewardsMenu::HexusRewardsMenu()
{
	this->background = Sprite::create(Resources::Menus_MinigamesMenu_Hexus_WoodBackground);
	this->rewardRow = CardRow::create(true);
	this->selectRewardLabel = Label::create("Select a Reward", Localization::getMainFont(), Localization::getFontSizeH1(Localization::getMainFont()));

	this->rewardRow->setCardScale(1.0f, 0.0f);
	this->selectRewardLabel->enableOutline(Color4B::BLACK, 2);

	this->addChild(this->background);
	this->addChild(this->rewardRow);
	this->addChild(this->selectRewardLabel);
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
	this->rewardRow->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->selectRewardLabel->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 320.0f));
}

void HexusRewardsMenu::onRewardSelect(Card* card)
{
	CardStorage::addStorageCard(card->cardData);

	NavigationEvents::navigateBack(2);
}

void HexusRewardsMenu::onRewardsOpen(EventCustom* eventCustom)
{
	HexusEvents::HexusRewardArgs* args = (HexusEvents::HexusRewardArgs*)(eventCustom->getUserData());

	this->rewardRow->clear();

	for (auto it = args->opponentData->rewards.begin(); it != args->opponentData->rewards.end(); it++)
	{
		Card* rewardOption = Card::create(Card::CardStyle::Earth, (*it));
		this->rewardRow->insertCard(rewardOption, 0.0f);
	}

	this->rewardRow->setMouseClickCallback(CC_CALLBACK_1(HexusRewardsMenu::onRewardSelect, this));

	NavigationEvents::navigate(NavigationEvents::GameScreen::Minigames_Hexus_Rewards);
}
