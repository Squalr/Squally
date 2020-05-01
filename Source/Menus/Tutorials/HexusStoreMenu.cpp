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
#include "Engine/Dialogue/SpeechBubble.h"
#include "Engine/Events/NavigationEvents.h"
#include "Engine/GlobalDirector.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Particles/SmartParticles.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/Special/Shopkeeper.h"
#include "Menus/Tutorials/TutorialSelectMenu.h"
#include "Scenes/Hexus/Menus/MenuCard.h"
#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Dialogue/EntityDialogueBehavior.h"

#include "Resources/ParticleResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

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
		UIResources::Menus_Buttons_WoodButton,
		UIResources::Menus_Buttons_WoodButtonSelected
	);

	this->chosenCardsNode = Node::create();

	this->shopKeeper->attachBehavior(EntityDialogueBehavior::create(this->shopKeeper));
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
	this->addChild(this->backButton);
	this->addChild(this->chosenCardsNode);
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
	
	this->shopKeeper->getAttachedBehavior<EntityDialogueBehavior>([=](EntityDialogueBehavior* dialogueBehavior)
	{
		dialogueBehavior->getSpeechBubble()->runDialogue(Strings::Common_Constant::create(), SoundResources::Platformer_Entities_Generic_ChatterMedium1);
	});
}

void HexusStoreMenu::initializeListeners()
{
	super::initializeListeners();

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_ESCAPE }, [=](InputEvents::InputArgs* args)
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
}

void HexusStoreMenu::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	const float storeOffsetY = -128.0f;
	const Vec2 storeMenuOffset = Vec2(336.0f, 0.0f);
	const Vec2 storeContentOffset = Vec2(0.0f, -64.0f);
	const Vec2 goldPanelOffset = Vec2(412.0f, 464.0f);

	this->dustParticles->setPosition(Vec2(visibleSize.width, visibleSize.height / 2));
	this->storeBack->setPosition(Vec2(0.0f, visibleSize.height / 2.0f + storeOffsetY + 144.0f));
	this->shopKeeper->setPosition(Vec2(visibleSize.width / 2.0f - 680.0f, visibleSize.height / 2.0f + storeOffsetY - 192.0f));
	this->storeFront->setPosition(Vec2(0.0f, visibleSize.height / 2.0f + storeOffsetY - 176.0f));
	this->storeMenu->setPosition(Vec2(visibleSize.width / 2.0f + storeMenuOffset.x, visibleSize.height / 2.0f + storeMenuOffset.y - 48.0f));

	this->goldPanel->setPosition(Vec2(visibleSize.width / 2.0f + storeMenuOffset.x + goldPanelOffset.x, visibleSize.height / 2.0f + storeMenuOffset.y + goldPanelOffset.y));
	this->goldIcon->setPosition(Vec2(visibleSize.width / 2.0f + storeMenuOffset.x + goldPanelOffset.x - 80.0f, visibleSize.height / 2.0f + storeMenuOffset.y + goldPanelOffset.y));
	this->goldLabel->setPosition(Vec2(visibleSize.width / 2.0f + storeMenuOffset.x + goldPanelOffset.x - 8.0f, visibleSize.height / 2.0f + storeMenuOffset.y + goldPanelOffset.y));

	this->backButton->setPosition(Vec2(visibleSize.width / 2.0f - 756.0f, visibleSize.height - 64.0f));
}

std::tuple<ClickableNode*, MenuCard*, int> HexusStoreMenu::constructCard(CardData* cardData)
{
	ClickableNode* cardContainer =  ClickableNode::create(UIResources::Menus_TutorialsMenu_Store_CardPanel, UIResources::Menus_TutorialsMenu_Store_CardPanelSelected);
	MenuCard* menuCard = MenuCard::create(Card::CardStyle::Earth, cardData);
	int price = 444;

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

	menuCard->reveal();
	menuCard->disableInteraction();
	menuCard->setPosition(Vec2(0.0f, 16.0f));
	menuCard->setScale(0.8f);

	cardContainer->setMouseClickCallback(CC_CALLBACK_0(HexusStoreMenu::onCardClick, this, cardData, price, countString));

	cardContainer->addChild(goldIcon);
	cardContainer->addChild(priceLabel);

	return std::tuple<ClickableNode*, MenuCard*, int>(cardContainer, menuCard, price);
}

void HexusStoreMenu::onCardClick(CardData* cardData, int price, ConstantString* countString)
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
}

void HexusStoreMenu::onBackClick()
{
	NavigationEvents::LoadScene(NavigationEvents::LoadSceneArgs([=]() { return TutorialSelectMenu::getInstance(); }));
}

void HexusStoreMenu::updateGoldText()
{
	this->goldString->setString(std::to_string(11111));
}
