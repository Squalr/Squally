#include "CinematicIndicator.h"

#include "2d/CCLayer.h"
#include "2d/CCSprite.h"
#include "2d/CCActionInstant.h"
#include "2d/CCActionInterval.h"
#include "base/CCEventCustom.h"
#include "base/CCEventListenerCustom.h"
#include "base/CCInputEvents.h"

#include "Engine/UI/HUD/Hud.h"
#include "Events/PlatformerEvents.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

CinematicIndicator* CinematicIndicator::create()
{
	CinematicIndicator* instance = new CinematicIndicator();

	instance->autorelease();

	return instance;
}

CinematicIndicator::CinematicIndicator()
{
	this->cinematicIndicator = Node::create();
	this->filmProjector = Sprite::create(UIResources::Cinematic_FilmProjectorBase);
	this->reelLarge = Sprite::create(UIResources::Cinematic_ReelLarge);
	this->reelSmall = Sprite::create(UIResources::Cinematic_ReelSmall);

	this->cinematicIndicator->addChild(this->filmProjector);
	this->cinematicIndicator->addChild(this->reelLarge);
	this->cinematicIndicator->addChild(this->reelSmall);
	this->addChild(this->cinematicIndicator);
}

CinematicIndicator::~CinematicIndicator()
{
}

void CinematicIndicator::onEnter()
{
	super::onEnter();

	this->setOpacity(0);

	this->reelLarge->runAction(RepeatForever::create(RotateBy::create(1.5f, 360.0f)));
	this->reelSmall->runAction(RepeatForever::create(RotateBy::create(1.5f, -360.0f)));
}

void CinematicIndicator::initializePositions()
{
	super::initializePositions();

	this->reelLarge->setPosition(Vec2(-12.0f, 28.0f - 4.0f));
	this->reelSmall->setPosition(Vec2(10.0f, 23.0f - 4.0f));
}

void CinematicIndicator::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventCinematicHijack, [=](EventCustom*)
	{
		this->runAction(FadeTo::create(0.5f, 255));
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventCinematicRestore, [=](EventCustom*)
	{
		this->runAction(FadeTo::create(0.5f, 0));
	}));
}
