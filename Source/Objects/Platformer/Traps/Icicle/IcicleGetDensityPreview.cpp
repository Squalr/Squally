#include "IcicleGetDensityPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

IcicleGetDensityPreview* IcicleGetDensityPreview::create()
{
	IcicleGetDensityPreview* instance = new IcicleGetDensityPreview();

	instance->autorelease();

	return instance;
}

IcicleGetDensityPreview::IcicleGetDensityPreview()
{
	this->previewAsteroid = Sprite::create(ObjectResources::Physics_Asteroid_Asteroid);

	this->xmm0Top = this->createRegisterEqualsValueLabel(HackableCode::Register::xmm0, false, ConstantString::create("0.0f"));
	this->xmm0Bottom = this->createRegisterEqualsValueLabel(HackableCode::Register::xmm0, false, ConstantString::create("1.0f"));

	this->previewAsteroid->setScale(0.35f);

	this->previewNode->addChild(this->previewAsteroid);
	this->assemblyTextNode->addChild(this->xmm0Top);
	this->assemblyTextNode->addChild(this->xmm0Bottom);
}

IcicleGetDensityPreview::~IcicleGetDensityPreview()
{
}

HackablePreview* IcicleGetDensityPreview::clone()
{
	return IcicleGetDensityPreview::create();
}

void IcicleGetDensityPreview::onEnter()
{
	super::onEnter();

	const float speed = 1.5f;
	const float offset = 48.0f;

	this->previewAsteroid->setPosition(Vec2(0.0f, HackablePreview::PreviewRadius - offset));

	this->previewAsteroid->runAction(
		RepeatForever::create(Sequence::create(
			EaseSineInOut::create(MoveTo::create(speed, Vec2(this->previewAsteroid->getPositionX(), -(HackablePreview::PreviewRadius - offset)))),
			EaseSineInOut::create(MoveTo::create(speed, Vec2(this->previewAsteroid->getPositionX(), HackablePreview::PreviewRadius - offset))),
			nullptr
		))
	);
}

void IcicleGetDensityPreview::initializePositions()
{
	super::initializePositions();

	const float offset = 32.0f;

	this->xmm0Bottom->setPosition(Vec2(0.0f, -HackablePreview::PreviewRadius + offset));
	this->xmm0Top->setPosition(Vec2(0.0f, HackablePreview::PreviewRadius - offset));
}
