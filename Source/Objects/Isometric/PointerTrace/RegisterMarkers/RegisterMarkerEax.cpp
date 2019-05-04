#include "RegisterMarkerEax.h"

#include "cocos/2d/CCSprite.h"

#include "Objects/Isometric/PointerTrace/MemoryGrid.h"
#include "Scenes/PointerTrace/RegisterState.h"

#include "Resources/IsometricObjectResources.h"

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

    this->addChild(this->marker);
}

RegisterMarkerEax::~RegisterMarkerEax()
{
}

int RegisterMarkerEax::getRegisterIndex()
{
    return RegisterState::getRegisterEax();
}