#include "HexusOpponentFrame.h"

HexusOpponentFrame* HexusOpponentFrame::create(HexusOpponentData* opponentData, std::function<void(HexusOpponentFrame*)> onMouseOver)
{
	HexusOpponentFrame* instance = new HexusOpponentFrame(opponentData, onMouseOver);

	instance->autorelease();

	return instance;
}

HexusOpponentFrame::HexusOpponentFrame(HexusOpponentData* opponentData, std::function<void(HexusOpponentFrame*)> onMouseOver)
{
	this->hexusOpponentData = opponentData;
	this->opponentSprite = AnimationNode::create(opponentData->animationResourceFile);
	this->opponentSprite->setScale(opponentData->animationScale);
	this->opponentEntity = this->opponentSprite->play("Entity");
	this->opponentEntity->setCurrentAnimation("Idle");

	this->frame = MenuSprite::create(Resources::Menus_MinigamesMenu_Hexus_EnemyFrame, Resources::Menus_MinigamesMenu_Hexus_EnemyFrameGray, Resources::Menus_MinigamesMenu_Hexus_EnemyFrameGray);

	this->setContentSize(this->frame->getContentSize());
	this->setCascadeOpacityEnabled(true);

	this->frame->setClickCallback(CC_CALLBACK_1(HexusOpponentFrame::onOpponentClick, this));

	this->addChild(this->opponentSprite);
	this->addChild(this->frame);
}

HexusOpponentFrame::~HexusOpponentFrame()
{
}

void HexusOpponentFrame::onOpponentClick(MenuSprite* HexusOpponentFrame)
{
	HexusEvents::startGame(HexusEvents::HexusGameEventArgs(this->hexusOpponentData));
}

void HexusOpponentFrame::onOpponentMouseOver(MenuSprite* HexusOpponentFrame)
{
	this->onMouseOverEvent(this);
}
