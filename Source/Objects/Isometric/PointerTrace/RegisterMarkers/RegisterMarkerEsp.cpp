#include "RegisterMarkerEsp.h"

#include "cocos/2d/CCSprite.h"

#include "Objects/Isometric/PointerTrace/MemoryGrid.h"
#include "Scenes/PointerTrace/RegisterState.h"

#include "Resources/IsometricObjectResources.h"

#include "Strings/PointerTrace/Assembly/RegisterEsp.h"
#include "Strings/PointerTrace/Assembly/RegisterRsp.h"

using namespace cocos2d;

RegisterMarkerEsp* RegisterMarkerEsp::create()
{
    RegisterMarkerEsp* instance = new RegisterMarkerEsp();

    instance->autorelease();
    
    return instance;
}

RegisterMarkerEsp::RegisterMarkerEsp()
{
    this->marker = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_EspMarker);

    if (sizeof(void*) == 4)
    {
        this->registerString->setStringReplacementVariables(Strings::PointerTrace_Assembly_RegisterEsp::create());
    }
    else
    {
        this->registerString->setStringReplacementVariables(Strings::PointerTrace_Assembly_RegisterRsp::create());
    }

    this->addChild(this->marker);
}

RegisterMarkerEsp::~RegisterMarkerEsp()
{
}

int RegisterMarkerEsp::getRegisterIndex()
{
    return RegisterState::getRegisterEsp();
}