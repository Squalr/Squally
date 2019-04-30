#include "JmpMarker.h"

#include "cocos/base/CCValue.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Utils/GameUtils.h"
#include "Resources/IsometricObjectResources.h"

#include "Strings/Generics/Constant.h"
#include "Strings/PointerTrace/Assembly/Jmp.h"
#include "Strings/PointerTrace/Assembly/OffsetNegative.h"
#include "Strings/PointerTrace/Assembly/OffsetPositive.h"
#include "Strings/PointerTrace/Assembly/Ptr.h"

using namespace cocos2d;

const std::string JmpMarker::MapKeyOffset = "offset";

JmpMarker::JmpMarker(ValueMap& initProperties) : super(initProperties)
{
	this->markerNode = Node::create();
	this->assemblyString = Strings::Generics_Constant::create();
	this->assemblyLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H1, this->assemblyString);
	this->offset = GameUtils::getKeyOrDefault(initProperties, JmpMarker::MapKeyOffset, Value(0)).asInt();

	this->assemblyLabel->enableOutline(Color4B::BLACK, 3);

	this->addChild(this->markerNode);
	this->addChild(this->assemblyLabel);
}

JmpMarker::~JmpMarker()
{
}

void JmpMarker::onEnter()
{
	super::onEnter();
}

void JmpMarker::initializePositions()
{
	super::initializePositions();

	this->assemblyLabel->setPosition(Vec2(0.0f, 96.0f));
}

void JmpMarker::buildJmpString(LocalizedString* registerString)
{
	LocalizedString* jmpString = Strings::PointerTrace_Assembly_Jmp::create();
	
	// Note: there are no offsets for pure register jumps, so if one is set, it is simply ignored
	jmpString->setStringReplacementVariables(registerString);

	this->assemblyString->setStringReplacementVariables(jmpString);
}

void JmpMarker::buildJmpPtrString(LocalizedString* registerString)
{
	LocalizedString* jmpString = Strings::PointerTrace_Assembly_Jmp::create();
	
	if (this->getOffset() == 0)
	{
		LocalizedString* ptrString = Strings::PointerTrace_Assembly_Ptr::create();
		
		ptrString->setStringReplacementVariables(registerString);
		jmpString->setStringReplacementVariables(ptrString);
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
		jmpString->setStringReplacementVariables(ptrString);
	}

	this->assemblyString->setStringReplacementVariables(jmpString);
}

int JmpMarker::getOffset()
{
	return this->offset;
}
