#include "RegisterState.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/SmartNode.h"
#include "Engine/Utils/MathUtils.h"
#include "Events/PointerTraceEvents.h"

using namespace cocos2d;

int RegisterState::RegisterEax = 0;
int RegisterState::RegisterEbx = 0;
int RegisterState::RegisterEcx = 0;
int RegisterState::RegisterEdx = 0;
int RegisterState::RegisterEdi = 0;
int RegisterState::RegisterEsi = 0;
int RegisterState::RegisterEbp = 0;
int RegisterState::RegisterEsp = 0;
int RegisterState::RegisterEip = 0;
int RegisterState::RegisterMax = 0;

int RegisterState::getRegisterEax()
{
	return RegisterState::RegisterEax;
}

void RegisterState::setRegisterEax(int value)
{
	RegisterState::RegisterEax = MathUtils::wrappingNormalize(value, 0, RegisterState::RegisterMax);

	PointerTraceEvents::TriggerRegisterUpdated();
}

int RegisterState::getRegisterEbx()
{
	return RegisterState::RegisterEbx;
}

void RegisterState::setRegisterEbx(int value)
{
	RegisterState::RegisterEbx = MathUtils::wrappingNormalize(value, 0, RegisterState::RegisterMax);

	PointerTraceEvents::TriggerRegisterUpdated();
}

int RegisterState::getRegisterEcx()
{
	return RegisterState::RegisterEcx;
}

void RegisterState::setRegisterEcx(int value)
{
	RegisterState::RegisterEcx = MathUtils::wrappingNormalize(value, 0, RegisterState::RegisterMax);

	PointerTraceEvents::TriggerRegisterUpdated();
}

int RegisterState::getRegisterEdx()
{
	return RegisterState::RegisterEdx;
}

void RegisterState::setRegisterEdx(int value)
{
	RegisterState::RegisterEdx = MathUtils::wrappingNormalize(value, 0, RegisterState::RegisterMax);

	PointerTraceEvents::TriggerRegisterUpdated();
}

int RegisterState::getRegisterEdi()
{
	return RegisterState::RegisterEdi;
}

void RegisterState::setRegisterEdi(int value)
{
	RegisterState::RegisterEdi = MathUtils::wrappingNormalize(value, 0, RegisterState::RegisterMax);

	PointerTraceEvents::TriggerRegisterUpdated();
}

int RegisterState::getRegisterEsi()
{
	return RegisterState::RegisterEsi;
}

void RegisterState::setRegisterEsi(int value)
{
	RegisterState::RegisterEsi = MathUtils::wrappingNormalize(value, 0, RegisterState::RegisterMax);

	PointerTraceEvents::TriggerRegisterUpdated();
}

int RegisterState::getRegisterEbp()
{
	return RegisterState::RegisterEbp;
}

void RegisterState::setRegisterEbp(int value)
{
	RegisterState::RegisterEbp = MathUtils::wrappingNormalize(value, 0, RegisterState::RegisterMax);

	PointerTraceEvents::TriggerRegisterUpdated();
}

int RegisterState::getRegisterEsp()
{
	return RegisterState::RegisterEsp;
}

void RegisterState::setRegisterEsp(int value)
{
	RegisterState::RegisterEsp = MathUtils::wrappingNormalize(value, 0, RegisterState::RegisterMax);

	PointerTraceEvents::TriggerRegisterUpdated();
}

int RegisterState::getRegisterEip()
{
	return RegisterState::RegisterEip;
}

void RegisterState::setRegisterEip(int value)
{
	RegisterState::RegisterEip = MathUtils::wrappingNormalize(value, 0, RegisterState::RegisterMax);

	PointerTraceEvents::TriggerRegisterUpdated();
}

void RegisterState::setRegisterMax(int registerMax)
{
	RegisterState::RegisterMax = registerMax;
}
