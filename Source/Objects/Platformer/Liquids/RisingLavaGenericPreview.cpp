#include "RisingLavaGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

RisingLavaGenericPreview* RisingLavaGenericPreview::create()
{
	RisingLavaGenericPreview* instance = new RisingLavaGenericPreview();

	instance->autorelease();

	return instance;
}

RisingLavaGenericPreview::RisingLavaGenericPreview()
{
}

RisingLavaGenericPreview::~RisingLavaGenericPreview()
{
}

HackablePreview* RisingLavaGenericPreview::clone()
{
	return RisingLavaGenericPreview::create();
}

void RisingLavaGenericPreview::onEnter()
{
	super::onEnter();
}

void RisingLavaGenericPreview::initializePositions()
{
	super::initializePositions();
}
