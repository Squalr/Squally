#include "HexusDeckManagement.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCEventListenerKeyboard.h"

#include "Engine/GlobalDirector.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Sound/SoundManager.h"
#include "Engine/UI/Controls/CCheckbox.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Engine/UI/Controls/ToggleGroup.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Events/NavigationEvents.h"
#include "Menus/Hexus/MenuCard.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/CardStorage.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Menus/Back.h"
#include "Strings/Hexus/BinCards.h"
#include "Strings/Hexus/CardsInDeck.h"
#include "Strings/Hexus/DecCards.h"
#include "Strings/Hexus/CardsInStorage.h"
#include "Strings/Hexus/HexCards.h"
#include "Strings/Hexus/SpecialCards.h"
#include "Strings/Generics/Constant.h"
#include "Strings/Generics/TimesConstant.h"
#include "Strings/Generics/XOverY.h"

using namespace cocos2d;

HexusDeckManagement* HexusDeckManagement::instance;

void HexusDeckManagement::registerGlobalScene()
{
	if (HexusDeckManagement::instance == nullptr)
	{
		HexusDeckManagement::instance = new HexusDeckManagement();

		HexusDeckManagement::instance->autorelease();
		HexusDeckManagement::instance->initializeListeners();
	}

	GlobalDirector::registerGlobalScene(HexusDeckManagement::instance);
}

HexusDeckManagement::HexusDeckManagement()
{
	this->filters = ToggleGroup::create(CC_CALLBACK_1(HexusDeckManagement::onToggleSelect, this));
	this->activeFilter = CardFilterFlags::All;
	this->displayDeckCards = std::map<CardData*, MenuCard*>();
	this->displayStorageCards = std::map<CardData*, MenuCard*>();
	this->countLabels = std::map<MenuCard*, std::tuple<ConstantString*, LocalizedLabel*>>();
	this->deckCards = std::map<CardData*, int>();
	this->storageCards = std::map<CardData*, int>();

	this->background = Sprite::create(UIResources::Menus_MinigamesMenu_Hexus_WoodBackground);
	this->storageScrollPane = ScrollPane::create(Size(720.0f, 820.0f), Color4B(0, 0, 0, 196));
	this->deckScrollPane = ScrollPane::create(Size(720.0f, 820.0f), Color4B(0, 0, 0, 196));
	this->storageSprite = Sprite::create(UIResources::Menus_Icons_TreasureChest);
	this->storageLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Hexus_CardsInStorage::create(), Size::ZERO, cocos2d::TextHAlignment::LEFT);
	this->deckSprite = Sprite::create(UIResources::Menus_Icons_Satchel);
	this->deckLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Hexus_CardsInDeck::create(), Size::ZERO, cocos2d::TextHAlignment::RIGHT);
	this->titleSprite = Sprite::create(UIResources::Menus_MinigamesMenu_Hexus_AxeLogo);

	this->totalCardsInDeckLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Hexus_CardsInDeck::create());
	this->totalCardsInDeckValueXString = ConstantString::create();
	this->totalCardsInDeckValueYString = ConstantString::create();
	this->totalCardsInDeckValueLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Generics_XOverY::create());
	this->binaryCardsInDeckLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Hexus_BinCards::create());
	this->binaryCardsInDeckValueString = ConstantString::create();
	this->binaryCardsInDeckValueLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Generics_Constant::create());
	this->decimalCardsInDeckLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Hexus_DecCards::create());
	this->decimalCardsInDeckValueString = ConstantString::create();
	this->decimalCardsInDeckValueLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Generics_Constant::create());
	this->hexCardsInDeckLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Hexus_HexCards::create());
	this->hexCardsInDeckValueString = ConstantString::create();
	this->hexCardsInDeckValueLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Generics_Constant::create());
	this->specialCardsInDeckLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Hexus_SpecialCards::create());
	this->specialCardsInDeckValueString = ConstantString::create();
	this->specialCardsInDeckValueLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Generics_Constant::create());

	this->totalCardsInDeckValueLabel->setStringReplacementVariables({ this->totalCardsInDeckValueXString , this->totalCardsInDeckValueYString });
	this->binaryCardsInDeckValueLabel->setStringReplacementVariables(this->binaryCardsInDeckValueString);
	this->decimalCardsInDeckValueLabel->setStringReplacementVariables(this->decimalCardsInDeckValueString);
	this->hexCardsInDeckValueLabel->setStringReplacementVariables(this->hexCardsInDeckValueString);
	this->specialCardsInDeckValueLabel->setStringReplacementVariables(this->specialCardsInDeckValueString);

	ClickableNode* allButtonUnselected = ClickableNode::create(UIResources::Menus_Buttons_WoodSquareButtonSmall, UIResources::Menus_Buttons_WoodSquareButtonSmallSelected);
	ClickableNode* allButtonSelected = ClickableNode::create(UIResources::Menus_Buttons_WoodSquareButtonSmallToggled, UIResources::Menus_Buttons_WoodSquareButtonSmallToggled);
	allButtonUnselected->addChild(Sprite::create(UIResources::Menus_MinigamesMenu_Hexus_IconAll));
	allButtonSelected->addChild(Sprite::create(UIResources::Menus_MinigamesMenu_Hexus_IconAll));

	ClickableNode* specialButtonUnselected = ClickableNode::create(UIResources::Menus_Buttons_WoodSquareButtonSmall, UIResources::Menus_Buttons_WoodSquareButtonSmallSelected);
	ClickableNode* specialButtonSelected = ClickableNode::create(UIResources::Menus_Buttons_WoodSquareButtonSmallToggled, UIResources::Menus_Buttons_WoodSquareButtonSmallToggled);
	specialButtonUnselected->addChild(Sprite::create(UIResources::Menus_MinigamesMenu_Hexus_IconSpecial));
	specialButtonSelected->addChild(Sprite::create(UIResources::Menus_MinigamesMenu_Hexus_IconSpecial));

	ClickableNode* binaryButtonUnselected = ClickableNode::create(UIResources::Menus_Buttons_WoodSquareButtonSmall, UIResources::Menus_Buttons_WoodSquareButtonSmallSelected);
	ClickableNode* binaryButtonSelected = ClickableNode::create(UIResources::Menus_Buttons_WoodSquareButtonSmallToggled, UIResources::Menus_Buttons_WoodSquareButtonSmallToggled);
	binaryButtonUnselected->addChild(Sprite::create(UIResources::Menus_MinigamesMenu_Hexus_IconBinary));
	binaryButtonSelected->addChild(Sprite::create(UIResources::Menus_MinigamesMenu_Hexus_IconBinary));

	ClickableNode* decimalButtonUnselected = ClickableNode::create(UIResources::Menus_Buttons_WoodSquareButtonSmall, UIResources::Menus_Buttons_WoodSquareButtonSmallSelected);
	ClickableNode* decimalButtonSelected = ClickableNode::create(UIResources::Menus_Buttons_WoodSquareButtonSmallToggled, UIResources::Menus_Buttons_WoodSquareButtonSmallToggled);
	decimalButtonUnselected->addChild(Sprite::create(UIResources::Menus_MinigamesMenu_Hexus_IconDecimal));
	decimalButtonSelected->addChild(Sprite::create(UIResources::Menus_MinigamesMenu_Hexus_IconDecimal));

	ClickableNode* hexButtonUnselected = ClickableNode::create(UIResources::Menus_Buttons_WoodSquareButtonSmall, UIResources::Menus_Buttons_WoodSquareButtonSmallSelected);
	ClickableNode* hexButtonSelected = ClickableNode::create(UIResources::Menus_Buttons_WoodSquareButtonSmallToggled, UIResources::Menus_Buttons_WoodSquareButtonSmallToggled);
	hexButtonUnselected->addChild(Sprite::create(UIResources::Menus_MinigamesMenu_Hexus_IconHex));
	hexButtonSelected->addChild(Sprite::create(UIResources::Menus_MinigamesMenu_Hexus_IconHex));

	this->allButton = CCheckbox::create(allButtonUnselected, allButtonSelected, true, nullptr);
	this->specialButton = CCheckbox::create(specialButtonUnselected, specialButtonSelected, false, nullptr);
	this->binaryButton = CCheckbox::create(binaryButtonUnselected, binaryButtonSelected, false, nullptr);
	this->decimalButton = CCheckbox::create(decimalButtonUnselected, decimalButtonSelected, false, nullptr);
	this->hexButton = CCheckbox::create(hexButtonUnselected, hexButtonSelected, false, nullptr);

	this->filters->addToggle(this->allButton);
	this->filters->addToggle(this->specialButton);
	this->filters->addToggle(this->binaryButton);
	this->filters->addToggle(this->decimalButton);
	this->filters->addToggle(this->hexButton);
	
	this->activeFilter = CardFilterFlags::All;
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

	// Create all cards for deck. Every card gets created with count = 0, and those that are 0 get hidden
	for (auto it = CardList::getInstance()->cardListByName.begin(); it != CardList::getInstance()->cardListByName.end(); it++)
	{
		CardData* cardData = (*it).second;

		// These only need to be instantiated once
		if (this->displayDeckCards.find(cardData) == this->displayDeckCards.end())
		{
			MenuCard* card = this->createCard(cardData, 0);

			displayDeckCards.emplace(cardData, card);

			this->deckScrollPane->addChild(card);
		}
	}

	// Create all cards for storage. Every card gets created with count = 0, and those that are 0 get hidden
	for (auto it = CardList::getInstance()->cardListByName.begin(); it != CardList::getInstance()->cardListByName.end(); it++)
	{
		CardData* cardData = (*it).second;

		// These only need to be instantiated once
		if (this->displayStorageCards.find(cardData) == this->displayStorageCards.end())
		{
			MenuCard* card = this->createCard(cardData, 0);

			displayStorageCards.emplace(cardData, card);

			this->storageScrollPane->addChild(card);
		}
	}

	this->storageSprite->setAnchorPoint(Vec2(1.0f, 0.5f));
	this->storageLabel->setAnchorPoint(Vec2(1.0f, 0.5f));
	this->deckSprite->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->deckLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->storageLabel->enableOutline(Color4B::BLACK, 2);
	this->deckLabel->enableOutline(Color4B::BLACK, 2);

	this->totalCardsInDeckLabel->enableOutline(Color4B::BLACK, 2);
	this->totalCardsInDeckValueLabel->enableOutline(Color4B::BLACK, 2);
	this->binaryCardsInDeckLabel->enableOutline(Color4B::BLACK, 2);
	this->binaryCardsInDeckValueLabel->enableOutline(Color4B::BLACK, 2);
	this->decimalCardsInDeckLabel->enableOutline(Color4B::BLACK, 2);
	this->decimalCardsInDeckValueLabel->enableOutline(Color4B::BLACK, 2);
	this->hexCardsInDeckLabel->enableOutline(Color4B::BLACK, 2);
	this->hexCardsInDeckValueLabel->enableOutline(Color4B::BLACK, 2);
	this->specialCardsInDeckLabel->enableOutline(Color4B::BLACK, 2);
	this->specialCardsInDeckValueLabel->enableOutline(Color4B::BLACK, 2);

	this->addChild(this->background);
	this->addChild(this->titleSprite);
	this->addChild(this->storageScrollPane);
	this->addChild(this->deckScrollPane);
	this->addChild(this->storageSprite);
	this->addChild(this->storageLabel);
	this->addChild(this->deckSprite);
	this->addChild(this->deckLabel);
	this->addChild(this->totalCardsInDeckLabel);
	this->addChild(this->totalCardsInDeckValueLabel);
	this->addChild(this->binaryCardsInDeckLabel);
	this->addChild(this->binaryCardsInDeckValueLabel);
	this->addChild(this->decimalCardsInDeckLabel);
	this->addChild(this->decimalCardsInDeckValueLabel);
	this->addChild(this->hexCardsInDeckLabel);
	this->addChild(this->hexCardsInDeckValueLabel);
	this->addChild(this->specialCardsInDeckLabel);
	this->addChild(this->specialCardsInDeckValueLabel);
	this->addChild(this->filters);
	this->addChild(this->backButton);
}

HexusDeckManagement::~HexusDeckManagement()
{
}

void HexusDeckManagement::onEnter()
{
	super::onEnter();

	float delay = 0.25f;
	float duration = 0.35f;

	GameUtils::fadeInObject(this->backButton, delay, duration);

	this->rebuildCardLists();
}

void HexusDeckManagement::onExit()
{
	this->save(false);

	super::onExit();
}

void HexusDeckManagement::initializeListeners()
{
	super::initializeListeners();

	HexusDeckManagement::instance->addGlobalEventListener(EventListenerCustom::create(NavigationEvents::EventNavigateHexusDeckManagement, [](EventCustom* args)
	{
		GlobalDirector::loadScene(HexusDeckManagement::instance);
	}));

	EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();

	keyboardListener->onKeyPressed = CC_CALLBACK_2(HexusDeckManagement::onKeyPressed, this);
	
	for (auto it = this->displayDeckCards.begin(); it != this->displayDeckCards.end(); it++)
	{
		(*it).second->setMouseClickCallback(CC_CALLBACK_1(HexusDeckManagement::onDeckCardClick, this));
		(*it).second->setMouseOverCallback(CC_CALLBACK_1(HexusDeckManagement::onDeckCardMouseOver, this));
	}
	
	for (auto it = this->displayStorageCards.begin(); it != this->displayStorageCards.end(); it++)
	{
		(*it).second->setMouseClickCallback(CC_CALLBACK_1(HexusDeckManagement::onStorageCardClick, this));
		(*it).second->setMouseOverCallback(CC_CALLBACK_1(HexusDeckManagement::onStorageCardMouseOver, this));
	}

	this->backButton->setClickCallback(CC_CALLBACK_1(HexusDeckManagement::onBackClick, this));
	this->addEventListener(keyboardListener);
}

void HexusDeckManagement::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	const float totalsOffset = 448.0f;
	const float totalsSpacing = 72.0f;
	const float totalsValueOffset = 32.0f;

	this->background->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->storageScrollPane->setPosition(Vec2(visibleSize.width / 2.0f - 416.0f - 96.0f, visibleSize.height / 2.0f - 48.0f));
	this->deckScrollPane->setPosition(Vec2(visibleSize.width / 2.0f + 416.0f + 96.0f, visibleSize.height / 2.0f - 48.0f));
	this->storageSprite->setPosition(Vec2(visibleSize.width / 2.0f - 144.0f, visibleSize.height - 96.0f));
	this->storageLabel->setPosition(Vec2(visibleSize.width / 2.0f - (144.0f + 80.0f), visibleSize.height - 96.0f));
	this->deckSprite->setPosition(Vec2(visibleSize.width / 2.0f + 144.0f, visibleSize.height - 96.0f));
	this->deckLabel->setPosition(Vec2(visibleSize.width / 2.0f + (144.0f + 80.0f), visibleSize.height - 96.0f));
	this->titleSprite->setPosition(Vec2(visibleSize.width / 2.0f + 804.0f, visibleSize.height / 2.0f + 336.0f));

	this->totalCardsInDeckLabel->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + totalsOffset - totalsSpacing * 0));
	this->totalCardsInDeckValueLabel->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + totalsOffset - totalsSpacing * 0 - totalsValueOffset));
	this->binaryCardsInDeckLabel->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + totalsOffset - totalsSpacing * 1));
	this->binaryCardsInDeckValueLabel->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + totalsOffset - totalsSpacing * 1 - totalsValueOffset));
	this->decimalCardsInDeckLabel->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + totalsOffset - totalsSpacing * 2));
	this->decimalCardsInDeckValueLabel->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + totalsOffset - totalsSpacing * 2 - totalsValueOffset));
	this->hexCardsInDeckLabel->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + totalsOffset - totalsSpacing * 3));
	this->hexCardsInDeckValueLabel->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + totalsOffset - totalsSpacing * 3 - totalsValueOffset));
	this->specialCardsInDeckLabel->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + totalsOffset - totalsSpacing * 4));
	this->specialCardsInDeckValueLabel->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + totalsOffset - totalsSpacing * 4 - totalsValueOffset));

	this->backButton->setPosition(Vec2(visibleSize.width / 2.0f - 756.0f, visibleSize.height - 64.0f));
	this->allButton->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 32.0f - 112.0f * 0));
	this->specialButton->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 32.0f - 112.0f * 1));
	this->binaryButton->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 32.0f - 112.0f * 2));
	this->decimalButton->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 32.0f - 112.0f * 3));
	this->hexButton->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 32.0f - 112.0f * 4));

	auto positionCards = [=](ScrollPane* scrollPane, std::map<CardData*, MenuCard*> displayCards)
	{
		// Position cards
		const Size cardGridSize = Size(176.0f, 256.0f);
		const int cardsPerRow = 4;
		Size paneSize = scrollPane->getContentSize();
		Size marginSize = (paneSize - (cardGridSize * cardsPerRow)) / 2.0f;
		int index = 0;
		int visibleCardCount = 0;

		for (auto it = displayCards.begin(); it != displayCards.end(); it++)
		{
			MenuCard* card = (*it).second;

			if (card->isVisible())
			{
				visibleCardCount++;
			}
		}

		for (auto it = CardList::getInstance()->sortedCardList.begin(); it != CardList::getInstance()->sortedCardList.end(); it++)
		{
			MenuCard* card = displayCards[*it];

			int x = index % cardsPerRow;
			int y = (visibleCardCount - 1 - index + (cardsPerRow - visibleCardCount % cardsPerRow)) / cardsPerRow - (visibleCardCount % cardsPerRow == 0 ? 1 : 0);

			card->setPosition(Vec2(paneSize.width / 2.0f + marginSize.width - (((cardsPerRow - 1) - x) - cardsPerRow / 2 + 1) * cardGridSize.width, y * cardGridSize.height + 128.0f));

			if (card->isVisible())
			{
				index++;
			}
		}

		scrollPane->fitSizeToContent(Rect(0.0f, 64.0f, 0.0f, 0.0f));
	};

	positionCards(this->storageScrollPane, this->displayStorageCards);
	positionCards(this->deckScrollPane, this->displayDeckCards);
}

void HexusDeckManagement::onToggleSelect(CCheckbox* activeToggle)
{
	if (activeToggle == this->allButton)
	{
		this->activeFilter = CardFilterFlags::All;
	}
	else if (activeToggle == this->specialButton)
	{
		this->activeFilter = CardFilterFlags::Special;
	}
	else if (activeToggle == this->binaryButton)
	{
		this->activeFilter = CardFilterFlags::Binary;
	}
	else if (activeToggle == this->decimalButton)
	{
		this->activeFilter = CardFilterFlags::Decimal;
	}
	else if (activeToggle == this->hexButton)
	{
		this->activeFilter = CardFilterFlags::Hex;
	}

	this->rebuildCardLists();
}

void HexusDeckManagement::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
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
			this->save(true);
			break;
		}
		default:
		{
			break;
		}
	}
}

void HexusDeckManagement::onBackClick(ClickableNode* menuSprite)
{
	this->save(true);
}

void HexusDeckManagement::save(bool exit)
{
	CardStorage::saveDeckCardsByCount(this->deckCards);
	CardStorage::saveStorageCardsByCount(this->storageCards);

	if (exit)
	{
		NavigationEvents::navigateBack();
	}
}

void HexusDeckManagement::rebuildCardList(std::map<CardData*, int> cards, std::map<CardData*, MenuCard*> displayCards)
{
	// Update the display counts
	for (auto it = displayCards.begin(); it != displayCards.end(); it++)
	{
		CardData* cardData = (*it).first;
		MenuCard* card = (*it).second;
		int count = 0;

		if (cards.find(cardData) != cards.end())
		{
			count = cards[cardData];

			this->updateCardCount(displayCards[cardData], count);
		}

		// Always hide cards when we have none of that type
		if (count <= 0)
		{
			card->setVisible(false);
			continue;
		}

		// Hide based on filters
		switch (cardData->cardType)
		{
			case CardData::CardType::Binary:
			{
				if ((this->activeFilter & CardFilterFlags::Binary) != 0)
				{
					card->setVisible(true);
				}
				else
				{
					card->setVisible(false);
				}

				break;
			}
			case CardData::CardType::Decimal:
			{
				if ((this->activeFilter & CardFilterFlags::Decimal) != 0)
				{
					card->setVisible(true);
				}
				else
				{
					card->setVisible(false);
				}

				break;
			}
			case CardData::CardType::Hexidecimal:
			{
				if ((this->activeFilter & CardFilterFlags::Hex) != 0)
				{
					card->setVisible(true);
				}
				else
				{
					card->setVisible(false);
				}

				break;
			}
			default:
			{
				if ((this->activeFilter & CardFilterFlags::Special) != 0)
				{
					card->setVisible(true);
				}
				else
				{
					card->setVisible(false);
				}

				break;
			}
		}
	}
}

void HexusDeckManagement::rebuildCardLists()
{
	this->storageCards = CardStorage::getStorageCardsByCount();
	this->deckCards = CardStorage::getDeckCardsByCount();

	// Rebuild deck/storage
	this->rebuildCardList(this->deckCards, this->displayDeckCards);
	this->rebuildCardList(this->storageCards, this->displayStorageCards);

	// Update total counts
	int totalDeckCards = 0;
	int totalDeckBinaryCards = 0;
	int totalDeckDecimalCards = 0;
	int totalDeckHexCards = 0;
	int totalDeckSpecialCards = 0;

	for (auto it = this->deckCards.begin(); it != this->deckCards.end(); it++)
	{
		CardData* cardData = (*it).first;
		int count = (*it).second;

		totalDeckCards += count;

		switch (cardData->cardType)
		{
			case CardData::CardType::Binary:
			{
				totalDeckBinaryCards += count;
				break;
			}
			case CardData::CardType::Decimal:
			{
				totalDeckDecimalCards += count;
				break;
			}
			case CardData::CardType::Hexidecimal:
			{
				totalDeckHexCards += count;
				break;
			}
			default:
			{
				totalDeckSpecialCards += count;
				break;
			}
		}
	}

	this->totalCardsInDeckValueXString->setString(std::to_string(totalDeckCards));
	this->totalCardsInDeckValueYString->setString(std::to_string(CardStorage::minimumDeckCards));

	if (totalDeckCards < CardStorage::minimumDeckCards)
	{
		this->totalCardsInDeckValueLabel->setTextColor(Color4B::RED);
	}
	else
	{
		this->totalCardsInDeckValueLabel->setTextColor(Color4B::YELLOW);
	}

	this->binaryCardsInDeckValueString->setString({ std::to_string(totalDeckBinaryCards) });
	this->decimalCardsInDeckValueString->setString({ std::to_string(totalDeckDecimalCards) });
	this->hexCardsInDeckValueString->setString({ std::to_string(totalDeckHexCards) });
	this->specialCardsInDeckValueString->setString({ std::to_string(totalDeckSpecialCards) });

	// Position all the cards
	this->initializeListeners();
	this->initializePositions();
}

MenuCard* HexusDeckManagement::createCard(CardData* cardData, int count)
{
	MenuCard* card = MenuCard::create(Card::CardStyle::Earth, cardData);
	ConstantString* valueString = ConstantString::create();
	LocalizedLabel* label = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::M1, Strings::Generics_TimesConstant::create());

	label->setStringReplacementVariables(valueString);

	label->enableOutline(Color4B::BLACK, 4);
	label->setAnchorPoint(Vec2(0.0f, 0.5f));
	label->setPosition(Vec2(-96.0f, 128.0f));

	card->addDisplayItem(label);

	card->setScale(0.6f);
	card->reveal();

	this->countLabels[card] = std::make_tuple(valueString, label);
	this->updateCardCount(card, count);

	return card;
}

void HexusDeckManagement::updateCardCount(MenuCard* card, int count)
{
	if (this->countLabels.find(card) != this->countLabels.end())
	{
		ConstantString* valueString = std::get<0>(this->countLabels[card]);
		LocalizedLabel* label = std::get<1>(this->countLabels[card]);

		valueString->setString(std::to_string(count));

		switch (count)
		{
			case 1:
			default:
			{
				label->setTextColor(Color4B(192, 165, 108, 255));
				break;
			}
			case 2:
			{
				label->setTextColor(Color4B(214, 184, 121, 255));
				break;
			}
			case 3:
			{
				label->setTextColor(Color4B(238, 205, 135, 255));
				break;
			}
		}
	}
}

void HexusDeckManagement::onDeckCardClick(Card* card)
{
	// Remove from deck
	this->deckCards[card->cardData] = MathUtils::clamp(this->deckCards[card->cardData] - 1, 0, 3);

	// Add to storage
	this->storageCards[card->cardData] = MathUtils::clamp(this->storageCards[card->cardData] + 1, 0, 3);

	this->save(false);

	SoundManager::playSoundResource(SoundResources::Hexus_CardMovementStrong);

	this->rebuildCardLists();
}

void HexusDeckManagement::onStorageCardClick(Card* card)
{
	// Remove from storage
	this->storageCards[card->cardData] = MathUtils::clamp(this->storageCards[card->cardData] - 1, 0, 3);

	// Add to deck
	this->deckCards[card->cardData] = MathUtils::clamp(this->deckCards[card->cardData] + 1, 0, 3);

	this->save(false);

	SoundManager::playSoundResource(SoundResources::Hexus_CardMovementStrong);
	
	this->rebuildCardLists();
}

void HexusDeckManagement::onDeckCardMouseOver(Card* card)
{
}

void HexusDeckManagement::onStorageCardMouseOver(Card* card)
{
}
