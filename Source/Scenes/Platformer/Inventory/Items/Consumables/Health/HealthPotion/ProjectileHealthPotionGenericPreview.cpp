#include "ProjectileHealthPotionGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

ProjectileHealthPotionGenericPreview* ProjectileHealthPotionGenericPreview::create()
{
	ProjectileHealthPotionGenericPreview* instance = new ProjectileHealthPotionGenericPreview();

	instance->autorelease();

	return instance;
}

ProjectileHealthPotionGenericPreview::ProjectileHealthPotionGenericPreview()
{
	this->healthPotion = Sprite::create(ObjectResources::Items_Consumables_Potions_HEALTH_2);

	this->previewNode->addChild(this->healthPotion);
}

ProjectileHealthPotionGenericPreview::~ProjectileHealthPotionGenericPreview()
{
}

HackablePreview* ProjectileHealthPotionGenericPreview::clone()
{
	return ProjectileHealthPotionGenericPreview::create();
}

void ProjectileHealthPotionGenericPreview::onEnter()
{
	super::onEnter();

	this->healthPotion->runAction(RepeatForever::create(RotateBy::create(1.0f, 360.0f)));
}

void ProjectileHealthPotionGenericPreview::initializePositions()
{
	super::initializePositions();

	const float offset = 48.0f;

	this->healthPotion->setPosition(Vec2(0.0f, 0.0f));
}
