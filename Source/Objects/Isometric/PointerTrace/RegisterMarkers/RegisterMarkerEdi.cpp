#include "RegisterMarkerEdi.h"

#include "cocos/2d/CCSprite.h"

#include "Objects/Isometric/PointerTrace/MemoryGrid.h"
#include "Scenes/PointerTrace/RegisterState.h"

#include "Resources/IsometricObjectResources.h"

using namespace cocos2d;

RegisterMarkerEdi* RegisterMarkerEdi::create()
{
    RegisterMarkerEdi* instance = new RegisterMarkerEdi();

    instance->autorelease();
    
    return instance;
}

RegisterMarkerEdi::RegisterMarkerEdi()
{
    this->marker = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_EdiMarker);

    this->addChild(this->marker);
}

RegisterMarkerEdi::~RegisterMarkerEdi()
{
}

int RegisterMarkerEdi::getRegisterIndex()
{
    return RegisterState::getRegisterEdi();
}