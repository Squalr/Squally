#include "RegisterMarkerEax.h"

#include "cocos/2d/CCSprite.h"

#include "Objects/Isometric/PointerTrace/MemoryGrid.h"
#include "Scenes/PointerTrace/RegisterState.h"

#include "Resources/IsometricObjectResources.h"

#include "Strings/PointerTrace/Assembly/RegisterEax.h"
#include "Strings/PointerTrace/Assembly/RegisterRax.h"

using namespace cocos2d;

RegisterMarkerEax* RegisterMarkerEax::create()
{
    RegisterMarkerEax* instance = new RegisterMarkerEax();

    instance->autorelease();
    
    return instance;
}

RegisterMarkerEax::RegisterMarkerEax()
{
    this->marker = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_EaxMarker);

    if (sizeof(void*) == 4)
    {
        this->registerString->setStringReplacementVariables(Strings::PointerTrace_Assembly_RegisterEax::create());
    }
    else
    {
        this->registerString->setStringReplacementVariables(Strings::PointerTrace_Assembly_RegisterRax::create());
    }

    this->addChild(this->marker);
}

RegisterMarkerEax::~RegisterMarkerEax()
{
}

int RegisterMarkerEax::getRegisterIndex()
{
    return RegisterState::getRegisterEax();
}