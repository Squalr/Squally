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
	
	Label* chooseButtonLabel = Label::create("Choose", Localization::getMainFont(), Localization::getFontSizeP(Localization::getMainFont()));
	Label* chooseButtonLabelHover = Label::create("Choose", Localization::getMainFont(), Localization::getFontSizeP(Localization::getMainFont()));
	Label* chooseButtonLabelClick = Label::create("Choose", Localization::getMainFont(), Localization::getFontSizeP(Localization::getMainFont()));

	chooseButtonLabel->enableOutline(Color4B::BLACK, 2);
	chooseButtonLabelHover->enableOutline(Color4B::BLACK, 2);
	chooseButtonLabelClick->enableOutline(Color4B::BLACK, 2);

	this->chooseButton = TextMenuSprite::create(
		chooseButtonLabel,
		chooseButtonLabelHover,
		chooseButtonLabelClick,
		Resources::Minigames_Hexus_ButtonPlank,
		Resources::Minigames_Hexus_ButtonPlankHover,
		Resources::Minigames_Hexus_ButtonPlankClick
	);
	
	this->selectedCard = nullptr;

	this->rewardRow->setCardScale(1.0f, 0.0f);
	this->selectRewardLabel->enableOutline(Color4B::BLACK, 2);

	this->addChild(this->background);
	this->addChild(this->rewardRow);
	this->addChild(this->chooseButton);
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

	this->selectedCard = nullptr;
	this->chooseButton->disableInteraction(128);
}

void HexusRewardsMenu::initializeListeners()
{
	FadeScene::initializeListeners();

	this->chooseButton->setClickCallback(CC_CALLBACK_1(HexusRewardsMenu::onChooseClick, this));
}

void HexusRewardsMenu::initializePositions()
{
	FadeScene::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->background->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->rewardRow->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->selectRewardLabel->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 320.0f));
	this->chooseButton->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f - 320.0f));
}

void HexusRewardsMenu::onRewardSelect(Card* card)
{
	for (auto it = this->rewardRow->rowCards->begin(); it != this->rewardRow->rowCards->end(); it++)
	{
		(*it)->unfocus();
	}

	card->focus();
	this->selectedCard = card;

	this->chooseButton->enableInteraction();
}

void HexusRewardsMenu::onRewardsOpen(EventCustom* eventCustom)
{
	HexusEvents::HexusRewardArgs* args = (HexusEvents::HexusRewardArgs*)(eventCustom->getUserData());

	this->backToChapterSelect = args->backToChapterSelect;
	this->rewardRow->clear();

	for (auto it = args->opponentData->rewards.begin(); it != args->opponentData->rewards.end(); it++)
	{
		Card* rewardOption = Card::create(Card::CardStyle::Earth, (*it));
		this->rewardRow->insertCard(rewardOption, 0.0f);
	}

	this->rewardRow->setMouseClickCallback(CC_CALLBACK_1(HexusRewardsMenu::onRewardSelect, this));

	NavigationEvents::navigate(NavigationEvents::GameScreen::Minigames_Hexus_Rewards);
}

void HexusRewardsMenu::onChooseClick(MenuSprite* menuSprite)
{
	if (this->selectedCard != nullptr)
	{
		// TODO: Animate selecting / moving to storage

		CardStorage::addStorageCard(this->selectedCard->cardData);
		NavigationEvents::navigateBack(this->backToChapterSelect ? 3 : 2);
	}
}
