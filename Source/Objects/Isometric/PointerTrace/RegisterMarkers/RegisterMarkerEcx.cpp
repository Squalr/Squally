#include "RegisterMarkerEcx.h"

#include "cocos/2d/CCSprite.h"

#include "Objects/Isometric/PointerTrace/MemoryGrid.h"
#include "Scenes/PointerTrace/RegisterState.h"

#include "Resources/IsometricObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

RegisterMarkerEcx* RegisterMarkerEcx::create()
{
    RegisterMarkerEcx* instance = new RegisterMarkerEcx();

    instance->autorelease();
    
    return instance;
}

RegisterMarkerEcx::RegisterMarkerEcx()
{
    this->marker = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_EcxMarker);

    if (sizeof(void*) == 4)
    {
        this->registerString->setStringReplacementVariables(Strings::PointerTrace_Assembly_RegisterEcx::create());
    }
    else
    {
        this->registerString->setStringReplacementVariables(Strings::PointerTrace_Assembly_RegisterRcx::create());
    }

    this->addChild(this->marker);
}

RegisterMarkerEcx::~RegisterMarkerEcx()
{
}

int RegisterMarkerEcx::getRegisterIndex()
{
    return RegisterState::getRegisterEcx();
}