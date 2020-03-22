#include "Hexus.h"

#include "cocos/2d/CCLayer.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCEventListenerKeyboard.h"

#include "Engine/Events/NavigationEvents.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/GlobalDirector.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Sound/Music.h"
#include "Engine/Sound/MusicPlayer.h"
#include "Engine/UI/UIBoundObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/HexusEvents.h"
#include "Menus/Confirmation/ConfirmationMenu.h"
#include "Menus/Options/OptionsMenu.h"
#include "Menus/Pause/PauseMenu.h"
#include "Music/Tracks/Medieval.h"
#include "Music/Tracks/Medieval2.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/CardRow.h"
#include "Scenes/Hexus/Config.h"
#include "Scenes/Hexus/Deck.h"
#include "Scenes/Hexus/GameState.h"
#include "Scenes/Hexus/Components/Components.h"
#include "Scenes/Hexus/HelpMenus/HelpMenu.h"
#include "Scenes/Hexus/States/States.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Items/EntityInventoryBehavior.h"
#include "Scenes/Platformer/Inventory/EquipmentInventory.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Title/TitleScreen.h"

#include "Resources/HexusResources.h"
#include "Resources/MusicResources.h"

using namespace cocos2d;

Hexus* Hexus::instance = nullptr;

Hexus* Hexus::create()
{
	Hexus* instance = new Hexus();
	
	instance->autorelease();

	return instance;
}

Hexus::Hexus()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	this->gameBackground = Sprite::create(HexusResources::Gameboard);
	this->gameState = GameState::create();
	this->avatars = Avatars::create();
	this->cardReplaceBanner = CardReplaceBanner::create();
	this->opponentFirstBanner = OpponentFirstBanner::create();
	this->opponentLastStandBanner = OpponentLastStandBanner::create();
	this->opponentPassBanner = OpponentPassBanner::create();
	this->opponentRoundWinBanner = OpponentRoundWinBanner::create();
	this->opponentTurnBanner = OpponentTurnBanner::create();
	this->playerFirstBanner = PlayerFirstBanner::create();
	this->playerLastStandBanner = PlayerLastStandBanner::create();
	this->playerPassBanner = PlayerPassBanner::create();
	this->playerRoundWinBanner = PlayerRoundWinBanner::create();
	this->playerTurnBanner = PlayerTurnBanner::create();
	this->roundBanner = RoundBanner::create();
	this->roundTieBanner = RoundTieBanner::create();
	this->victoryBanner = VictoryBanner::create();
	this->defeatBanner = DefeatBanner::create();
	this->drawBanner = DrawBanner::create();
	this->cardPreviewComponent = CardPreviewComponent::create();
	this->stagingHelperText = StagingHelperText::create();
	this->assemblyHelpText = AssemblyHelpText::create();
	this->stateAIDecideCard = StateAIDecideCard::create();
	this->stateAIDecideCardReplace = StateAIDecideCardReplace::create();
	this->stateAIDecidePass = StateAIDecidePass::create();
	this->stateAIDecideTarget = StateAIDecideTarget::create();
	this->stateCardReplace = StateCardReplace::create();
	this->statePeekCards = StatePeekCards::create();
	this->stateCoinFlip = StateCoinFlip::create();
	this->stateSourceCardStaged = StateSourceCardStaged::create();
	this->stateDraw = StateDraw::create();
	this->stateDrawInitial = StateDrawInitial::create();
	this->stateGameEnd = StateGameEnd::create();
	this->stateGameExit = StateGameExit::create();
	this->stateGameStart = StateGameStart::create();
	this->stateLoadInitialState = StateLoadInitialState::create();
	this->stateNeutral = StateNeutral::create();
	this->stateOpponentTurnStart = StateOpponentTurnStart::create();
	this->statePass = StatePass::create();
	this->statePlayCard = StatePlayCard::create();
	this->statePlayerTurnStart = StatePlayerTurnStart::create();
	this->stateRoundEnd = StateRoundEnd::create();
	this->stateRoundStart = StateRoundStart::create();
	this->stateHandCardStaged = StateHandCardStaged::create();
	this->stateTurnEnd = StateTurnEnd::create();
	this->stateTutorial = StateTutorial::create();
	this->boardSelection = ClickableNode::create(HexusResources::BoardSelection, HexusResources::BoardSelection);
	this->deckCardCountDisplay = DeckCardCountDisplay::create();
	this->handCardCountDisplay = HandCardCountDisplay::create();
	this->drawCountDisplay = DrawCountDisplay::create();
	this->remainingCardDisplay = RemainingCardDisplay::create();
	this->lossesDisplay = LossesDisplay::create();
	this->rowTotals = RowTotals::create();
	this->scoreTotal = ScoreTotal::create();
	this->debugDisplay = DebugDisplay::create();
	this->tutorialLayer = Node::create();
	this->relocateLayer = Node::create();
	this->helpMenu = HelpMenu::create();
	this->menuBackDrop = LayerColor::create(Color4B(0, 0, 0, 0), visibleSize.width, visibleSize.height);
	this->musicA = Medieval::create();
	this->musicB = Medieval2::create();

	// Set up node pointers to be focused in tutorials -- a little hacky but avoids a cyclic dependency / refactor
	this->gameState->boardSelection = this->boardSelection;
	this->gameState->lossesDisplayPointer = this->lossesDisplay;
	this->gameState->playerBinaryRowTotalPointer = this->rowTotals->playerBinaryTotalSocket;
	this->gameState->playerDecimalRowTotalPointer = this->rowTotals->playerDecimalTotalSocket;
	this->gameState->playerHexRowTotalPointer = this->rowTotals->playerHexTotalSocket;
	this->gameState->enemyBinaryRowTotalPointer = this->rowTotals->enemyBinaryTotalSocket;
	this->gameState->enemyDecimalRowTotalPointer = this->rowTotals->enemyDecimalTotalSocket;
	this->gameState->enemyHexRowTotalPointer = this->rowTotals->enemyHexTotalSocket;
	this->gameState->scoreTotalPointer = this->scoreTotal;
	this->gameState->deckCardCountDisplayPointer = this->deckCardCountDisplay;
	this->gameState->handCardCountDisplayPointer = this->handCardCountDisplay;
	this->gameState->remainingCardDisplayPointer = this->remainingCardDisplay;
	this->gameState->drawCountDisplayPointer = this->drawCountDisplay;
	this->gameState->passButtonPointer = this->statePass->passButton;
	this->gameState->lastStandButtonPointer = this->statePass->lastStandButton;
	this->gameState->claimVictoryButtonPointer = this->statePass->claimVictoryButton;

	this->addChild(this->gameBackground);
	this->addChild(this->boardSelection);
	this->addChild(this->avatars);
	this->addChild(this->cardPreviewComponent);
	this->addChild(this->stagingHelperText);
	this->addChild(this->assemblyHelpText);
	this->addChild(this->lossesDisplay);
	this->addChild(this->deckCardCountDisplay);
	this->addChild(this->handCardCountDisplay);
	this->addChild(this->remainingCardDisplay);
	this->addChild(this->drawCountDisplay);
	this->addChild(this->rowTotals);
	this->addChild(this->scoreTotal);
	this->addChild(this->gameState);
	this->addChild(this->relocateLayer);
	this->addChild(this->stateAIDecideCard);
	this->addChild(this->stateAIDecideCardReplace);
	this->addChild(this->stateAIDecidePass);
	this->addChild(this->stateAIDecideTarget);
	this->addChild(this->stateCardReplace);
	this->addChild(this->statePeekCards);
	this->addChild(this->stateCoinFlip);
	this->addChild(this->stateSourceCardStaged);
	this->addChild(this->stateDraw);
	this->addChild(this->stateDrawInitial);
	this->addChild(this->stateGameEnd);
	this->addChild(this->stateGameExit);
	this->addChild(this->stateGameStart);
	this->addChild(this->stateLoadInitialState);
	this->addChild(this->stateNeutral);
	this->addChild(this->stateOpponentTurnStart);
	this->addChild(this->statePass);
	this->addChild(this->statePlayCard);
	this->addChild(this->statePlayerTurnStart);
	this->addChild(this->stateRoundEnd);
	this->addChild(this->stateRoundStart);
	this->addChild(this->stateHandCardStaged);
	this->addChild(this->stateTurnEnd);
	this->addChild(this->stateTutorial);
	this->addChild(this->debugDisplay);
	this->addChild(this->tutorialLayer);
	this->addChild(this->cardReplaceBanner);
	this->addChild(this->opponentFirstBanner);
	this->addChild(this->opponentLastStandBanner);
	this->addChild(this->opponentPassBanner);
	this->addChild(this->opponentRoundWinBanner);
	this->addChild(this->opponentTurnBanner);
	this->addChild(this->playerFirstBanner);
	this->addChild(this->playerLastStandBanner);
	this->addChild(this->playerPassBanner);
	this->addChild(this->playerRoundWinBanner);
	this->addChild(this->playerTurnBanner);
	this->addChild(this->roundBanner);
	this->addChild(this->roundTieBanner);
	this->addChild(this->victoryBanner);
	this->addChild(this->defeatBanner);
	this->addChild(this->drawBanner);
	this->addChild(this->menuBackDrop);
	this->addChild(this->helpMenu);
	this->addChild(this->musicA);
	this->addChild(this->musicB);
}

Hexus::~Hexus()
{
}

void Hexus::onEnter()
{
	super::onEnter();

	this->setVisible(false);
}

void Hexus::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->gameBackground->setPosition(visibleSize.width / 2.0f, visibleSize.height / 2.0f);
	this->boardSelection->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f + Config::boardCenterOffsetY);
}

void Hexus::initializeListeners()
{
	super::initializeListeners();

	this->cardPreviewComponent->setHelpClickCallback([=](CardData* cardData)
	{
		this->menuBackDrop->setOpacity(196);
		this->helpMenu->openMenu(cardData);
		GameUtils::focus(this->helpMenu);
	});

	this->helpMenu->setExitCallback([=]()
	{
		this->menuBackDrop->setOpacity(0);
		this->helpMenu->setVisible(false);
		GameUtils::focus(this);
	});

	this->addEventListenerIgnorePause(EventListenerCustom::create(HexusEvents::EventExitHexus, [=](EventCustom* eventCustom)
	{
		HexusEvents::HexusExitArgs* args = static_cast<HexusEvents::HexusExitArgs*>(eventCustom->getUserData());

		if (args != nullptr)
		{
			this->musicA->pop();
			this->musicB->pop();
		}
	}));
}

void Hexus::open(HexusOpponentData* opponentData)
{
	if (this->gameState->opponentData != nullptr)
	{
		this->removeChild(this->gameState->opponentData);
	}
	
	this->gameState->opponentData = opponentData;

	if (this->gameState->opponentData == nullptr)
	{
		return;
	}
	
	this->addChild(this->gameState->opponentData);

	this->relocateLayer->removeAllChildren();
	this->tutorialLayer->removeAllChildren();

	for (auto next : opponentData->tutorials)
	{
		this->tutorialLayer->addChild(next);
	}

	this->gameState->previousStateType = GameState::StateType::EmptyState;
	this->gameState->stateType = GameState::StateType::EmptyState;

	this->avatars->initializeEnemyAvatar(opponentData);

	this->gameState->playerBinaryCards->clear();
	this->gameState->playerDecimalCards->clear();
	this->gameState->playerHexCards->clear();

	this->gameState->enemyBinaryCards->clear();
	this->gameState->enemyDecimalCards->clear();
	this->gameState->enemyHexCards->clear();

	this->gameState->playerGraveyard->clear();
	this->gameState->enemyGraveyard->clear();
	this->gameState->playerHand->clear();
	this->gameState->enemyHand->clear();
	this->gameState->playerDeck->clear();
	this->gameState->enemyDeck->clear();

	if (opponentData->stateOverride == nullptr)
	{
		this->buildEnemyDeck(opponentData);
		this->buildPlayerDeck();
	}

	GameState::updateState(this->gameState, GameState::StateType::GameStart);
	this->setVisible(true);

	if (RandomHelper::random_real(0.0f, 1.0f) < 0.5f)
	{
		this->musicA->push();
	}
	else
	{
		this->musicB->push();
	}
}

void Hexus::buildEnemyDeck(HexusOpponentData* opponentData)
{
	std::vector<CardData*> enemyCards = opponentData->getDeck();

	this->gameState->enemyDeck->style = opponentData->cardStyle;

	for (auto card : enemyCards)
	{
		this->gameState->enemyDeck->insertCardRandom(Card::create(opponentData->cardStyle, card, false), false, 0.0f, false);
	}
}

void Hexus::buildPlayerDeck()
{
	ObjectEvents::watchForObject<Squally>(this, [=](Squally* squally)
	{
		squally->watchForAttachedBehavior<EntityInventoryBehavior>([&](EntityInventoryBehavior* entityInventoryBehavior)
		{
			EquipmentInventory* equipmentInventory = entityInventoryBehavior->getEquipmentInventory();
			std::vector<CardData*> cardData = std::vector<CardData*>();
			std::vector<HexusCard*> cards = equipmentInventory->getHexusCards();
			std::map<std::string, CardData*> cardList = CardList::getInstance()->cardListByName;

			for (auto it = cards.begin(); it != cards.end(); it++)
			{
				std::string key = (*it)->getCardKey();

				if (cardList.find(key) != cardList.end())
				{
					cardData.push_back(cardList[key]);
				}
			}

			this->gameState->playerDeck->style = Card::CardStyle::Earth;

			for (auto it = cardData.begin(); it != cardData.end(); it++)
			{
				this->gameState->playerDeck->insertCardRandom(Card::create(Card::CardStyle::Earth, (*it), true), false, 0.0f, false);
			}
		});
	}, Squally::MapKey);
}
