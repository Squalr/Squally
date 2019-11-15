#include "ProjectileRestorePotionGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

ProjectileRestorePotionGenericPreview* ProjectileRestorePotionGenericPreview::create()
{
	ProjectileRestorePotionGenericPreview* instance = new ProjectileRestorePotionGenericPreview();

	instance->autorelease();

	return instance;
}

ProjectileRestorePotionGenericPreview::ProjectileRestorePotionGenericPreview()
{
	this->restorePotion = Sprite::create(ObjectResources::Items_Consumables_Potions_HEALTH_2);

	this->previewNode->addChild(this->restorePotion);
}

ProjectileRestorePotionGenericPreview::~ProjectileRestorePotionGenericPreview()
{
}

HackablePreview* ProjectileRestorePotionGenericPreview::clone()
{
	return ProjectileRestorePotionGenericPreview::create();
}

void ProjectileRestorePotionGenericPreview::onEnter()
{
	super::onEnter();

	this->restorePotion->runAction(RepeatForever::create(RotateBy::create(1.0f, 360.0f)));
}

void ProjectileRestorePotionGenericPreview::initializePositions()
{
	super::initializePositions();

	const float offset = 48.0f;

	this->restorePotion->setPosition(Vec2(0.0f, 0.0f));
}
