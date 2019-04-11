#include "HexusOpponentPreview.h"

#include "cocos/2d/CCClippingNode.h"
#include "cocos/2d/CCLayer.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Input/ClickableNode.h"
#include "Events/NavigationEvents.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

#include "Resources/HexusResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

HexusOpponentPreview* HexusOpponentPreview::create(HexusOpponentData* opponentData)
{
	HexusOpponentPreview* instance = new HexusOpponentPreview(opponentData);

	instance->autorelease();

	return instance;
}

HexusOpponentPreview::HexusOpponentPreview(HexusOpponentData* opponentData)
{
	this->hexusOpponentData = opponentData;
	this->opponentSprite = SmartAnimationNode::create(opponentData->animationResourceFile);
	this->disabledLayer = LayerColor::create(Color4B(0, 0, 0, 0), 512, 512);
	this->lockedSprite = Sprite::create(UIResources::Menus_Icons_Lock);

	this->frame = ClickableNode::create(HexusResources::Menus_EnemyFrame, HexusResources::Menus_EnemyFrameHover);
	this->frame->setClickSound(SoundResources::Menus_Simple_Button);

	DrawNode* clipStencil = DrawNode::create();
	Size frameSize = Size(this->frame->getContentSize().width, this->frame->getContentSize().height);
	Size clipSize = Size(frameSize.width - 52.0f, frameSize.height - 52.0f);
	clipStencil->drawSolidRect(Vec2(-clipSize.width / 2.0f, -clipSize.height / 2.0f), Vec2(clipSize.width / 2.0f, clipSize.height / 2.0f), Color4F::GREEN);

	// Enable to debug clipping:
	// this->addChild(clipStencil);

	this->frameClip = ClippingNode::create(clipStencil);
	this->frameClip->setAnchorPoint(Vec2::ZERO);

	this->opponentSprite->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->opponentSprite->setScale(opponentData->animationScale);
	this->opponentSprite->playAnimation();
	this->opponentSprite->setCascadeOpacityEnabled(false);
	this->lockedSprite->setVisible(false);

	this->setContentSize(this->frame->getContentSize());

	this->frame->setMouseClickCallback(CC_CALLBACK_0(HexusOpponentPreview::onOpponentClick, this));

	this->frameClip->addChild(Sprite::create(opponentData->backgroundResourceFile));
	this->frameClip->addChild(this->opponentSprite);
	this->frameClip->addChild(this->disabledLayer);
	this->addChild(this->frameClip);
	this->addChild(this->frame);
	this->addChild(this->lockedSprite);
}

HexusOpponentPreview::~HexusOpponentPreview()
{
}

void HexusOpponentPreview::initializePositions()
{
	super::initializePositions();

	this->disabledLayer->setPosition(Vec2(-256.0f, -256.0f));

	if (this->hexusOpponentData != nullptr)
	{
		this->opponentSprite->setPosition(this->hexusOpponentData->frameOffset);
	}

	this->lockedSprite->setPosition(Vec2(0.0f, -188.0f));
}

void HexusOpponentPreview::onOpponentClick()
{
	NavigationEvents::navigateHexus(NavigationEvents::NavigateHexusArgs(this->hexusOpponentData));
}

void HexusOpponentPreview::disableInteraction()
{
	this->frame->disableInteraction();
	this->frameClip->setOpacity(128);
	this->disabledLayer->setOpacity(196);
	this->lockedSprite->setVisible(true);
}

void HexusOpponentPreview::enableInteraction()
{
	this->frame->enableInteraction();
	this->frameClip->setOpacity(255);
	this->disabledLayer->setOpacity(0);
	this->lockedSprite->setVisible(false);
}
