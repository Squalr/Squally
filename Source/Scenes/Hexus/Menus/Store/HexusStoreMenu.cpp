#include "HexusStoreMenu.h"

#include <math.h>

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCLayer.h"
#include "cocos/2d/CCParticleSystemQuad.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCEventListenerKeyboard.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/GlobalDirector.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/Sound/SoundManager.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Special/Shopkeeper.h"
#include "Events/NavigationEvents.h"
#include "Menus/Confirmation/ConfirmationMenu.h"
#include "Scenes/Hexus/Menus/MenuCard.h"
#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/CardPreview.h"
#include "Scenes/Hexus/CardStorage.h"

#include "Resources/HexusResources.h"
#include "Resources/ParticleResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Menus/Back.h"
#include "Strings/Hexus/PurchaseConfirmation.h"
#include "Strings/Menus/Return.h"
#include "Strings/Hexus/StoreLabelBinary.h"
#include "Strings/Hexus/StoreLabelDecimal.h"
#include "Strings/Hexus/StoreLabelHex.h"
#include "Strings/Hexus/StoreLabelSpecial.h"
#include "Strings/Generics/Constant.h"
#include "Strings/Generics/XOverY.h"

using namespace cocos2d;

HexusStoreMenu* HexusStoreMenu::instance;
const float HexusStoreMenu::LootBoxScale = 0.5f;

void HexusStoreMenu::registerGlobalScene()
{
	if (HexusStoreMenu::instance == nullptr)
	{
		HexusStoreMenu::instance = new HexusStoreMenu();

		HexusStoreMenu::instance->autorelease();
		HexusStoreMenu::instance->initializeListeners();
	}

	GlobalDirector::registerGlobalScene(HexusStoreMenu::instance);
}

HexusStoreMenu::HexusStoreMenu()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->lootBoxes = std::vector<std::tuple<ClickableNode*, int>>();
	this->binaryCards = std::vector<std::tuple<ClickableNode*, MenuCard*, int>>();
	this->decimalCards = std::vector<std::tuple<ClickableNode*, MenuCard*, int>>();
	this->hexCards = std::vector<std::tuple<ClickableNode*, MenuCard*, int>>();
	this->specialCards = std::vector<std::tuple<ClickableNode*, MenuCard*, int>>();
	this->limitLabels = std::map<MenuCard*, std::tuple<ConstantString*, ConstantString*, LocalizedLabel*>>();

	this->dustParticles = ParticleSystemQuad::create(ParticleResources::Dust);

	this->goldPanel = Sprite::create(HexusResources::StoreMenu_GoldPanel);
	this->goldIcon = Sprite::create(UIResources::Menus_Objects_GOLD_2);
	this->goldString = ConstantString::create();
	this->goldLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H2, Strings::Generics_Constant::create());

	this->goldLabel->setStringReplacementVariables(this->goldString);
	this->goldLabel->enableOutline(Color4B::BLACK, 3);
	this->goldLabel->setPosition(Vec2(-32.0f, 0.0f));
	this->goldLabel->setAlignment(TextHAlignment::LEFT);
	this->goldLabel->setAnchorPoint(Vec2(0.0f, 0.5f));

	this->storeBack = Sprite::create(HexusResources::StoreMenu_StoreBack);
	this->shopKeeper = Shopkeeper::create();
	this->storeFront = Sprite::create(HexusResources::StoreMenu_Store);
	this->storeNode = Node::create();
	this->lootboxesNode = Node::create();
	this->storeMenu = Sprite::create(HexusResources::StoreMenu_StoreBoard);

	LocalizedLabel* backButtonLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Back::create());
	LocalizedLabel* backButtonLabelHover = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Back::create());
	
	backButtonLabel->enableOutline(Color4B::BLACK, 2);
	backButtonLabelHover->enableOutline(Color4B::BLACK, 2);

	this->backButton = ClickableTextNode::create(
		backButtonLabel,
		backButtonLabelHover,
		UIResources::Menus_Buttons_GenericButton,
		UIResources::Menus_Buttons_GenericButtonHover
	);
	this->cardPreview = CardPreview::create();

	this->lootBoxRewardBackground = LayerColor::create(Color4B::BLACK);
	this->lootBoxRewardBackground->setOpacity(0);

	this->chosenCardsNode = Node::create();
	LocalizedLabel* lootBoxReturnLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Return::create());
	LocalizedLabel* lootBoxReturnLabelSelected = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Return::create());

	lootBoxReturnLabel->enableOutline(Color4B::BLACK, 2);
	lootBoxReturnLabelSelected->enableOutline(Color4B::BLACK, 2);

	this->lootBoxReturnButton = ClickableTextNode::create(
		lootBoxReturnLabel,
		lootBoxReturnLabelSelected,
		UIResources::Menus_Buttons_WoodButton,
		UIResources::Menus_Buttons_WoodButtonSelected
	);

	this->lootBoxReturnButton->disableInteraction(0);

	this->lootBoxButton = ClickableNode::create(HexusResources::StoreMenu_TabButton, HexusResources::StoreMenu_TabButtonSelected);
	this->binaryButton = ClickableNode::create(HexusResources::StoreMenu_TabButton, HexusResources::StoreMenu_TabButtonSelected);
	this->decimalButton = ClickableNode::create(HexusResources::StoreMenu_TabButton, HexusResources::StoreMenu_TabButtonSelected);
	this->hexButton = ClickableNode::create(HexusResources::StoreMenu_TabButton, HexusResources::StoreMenu_TabButtonSelected);
	this->specialButton = ClickableNode::create(HexusResources::StoreMenu_TabButton, HexusResources::StoreMenu_TabButtonSelected);

	const Size scrollPaneSize = Size(780.0f, 800.0f);

	this->binaryCardsScrollPane = ScrollPane::create(scrollPaneSize, UIResources::Menus_Buttons_SliderButton, UIResources::Menus_Buttons_SliderButtonSelected);
	this->decimalCardsScrollPane = ScrollPane::create(scrollPaneSize, UIResources::Menus_Buttons_SliderButton, UIResources::Menus_Buttons_SliderButtonSelected);
	this->hexCardsScrollPane = ScrollPane::create(scrollPaneSize, UIResources::Menus_Buttons_SliderButton, UIResources::Menus_Buttons_SliderButtonSelected);
	this->specialCardsScrollPane = ScrollPane::create(scrollPaneSize, UIResources::Menus_Buttons_SliderButton, UIResources::Menus_Buttons_SliderButtonSelected);

	this->backdrop = LayerColor::create(Color4B::BLACK, visibleSize.width, visibleSize.height);
	this->confirmationMenu = ConfirmationMenu::create();

	this->backdrop->setOpacity(196);

	Sprite* lootBoxIcon = Sprite::create(HexusResources::StoreMenu_IconLootBox);
	Sprite* binaryIcon = Sprite::create(HexusResources::StoreMenu_IconBin);
	Sprite* decimalIcon = Sprite::create(HexusResources::StoreMenu_IconDec);
	Sprite* hexIcon = Sprite::create(HexusResources::StoreMenu_IconHex);
	Sprite* specialIcon = Sprite::create(HexusResources::StoreMenu_IconSpecial);

	lootBoxIcon->setPosition(Vec2(48.0f, 0.0f));
	binaryIcon->setPosition(Vec2(48.0f, 0.0f));
	decimalIcon->setPosition(Vec2(48.0f, 0.0f));
	hexIcon->setPosition(Vec2(48.0f, 0.0f));
	specialIcon->setPosition(Vec2(48.0f, 0.0f));

	LocalizedLabel* binaryLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H1, Strings::Hexus_StoreLabelBinary::create());
	LocalizedLabel* decimalLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H1, Strings::Hexus_StoreLabelDecimal::create());
	LocalizedLabel* hexLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H1, Strings::Hexus_StoreLabelHex::create());
	LocalizedLabel* specialLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H1, Strings::Hexus_StoreLabelSpecial::create());

	binaryLabel->enableOutline(Color4B::BLACK, 3);
	binaryLabel->setPosition(Vec2(binaryIcon->getPositionX(), 0.0f));
	binaryLabel->setAlignment(TextHAlignment::CENTER);
	binaryLabel->setAnchorPoint(Vec2(0.5f, 0.5f));
	decimalLabel->enableOutline(Color4B::BLACK, 3);
	decimalLabel->setPosition(Vec2(decimalIcon->getPositionX(), 0.0f));
	decimalLabel->setAlignment(TextHAlignment::CENTER);
	decimalLabel->setAnchorPoint(Vec2(0.5f, 0.5f));
	hexLabel->enableOutline(Color4B::BLACK, 3);
	hexLabel->setPosition(Vec2(hexIcon->getPositionX(), 0.0f));
	hexLabel->setAlignment(TextHAlignment::CENTER);
	hexLabel->setAnchorPoint(Vec2(0.5f, 0.5f));
	specialLabel->enableOutline(Color4B::BLACK, 3);
	specialLabel->setPosition(Vec2(specialIcon->getPositionX(), 0.0f));
	specialLabel->setAlignment(TextHAlignment::CENTER);
	specialLabel->setAnchorPoint(Vec2(0.5f, 0.5f));

	binaryLabel->setTextColor(Card::binaryColor);
	decimalLabel->setTextColor(Card::decimalColor);
	hexLabel->setTextColor(Card::hexColor);
	specialLabel->setTextColor(Card::specialColor);

	this->lootBoxButton->addChild(lootBoxIcon);
	this->binaryButton->addChild(binaryIcon);
	this->decimalButton->addChild(decimalIcon);
	this->hexButton->addChild(hexIcon);
	this->specialButton->addChild(specialIcon);

	this->binaryButton->addChild(binaryLabel);
	this->decimalButton->addChild(decimalLabel);
	this->hexButton->addChild(hexLabel);
	this->specialButton->addChild(specialLabel);

	this->lootBoxes.push_back(this->constructLootBoxButton(HexusResources::StoreMenu_LootBoxes_Jungle_Animations, 64, HexusStoreMenu::getCardsTier1()));
	this->lootBoxes.push_back(this->constructLootBoxButton(HexusResources::StoreMenu_LootBoxes_Ruins_Animations, 128, HexusStoreMenu::getCardsTier2()));
	this->lootBoxes.push_back(this->constructLootBoxButton(HexusResources::StoreMenu_LootBoxes_Forest_Animations, 256, HexusStoreMenu::getCardsTier3()));
	this->lootBoxes.push_back(this->constructLootBoxButton(HexusResources::StoreMenu_LootBoxes_Caverns_Animations, 512, HexusStoreMenu::getCardsTier4()));
	this->lootBoxes.push_back(this->constructLootBoxButton(HexusResources::StoreMenu_LootBoxes_Castle_Animations, 1024, HexusStoreMenu::getCardsTier5()));
	this->lootBoxes.push_back(this->constructLootBoxButton(HexusResources::StoreMenu_LootBoxes_Ice_Animations, 2048, HexusStoreMenu::getCardsTier6()));
	this->lootBoxes.push_back(this->constructLootBoxButton(HexusResources::StoreMenu_LootBoxes_Volcano_Animations, 4096, HexusStoreMenu::getCardsTier7()));
	this->lootBoxes.push_back(this->constructLootBoxButton(HexusResources::StoreMenu_LootBoxes_Obelisk_Animations, 8192, HexusStoreMenu::getCardsTier8()));
	this->lootBoxes.push_back(this->constructLootBoxButton(HexusResources::StoreMenu_LootBoxes_Vapor_Animations, 16384, HexusStoreMenu::getCardsTier9()));

	for (auto it = CardList::getInstance()->cardListByName.begin(); it != CardList::getInstance()->cardListByName.end(); it++)
	{
		CardData* cardData = (*it).second;

		switch (cardData->cardType)
		{
			case CardData::CardType::Binary:
			{
				this->binaryCards.push_back(this->constructCard(cardData));
				break;
			}
			case CardData::CardType::Decimal:
			{
				this->decimalCards.push_back(this->constructCard(cardData));
				break;
			}
			case CardData::CardType::Hexidecimal:
			{
				this->hexCards.push_back(this->constructCard(cardData));
				break;
			}
			default:
			{
				this->specialCards.push_back(this->constructCard(cardData));
				break;
			}
		}
	}

	// Sort cards on price
	std::sort(this->binaryCards.begin(), this->binaryCards.end(), [](std::tuple<ClickableNode*, MenuCard*, int> a, std::tuple<ClickableNode*, MenuCard*, int> b) -> bool
	{
		return std::get<2>(a) < std::get<2>(b);
	});

	std::sort(this->decimalCards.begin(), this->decimalCards.end(), [](std::tuple<ClickableNode*, MenuCard*, int> a, std::tuple<ClickableNode*, MenuCard*, int> b) -> bool
	{
		return std::get<2>(a) < std::get<2>(b);
	});

	std::sort(this->hexCards.begin(), this->hexCards.end(), [](std::tuple<ClickableNode*, MenuCard*, int> a, std::tuple<ClickableNode*, MenuCard*, int> b) -> bool
	{
		return std::get<2>(a) < std::get<2>(b);
	});

	std::sort(this->specialCards.begin(), this->specialCards.end(), [](std::tuple<ClickableNode*, MenuCard*, int> a, std::tuple<ClickableNode*, MenuCard*, int> b) -> bool
	{
		return std::get<2>(a) < std::get<2>(b);
	});

	this->storeBack->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->storeFront->setAnchorPoint(Vec2(0.0f, 0.5f));

	this->addChild(this->dustParticles);
	this->addChild(this->storeBack);
	this->addChild(this->shopKeeper);
	this->addChild(this->storeFront);
	this->addChild(storeNode);
	this->storeNode->addChild(this->storeMenu);
	this->storeNode->addChild(this->goldPanel);
	this->storeNode->addChild(this->goldIcon);
	this->storeNode->addChild(this->goldLabel);
	this->storeNode->addChild(this->lootboxesNode);
	this->storeNode->addChild(this->binaryCardsScrollPane);
	this->storeNode->addChild(this->decimalCardsScrollPane);
	this->storeNode->addChild(this->hexCardsScrollPane);
	this->storeNode->addChild(this->specialCardsScrollPane);
	this->storeNode->addChild(this->lootBoxButton);
	this->storeNode->addChild(this->binaryButton);
	this->storeNode->addChild(this->hexButton);
	this->storeNode->addChild(this->decimalButton);
	this->storeNode->addChild(this->specialButton);
	this->addChild(this->backButton);
	this->addChild(this->cardPreview);
	this->addChild(this->lootBoxRewardBackground);
	this->addChild(this->chosenCardsNode);
	this->addChild(this->lootBoxReturnButton);
	this->addChild(this->backdrop);
	this->addChild(this->confirmationMenu);

	for (auto it = this->lootBoxes.begin(); it != this->lootBoxes.end(); it++)
	{
		this->lootboxesNode->addChild(std::get<0>(*it));
	}

	for (auto it = this->binaryCards.begin(); it != this->binaryCards.end(); it++)
	{
		this->binaryCardsScrollPane->addChild(std::get<0>(*it));
	}

	for (auto it = this->decimalCards.begin(); it != this->decimalCards.end(); it++)
	{
		this->decimalCardsScrollPane->addChild(std::get<0>(*it));
	}

	for (auto it = this->hexCards.begin(); it != this->hexCards.end(); it++)
	{
		this->hexCardsScrollPane->addChild(std::get<0>(*it));
	}

	for (auto it = this->specialCards.begin(); it != this->specialCards.end(); it++)
	{
		this->specialCardsScrollPane->addChild(std::get<0>(*it));
	}

	this->onBinaryTabClick();
}

HexusStoreMenu::~HexusStoreMenu()
{
}

void HexusStoreMenu::onEnter()
{
	super::onEnter();

	const float delay = 0.25f;
	const float duration = 0.35f;

	this->backdrop->setVisible(false);

	// Disabled for now
	this->lootBoxButton->setVisible(false);

	GameUtils::fadeInObject(this->backButton, delay, duration);

	GameUtils::accelerateParticles(this->dustParticles, 5.0f);

	this->updateGoldText();
}

void HexusStoreMenu::initializeListeners()
{
	super::initializeListeners();

	HexusStoreMenu::instance->addGlobalEventListener(EventListenerCustom::create(NavigationEvents::EventNavigateHexusShop, [](EventCustom* args)
	{
		GlobalDirector::loadScene(HexusStoreMenu::instance);
	}));

	EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();

	keyboardListener->onKeyPressed = CC_CALLBACK_2(HexusStoreMenu::onKeyPressed, this);

	this->addEventListener(keyboardListener);

	this->lootBoxButton->setMouseClickCallback(CC_CALLBACK_0(HexusStoreMenu::onLootBoxTabClick, this));
	this->binaryButton->setMouseClickCallback(CC_CALLBACK_0(HexusStoreMenu::onBinaryTabClick, this));
	this->decimalButton->setMouseClickCallback(CC_CALLBACK_0(HexusStoreMenu::onDecimalTabClick, this));
	this->hexButton->setMouseClickCallback(CC_CALLBACK_0(HexusStoreMenu::onHexTabClick, this));
	this->specialButton->setMouseClickCallback(CC_CALLBACK_0(HexusStoreMenu::onSpecialTabClick, this));

	this->backButton->setMouseClickCallback(CC_CALLBACK_0(HexusStoreMenu::onBackClick, this));
}

void HexusStoreMenu::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	const float storeOffsetY = -128.0f;
	const Vec2 storeMenuOffset = Vec2(192.0f, 0.0f);
	const Vec2 storeContentOffset = Vec2(64.0f, -48.0f);
	const Vec2 goldPanelOffset = Vec2(476.0f, 464.0f);

	this->dustParticles->setPosition(Vec2(visibleSize.width, visibleSize.height / 2));
	this->storeBack->setPosition(Vec2(0.0f, visibleSize.height / 2.0f + storeOffsetY + 144.0f));
	this->shopKeeper->setPosition(Vec2(visibleSize.width / 2.0f - 680.0f, visibleSize.height / 2.0f + storeOffsetY));
	this->storeFront->setPosition(Vec2(0.0f, visibleSize.height / 2.0f + storeOffsetY - 176.0f));
	this->storeMenu->setPosition(Vec2(visibleSize.width / 2.0f + storeMenuOffset.x, visibleSize.height / 2.0f + storeMenuOffset.y - 48.0f));

	this->goldPanel->setPosition(Vec2(visibleSize.width / 2.0f + storeMenuOffset.x + goldPanelOffset.x, visibleSize.height / 2.0f + storeMenuOffset.y + goldPanelOffset.y));
	this->goldIcon->setPosition(Vec2(visibleSize.width / 2.0f + storeMenuOffset.x + goldPanelOffset.x - 80.0f, visibleSize.height / 2.0f + storeMenuOffset.y + goldPanelOffset.y));
	this->goldLabel->setPosition(Vec2(visibleSize.width / 2.0f + storeMenuOffset.x + goldPanelOffset.x - 8.0f, visibleSize.height / 2.0f + storeMenuOffset.y + goldPanelOffset.y));

	this->backButton->setPosition(Vec2(visibleSize.width / 2.0f - 756.0f, visibleSize.height - 64.0f));
	this->cardPreview->setPosition(Vec2(visibleSize.width / 2.0f + storeMenuOffset.x - 480.0f, visibleSize.height / 2.0f + 160.0f));

	this->lootboxesNode->setPosition(Vec2(visibleSize.width / 2.0f + storeMenuOffset.x + storeContentOffset.x, visibleSize.height / 2.0f + storeMenuOffset.y + storeContentOffset.y));
	this->binaryCardsScrollPane->setPosition(Vec2(visibleSize.width / 2.0f + storeMenuOffset.x + storeContentOffset.x, visibleSize.height / 2.0f + storeMenuOffset.y + storeContentOffset.y));
	this->decimalCardsScrollPane->setPosition(Vec2(visibleSize.width / 2.0f + storeMenuOffset.x + storeContentOffset.x, visibleSize.height / 2.0f + storeMenuOffset.y + storeContentOffset.y));
	this->hexCardsScrollPane->setPosition(Vec2(visibleSize.width / 2.0f + storeMenuOffset.x + storeContentOffset.x, visibleSize.height / 2.0f + storeMenuOffset.y + storeContentOffset.y));
	this->specialCardsScrollPane->setPosition(Vec2(visibleSize.width / 2.0f + storeMenuOffset.x + storeContentOffset.x, visibleSize.height / 2.0f + storeMenuOffset.y + storeContentOffset.y));
	this->binaryButton->setPosition(Vec2(visibleSize.width / 2.0f + storeMenuOffset.x + 640.0f, visibleSize.height / 2.0f + 256.0f - 144.0f * 0));
	this->decimalButton->setPosition(Vec2(visibleSize.width / 2.0f + storeMenuOffset.x + 640.0f, visibleSize.height / 2.0f + 256.0f - 144.0f * 1));
	this->hexButton->setPosition(Vec2(visibleSize.width / 2.0f + storeMenuOffset.x + 640.0f, visibleSize.height / 2.0f + 256.0f - 144.0f * 2));
	this->specialButton->setPosition(Vec2(visibleSize.width / 2.0f + storeMenuOffset.x + 640.0f, visibleSize.height / 2.0f + 256.0f - 144.0f * 3));
	this->lootBoxButton->setPosition(Vec2(visibleSize.width / 2.0f + storeMenuOffset.x + 640.0f, visibleSize.height / 2.0f + 256.0f - 144.0f * 4));
	this->lootBoxReturnButton->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));

	const Size chestGridSize = Size(288.0f, 240.0f);
	int index = 0;

	for (auto it = this->lootBoxes.begin(); it != this->lootBoxes.end(); it++)
	{
		int x = index % 3 - 1;
		int y = index / 3 - 1;

		std::get<0>(*it)->setPosition(Vec2(x * chestGridSize.width, - 32.0f - y * chestGridSize.height));

		index++;
	}

	const Size cardGridSize = Size(256.0f, 384.0f);

	index = 0;

	for (auto it = this->binaryCards.begin(); it != this->binaryCards.end(); it++)
	{
		int x = index % 3;
		int y = index / 3;

		std::get<0>(*it)->setPosition(Vec2((x - 1) * cardGridSize.width, y * -cardGridSize.height - 160.0f));

		index++;
	}

	index = 0;

	for (auto it = this->decimalCards.begin(); it != this->decimalCards.end(); it++)
	{
		int x = index % 3;
		int y = index / 3;

		std::get<0>((*it))->setPosition(Vec2((x - 1) * cardGridSize.width, y * -cardGridSize.height - 160.0f));

		index++;
	}

	index = 0;

	for (auto it = this->hexCards.begin(); it != this->hexCards.end(); it++)
	{
		int x = index % 3;
		int y = index / 3;

		std::get<0>(*it)->setPosition(Vec2((x - 1) * cardGridSize.width, y * -cardGridSize.height - 160.0f));

		index++;
	}

	index = 0;

	for (auto it = this->specialCards.begin(); it != this->specialCards.end(); it++)
	{
		int x = index % 3;
		int y = index / 3;

		std::get<0>(*it)->setPosition(Vec2((x - 1) * cardGridSize.width, y * -cardGridSize.height - 160.0f));

		index++;
	}
}

std::tuple<ClickableNode*, int> HexusStoreMenu::constructLootBoxButton(std::string lootBoxAnimations, int price, std::map<CardData*, float> cardChoices)
{
	SmartAnimationNode* animationNode = SmartAnimationNode::create(lootBoxAnimations);

	animationNode->playAnimation();

	ClickableNode* frame = ClickableNode::create(HexusResources::StoreMenu_StoreOption, HexusResources::StoreMenu_StoreOptionSelected);
	ConstantString* priceString = ConstantString::create(std::to_string(price));
	LocalizedLabel* priceLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Generics_Constant::create());
	Sprite* goldIcon = Sprite::create(UIResources::Menus_Objects_GOLD_1);

	priceLabel->setStringReplacementVariables(priceString);

	animationNode->setScale(HexusStoreMenu::LootBoxScale);
	animationNode->setPosition(Vec2(0.0f, 16.0f));

	frame->setMouseClickCallback(CC_CALLBACK_0(HexusStoreMenu::onLootBoxClick, this, price, cardChoices, animationNode));
	goldIcon->setScale(0.75f);
	goldIcon->setPosition(Vec2(-32.0f, -72.0f));
	priceLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
	priceLabel->setPosition(Vec2(16.0f, -72.0f));
	priceLabel->enableOutline(Color4B::BLACK, 4);

	frame->addChild(animationNode);
	frame->addChild(goldIcon);
	frame->addChild(priceLabel);

	return std::tuple<ClickableNode*, int>(frame, price);
}

std::tuple<ClickableNode*, MenuCard*, int> HexusStoreMenu::constructCard(CardData* cardData)
{
	ClickableNode* cardContainer =  ClickableNode::create(HexusResources::StoreMenu_CardPanel, HexusResources::StoreMenu_CardPanelSelected);
	MenuCard* menuCard = MenuCard::create(Card::CardStyle::Earth, cardData);
	int price = 0;

	switch (cardData->cardType)
	{
		case CardData::CardType::Special_FLIP1:
		{
			price = 25;
			break;
		}
		case CardData::CardType::Special_PEEK:
		{
			price = 25;
			break;
		}
		case CardData::CardType::Special_FLIP2:
		{
			price = 48;
			break;
		}
		case CardData::CardType::Special_XOR:
		{
			price = 64;
			break;
		}
		case CardData::CardType::Special_AND:
		{
			price = 64;
			break;
		}
		case CardData::CardType::Special_OR:
		{
			price = 64;
			break;
		}
		case CardData::CardType::Special_ABSORB:
		{
			price = 72;
			break;
		}
		case CardData::CardType::Special_MOV:
		{
			price = 96;
			break;
		}
		case CardData::CardType::Special_ROL:
		{
			price = 128;
			break;
		}
		case CardData::CardType::Special_SHR:
		{
			price = 160;
			break;
		}
		case CardData::CardType::Special_SHL:
		{
			price = 160;
			break;
		}
		case CardData::CardType::Special_RETURN_TO_HAND:
		{
			price = 224;
			break;
		}
		case CardData::CardType::Special_ADD:
		{
			price = 335;
			break;
		}
		case CardData::CardType::Special_BONUS_MOVES:
		{
			price = 480;
			break;
		}
		case CardData::CardType::Special_ROR:
		{
			price = 768;
			break;
		}
		case CardData::CardType::Special_FLIP3:
		{
			price = 800;
			break;
		}
		case CardData::CardType::Special_GREED:
		{
			price = 1024;
			break;
		}
		case CardData::CardType::Special_NOT:
		{
			price = 1280;
			break;
		}
		case CardData::CardType::Special_SUB:
		{
			price = 1280;
			break;
		}
		case CardData::CardType::Special_KILL:
		{
			price = 1480;
			break;
		}
		case CardData::CardType::Special_FLIP4:
		{
			price = 1720;
			break;
		}
		case CardData::CardType::Special_SUDDEN_DEATH:
		{
			price = 2048;
			break;
		}
		case CardData::CardType::Special_STEAL:
		{
			price = 3072;
			break;
		}
		case CardData::CardType::Binary:
		{
			// Formula: Lagrange interpolation over 4 price pairs (0, 16), (2, 48), (5, 320), (15, 4096) (Note: 3 pairs produce negative values)
			float atk = float(cardData->attack);
			const float alpha = 0.475897f;
			const float beta = 11.6021f;
			const float gamma = -9.10769f;
			const float delta = 16.0f;

			int calculatedPrice = int((atk * atk* atk) * alpha + (atk * atk * beta) + (atk * gamma) + delta);

			price = MathUtils::clamp(calculatedPrice, 16, 4096);

			break;
		}
		case CardData::CardType::Decimal:
		{
			// Formula: Lagrange interpolation over 4 price pairs (0, 16), (3, 96), (5, 288), (15, 4096) (Note: 3 pairs produce negative values)
			float atk = float(cardData->attack);
			const float alpha = 0.657778f;
			const float beta = 8.604444f;
			const float gamma = -5.06667f;
			const float delta = 16.0f;

			int calculatedPrice = int((atk * atk* atk) * alpha + (atk * atk * beta) + (atk * gamma) + delta);

			price = MathUtils::clamp(calculatedPrice, 16, 4096);

			break;
		}
		case CardData::CardType::Hexidecimal:
		{
			// Formula: Lagrange interpolation over 4 price pairs (0, 16), (4, 192), (6, 480), (15, 4096) (Note: 3 pairs produce negative values)
			float atk = float(cardData->attack);
			const float alpha = 0.451178f;
			const float beta = 12.1549f;
			const float gamma = -11.8384f;
			const float delta = 16.0f;

			int calculatedPrice = int((atk * atk* atk) * alpha + (atk * atk * beta) + (atk * gamma) + delta);

			price = MathUtils::clamp(calculatedPrice, 16, 4096);

			break;
		}
		default:
		{
			// Error value
			price = 666;
			break;
		}
	}

	ConstantString* countString = ConstantString::create();
	ConstantString* limitString = ConstantString::create();
	LocalizedLabel* cardLimitLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H1, Strings::Generics_XOverY::create());

	cardLimitLabel->setStringReplacementVariables({ countString, limitString });
	cardLimitLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
	cardLimitLabel->enableOutline(Color4B::BLACK, 4);
	cardLimitLabel->setPosition(Vec2(-96.0f, 128.0f));

	this->updateCardLimitText(cardLimitLabel, countString, limitString, cardData);

	ConstantString* priceString = ConstantString::create(std::to_string(price));
	LocalizedLabel* priceLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H3, Strings::Generics_Constant::create());
	Sprite* goldIcon = Sprite::create(UIResources::Menus_Objects_GOLD_1);

	priceLabel->setStringReplacementVariables(priceString);

	goldIcon->setScale(0.75f);
	goldIcon->setPosition(Vec2(-32.0f, -144.0f));
	priceLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
	priceLabel->setPosition(Vec2(16.0f, -144.0f));
	priceLabel->enableOutline(Color4B::BLACK, 4);

	cardContainer->addChild(menuCard);

	menuCard->reveal();
	menuCard->disableInteraction();
	menuCard->setPosition(Vec2(0.0f, 16.0f));
	menuCard->setScale(0.8f);

	cardContainer->setMouseClickCallback(CC_CALLBACK_0(HexusStoreMenu::onCardClick, this, cardData, price, cardLimitLabel, countString, limitString));
	cardContainer->setMouseOverCallback([=](MouseEvents::MouseEventArgs*)
	{
		this->cardPreview->previewCard(menuCard);
	});

	cardContainer->addChild(goldIcon);
	cardContainer->addChild(priceLabel);
	menuCard->addDisplayItem(cardLimitLabel);

	this->limitLabels[menuCard] = std::make_tuple(countString, limitString, cardLimitLabel);

	return std::tuple<ClickableNode*, MenuCard*, int>(cardContainer, menuCard, price);
}

void HexusStoreMenu::updateAllCardLimits()
{
	auto iterateAndUpdateCardLimits = [=](std::vector<std::tuple<ClickableNode*, MenuCard*, int>> cards)
	{
		for (auto it = this->binaryCards.begin(); it != this->binaryCards.end(); it++)
		{
			MenuCard* card = std::get<1>(*it);
			ConstantString* countString = std::get<0>(this->limitLabels[card]);
			ConstantString* limitString = std::get<1>(this->limitLabels[card]);
			LocalizedLabel* label = std::get<2>(this->limitLabels[card]);

			this->updateCardLimitText(label, countString, limitString, card->cardData);
		}
	};

	iterateAndUpdateCardLimits(this->binaryCards);
	iterateAndUpdateCardLimits(this->decimalCards);
	iterateAndUpdateCardLimits(this->hexCards);
}

void HexusStoreMenu::updateCardLimitText(LocalizedLabel* label, ConstantString* countString, ConstantString* limitString, CardData* cardData)
{
	int ownedCount = CardStorage::getOwnedCardCount(cardData);

	countString->setString(std::to_string(ownedCount));
	limitString->setString(std::to_string(3));

	if (ownedCount >= 3)
	{
		label->setTextColor(Color4B::GREEN);
	}
	else
	{
		label->setTextColor(Color4B::WHITE);
	}
}

void HexusStoreMenu::onCardClick(CardData* cardData, int price, LocalizedLabel* cardLimitLabel, ConstantString* countString, ConstantString* limitString)
{
	if (CardStorage::getGold() < price || CardStorage::getOwnedCardCount(cardData) >= 3)
	{
		SoundManager::playSoundResource(SoundResources::AFX_INTERFACE_ERROR_1_DFMG);
		return;
	}

	LocalizedString* message = Strings::Hexus_PurchaseConfirmation::create();

	message->setStringReplacementVariables(ConstantString::create(std::to_string(price)));

	this->confirmationMenu->showMessage(message, [=]()
	{
		int gold = CardStorage::getGold();

		gold -= price;

		SoundManager::playSoundResource(SoundResources::Item_Purchase__1_);

		CardStorage::saveGold(gold);
		this->updateGoldText();

		CardStorage::addStorageCard(cardData);

		this->updateCardLimitText(cardLimitLabel, countString, limitString, cardData);
		GameUtils::focus(this);
		this->backdrop->setVisible(false);
	}, [=]()
	{
		GameUtils::focus(this);
		this->backdrop->setVisible(false);
	});

	this->backdrop->setVisible(true);
	GameUtils::focus(this->confirmationMenu);
}

void HexusStoreMenu::onLootBoxClick(int price, std::map<CardData*, float> cardChoices, SmartAnimationNode* animationNode)
{
	int gold = CardStorage::getGold();

	if (gold < price)
	{
		SoundManager::playSoundResource(SoundResources::AFX_INTERFACE_ERROR_1_DFMG);
		return;
	}

	gold -= price;
	SoundManager::playSoundResource(SoundResources::Item_Purchase__1_);

	CardStorage::saveGold(gold);
	this->updateGoldText();

	std::vector<Card*> chosenCards = std::vector<Card*>
	{
		Card::create(Card::CardStyle::Earth, HexusStoreMenu::chooseRandomCard(cardChoices)),
		Card::create(Card::CardStyle::Earth, HexusStoreMenu::chooseRandomCard(cardChoices)),
		Card::create(Card::CardStyle::Earth, HexusStoreMenu::chooseRandomCard(cardChoices)),
	};

	Size visibleSize = Director::getInstance()->getVisibleSize();

	int index = 0;

	for (auto it = chosenCards.begin(); it != chosenCards.end(); it++)
	{
		float radians = (index * 360.0f / float(chosenCards.size()) + 90.0f) * float(M_PI) / 180.0f;

		(*it)->setScale(1.0f);
		(*it)->reveal();
		(*it)->disableInteraction();
		(*it)->setOpacity(0);
		(*it)->setPosition(Vec2(visibleSize.width / 2.0f + std::cos(radians) * 320.0f, visibleSize.height / 2.0f + std::sin(radians) * 320.0f));

		this->chosenCardsNode->addChild((*it));
		index++;

		// Save the card
		CardStorage::addStorageCard((*it)->cardData);
	}

	this->updateAllCardLimits();

	animationNode->runAction(Sequence::create(
		CallFunc::create([=]()
		{
			this->lootBoxReturnButton->setMouseClickCallback(nullptr);

			for (auto it = this->lootBoxes.begin(); it != this->lootBoxes.end(); it++)
			{
				std::get<0>(*it)->disableInteraction();
			}

			this->backButton->disableInteraction();
			this->lootBoxButton->disableInteraction();
			this->binaryButton->disableInteraction();
			this->decimalButton->disableInteraction();
			this->hexButton->disableInteraction();
			this->specialButton->disableInteraction();

			animationNode->playAnimation("Open");
		}),
		DelayTime::create(1.5f),
		CallFunc::create([=]()
		{
			this->lootBoxRewardBackground->runAction(FadeTo::create(0.5f, 196));

			for (auto it = chosenCards.begin(); it != chosenCards.end(); it++)
			{
				(*it)->runAction(FadeIn::create(0.5f));
			}

			this->lootBoxReturnButton->runAction(Sequence::create(
				FadeIn::create(0.5f),
				CallFunc::create([=]()
				{
					this->lootBoxReturnButton->setMouseClickCallback(CC_CALLBACK_0(HexusStoreMenu::onLootBoxReturnButtonClick, this, price, chosenCards));
					this->lootBoxReturnButton->enableInteraction();
				}),
				nullptr
			));

			animationNode->playAnimation("Idle");
		}),
		nullptr
	));
}

void HexusStoreMenu::onLootBoxReturnButtonClick(int price, std::vector<Card*> chosenCards)
{
	this->runAction(Sequence::create(
		CallFunc::create([=]()
		{
			this->lootBoxRewardBackground->runAction(FadeTo::create(0.25f, 0));

			this->lootBoxReturnButton->disableInteraction(255);
			this->lootBoxReturnButton->runAction(FadeOut::create(0.25f));

			for (auto it = chosenCards.begin(); it != chosenCards.end(); it++)
			{
				Card* card = *it;

				card->runAction(Sequence::create(
					FadeOut::create(0.25f),
					DelayTime::create(0.25f),
					CallFunc::create([=]()
					{
						this->chosenCardsNode->removeChild(card);
					}),
					nullptr
				));
			}
		}),
		DelayTime::create(0.25f),
		CallFunc::create([=]()
		{
			for (auto it = this->lootBoxes.begin(); it != this->lootBoxes.end(); it++)
			{
				std::get<0>(*it)->enableInteraction();
			}

			this->backButton->enableInteraction();
			this->lootBoxButton->enableInteraction();
			this->binaryButton->enableInteraction();
			this->decimalButton->enableInteraction();
			this->hexButton->enableInteraction();
			this->specialButton->enableInteraction();
		}),
		nullptr
	));
}

void HexusStoreMenu::onBackClick()
{
	NavigationEvents::navigateBack();
}

void HexusStoreMenu::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (!GameUtils::isVisible(this))
	{
		return;
	}

	switch (keyCode)
	{
		case EventKeyboard::KeyCode::KEY_ESCAPE:
		{
			event->stopPropagation();
			NavigationEvents::navigateBack();
			break;
		}
		default:
		{
			break;
		}
	}
}

void HexusStoreMenu::onLootBoxTabClick()
{
	this->hideMenus();
	this->lootBoxButton->setLocalZOrder(1);
	this->lootboxesNode->setVisible(true);
}

void HexusStoreMenu::onBinaryTabClick()
{
	this->hideMenus();
	this->binaryButton->setLocalZOrder(1);
	this->binaryCardsScrollPane->setVisible(true);
}

void HexusStoreMenu::onDecimalTabClick()
{
	this->hideMenus();
	this->decimalButton->setLocalZOrder(1);
	this->decimalCardsScrollPane->setVisible(true);
}

void HexusStoreMenu::onHexTabClick()
{
	this->hideMenus();
	this->hexButton->setLocalZOrder(1);
	this->hexCardsScrollPane->setVisible(true);
}

void HexusStoreMenu::onSpecialTabClick()
{
	this->hideMenus();
	this->specialButton->setLocalZOrder(1);
	this->specialCardsScrollPane->setVisible(true);
}

void HexusStoreMenu::hideMenus()
{
	this->lootBoxButton->setLocalZOrder(-1);
	this->storeMenu->setLocalZOrder(0);
	this->binaryButton->setLocalZOrder(-1);
	this->decimalButton->setLocalZOrder(-1);
	this->hexButton->setLocalZOrder(-1);
	this->specialButton->setLocalZOrder(-1);

	this->lootboxesNode->setVisible(false);
	this->binaryCardsScrollPane->setVisible(false);
	this->decimalCardsScrollPane->setVisible(false);
	this->hexCardsScrollPane->setVisible(false);
	this->specialCardsScrollPane->setVisible(false);
}

void HexusStoreMenu::updateGoldText()
{
	this->goldString->setString(std::to_string(CardStorage::getGold()));
}

CardData* HexusStoreMenu::chooseRandomCard(std::map<CardData*, float> cardChoices)
{
	float totalChance = 0.0f;

	for (auto it = cardChoices.begin(); it != cardChoices.end(); it++)
	{
		totalChance += (*it).second;
	}

	float selection = RandomHelper::random_real(0.0f, totalChance);
	float sum = 0.0f;

	for (auto it = cardChoices.begin(); it != cardChoices.end(); it++)
	{
		sum += (*it).second;

		if (selection <= sum)
		{
			return (*it).first;
		}
	}

	// Just some non-null default (should not be possible)
	return CardList::getInstance()->cardListByName.at(CardKeys::Binary0);
}

std::map<CardData*, float> HexusStoreMenu::getCardsTier1()
{
	return std::map<CardData*, float>
	{
		{ CardList::getInstance()->cardListByName.at(CardKeys::Decimal0), 0.75f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Decimal1), 1.0f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Decimal2), 1.0f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Hex0), 0.75f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Hex1), 1.0f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Hex2), 1.0f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Binary0), 0.75f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Binary1), 1.0f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Binary2), 1.0f },
	};
}

std::map<CardData*, float> HexusStoreMenu::getCardsTier2()
{
	return std::map<CardData*, float>
	{
		{ CardList::getInstance()->cardListByName.at(CardKeys::Decimal2), 0.75f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Decimal3), 1.0f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Decimal4), 1.0f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Hex2), 0.75f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Hex3), 1.0f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Hex4), 1.0f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Binary2), 0.75f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Binary3), 1.0f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Binary4), 1.0f },
	};
}

std::map<CardData*, float> HexusStoreMenu::getCardsTier3()
{
	return std::map<CardData*, float>
	{
		{ CardList::getInstance()->cardListByName.at(CardKeys::Decimal4), 0.75f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Decimal5), 1.0f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Decimal6), 1.0f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Hex4), 0.75f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Hex5), 1.0f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Hex6), 1.0f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Binary4), 0.75f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Binary5), 1.0f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Binary6), 1.0f },
	};
}

std::map<CardData*, float> HexusStoreMenu::getCardsTier4()
{
	return std::map<CardData*, float>
	{
		{ CardList::getInstance()->cardListByName.at(CardKeys::Decimal5), 0.75f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Decimal6), 1.0f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Decimal7), 1.0f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Hex5), 0.75f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Hex6), 1.0f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Hex7), 1.0f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Binary5), 0.75f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Binary6), 1.0f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Binary7), 1.0f },
	};
}

std::map<CardData*, float> HexusStoreMenu::getCardsTier5()
{
	return std::map<CardData*, float>
	{
		{ CardList::getInstance()->cardListByName.at(CardKeys::Decimal7), 0.75f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Decimal8), 1.0f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Decimal9), 1.0f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Hex7), 0.75f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Hex8), 1.0f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Hex9), 1.0f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Binary7), 0.75f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Binary8), 1.0f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Binary9), 1.0f },
	};
}

std::map<CardData*, float> HexusStoreMenu::getCardsTier6()
{
	return std::map<CardData*, float>
	{
		{ CardList::getInstance()->cardListByName.at(CardKeys::Decimal9), 0.75f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Decimal10), 1.0f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Decimal11), 1.0f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Hex9), 0.75f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Hex10), 1.0f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Hex11), 1.0f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Binary9), 0.75f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Binary10), 1.0f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Binary11), 1.0f },
	};
}

std::map<CardData*, float> HexusStoreMenu::getCardsTier7()
{
	return std::map<CardData*, float>
	{
		{ CardList::getInstance()->cardListByName.at(CardKeys::Decimal10), 0.75f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Decimal11), 1.0f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Decimal12), 1.0f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Hex10), 0.75f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Hex11), 1.0f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Hex12), 1.0f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Binary10), 0.75f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Binary11), 1.0f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Binary12), 1.0f },
	};
}

std::map<CardData*, float> HexusStoreMenu::getCardsTier8()
{
	return std::map<CardData*, float>
	{
		{ CardList::getInstance()->cardListByName.at(CardKeys::Decimal12), 0.75f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Decimal13), 1.0f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Decimal14), 1.0f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Hex12), 0.75f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Hex13), 1.0f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Hex14), 1.0f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Binary12), 0.75f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Binary13), 1.0f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Binary14), 1.0f },
	};
}

std::map<CardData*, float> HexusStoreMenu::getCardsTier9()
{
	return std::map<CardData*, float>
	{
		{ CardList::getInstance()->cardListByName.at(CardKeys::Decimal13), 0.75f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Decimal14), 1.0f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Decimal15), 1.0f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Hex13), 0.75f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Hex14), 1.0f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Hex15), 1.0f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Binary13), 0.75f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Binary14), 1.0f },
		{ CardList::getInstance()->cardListByName.at(CardKeys::Binary15), 1.0f },
	};
}
