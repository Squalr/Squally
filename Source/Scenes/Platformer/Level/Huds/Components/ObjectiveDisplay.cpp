#include "ObjectiveDisplay.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/Objectives/Objectives.h"

using namespace cocos2d;

ObjectiveDisplay* ObjectiveDisplay::create()
{
	ObjectiveDisplay* instance = new ObjectiveDisplay();

	instance->autorelease();

	return instance;
}

ObjectiveDisplay::ObjectiveDisplay()
{
	this->label = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, nullptr);

	this->label->setHorizontalAlignment(TextHAlignment::RIGHT);
	this->label->setAnchorPoint(Vec2(1.0f, 0.5f));
	this->label->enableOutline(Color4B::BLACK, 2);

	this->addChild(this->label);
}

ObjectiveDisplay::~ObjectiveDisplay()
{
}

void ObjectiveDisplay::onEnter()
{
	super::onEnter();

	this->loadObjective();
}

void ObjectiveDisplay::initializeListeners()
{
	super::initializeListeners();
	
	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventObjectiveChanged, [=](EventCustom* eventCustom)
	{
		this->loadObjective();
	}));
}
	
void ObjectiveDisplay::loadObjective()
{
	this->label->setLocalizedString(Objectives::GetObjectiveString());
}
