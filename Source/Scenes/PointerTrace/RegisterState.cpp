#include "RegisterState.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/SmartNode.h"
#include "Events/PointerTraceEvents.h"

using namespace cocos2d;

int RegisterState::registerEax = 0;
int RegisterState::registerEbx = 0;
int RegisterState::registerEcx = 0;
int RegisterState::registerEdx = 0;
int RegisterState::registerEdi = 0;
int RegisterState::registerEsi = 0;
int RegisterState::registerEbp = 0;
int RegisterState::registerEsp = 0;
int RegisterState::registerEip = 0;

int RegisterState::getRegisterEax()
{
	return RegisterState::registerEax;
}

void RegisterState::setRegisterEax(int value)
{
	RegisterState::registerEax = value;
}

int RegisterState::getRegisterEbx()
{
	return RegisterState::registerEbx;
}

void RegisterState::setRegisterEbx(int value)
{
	RegisterState::registerEbx = value;
}

int RegisterState::getRegisterEcx()
{
	return RegisterState::registerEcx;
}

void RegisterState::setRegisterEcx(int value)
{
	RegisterState::registerEcx = value;
}

int RegisterState::getRegisterEdx()
{
	return RegisterState::registerEdx;
}

void RegisterState::setRegisterEdx(int value)
{
	RegisterState::registerEdx = value;
}

int RegisterState::getRegisterEdi()
{
	return RegisterState::registerEdi;
}

void RegisterState::setRegisterEdi(int value)
{
	RegisterState::registerEdi = value;
}

int RegisterState::getRegisterEsi()
{
	return RegisterState::registerEsi;
}

void RegisterState::setRegisterEsi(int value)
{
	RegisterState::registerEsi = value;
}

int RegisterState::getRegisterEbp()
{
	return RegisterState::registerEbp;
}

void RegisterState::setRegisterEbp(int value)
{
	RegisterState::registerEbp = value;
}

int RegisterState::getRegisterEsp()
{
	return RegisterState::registerEsp;
}

void RegisterState::setRegisterEsp(int value)
{
	RegisterState::registerEsp = value;
}

int RegisterState::getRegisterEip()
{
	return RegisterState::registerEip;
}

void RegisterState::setRegisterEip(int value)
{
	RegisterState::registerEip = value;
}
