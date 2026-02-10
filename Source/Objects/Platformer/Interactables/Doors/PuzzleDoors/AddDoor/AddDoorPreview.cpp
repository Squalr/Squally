#include "AddDoorPreview.h"

#include "2d/CCActionEase.h"
#include "2d/CCActionInterval.h"
#include "2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

AddDoorPreview* AddDoorPreview::create()
{
	AddDoorPreview* instance = new AddDoorPreview();

	instance->autorelease();

	return instance;
}

AddDoorPreview::AddDoorPreview()
{
}

AddDoorPreview::~AddDoorPreview()
{
}

HackablePreview* AddDoorPreview::clone()
{
	return AddDoorPreview::create();
}

void AddDoorPreview::onEnter()
{
	super::onEnter();
}

void AddDoorPreview::initializePositions()
{
	super::initializePositions();
}
