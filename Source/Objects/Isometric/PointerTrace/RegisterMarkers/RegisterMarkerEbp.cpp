#include "RegisterMarkerEbp.h"

#include "cocos/2d/CCSprite.h"

#include "Objects/Isometric/PointerTrace/MemoryGrid.h"
#include "Scenes/PointerTrace/RegisterState.h"

#include "Resources/IsometricObjectResources.h"

#include "Strings/PointerTrace/Assembly/RegisterEbp.h"
#include "Strings/PointerTrace/Assembly/RegisterRbp.h"

using namespace cocos2d;

RegisterMarkerEbp* RegisterMarkerEbp::create()
{
    RegisterMarkerEbp* instance = new RegisterMarkerEbp();

    instance->autorelease();
    
    return instance;
}

RegisterMarkerEbp::RegisterMarkerEbp()
{
    this->marker = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_EbpMarker);

    if (sizeof(void*) == 4)
    {
        this->registerString->setStringReplacementVariables(Strings::PointerTrace_Assembly_RegisterEbp::create());
    }
    else
    {
        this->registerString->setStringReplacementVariables(Strings::PointerTrace_Assembly_RegisterRbp::create());
    }

    this->addChild(this->marker);
}

RegisterMarkerEbp::~RegisterMarkerEbp()
{
}

int RegisterMarkerEbp::getRegisterIndex()
{
    return RegisterState::getRegisterEbp();
}