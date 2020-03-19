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

#include "Strings/Strings.h"

#include "Resources/FXResources.h"
#include "Resources/IsometricObjectResources.h"

using namespace cocos2d;

const std::string RegisterCrystal::PropertyRegisterInstruction = "instruction";
const std::string RegisterCrystal::PropertyRegisterIsPointer = "is-pointer";
const std::string RegisterCrystal::PropertyRegisterValue = "value";
const std::string RegisterCrystal::PropertyRegisterOffset = "offset";

RegisterCrystal::RegisterCrystal(ValueMap& properties) : super(properties)
{
	this->shadow = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_Shadow);
	this->crystalContainerNode = Node::create();
	this->crystalNode = Node::create();
	this->assemblyString = Strings::Common_Constant::create();
	this->assemblyLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::M3, this->assemblyString);
	this->shineFx = SmartAnimationSequenceNode::create();

	this->setZSorted(true);

	this->instruction = GameUtils::getKeyOrDefault(this->properties, RegisterCrystal::PropertyRegisterInstruction, Value("mov")).asString();
	this->isPointer = GameUtils::getKeyOrDefault(this->properties, RegisterCrystal::PropertyRegisterIsPointer, Value(false)).asBool();
	this->value = GameUtils::getKeyOrDefault(this->properties, RegisterCrystal::PropertyRegisterValue, Value(0)).asInt();
	this->offset = GameUtils::getKeyOrDefault(this->properties, RegisterCrystal::PropertyRegisterOffset, Value(0)).asInt();

	this->assemblyLabel->enableOutline(Color4B::BLACK, 4);

	this->crystalContainerNode->addChild(this->crystalNode);
	this->crystalContainerNode->addChild(this->shineFx);
	this->addChild(this->shadow);
	this->addChild(this->crystalContainerNode);
	this->addChild(this->assemblyLabel);
}

RegisterCrystal::~RegisterCrystal()
{
}

void RegisterCrystal::onEnter()
{
	super::onEnter();

	ObjectEvents::TriggerBindObjectToUI(ObjectEvents::RelocateObjectArgs(this->assemblyLabel));

	this->crystalContainerNode->runAction(RepeatForever::create(
		Sequence::create(
			EaseSineInOut::create(MoveTo::create(4.0f, Vec2(0.0f, 128.0f))),
			EaseSineInOut::create(MoveTo::create(4.0f, Vec2(0.0f, 96.0f))),
			nullptr
		)
	));
	
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
				this->shineFx->playAnimation(FXResources::Shine_Shine_0000, 0.015f, true);

				if (this->isPointer)
				{
					this->updateMemory(this->runInstruction());
				}
				else
				{
					this->updateRegister(this->runInstruction());
				}
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

void RegisterCrystal::buildString(LocalizedString* registerString)
{
	if (this->instruction == "add")
	{
		if (this->isPointer)
		{
			this->buildInstructionPtrString(registerString, Strings::PointerTrace_Assembly_Add::create(), true);
		}
		else
		{
			this->buildInstructionString(registerString, Strings::PointerTrace_Assembly_Add::create(), true);
		}
	}
	else if (this->instruction == "sub")
	{
		if (this->isPointer)
		{
			this->buildInstructionPtrString(registerString, Strings::PointerTrace_Assembly_Sub::create(), true);
		}
		else
		{
			this->buildInstructionString(registerString, Strings::PointerTrace_Assembly_Sub::create(), true);
		}
	}
	else if (this->instruction == "div")
	{
		if (this->isPointer)
		{
			this->buildInstructionPtrString(registerString, Strings::PointerTrace_Assembly_Div::create(), true);
		}
		else
		{
			this->buildInstructionString(registerString, Strings::PointerTrace_Assembly_Div::create(), true);
		}
	}
	else if (this->instruction == "mul")
	{
		if (this->isPointer)
		{
			this->buildInstructionPtrString(registerString, Strings::PointerTrace_Assembly_Mul::create(), true);
		}
		else
		{
			this->buildInstructionString(registerString, Strings::PointerTrace_Assembly_Mul::create(), true);
		}
	}
	else if (this->instruction == "inc")
	{
		if (this->isPointer)
		{
			this->buildInstructionPtrString(registerString, Strings::PointerTrace_Assembly_Inc::create(), false);
		}
		else
		{
			this->buildInstructionString(registerString, Strings::PointerTrace_Assembly_Inc::create(), false);
		}
	}
	else if (this->instruction == "dec")
	{
		if (this->isPointer)
		{
			this->buildInstructionPtrString(registerString, Strings::PointerTrace_Assembly_Dec::create(), false);
		}
		else
		{
			this->buildInstructionString(registerString, Strings::PointerTrace_Assembly_Dec::create(), false);
		}
	}
	else // if (this->instruction == "mov")
	{
		if (this->isPointer)
		{
			this->buildInstructionPtrString(registerString, Strings::PointerTrace_Assembly_Mov::create(), true);
		}
		else
		{
			this->buildInstructionString(registerString, Strings::PointerTrace_Assembly_Mov::create(), true);
		}
	}
}

void RegisterCrystal::buildInstructionString(LocalizedString* registerString, LocalizedString* instructionString, bool bindValue)
{
	ConstantString* valueString = ConstantString::create(std::to_string(this->getValue()));
	
	if (bindValue)
	{
		instructionString->setStringReplacementVariables({ registerString, valueString });
	}
	else
	{
		instructionString->setStringReplacementVariables(registerString);
	}

	this->assemblyString->setStringReplacementVariables(instructionString);
}

void RegisterCrystal::buildInstructionPtrString(LocalizedString* registerString, LocalizedString* instructionString, bool bindValue)
{
	ConstantString* valueString = ConstantString::create(std::to_string(this->getValue()));
	LocalizedString* ptrString = Strings::PointerTrace_Assembly_Ptr::create();
	
	if (this->getOffset() == 0)
	{
		ptrString->setStringReplacementVariables(registerString);
	}
	else
	{
		LocalizedString* offsetString = (this->getOffset() < 0) 
			? (LocalizedString*)Strings::PointerTrace_Assembly_OffsetNegative::create()
			: (LocalizedString*)Strings::PointerTrace_Assembly_OffsetPositive::create();
		ConstantString* offsetValueString = ConstantString::create(std::to_string(std::abs(this->getOffset())));

		offsetString->setStringReplacementVariables({ registerString, offsetValueString });
		ptrString->setStringReplacementVariables(offsetString);
	}

	if (bindValue)
	{
		instructionString->setStringReplacementVariables({ ptrString, valueString });
	}
	else
	{
		instructionString->setStringReplacementVariables(ptrString);
	}

	this->assemblyString->setStringReplacementVariables(instructionString);
}

int RegisterCrystal::runInstruction()
{
	// Note: this does not support multiple registers (ie mov eax, ebx) yet

	if (this->instruction == "add")
	{
		return this->getRegisterValue() + this->getValue();
	}
	else if (this->instruction == "sub")
	{
		return this->getRegisterValue() - this->getValue();
	}
	else if (this->instruction == "div")
	{
		return this->getRegisterValue() / this->getValue();
	}
	else if (this->instruction == "mul")
	{
		return this->getRegisterValue() * this->getValue();
	}
	else if (this->instruction == "inc")
	{
		return this->getRegisterValue() + 1;
	}
	else if (this->instruction == "dec")
	{
		return this->getRegisterValue() - 1;
	}
	else // if (this->instruction == "mov")
	{
		return this->getValue();
	}
}

void RegisterCrystal::updateMemory(int writeValue)
{
	int address = this->getRegisterValue() + this->getOffset();

	PointerTraceEvents::TriggerWriteValue(PointerTraceEvents::PointerTraceWriteArgs(address, writeValue));
}

int RegisterCrystal::getValue()
{
	return this->value;
}

int RegisterCrystal::getOffset()
{
	return this->offset;
}
