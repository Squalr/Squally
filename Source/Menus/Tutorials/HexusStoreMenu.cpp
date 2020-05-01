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
#include "Engine/Events/NavigationEvents.h"
#include "Engine/GlobalDirector.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Particles/SmartParticles.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/Special/Shopkeeper.h"
#include "Scenes/Hexus/Menus/MenuCard.h"
#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"

#include "Resources/ParticleResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

HexusStoreMenu* HexusStoreMenu::instance;

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
	this->binaryCards = std::vector<std::tuple<ClickableNode*, MenuCard*, int>>();
	this->decimalCards = std::vector<std::tuple<ClickableNode*, MenuCard*, int>>();
	this->hexCards = std::vector<std::tuple<ClickableNode*, MenuCard*, int>>();
	this->specialCards = std::vector<std::tuple<ClickableNode*, MenuCard*, int>>();
	this->limitLabels = std::map<MenuCard*, std::tuple<ConstantString*, ConstantString*, LocalizedLabel*>>();

	this->dustParticles = SmartParticles::create(ParticleResources::Dust);

	this->goldPanel = Sprite::create(UIResources::Menus_TutorialsMenu_Store_GoldPanel);
	this->goldIcon = Sprite::create(UIResources::Menus_Icons_Currency_GOLD_2);
	this->goldString = ConstantString::create();
	this->goldLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H2, Strings::Common_Constant::create());

	this->goldLabel->setStringReplacementVariables(this->goldString);
	this->goldLabel->enableOutline(Color4B::BLACK, 3);
	this->goldLabel->setPosition(Vec2(-32.0f, 0.0f));
	this->goldLabel->setAlignment(TextHAlignment::LEFT);
	this->goldLabel->setAnchorPoint(Vec2(0.0f, 0.5f));

	this->storeBack = Sprite::create(UIResources::Menus_TutorialsMenu_Store_StoreBack);
	this->shopKeeper = Shopkeeper::deserialize(ValueMap());
	this->storeFront = Sprite::create(UIResources::Menus_TutorialsMenu_Store_Store);
	this->storeNode = Node::create();
	this->storeMenu = Sprite::create(UIResources::Menus_TutorialsMenu_Store_StoreBoard);

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

	this->chosenCardsNode = Node::create();

	this->binaryButton = ClickableNode::create(UIResources::Menus_TutorialsMenu_Store_TabButton, UIResources::Menus_TutorialsMenu_Store_TabButtonSelected);
	this->decimalButton = ClickableNode::create(UIResources::Menus_TutorialsMenu_Store_TabButton, UIResources::Menus_TutorialsMenu_Store_TabButtonSelected);
	this->hexButton = ClickableNode::create(UIResources::Menus_TutorialsMenu_Store_TabButton, UIResources::Menus_TutorialsMenu_Store_TabButtonSelected);
	this->specialButton = ClickableNode::create(UIResources::Menus_TutorialsMenu_Store_TabButton, UIResources::Menus_TutorialsMenu_Store_TabButtonSelected);

	const Size scrollPaneSize = Size(840.0f, 720.0f);

	this->binaryCardsScrollPane = ScrollPane::create(scrollPaneSize, UIResources::Menus_Buttons_SliderButton, UIResources::Menus_Buttons_SliderButtonSelected);
	this->decimalCardsScrollPane = ScrollPane::create(scrollPaneSize, UIResources::Menus_Buttons_SliderButton, UIResources::Menus_Buttons_SliderButtonSelected);
	this->hexCardsScrollPane = ScrollPane::create(scrollPaneSize, UIResources::Menus_Buttons_SliderButton, UIResources::Menus_Buttons_SliderButtonSelected);
	this->specialCardsScrollPane = ScrollPane::create(scrollPaneSize, UIResources::Menus_Buttons_SliderButton, UIResources::Menus_Buttons_SliderButtonSelected);

	Sprite* binaryIcon = Sprite::create(UIResources::Menus_TutorialsMenu_Store_IconBin);
	Sprite* decimalIcon = Sprite::create(UIResources::Menus_TutorialsMenu_Store_IconDec);
	Sprite* hexIcon = Sprite::create(UIResources::Menus_TutorialsMenu_Store_IconHex);
	Sprite* specialIcon = Sprite::create(UIResources::Menus_TutorialsMenu_Store_IconSpecial);

	binaryIcon->setPosition(Vec2(-32.0f, 0.0f));
	decimalIcon->setPosition(Vec2(-32.0f, 0.0f));
	hexIcon->setPosition(Vec2(-32.0f, 0.0f));
	specialIcon->setPosition(Vec2(-32.0f, 0.0f));

	LocalizedLabel* binaryLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H1, Strings::Hexus_StoreLabelBinary::create());
	LocalizedLabel* decimalLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H1, Strings::Hexus_StoreLabelDecimal::create());
	LocalizedLabel* hexLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H1, Strings::Hexus_StoreLabelHex::create());
	LocalizedLabel* specialLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H1, Strings::Hexus_StoreLabelSpecial::create());

	binaryLabel->enableOutline(Color4B::BLACK, 3);
	binaryLabel->setPosition(Vec2(-32.0f, 0.0f));
	binaryLabel->setAlignment(TextHAlignment::CENTER);
	binaryLabel->setAnchorPoint(Vec2(0.5f, 0.5f));
	decimalLabel->enableOutline(Color4B::BLACK, 3);
	decimalLabel->setPosition(Vec2(-32.0f, 0.0f));
	decimalLabel->setAlignment(TextHAlignment::CENTER);
	decimalLabel->setAnchorPoint(Vec2(0.5f, 0.5f));
	hexLabel->enableOutline(Color4B::BLACK, 3);
	hexLabel->setPosition(Vec2(-32.0f, 0.0f));
	hexLabel->setAlignment(TextHAlignment::CENTER);
	hexLabel->setAnchorPoint(Vec2(0.5f, 0.5f));
	specialLabel->enableOutline(Color4B::BLACK, 3);
	specialLabel->setPosition(Vec2(-32.0f, 0.0f));
	specialLabel->setAlignment(TextHAlignment::CENTER);
	specialLabel->setAnchorPoint(Vec2(0.5f, 0.5f));

	binaryLabel->setTextColor(Card::BinaryColor);
	decimalLabel->setTextColor(Card::DecimalColor);
	hexLabel->setTextColor(Card::HexColor);
	specialLabel->setTextColor(Card::SpecialColor);

	this->binaryButton->addChild(binaryIcon);
	this->decimalButton->addChild(decimalIcon);
	this->hexButton->addChild(hexIcon);
	this->specialButton->addChild(specialIcon);

	this->binaryButton->addChild(binaryLabel);
	this->decimalButton->addChild(decimalLabel);
	this->hexButton->addChild(hexLabel);
	this->specialButton->addChild(specialLabel);

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
	this->storeNode->addChild(this->binaryCardsScrollPane);
	this->storeNode->addChild(this->decimalCardsScrollPane);
	this->storeNode->addChild(this->hexCardsScrollPane);
	this->storeNode->addChild(this->specialCardsScrollPane);
	this->storeNode->addChild(this->binaryButton);
	this->storeNode->addChild(this->hexButton);
	this->storeNode->addChild(this->decimalButton);
	this->storeNode->addChild(this->specialButton);
	this->addChild(this->backButton);
	this->addChild(this->chosenCardsNode);

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
}

HexusStoreMenu::~HexusStoreMenu()
{
}

void HexusStoreMenu::onEnter()
{
	super::onEnter();

	const float delay = 0.25f;
	const float duration = 0.35f;

	GameUtils::fadeInObject(this->backButton, delay, duration);

	this->dustParticles->accelerate(5.0f);

	this->updateGoldText();
}

void HexusStoreMenu::initializeListeners()
{
	super::initializeListeners();

	EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();

	keyboardListener->onKeyPressed = CC_CALLBACK_2(HexusStoreMenu::onKeyPressed, this);

	this->addEventListener(keyboardListener);

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
	const Vec2 storeMenuOffset = Vec2(352.0f, 0.0f);
	const Vec2 storeContentOffset = Vec2(0.0f, -64.0f);
	const Vec2 goldPanelOffset = Vec2(412.0f, 464.0f);

	this->dustParticles->setPosition(Vec2(visibleSize.width, visibleSize.height / 2));
	this->storeBack->setPosition(Vec2(0.0f, visibleSize.height / 2.0f + storeOffsetY + 144.0f));
	this->shopKeeper->setPosition(Vec2(visibleSize.width / 2.0f - 680.0f, visibleSize.height / 2.0f + storeOffsetY));
	this->storeFront->setPosition(Vec2(0.0f, visibleSize.height / 2.0f + storeOffsetY - 176.0f));
	this->storeMenu->setPosition(Vec2(visibleSize.width / 2.0f + storeMenuOffset.x, visibleSize.height / 2.0f + storeMenuOffset.y - 48.0f));

	this->goldPanel->setPosition(Vec2(visibleSize.width / 2.0f + storeMenuOffset.x + goldPanelOffset.x, visibleSize.height / 2.0f + storeMenuOffset.y + goldPanelOffset.y));
	this->goldIcon->setPosition(Vec2(visibleSize.width / 2.0f + storeMenuOffset.x + goldPanelOffset.x - 80.0f, visibleSize.height / 2.0f + storeMenuOffset.y + goldPanelOffset.y));
	this->goldLabel->setPosition(Vec2(visibleSize.width / 2.0f + storeMenuOffset.x + goldPanelOffset.x - 8.0f, visibleSize.height / 2.0f + storeMenuOffset.y + goldPanelOffset.y));

	this->backButton->setPosition(Vec2(visibleSize.width / 2.0f - 756.0f, visibleSize.height - 64.0f));

	this->binaryCardsScrollPane->setPosition(Vec2(visibleSize.width / 2.0f + storeMenuOffset.x + storeContentOffset.x, visibleSize.height / 2.0f + storeMenuOffset.y + storeContentOffset.y));
	this->decimalCardsScrollPane->setPosition(Vec2(visibleSize.width / 2.0f + storeMenuOffset.x + storeContentOffset.x, visibleSize.height / 2.0f + storeMenuOffset.y + storeContentOffset.y));
	this->hexCardsScrollPane->setPosition(Vec2(visibleSize.width / 2.0f + storeMenuOffset.x + storeContentOffset.x, visibleSize.height / 2.0f + storeMenuOffset.y + storeContentOffset.y));
	this->specialCardsScrollPane->setPosition(Vec2(visibleSize.width / 2.0f + storeMenuOffset.x + storeContentOffset.x, visibleSize.height / 2.0f + storeMenuOffset.y + storeContentOffset.y));
	this->binaryButton->setPosition(Vec2(visibleSize.width / 2.0f + storeMenuOffset.x - 640.0f, visibleSize.height / 2.0f + 256.0f - 144.0f * 1));
	this->decimalButton->setPosition(Vec2(visibleSize.width / 2.0f + storeMenuOffset.x - 640.0f, visibleSize.height / 2.0f + 256.0f - 144.0f * 2));
	this->hexButton->setPosition(Vec2(visibleSize.width / 2.0f + storeMenuOffset.x - 640.0f, visibleSize.height / 2.0f + 256.0f - 144.0f * 3));
	this->specialButton->setPosition(Vec2(visibleSize.width / 2.0f + storeMenuOffset.x - 640.0f, visibleSize.height / 2.0f + 256.0f - 144.0f * 4));

	const Size chestGridSize = Size(288.0f, 240.0f);
	int index = 0;

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

std::tuple<ClickableNode*, MenuCard*, int> HexusStoreMenu::constructCard(CardData* cardData)
{
	ClickableNode* cardContainer =  ClickableNode::create(UIResources::Menus_TutorialsMenu_Store_CardPanel, UIResources::Menus_TutorialsMenu_Store_CardPanelSelected);
	MenuCard* menuCard = MenuCard::create(Card::CardStyle::Earth, cardData);
	int price = 444;

	ConstantString* countString = ConstantString::create();
	ConstantString* limitString = ConstantString::create();
	LocalizedLabel* cardLimitLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H1, Strings::Common_XOverY::create());

	cardLimitLabel->setStringReplacementVariables({ countString, limitString });
	cardLimitLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
	cardLimitLabel->enableOutline(Color4B::BLACK, 4);
	cardLimitLabel->setPosition(Vec2(-96.0f, 128.0f));

	this->updateCardLimitText(cardLimitLabel, countString, limitString, cardData);

	ConstantString* priceString = ConstantString::create(std::to_string(price));
	LocalizedLabel* priceLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H3, Strings::Common_Constant::create());
	Sprite* goldIcon = Sprite::create(UIResources::Menus_Icons_Currency_GOLD_1);

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
	int ownedCount = 2; //CardStorage::getOwnedCardCount(cardData);

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
	int gold = 42424; //CardStorage::getGold();

	if (gold < price)
	{
		// SoundManager::playSoundResource(SoundResources::AFX_INTERFACE_ERROR_1_DFMG);
		return;
	}

	gold -= price;
	// SoundManager::playSoundResource(SoundResources::Item_Purchase__1_);

	// CardStorage::saveGold(gold);
	this->updateGoldText();

	this->updateCardLimitText(cardLimitLabel, countString, limitString, cardData);
}

void HexusStoreMenu::onBackClick()
{
	// NavigationEvents::LoadScene();
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
			// NavigationEvents::navigateBack();
			break;
		}
		default:
		{
			break;
		}
	}
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
	this->storeMenu->setLocalZOrder(0);
	this->binaryButton->setLocalZOrder(-1);
	this->decimalButton->setLocalZOrder(-1);
	this->hexButton->setLocalZOrder(-1);
	this->specialButton->setLocalZOrder(-1);
	
	this->binaryCardsScrollPane->setVisible(false);
	this->decimalCardsScrollPane->setVisible(false);
	this->hexCardsScrollPane->setVisible(false);
	this->specialCardsScrollPane->setVisible(false);
}

void HexusStoreMenu::updateGoldText()
{
	this->goldString->setString(std::to_string(11111));
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
