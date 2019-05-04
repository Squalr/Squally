#include "RegisterMarkerEsp.h"

#include "cocos/2d/CCSprite.h"

#include "Objects/Isometric/PointerTrace/MemoryGrid.h"
#include "Scenes/PointerTrace/RegisterState.h"

#include "Resources/IsometricObjectResources.h"

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

    this->addChild(this->marker);
}

RegisterMarkerEsp::~RegisterMarkerEsp()
{
}

int RegisterMarkerEsp::getRegisterIndex()
{
    return RegisterState::getRegisterEsp();
}