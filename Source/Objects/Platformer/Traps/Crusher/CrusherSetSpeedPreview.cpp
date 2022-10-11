#include "CrusherSetSpeedPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/UI/SmartClippingNode.h"

#include "Resources/EntityResources.h"
#include "Resources/ObjectResources.h"

using namespace cocos2d;

const float CrusherSetSpeedPreview::TravelDistance = 600.0f;

CrusherSetSpeedPreview* CrusherSetSpeedPreview::create()
{
	CrusherSetSpeedPreview* instance = new CrusherSetSpeedPreview();

	instance->autorelease();

	return instance;
}

CrusherSetSpeedPreview::CrusherSetSpeedPreview()
{
	this->base = Sprite::create(ObjectResources::Traps_SpikedCrusher_Base);
	this->pole = Sprite::create(ObjectResources::Traps_SpikedCrusher_Pole);
	this->previewSqually = Sprite::create(EntityResources::Squally_Emblem);
	this->crusher = Sprite::create(ObjectResources::Traps_SpikedCrusher_HeadJagged);
	this->poleClip = SmartClippingNode::create(this->pole, CSize(this->pole->getContentSize().width, CrusherSetSpeedPreview::TravelDistance - 180.0f));
	this->eax0Label = this->createRegisterEqualsValueLabel(HackableCode::Register::zax, false, ConstantString::create("0"));
	this->ebx0Label = this->createRegisterEqualsValueLabel(HackableCode::Register::zbx, false, ConstantString::create("0"));
	this->ecx0Label = this->createRegisterEqualsValueLabel(HackableCode::Register::zcx, false, ConstantString::create("0"));
	this->eax1Label = this->createRegisterEqualsValueLabel(HackableCode::Register::zax, false, ConstantString::create("1"));
	this->ebx1Label = this->createRegisterEqualsValueLabel(HackableCode::Register::zbx, false, ConstantString::create("1"));
	this->ecx1Label = this->createRegisterEqualsValueLabel(HackableCode::Register::zcx, false, ConstantString::create("1"));
	
	this->base->setAnchorPoint(Vec2(0.5f, 1.0f));
	this->base->setFlippedY(true);
	this->crusher->setFlippedY(true);
	
	// Create parameters to repeat the texture
	Texture2D::TexParams params = Texture2D::TexParams();
	params.minFilter = GL_LINEAR;
	params.magFilter = GL_LINEAR;
	params.wrapT = GL_REPEAT;
	this->pole->setTextureRect(CRect(0.0f, 0.0f, this->pole->getContentSize().width, CrusherSetSpeedPreview::TravelDistance));
	
	if (this->pole->getTexture() != nullptr)
	{
		this->pole->getTexture()->setTexParameters(params);
	}

	this->poleClip->setScale(0.33f);
	this->base->setScale(0.33f);
	this->crusher->setScale(0.33f);

	this->previewNode->addChild(this->previewSqually);
	this->previewNode->addChild(this->poleClip);
	this->previewNode->addChild(this->base);
	this->previewNode->addChild(this->crusher);
	this->assemblyTextNode->addChild(this->eax0Label);
	this->assemblyTextNode->addChild(this->ebx0Label);
	this->assemblyTextNode->addChild(this->ecx0Label);
	this->assemblyTextNode->addChild(this->eax1Label);
	this->assemblyTextNode->addChild(this->ebx1Label);
	this->assemblyTextNode->addChild(this->ecx1Label);
}

CrusherSetSpeedPreview::~CrusherSetSpeedPreview()
{
}

HackablePreview* CrusherSetSpeedPreview::clone()
{
	return CrusherSetSpeedPreview::create();
}

void CrusherSetSpeedPreview::onEnter()
{
	super::onEnter();

	const float speed = 1.5f;
	const float offset = 48.0f;
	const float topOffset = 48.0f;

	this->crusher->setPosition(Vec2(0.0f, HackablePreview::PreviewRadius - offset - topOffset));
	this->poleClip->setPositionY(48.0f);
	this->base->setPositionY(HackablePreview::PreviewRadius - offset + 12.0f);
	this->previewSqually->setPositionY(-72.0f);

	this->previewSqually->runAction(
		RepeatForever::create(Sequence::create(
			EaseSineInOut::create(MoveTo::create(speed, Vec2(-(HackablePreview::PreviewRadius - 72.0f), this->previewSqually->getPositionY()))),
			DelayTime::create(speed),
			EaseSineInOut::create(MoveTo::create(speed, Vec2((HackablePreview::PreviewRadius - 72.0f), this->previewSqually->getPositionY()))),
			DelayTime::create(speed),
			nullptr
		))
	);
	this->crusher->runAction(
		RepeatForever::create(Sequence::create(
			EaseSineInOut::create(MoveTo::create(speed, Vec2(this->crusher->getPositionX(), -(HackablePreview::PreviewRadius - offset) / 2.0f))),
			EaseSineInOut::create(MoveTo::create(speed, Vec2(this->crusher->getPositionX(), HackablePreview::PreviewRadius - offset - topOffset))),
			nullptr
		))
	);
	// this->pole->setPositionY(this->crusher->getPositionY() + CrusherSetSpeedPreview::TravelDistance / 2.0f);
	this->pole->runAction(
		RepeatForever::create(Sequence::create(
			EaseSineInOut::create(MoveTo::create(speed, Vec2(this->pole->getPositionX(), -(HackablePreview::PreviewRadius - offset) / 2.0f))),
			EaseSineInOut::create(MoveTo::create(speed, Vec2(this->pole->getPositionX(), HackablePreview::PreviewRadius - offset - topOffset))),
			nullptr
		))
	);

	this->scheduleUpdate();
}

void CrusherSetSpeedPreview::initializePositions()
{
	super::initializePositions();

	this->eax0Label->setPosition(Vec2(-112.0f, 0.0f));
	this->eax1Label->setPosition(Vec2(-112.0f, 0.0f));
	this->ebx0Label->setPosition(Vec2(112.0f, 0.0f));
	this->ebx1Label->setPosition(Vec2(112.0f, 0.0f));
	this->ecx0Label->setPosition(Vec2(0.0f, -112.0f));
	this->ecx1Label->setPosition(Vec2(0.0f, -112.0f));
}

void CrusherSetSpeedPreview::update(float dt)
{
	super::update(dt);

	this->eax1Label->setVisible(this->previewSqually->getPositionX() > this->pole->getPositionX() - 40.0f);
	this->ebx1Label->setVisible(this->previewSqually->getPositionX() < this->pole->getPositionX() + 40.0f);
	this->eax0Label->setVisible(!this->eax1Label->isVisible());
	this->ebx0Label->setVisible(!this->ebx1Label->isVisible());
	this->ecx1Label->setVisible(this->eax1Label->isVisible() && this->ebx1Label->isVisible());
	this->ecx0Label->setVisible(!this->ecx1Label->isVisible());
}
