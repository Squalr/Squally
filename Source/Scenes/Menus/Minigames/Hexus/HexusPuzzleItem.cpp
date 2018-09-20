#include "HexusPuzzleItem.h"

HexusPuzzleItem* HexusPuzzleItem::create(std::string description, std::string mapFile, int index, std::function<void(HexusPuzzleItem*)> onMouseOver)
{
	HexusPuzzleItem* instance = new HexusPuzzleItem(description, mapFile, index, onMouseOver);

	instance->autorelease();

	return instance;
}

HexusPuzzleItem::HexusPuzzleItem(std::string description, std::string mapFile, int index, std::function<void(HexusPuzzleItem*)> onMouseOver)
{
	this->tutorialMapFile = mapFile;
	this->tutorialDescription = description;
	this->onMouseOverEvent = onMouseOver;
	this->levelIndex = index;
	this->page = index / HexusPuzzleItem::MaxEntriesPerPage;

	this->frame = Sprite::create(Resources::Menus_TutorialMenu_TutorialEntry);
	this->indexLabel = Label::create(std::to_string(index + 1), Localization::getMainFont(), 28.0f);

	// TODO: Load save data (steam cloud)
	this->isLevelComplete = true;

	if (this->isLevelComplete)
	{
		this->startButton = MenuSprite::create(
			Resources::Menus_TutorialMenu_TutorialEntryComplete,
			Resources::Menus_TutorialMenu_TutorialEntryCompleteSelected,
			Resources::Menus_TutorialMenu_TutorialEntryCompleteSelected);
	}
	else
	{
		this->startButton = MenuSprite::create(
			Resources::Menus_TutorialMenu_TutorialEntry,
			Resources::Menus_TutorialMenu_TutorialEntrySelected,
			Resources::Menus_TutorialMenu_TutorialEntrySelected);
	}

	this->startButton->setClickCallback(CC_CALLBACK_1(HexusPuzzleItem::onTutorialClick, this));
	this->startButton->setMouseOverCallback(CC_CALLBACK_1(HexusPuzzleItem::onTutorialMouseOver, this));
	this->setContentSize(this->frame->getContentSize());
	this->setCascadeOpacityEnabled(true);

	this->addChild(this->frame);
	this->addChild(this->startButton);
	this->addChild(this->indexLabel);
}

HexusPuzzleItem::~HexusPuzzleItem()
{
}

void HexusPuzzleItem::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// Adjust index to be relative to the current page
	int orderIndex = this->levelIndex % HexusPuzzleItem::MaxEntriesPerPage;

	// Set position based on order index
	Vec2 position = Vec2(
		origin.x + visibleSize.width / 2 - 272.0f + (orderIndex % HexusPuzzleItem::MaxEntriesPerRow) * 136.0f,
		origin.y + visibleSize.height / 2 + 104.0f + ((orderIndex / HexusPuzzleItem::MaxEntriesPerRow) * -160.0f)
	);

	this->frame->setPosition(position);
	this->startButton->setPosition(Vec2(position.x + this->frame->getContentSize().width / 2 - this->startButton->getContentSize().width / 2, position.y));
	this->indexLabel->setPosition(Vec2(position.x + this->frame->getContentSize().width / 2 - this->startButton->getContentSize().width / 2, position.y + 20));
}

void HexusPuzzleItem::onTutorialClick(MenuSprite* HexusPuzzleItem)
{
	Deck* deck1 = Deck::create(Card::CardStyle::Earth, new std::vector<CardData*>({
			CardList::getInstance()->cardListByName->at(CardList::Binary0),
			CardList::getInstance()->cardListByName->at(CardList::Binary1),
			CardList::getInstance()->cardListByName->at(CardList::Binary2),
			CardList::getInstance()->cardListByName->at(CardList::Binary3),
			CardList::getInstance()->cardListByName->at(CardList::Binary4),
			CardList::getInstance()->cardListByName->at(CardList::Binary5),
			CardList::getInstance()->cardListByName->at(CardList::Binary6),
			CardList::getInstance()->cardListByName->at(CardList::Binary7),
			CardList::getInstance()->cardListByName->at(CardList::Binary8),
			CardList::getInstance()->cardListByName->at(CardList::Binary9),
			CardList::getInstance()->cardListByName->at(CardList::Binary10),
			CardList::getInstance()->cardListByName->at(CardList::Binary11),
			CardList::getInstance()->cardListByName->at(CardList::Binary12),
			CardList::getInstance()->cardListByName->at(CardList::Binary13),
			CardList::getInstance()->cardListByName->at(CardList::Binary14),
			CardList::getInstance()->cardListByName->at(CardList::Binary15),
			CardList::getInstance()->cardListByName->at(CardList::Decimal0),
			CardList::getInstance()->cardListByName->at(CardList::Decimal1),
			CardList::getInstance()->cardListByName->at(CardList::Decimal2),
			CardList::getInstance()->cardListByName->at(CardList::Decimal3),
			CardList::getInstance()->cardListByName->at(CardList::Decimal4),
			CardList::getInstance()->cardListByName->at(CardList::Decimal5),
			CardList::getInstance()->cardListByName->at(CardList::Decimal6),
			CardList::getInstance()->cardListByName->at(CardList::Decimal7),
			CardList::getInstance()->cardListByName->at(CardList::Decimal8),
			CardList::getInstance()->cardListByName->at(CardList::Decimal9),
			CardList::getInstance()->cardListByName->at(CardList::Decimal10),
			CardList::getInstance()->cardListByName->at(CardList::Decimal11),
			CardList::getInstance()->cardListByName->at(CardList::Decimal12),
			CardList::getInstance()->cardListByName->at(CardList::Decimal13),
			CardList::getInstance()->cardListByName->at(CardList::Decimal14),
			CardList::getInstance()->cardListByName->at(CardList::Decimal15),
			CardList::getInstance()->cardListByName->at(CardList::Hex0),
			CardList::getInstance()->cardListByName->at(CardList::Hex1),
			CardList::getInstance()->cardListByName->at(CardList::Hex2),
			CardList::getInstance()->cardListByName->at(CardList::Hex3),
			CardList::getInstance()->cardListByName->at(CardList::Hex4),
			CardList::getInstance()->cardListByName->at(CardList::Hex5),
			CardList::getInstance()->cardListByName->at(CardList::Hex6),
			CardList::getInstance()->cardListByName->at(CardList::Hex7),
			CardList::getInstance()->cardListByName->at(CardList::Hex8),
			CardList::getInstance()->cardListByName->at(CardList::Hex9),
			CardList::getInstance()->cardListByName->at(CardList::Hex10),
			CardList::getInstance()->cardListByName->at(CardList::Hex11),
			CardList::getInstance()->cardListByName->at(CardList::Hex12),
			CardList::getInstance()->cardListByName->at(CardList::Hex13),
			CardList::getInstance()->cardListByName->at(CardList::Hex14),
			CardList::getInstance()->cardListByName->at(CardList::Hex15),
			CardList::getInstance()->cardListByName->at(CardList::ShiftLeft),
			CardList::getInstance()->cardListByName->at(CardList::ShiftRight),
			CardList::getInstance()->cardListByName->at(CardList::LogicalAnd),
			CardList::getInstance()->cardListByName->at(CardList::LogicalOr),
			CardList::getInstance()->cardListByName->at(CardList::LogicalXor),
			CardList::getInstance()->cardListByName->at(CardList::ShiftLeft),
			CardList::getInstance()->cardListByName->at(CardList::ShiftRight),
			CardList::getInstance()->cardListByName->at(CardList::Flip1),
			CardList::getInstance()->cardListByName->at(CardList::Flip2),
			CardList::getInstance()->cardListByName->at(CardList::Flip3),
			CardList::getInstance()->cardListByName->at(CardList::Flip4),
			CardList::getInstance()->cardListByName->at(CardList::Inverse),
			CardList::getInstance()->cardListByName->at(CardList::Inverse),
			CardList::getInstance()->cardListByName->at(CardList::Inverse),
			CardList::getInstance()->cardListByName->at(CardList::Addition),
			CardList::getInstance()->cardListByName->at(CardList::Subtraction),
		}));

	deck1->retain();

	Deck* deck2 = Deck::create(Card::CardStyle::Earth, new std::vector<CardData*>({
			CardList::getInstance()->cardListByName->at(CardList::Binary0),
			CardList::getInstance()->cardListByName->at(CardList::Binary1),
			CardList::getInstance()->cardListByName->at(CardList::Binary2),
			CardList::getInstance()->cardListByName->at(CardList::Binary3),
			CardList::getInstance()->cardListByName->at(CardList::Binary4),
			CardList::getInstance()->cardListByName->at(CardList::Binary5),
			CardList::getInstance()->cardListByName->at(CardList::Binary6),
			CardList::getInstance()->cardListByName->at(CardList::Binary7),
			CardList::getInstance()->cardListByName->at(CardList::Binary8),
			CardList::getInstance()->cardListByName->at(CardList::Binary9),
			CardList::getInstance()->cardListByName->at(CardList::Binary10),
			CardList::getInstance()->cardListByName->at(CardList::Binary11),
			CardList::getInstance()->cardListByName->at(CardList::Binary12),
			CardList::getInstance()->cardListByName->at(CardList::Binary13),
			CardList::getInstance()->cardListByName->at(CardList::Binary14),
			CardList::getInstance()->cardListByName->at(CardList::Binary15),
			CardList::getInstance()->cardListByName->at(CardList::Decimal0),
			CardList::getInstance()->cardListByName->at(CardList::Decimal1),
			CardList::getInstance()->cardListByName->at(CardList::Decimal2),
			CardList::getInstance()->cardListByName->at(CardList::Decimal3),
			CardList::getInstance()->cardListByName->at(CardList::Decimal4),
			CardList::getInstance()->cardListByName->at(CardList::Decimal5),
			CardList::getInstance()->cardListByName->at(CardList::Decimal6),
			CardList::getInstance()->cardListByName->at(CardList::Decimal7),
			CardList::getInstance()->cardListByName->at(CardList::Decimal8),
			CardList::getInstance()->cardListByName->at(CardList::Decimal9),
			CardList::getInstance()->cardListByName->at(CardList::Decimal10),
			CardList::getInstance()->cardListByName->at(CardList::Decimal11),
			CardList::getInstance()->cardListByName->at(CardList::Decimal12),
			CardList::getInstance()->cardListByName->at(CardList::Decimal13),
			CardList::getInstance()->cardListByName->at(CardList::Decimal14),
			CardList::getInstance()->cardListByName->at(CardList::Decimal15),
			CardList::getInstance()->cardListByName->at(CardList::Hex0),
			CardList::getInstance()->cardListByName->at(CardList::Hex1),
			CardList::getInstance()->cardListByName->at(CardList::Hex2),
			CardList::getInstance()->cardListByName->at(CardList::Hex3),
			CardList::getInstance()->cardListByName->at(CardList::Hex4),
			CardList::getInstance()->cardListByName->at(CardList::Hex5),
			CardList::getInstance()->cardListByName->at(CardList::Hex6),
			CardList::getInstance()->cardListByName->at(CardList::Hex7),
			CardList::getInstance()->cardListByName->at(CardList::Hex8),
			CardList::getInstance()->cardListByName->at(CardList::Hex9),
			CardList::getInstance()->cardListByName->at(CardList::Hex10),
			CardList::getInstance()->cardListByName->at(CardList::Hex11),
			CardList::getInstance()->cardListByName->at(CardList::Hex12),
			CardList::getInstance()->cardListByName->at(CardList::Hex13),
			CardList::getInstance()->cardListByName->at(CardList::Hex14),
			CardList::getInstance()->cardListByName->at(CardList::Hex15),
			CardList::getInstance()->cardListByName->at(CardList::ShiftLeft),
			CardList::getInstance()->cardListByName->at(CardList::ShiftRight),
			CardList::getInstance()->cardListByName->at(CardList::LogicalAnd),
			CardList::getInstance()->cardListByName->at(CardList::LogicalOr),
			CardList::getInstance()->cardListByName->at(CardList::LogicalXor),
			CardList::getInstance()->cardListByName->at(CardList::ShiftLeft),
			CardList::getInstance()->cardListByName->at(CardList::ShiftRight),
			CardList::getInstance()->cardListByName->at(CardList::Flip1),
			CardList::getInstance()->cardListByName->at(CardList::Flip2),
			CardList::getInstance()->cardListByName->at(CardList::Flip3),
			CardList::getInstance()->cardListByName->at(CardList::Flip4),
			CardList::getInstance()->cardListByName->at(CardList::Inverse),
			CardList::getInstance()->cardListByName->at(CardList::Inverse),
			CardList::getInstance()->cardListByName->at(CardList::Inverse),
			CardList::getInstance()->cardListByName->at(CardList::Addition),
			CardList::getInstance()->cardListByName->at(CardList::Subtraction),
		}));

	deck2->retain();

	HexusEvents::startGame(HexusEvents::HexusGameEventArgs(deck1, deck2));
}

void HexusPuzzleItem::onTutorialMouseOver(MenuSprite* HexusPuzzleItem)
{
	this->onMouseOverEvent(this);
}
