#include "RegisterMarkerEsi.h"

#include "cocos/2d/CCSprite.h"

#include "Objects/Isometric/PointerTrace/MemoryGrid.h"
#include "Scenes/PointerTrace/RegisterState.h"

#include "Resources/IsometricObjectResources.h"

#include "Strings/PointerTrace/Assembly/RegisterEsi.h"
#include "Strings/PointerTrace/Assembly/RegisterRsi.h"

using namespace cocos2d;

RegisterMarkerEsi* RegisterMarkerEsi::create()
{
    RegisterMarkerEsi* instance = new RegisterMarkerEsi();

    instance->autorelease();
    
    return instance;
}

RegisterMarkerEsi::RegisterMarkerEsi()
{
    this->marker = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_EsiMarker);

    if (sizeof(void*) == 4)
    {
        this->registerString->setStringReplacementVariables(Strings::PointerTrace_Assembly_RegisterEsi::create());
    }
    else
    {
        this->registerString->setStringReplacementVariables(Strings::PointerTrace_Assembly_RegisterRsi::create());
    }

    this->addChild(this->marker);
}

RegisterMarkerEsi::~RegisterMarkerEsi()
{
}

int RegisterMarkerEsi::getRegisterIndex()
{
    return RegisterState::getRegisterEsi();
}