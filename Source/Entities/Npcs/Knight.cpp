#include "Knight.h"

Knight* Knight::create()
{
	Knight* knight = new Knight();

	knight->autorelease();

	return knight;
}

Knight::Knight() : NpcBase::NpcBase()
{
	this->actualJumpLaunchVelocity = 640.0f;
	this->actualGravityAcceleration = 1000.0f;
	this->actualMaxFallSpeed = 600.0f;
	this->moveAcceleration = 3000.0f;

	this->movement.x = 0.0f;
	this->movement.y = 0.0f;

	this->spriteNode = Node::create();
	this->knightSprite = Sprite::create(Resources::Ingame_Sprites_Knight_KnightStanding);

	this->init(PhysicsBody::createBox(this->knightSprite->getContentSize()), CategoryGroup::G_Npc, true, false);

	this->spriteNode->addChild(this->knightSprite);
	this->addChild(this->spriteNode);
}

Knight::~Knight()
{
	this->deck->release();
}

void Knight::initializeCardData()
{
	this->deck = Deck::create(Card::CardStyle::Shadow, new std::vector<CardData*>({
		CardData::cardListByName.at(CardData::Binary0),
		CardData::cardListByName.at(CardData::Binary1),
		CardData::cardListByName.at(CardData::Binary2),
		CardData::cardListByName.at(CardData::Decimal0),
		CardData::cardListByName.at(CardData::Decimal1),
		CardData::cardListByName.at(CardData::Decimal2),
		CardData::cardListByName.at(CardData::Hex0),
		CardData::cardListByName.at(CardData::Hex1),
		CardData::cardListByName.at(CardData::Hex2),
		CardData::cardListByName.at(CardData::ShiftLeft),
		CardData::cardListByName.at(CardData::ShiftRight),
		CardData::cardListByName.at(CardData::LogicalAnd),
		CardData::cardListByName.at(CardData::LogicalOr),
		CardData::cardListByName.at(CardData::LogicalXor),
		}));

	this->deck->retain();
}

void Knight::update(float dt)
{
	NpcBase::update(dt);
}
