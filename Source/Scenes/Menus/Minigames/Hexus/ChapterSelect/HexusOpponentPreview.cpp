#include "HexusOpponentPreview.h"

HexusOpponentPreview* HexusOpponentPreview::create(HexusOpponentData* opponentData)
{
	HexusOpponentPreview* instance = new HexusOpponentPreview(opponentData);

	instance->autorelease();

	return instance;
}

HexusOpponentPreview::HexusOpponentPreview(HexusOpponentData* opponentData)
{
	this->hexusOpponentData = opponentData;
	this->opponentSprite = AnimationNode::create(opponentData->animationResourceFile);
	this->opponentSprite->setScale(opponentData->animationScale);
	this->opponentEntity = this->opponentSprite->play("Entity");
	this->opponentEntity->setCurrentAnimation("Idle");

	this->frame = MenuSprite::create(Resources::Menus_MinigamesMenu_Hexus_EnemyFrame, Resources::Menus_MinigamesMenu_Hexus_EnemyFrameGray, Resources::Menus_MinigamesMenu_Hexus_EnemyFrameGray);

	DrawNode* clipStencil = DrawNode::create();
	Size frameSize = Size(this->frame->getContentSize().width, this->frame->getContentSize().height);
	Size clipSize = Size(frameSize.width - 48.0f, frameSize.height - 48.0f);
	clipStencil->drawSolidRect(Vec2(-clipSize.width / 2.0f, -clipSize.height / 2.0f), Vec2(clipSize.width / 2.0f, clipSize.height / 2.0f), Color4F::GREEN);

	// Enable to debug clipping:
	// this->addChild(clipStencil);

	this->frameClip = ClippingNode::create(clipStencil);
	this->frameClip->setAnchorPoint(Vec2::ZERO);

	this->setContentSize(this->frame->getContentSize());
	this->setCascadeOpacityEnabled(true);

	this->frame->setClickCallback(CC_CALLBACK_1(HexusOpponentPreview::onOpponentClick, this));
	this->frame->setCascadeOpacityEnabled(true);
	this->frameClip->setCascadeOpacityEnabled(true);

	this->frameClip->addChild(this->opponentSprite);
	this->addChild(this->frameClip);
	this->addChild(this->frame);
}

HexusOpponentPreview::~HexusOpponentPreview()
{
}

void HexusOpponentPreview::initializePositions()
{
	SmartNode::initializePositions();

	if (this->hexusOpponentData != nullptr)
	{
		this->opponentSprite->setPosition(this->hexusOpponentData->animationOffset);
	}
}

void HexusOpponentPreview::onOpponentClick(MenuSprite* HexusOpponentPreview)
{
	HexusEvents::startGame(HexusEvents::HexusGameEventArgs(this->hexusOpponentData));
}
