#include "RegisterCrystal.h"

#include "cocos/2d/CCAction.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Input/Input.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Isometric/PointerTrace/GridEntity.h"
#include "Events/PointerTraceEvents.h"
#include "Resources/IsometricObjectResources.h"

#include "Strings/Generics/Constant.h"
#include "Strings/PointerTrace/Assembly/Mov.h"
#include "Strings/PointerTrace/Assembly/OffsetNegative.h"
#include "Strings/PointerTrace/Assembly/OffsetPositive.h"
#include "Strings/PointerTrace/Assembly/Ptr.h"

#include "Resources/IsometricObjectResources.h"
#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string RegisterCrystal::MapKeyRegisterValue = "value";
const std::string RegisterCrystal::MapKeyRegisterOffset = "offset";

RegisterCrystal::RegisterCrystal(ValueMap& properties) : super(properties)
{
	this->shadow = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_Shadow);
	this->crystalContainerNode = Node::create();
	this->crystalNode = Node::create();
	this->assemblyString = Strings::Generics_Constant::create();
	this->assemblyLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::M3, this->assemblyString);
	this->shineFx = SmartAnimationSequenceNode::create();

	this->setZSorted(true);

	this->value = GameUtils::getKeyOrDefault(this->properties, RegisterCrystal::MapKeyRegisterValue, Value(0)).asInt();
	this->offset = GameUtils::getKeyOrDefault(this->properties, RegisterCrystal::MapKeyRegisterOffset, Value(0)).asInt();

	this->assemblyLabel->enableOutline(Color4B::BLACK, 4);

	this->crystalContainerNode->addChild(this->crystalNode);
	this->crystalContainerNode->addChild(this->shineFx);
	this->addChild(this->shadow);
	this->addChild(this->crystalContainerNode);
	this->addChild(this->assemblyLabel);
}

RegisterCrystal::~RegisterCrystal()
{
	ObjectEvents::TriggerUnbindObject(ObjectEvents::RelocateObjectArgs(this->assemblyLabel));
}

void RegisterCrystal::onEnter()
{
	super::onEnter();

	ObjectEvents::TriggerMoveObjectToTopLayer(ObjectEvents::RelocateObjectArgs(this->assemblyLabel));

	this->crystalContainerNode->stopAllActions();
	this->crystalContainerNode->runAction(RepeatForever::create(
		Sequence::create(
			EaseSineInOut::create(MoveTo::create(4.0f, Vec2(0.0f, 128.0f))),
			EaseSineInOut::create(MoveTo::create(4.0f, Vec2(0.0f, 96.0f))),
			nullptr
		)
	));
	this->shadow->stopAllActions();
	this->shadow->runAction(RepeatForever::create(
		Sequence::create(
			ScaleTo::create(4.0f, 0.75f),
			ScaleTo::create(4.0f, 1.0f),
			nullptr
		)
	));
	
	this->scheduleUpdate();
}

void RegisterCrystal::initializePositions()
{
	super::initializePositions();

	this->crystalContainerNode->setPosition(Vec2(0.0f, 96.0f));
	this->assemblyLabel->setPosition(Vec2(0.0f, 160.0f));
	this->shineFx->setPosition(Vec2(-8.0f, 24.0f));
}

void RegisterCrystal::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(
		PointerTraceEvents::EventEntityMoved,
		[=](EventCustom* eventCustom)
		{
			PointerTraceEvents::PointerTraceEntityMovedArgs* args = static_cast<PointerTraceEvents::PointerTraceEntityMovedArgs*>(eventCustom->getUserData());

			if (args != nullptr && args->gridEntity != nullptr && args->gridEntity->getGridIndex() == this->getGridIndex())
			{
				this->shineFx->playAnimation(ObjectResources::FX_Shine_Shine_0000, 0.015f, true);
				this->updateRegister(this->getValue());
			}
		}
	));
}

void RegisterCrystal::update(float dt)
{
	super::update(dt);

	if (Input::isPressed(EventKeyboard::KeyCode::KEY_TAB) || Input::isPressed(EventKeyboard::KeyCode::KEY_SHIFT))
	{
		this->assemblyLabel->setOpacity(0);
	}
	else
	{
		this->assemblyLabel->setOpacity(255);
	}
}

void RegisterCrystal::buildMovString(LocalizedString* registerString)
{
	LocalizedString* movString = Strings::PointerTrace_Assembly_Mov::create();
	ConstantString* valueString = ConstantString::create(std::to_string(this->getValue()));
	
	// Note: there are no offsets for pure register movs, so if one is set, it is simply ignored
	movString->setStringReplacementVariables({ registerString, valueString });

	this->assemblyString->setStringReplacementVariables(movString);
}

void RegisterCrystal::buildMovPtrString(LocalizedString* registerString)
{
	LocalizedString* movString = Strings::PointerTrace_Assembly_Mov::create();
	ConstantString* valueString = ConstantString::create(std::to_string(this->getValue()));
	
	if (this->getOffset() == 0)
	{
		LocalizedString* ptrString = Strings::PointerTrace_Assembly_Ptr::create();
		
		ptrString->setStringReplacementVariables(registerString);
		movString->setStringReplacementVariables({ ptrString, valueString });
	}
	else
	{
		LocalizedString* ptrString = Strings::PointerTrace_Assembly_Ptr::create();
		LocalizedString* offsetString = (this->getOffset() < 0) 
			? (LocalizedString*)Strings::PointerTrace_Assembly_OffsetNegative::create()
			: (LocalizedString*)Strings::PointerTrace_Assembly_OffsetPositive::create();
		ConstantString* offsetValueString = ConstantString::create(std::to_string(this->getOffset()));

		offsetString->setStringReplacementVariables({ registerString, offsetValueString });
		ptrString->setStringReplacementVariables(offsetString);
		movString->setStringReplacementVariables({ ptrString, valueString });
	}

	this->assemblyString->setStringReplacementVariables(movString);
}

int RegisterCrystal::getValue()
{
	return this->value;
}

int RegisterCrystal::getOffset()
{
	return this->offset;
}
