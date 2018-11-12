#include "HexusOpponentPreview.h"

HexusOpponentPreview* HexusOpponentPreview::create(HexusOpponentData* opponentData, std::function<void(HexusEvents::HexusGameResultEventArgs)> onGameEndCallback)
{
	HexusOpponentPreview* instance = new HexusOpponentPreview(opponentData, onGameEndCallback);

	instance->autorelease();

	return instance;
}

HexusOpponentPreview::HexusOpponentPreview(HexusOpponentData* opponentData, std::function<void(HexusEvents::HexusGameResultEventArgs)> onGameEndCallback)
{
	this->hexusOpponentData = opponentData;
	this->onGameEndCallback = onGameEndCallback;
	this->opponentSprite = AnimationNode::create(opponentData->animationResourceFile);
	this->opponentSprite->setScale(opponentData->animationScale);
	this->opponentEntity = this->opponentSprite->play("Entity");
	this->opponentEntity->setCurrentAnimation("Idle");
	this->disabledLayer = LayerColor::create(Color4B(0, 0, 0, 0), 512, 512);

	this->frame = MenuSprite::create(Resources::Menus_MinigamesMenu_Hexus_EnemyFrame, Resources::Menus_MinigamesMenu_Hexus_EnemyFrameHover);
	this->frame->setClickSound(Resources::Sounds_Menus_Simple_Button);

	DrawNode* clipStencil = DrawNode::create();
	Size frameSize = Size(this->frame->getContentSize().width, this->frame->getContentSize().height);
	Size clipSize = Size(frameSize.width - 48.0f, frameSize.height - 48.0f);
	clipStencil->drawSolidRect(Vec2(-clipSize.width / 2.0f, -clipSize.height / 2.0f), Vec2(clipSize.width / 2.0f, clipSize.height / 2.0f), Color4F::GREEN);

	// Enable to debug clipping:
	// this->addChild(clipStencil);

	this->frameClip = ClippingNode::create(clipStencil);
	this->frameClip->setAnchorPoint(Vec2::ZERO);

	this->opponentSprite->setCascadeOpacityEnabled(false);

	this->setContentSize(this->frame->getContentSize());

	this->frame->setClickCallback(CC_CALLBACK_1(HexusOpponentPreview::onOpponentClick, this));

	this->frameClip->addChild(Sprite::create(opponentData->backgroundResourceFile));
	this->frameClip->addChild(this->opponentSprite);
	this->frameClip->addChild(this->disabledLayer);
	this->addChild(this->frameClip);
	this->addChild(this->frame);
}

HexusOpponentPreview::~HexusOpponentPreview()
{
}

void HexusOpponentPreview::initializePositions()
{
	SmartNode::initializePositions();

	this->disabledLayer->setPosition(Vec2(-256.0f, -256.0f));

	if (this->hexusOpponentData != nullptr)
	{
		this->opponentSprite->setPosition(this->hexusOpponentData->animationOffset);
	}
}

void HexusOpponentPreview::onOpponentClick(MenuSprite* HexusOpponentPreview)
{
	HexusEvents::startGame(HexusEvents::HexusGameEventArgs(this->hexusOpponentData, this->onGameEndCallback));
}

void HexusOpponentPreview::disableInteraction()
{
	this->frame->disableInteraction();
	this->frameClip->setOpacity(128);
	this->disabledLayer->setOpacity(196);
}

void HexusOpponentPreview::enableInteraction()
{
	this->frame->enableInteraction();
	this->frameClip->setOpacity(255);
	this->disabledLayer->setOpacity(0);
}

