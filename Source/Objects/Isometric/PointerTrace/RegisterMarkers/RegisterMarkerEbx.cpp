#include "RegisterMarkerEbx.h"

#include "cocos/2d/CCSprite.h"

#include "Objects/Isometric/PointerTrace/MemoryGrid.h"
#include "Scenes/PointerTrace/RegisterState.h"

#include "Resources/IsometricObjectResources.h"

#include "Strings/PointerTrace/Assembly/RegisterEbx.h"
#include "Strings/PointerTrace/Assembly/RegisterRbx.h"

using namespace cocos2d;

RegisterMarkerEbx* RegisterMarkerEbx::create()
{
    RegisterMarkerEbx* instance = new RegisterMarkerEbx();

    instance->autorelease();
    
    return instance;
}

RegisterMarkerEbx::RegisterMarkerEbx()
{
    this->marker = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_EbxMarker);

    if (sizeof(void*) == 4)
    {
        this->registerString->setStringReplacementVariables(Strings::PointerTrace_Assembly_RegisterEbx::create());
    }
    else
    {
        this->registerString->setStringReplacementVariables(Strings::PointerTrace_Assembly_RegisterRbx::create());
    }

    this->addChild(this->marker);
}

RegisterMarkerEbx::~RegisterMarkerEbx()
{
}

int RegisterMarkerEbx::getRegisterIndex()
{
    return RegisterState::getRegisterEbx();
}