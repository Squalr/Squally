#include "HexusStoreMenu.h"

#include <math.h>

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCLayer.h"
#include "cocos/2d/CCParticleSystemQuad.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCInputEvents.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/SpeechBubble.h"
#include "Engine/Events/NavigationEvents.h"
#include "Engine/GlobalDirector.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Particles/SmartParticles.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Sound/Sound.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/Special/Shopkeeper.h"
#include "Menus/Tutorials/TutorialSelectMenu.h"
#include "Scenes/Hexus/Menus/MenuCard.h"
#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Dialogue/Voices.h"
#include "Scenes/Tutorials/Save/TutorialSaveKeys.h"

#include "Resources/ParticleResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

const std::string HexusStoreMenu::SaveKeyGold = "SAVE_KEY_GOLD";
const int HexusStoreMenu::DefaultGold = 1000;

using namespace cocos2d;

HexusStoreMenu* HexusStoreMenu::instance;

HexusStoreMenu* HexusStoreMenu::getInstance()
{
	if (HexusStoreMenu::instance == nullptr)
	{
		HexusStoreMenu::instance = new HexusStoreMenu();

		HexusStoreMenu::instance->autorelease();
		HexusStoreMenu::instance->initializeListeners();

		GlobalDirector::registerGlobalScene(HexusStoreMenu::getInstance());
	}

	return HexusStoreMenu::instance;
}

HexusStoreMenu::HexusStoreMenu()
{
	this->dustParticles = SmartParticles::create(ParticleResources::Dust);
	this->purchaseSound = Sound::create(SoundResources::Menus_TransactGold1);
	this->errorSound = Sound::create(SoundResources::Menus_Error1);

	this->goldPanel = Sprite::create(UIResources::Menus_TutorialsMenu_Store_GoldPanel);
	this->goldIcon = Sprite::create(UIResources::Menus_Icons_Currency_GOLD_2);
	this->goldString = ConstantString::create();
	this->goldLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H2, Strings::Common_Constant::create());

	this->goldLabel->setStringReplacementVariables(this->goldString);
	this->goldLabel->enableOutline(Color4B::BLACK, 3);
	this->goldLabel->setPosition(Vec2(-32.0f, 0.0f));
	this->goldLabel->setAlignment(TextHAlignment::LEFT);
	this->goldLabel->setAnchorPoint(Vec2(0.0f, 0.5f));

	ValueMap properties = ValueMap();
	this->storeBack = Sprite::create(UIResources::Menus_TutorialsMenu_Store_StoreBack);
	this->shopKeeper = Shopkeeper::deserialize(properties);
	this->storeFront = Sprite::create(UIResources::Menus_TutorialsMenu_Store_Store);
	this->storeNode = Node::create();
	this->storeMenu = Sprite::create(UIResources::Menus_TutorialsMenu_Store_StoreBoard);

	LocalizedLabel* backButtonLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Back::create());
	LocalizedLabel* backButtonLabelSelected = backButtonLabel->clone();
	
	backButtonLabel->enableOutline(Color4B::BLACK, 2);
	backButtonLabelSelected->enableOutline(Color4B::BLACK, 2);

	this->backButton = ClickableTextNode::create(
		backButtonLabel,
		backButtonLabelSelected,
		UIResources::Menus_Buttons_WoodButton,
		UIResources::Menus_Buttons_WoodButtonSelected
	);

	LocalizedLabel* resetButtonLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Reset::create());
	LocalizedLabel* resetButtonLabelSelected = resetButtonLabel->clone();
	
	resetButtonLabel->enableOutline(Color4B::BLACK, 2);
	resetButtonLabelSelected->enableOutline(Color4B::BLACK, 2);

	this->resetButton = ClickableTextNode::create(
		resetButtonLabel,
		resetButtonLabelSelected,
		UIResources::Menus_Buttons_DarkWoodButton,
		UIResources::Menus_Buttons_DarkWoodButtonSelected
	);

	this->xorCard = this->constructCard(CardList::getInstance()->cardListByName[CardKeys::LogicalXor], 420, [=](CardData* cardData, int price)
	{
		this->purchaseCard(cardData, price);
	});

	this->andCard = this->constructCard(CardList::getInstance()->cardListByName[CardKeys::LogicalAnd], 542, [=](CardData* cardData, int price)
	{
		this->purchaseCard(cardData, price);
	});

	this->inverseCard = this->constructCard(CardList::getInstance()->cardListByName[CardKeys::Inverse], 2000, [=](CardData* cardData, int price)
	{
		if (this->purchaseCard(cardData, price))
		{
			this->onChallengeComplete();
		}
	});

	this->resetButton->setClickSound(SoundResources::Menus_ButtonClick5);

	this->shopKeeper->attachBehavior(EntityDialogueBehavior::create(this->shopKeeper));
	this->storeBack->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->storeFront->setAnchorPoint(Vec2(0.0f, 0.5f));

	this->storeNode->addChild(this->storeMenu);
	this->storeNode->addChild(this->goldPanel);
	this->storeNode->addChild(this->goldIcon);
	this->storeNode->addChild(this->goldLabel);
	this->storeNode->addChild(this->xorCard);
	this->storeNode->addChild(this->andCard);
	this->storeNode->addChild(this->inverseCard);
	this->addChild(this->dustParticles);
	this->addChild(this->storeBack);
	this->addChild(this->shopKeeper);
	this->addChild(this->storeFront);
	this->addChild(this->storeNode);
	this->addChild(this->backButton);
	this->addChild(this->resetButton);
	this->addChild(this->purchaseSound);
	this->addChild(this->errorSound);
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
	GameUtils::fadeInObject(this->resetButton, delay, duration);

	this->dustParticles->accelerate(5.0f);

	this->updateGoldText();
	
	this->shopKeeper->getAttachedBehavior<EntityDialogueBehavior>([=](EntityDialogueBehavior* dialogueBehavior)
	{
		dialogueBehavior->getSpeechBubble()->runDialogue(Strings::Menus_Tutorials_HexEditing_TutorialStringSearch::create(), Voices::GetNextVoiceMedium(), SpeechBubble::InfiniteDuration);
	});
}

void HexusStoreMenu::initializeListeners()
{
	super::initializeListeners();

	this->whenKeyPressed({ InputEvents::KeyCode::KEY_ESCAPE }, [=](InputEvents::KeyboardEventArgs* args)
	{
		if (!GameUtils::isVisible(this))
		{
			return;
		}

		args->handle();
		NavigationEvents::LoadScene(NavigationEvents::LoadSceneArgs([=]() { return TutorialSelectMenu::getInstance(); }));
	});

	this->backButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->onBackClick();
	});

	this->resetButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->onResetClick();
	});
}

void HexusStoreMenu::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	const float StoreOffsetY = -128.0f;

	this->dustParticles->setPosition(Vec2(visibleSize.width, visibleSize.height / 2));
	this->storeBack->setPosition(Vec2(0.0f, visibleSize.height / 2.0f + StoreOffsetY + 144.0f));
	this->shopKeeper->setPosition(Vec2(visibleSize.width / 2.0f - 680.0f, visibleSize.height / 2.0f + StoreOffsetY - 192.0f));
	this->storeFront->setPosition(Vec2(0.0f, visibleSize.height / 2.0f + StoreOffsetY - 176.0f));

	const Vec2 StoreMenuOffset = Vec2(336.0f, -48.0f);
	const Vec2 GoldPanelOffset = Vec2(412.0f, 464.0f + 48.0f);

	this->storeNode->setPosition(Vec2(visibleSize.width / 2.0f + StoreMenuOffset.x, visibleSize.height / 2.0f + StoreMenuOffset.y));
	this->goldPanel->setPosition(GoldPanelOffset);
	this->goldIcon->setPosition(Vec2(GoldPanelOffset.x - 80.0f, GoldPanelOffset.y));
	this->goldLabel->setPosition(Vec2(GoldPanelOffset.x - 8.0f, GoldPanelOffset.y));

	this->backButton->setPosition(Vec2(visibleSize.width / 2.0f - 756.0f, visibleSize.height - 64.0f));
	this->resetButton->setPosition(Vec2(visibleSize.width / 2.0f + 320.0f, visibleSize.height - 64.0f));

	this->xorCard->setPositionX(-320.0f);
	this->inverseCard->setPositionX(320.0f);
}

ClickableNode* HexusStoreMenu::constructCard(CardData* cardData, int price, std::function<void(CardData*, int)> clickCallback)
{
	ClickableNode* cardContainer =  ClickableNode::create(UIResources::Menus_TutorialsMenu_Store_CardPanel, UIResources::Menus_TutorialsMenu_Store_CardPanelSelected);
	MenuCard* menuCard = MenuCard::create(Card::CardStyle::Earth, cardData);

	ConstantString* countString = ConstantString::create();
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

	cardContainer->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		if (clickCallback != nullptr)
		{
			clickCallback(cardData, price);
		}
	});

	menuCard->reveal();
	menuCard->disableInteraction();
	menuCard->setPosition(Vec2(0.0f, 16.0f));
	menuCard->setScale(0.8f);

	cardContainer->addChild(goldIcon);
	cardContainer->addChild(priceLabel);

	return cardContainer;
}

bool HexusStoreMenu::purchaseCard(CardData* cardData, int price)
{
	int gold = SaveManager::GetGlobalDataOrDefault(HexusStoreMenu::SaveKeyGold, Value(HexusStoreMenu::DefaultGold)).asInt();

	if (gold < price)
	{
		this->errorSound->play();
		return false;
	}

	gold -= price;
	this->purchaseSound->play();

	SaveManager::SaveGlobalData(HexusStoreMenu::SaveKeyGold, Value(gold));
	this->updateGoldText();

	return true;
}

void HexusStoreMenu::onChallengeComplete()
{
	SaveManager::SaveGlobalData(TutorialSaveKeys::SaveKeyHexEditGold, Value(true));

	this->runAction(Sequence::create(
		DelayTime::create(1.0f),
		CallFunc::create([=]()
		{
			NavigationEvents::LoadScene(NavigationEvents::LoadSceneArgs([=]() { return TutorialSelectMenu::getInstance(); }));
		}),
		nullptr
	));
}

void HexusStoreMenu::onBackClick()
{
	NavigationEvents::LoadScene(NavigationEvents::LoadSceneArgs([=]() { return TutorialSelectMenu::getInstance(); }));
}

void HexusStoreMenu::onResetClick()
{
	SaveManager::SaveGlobalData(HexusStoreMenu::SaveKeyGold, Value(HexusStoreMenu::DefaultGold));

	this->updateGoldText();
}

void HexusStoreMenu::updateGoldText()
{
	this->goldString->setString(std::to_string(SaveManager::GetGlobalDataOrDefault(HexusStoreMenu::SaveKeyGold, Value(HexusStoreMenu::DefaultGold)).asInt()));
}
