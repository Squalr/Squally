#include "PointerTrace.h"

#include "Engine/SmartNode.h"

#include "Resources/CipherResources.h"

using namespace cocos2d;

PointerTrace* PointerTrace::create()
{
	PointerTrace* instance = new PointerTrace();

	instance->autorelease();

	return instance;
}

PointerTrace::PointerTrace()
{
}

PointerTrace::~PointerTrace()
{
}

void PointerTrace::onEnter()
{
	super::onEnter();
}

void PointerTrace::initializePositions()
{
	super::initializePositions();
}

void PointerTrace::initializeListeners()
{
	super::initializeListeners();
}
