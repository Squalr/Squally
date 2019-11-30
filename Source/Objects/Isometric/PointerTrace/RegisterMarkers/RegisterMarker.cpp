#include "RegisterMarker.h"

#include "cocos/base/CCValue.h"

#include "Engine/Events/ObjectEvents.h"
#include "Engine/Input/Input.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"
#include "Objects/Isometric/PointerTrace/MemoryGrid.h"
#include "Scenes/PointerTrace/RegisterState.h"

#include "Resources/IsometricObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

RegisterMarker::RegisterMarker() : super(ValueMap())
{
	this->registerString = Strings::Common_Constant::create();
	this->registerLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::M3, this->registerString);

	this->registerLabel->setTextColor(Color4B::YELLOW);
	this->registerLabel->enableOutline(Color4B::BLACK, 4);

	this->addChild(this->registerLabel);
}

RegisterMarker::~RegisterMarker()
{
}

void RegisterMarker::onEnter()
{
	super::onEnter();

	ObjectEvents::TriggerBindObjectToUI(ObjectEvents::RelocateObjectArgs(this->registerLabel));
}

void RegisterMarker::initializePositions()
{
	super::initializePositions();

	this->registerLabel->setPosition(Vec2(0.0f, 48.0f));
}

void RegisterMarker::update(float dt)
{
	super::update(dt);

	if (Input::isPressed(EventKeyboard::KeyCode::KEY_TAB) || Input::isPressed(EventKeyboard::KeyCode::KEY_SHIFT))
	{
		this->registerLabel->setOpacity(0);
	}
	else
	{
		this->registerLabel->setOpacity(255);
	}
}

void RegisterMarker::moveToRegister(MemoryGrid* memoryGrid)
{
	this->setPosition(memoryGrid->gridIndexToRelativePosition(this->getRegisterIndex()));
}
