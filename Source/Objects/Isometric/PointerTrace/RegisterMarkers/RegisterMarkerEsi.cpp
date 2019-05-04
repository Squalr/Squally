#include "RegisterMarkerEsi.h"

#include "cocos/2d/CCSprite.h"

#include "Objects/Isometric/PointerTrace/MemoryGrid.h"
#include "Scenes/PointerTrace/RegisterState.h"

#include "Resources/IsometricObjectResources.h"

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

    this->addChild(this->marker);
}

RegisterMarkerEsi::~RegisterMarkerEsi()
{
}

int RegisterMarkerEsi::getRegisterIndex()
{
    return RegisterState::getRegisterEsi();
}