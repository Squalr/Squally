#include "CrusherGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/UI/SmartClippingNode.h"

#include "Resources/EntityResources.h"
#include "Resources/ObjectResources.h"

using namespace cocos2d;

const float CrusherGenericPreview::TravelDistance = 600.0f;

CrusherGenericPreview* CrusherGenericPreview::create()
{
	CrusherGenericPreview* instance = new CrusherGenericPreview();

	instance->autorelease();

	return instance;
}

CrusherGenericPreview::CrusherGenericPreview()
{
	this->base = Sprite::create(ObjectResources::Traps_SpikedCrusher_Base);
	this->pole = Sprite::create(ObjectResources::Traps_SpikedCrusher_Pole);
	this->crusher = Sprite::create(ObjectResources::Traps_SpikedCrusher_HeadJagged);
	this->poleClip = SmartClippingNode::create(this->pole, CSize(this->pole->getContentSize().width, CrusherGenericPreview::TravelDistance - 180.0f));
	
	this->base->setAnchorPoint(Vec2(0.5f, 1.0f));
	this->base->setFlippedY(true);
	this->crusher->setFlippedY(true);
	
	// Create parameters to repeat the texture
	Texture2D::TexParams params = Texture2D::TexParams();
	params.minFilter = GL_LINEAR;
	params.magFilter = GL_LINEAR;
	params.wrapT = GL_REPEAT;
	this->pole->setTextureRect(CRect(0.0f, 0.0f, this->pole->getContentSize().width, CrusherGenericPreview::TravelDistance));
	
	if (this->pole->getTexture() != nullptr)
	{
		this->pole->getTexture()->setTexParameters(params);
	}

	this->poleClip->setScale(0.33f);
	this->base->setScale(0.33f);
	this->crusher->setScale(0.33f);

	this->previewNode->addChild(this->poleClip);
	this->previewNode->addChild(this->base);
	this->previewNode->addChild(this->crusher);
}

CrusherGenericPreview::~CrusherGenericPreview()
{
}

HackablePreview* CrusherGenericPreview::clone()
{
	return CrusherGenericPreview::create();
}

void CrusherGenericPreview::onEnter()
{
	super::onEnter();

	const float speed = 1.5f;
	const float offset = 48.0f;
	const float topOffset = 48.0f;

	this->crusher->setPosition(Vec2(0.0f, HackablePreview::PreviewRadius - offset - topOffset));
	this->poleClip->setPositionY(48.0f);
	this->base->setPositionY(HackablePreview::PreviewRadius - offset + 12.0f);

	this->crusher->runAction(
		RepeatForever::create(Sequence::create(
			EaseSineInOut::create(MoveTo::create(speed, Vec2(this->crusher->getPositionX(), -(HackablePreview::PreviewRadius - offset) / 2.0f))),
			EaseSineInOut::create(MoveTo::create(speed, Vec2(this->crusher->getPositionX(), HackablePreview::PreviewRadius - offset - topOffset))),
			nullptr
		))
	);
	this->pole->runAction(
		RepeatForever::create(Sequence::create(
			EaseSineInOut::create(MoveTo::create(speed, Vec2(this->pole->getPositionX(), -(HackablePreview::PreviewRadius - offset) / 2.0f))),
			EaseSineInOut::create(MoveTo::create(speed, Vec2(this->pole->getPositionX(), HackablePreview::PreviewRadius - offset - topOffset))),
			nullptr
		))
	);

}

void CrusherGenericPreview::initializePositions()
{
	super::initializePositions();
}
