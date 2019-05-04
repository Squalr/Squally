#include "RegisterMarkerEcx.h"

#include "cocos/2d/CCSprite.h"

#include "Objects/Isometric/PointerTrace/MemoryGrid.h"
#include "Scenes/PointerTrace/RegisterState.h"

#include "Resources/IsometricObjectResources.h"

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

    this->addChild(this->marker);
}

RegisterMarkerEcx::~RegisterMarkerEcx()
{
}

int RegisterMarkerEcx::getRegisterIndex()
{
    return RegisterState::getRegisterEcx();
}