#include "ThrownWeaponGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

ThrownWeaponGenericPreview* ThrownWeaponGenericPreview::create(std::string weaponResource)
{
	ThrownWeaponGenericPreview* instance = new ThrownWeaponGenericPreview(weaponResource);

	instance->autorelease();

	return instance;
}

ThrownWeaponGenericPreview::ThrownWeaponGenericPreview(std::string weaponResource)
{
	this->weaponResource = weaponResource;
	this->bomberTorch = Sprite::create(this->weaponResource);

	this->previewNode->addChild(this->bomberTorch);
}

ThrownWeaponGenericPreview::~ThrownWeaponGenericPreview()
{
}

HackablePreview* ThrownWeaponGenericPreview::clone()
{
	return ThrownWeaponGenericPreview::create(this->weaponResource);
}

void ThrownWeaponGenericPreview::onEnter()
{
	super::onEnter();

	this->bomberTorch->runAction(RepeatForever::create(RotateBy::create(1.0f, 360.0f)));
}

void ThrownWeaponGenericPreview::initializePositions()
{
	super::initializePositions();

	const float offset = 48.0f;

	this->bomberTorch->setPosition(Vec2(0.0f, 0.0f));
}
