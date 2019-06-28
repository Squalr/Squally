#include "ProjectileSpeedRuneGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

ProjectileSpeedRuneGenericPreview* ProjectileSpeedRuneGenericPreview::create()
{
	ProjectileSpeedRuneGenericPreview* instance = new ProjectileSpeedRuneGenericPreview();

	instance->autorelease();

	return instance;
}

ProjectileSpeedRuneGenericPreview::ProjectileSpeedRuneGenericPreview()
{
	this->speedRune = Sprite::create(ObjectResources::Items_Consumables_YELLOW_RUNE);

	this->previewNode->addChild(this->speedRune);
}

ProjectileSpeedRuneGenericPreview::~ProjectileSpeedRuneGenericPreview()
{
}

HackablePreview* ProjectileSpeedRuneGenericPreview::clone()
{
	return ProjectileSpeedRuneGenericPreview::create();
}

void ProjectileSpeedRuneGenericPreview::onEnter()
{
	super::onEnter();

	this->speedRune->runAction(RepeatForever::create(RotateBy::create(1.0f, 360.0f)));
}

void ProjectileSpeedRuneGenericPreview::initializePositions()
{
	super::initializePositions();

	const float offset = 48.0f;

	this->speedRune->setPosition(Vec2(0.0f, 0.0f));
}
