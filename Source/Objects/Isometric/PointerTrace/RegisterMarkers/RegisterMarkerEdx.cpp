#include "RegisterMarkerEdx.h"

#include "cocos/2d/CCSprite.h"

#include "Objects/Isometric/PointerTrace/MemoryGrid.h"
#include "Scenes/PointerTrace/RegisterState.h"

#include "Resources/IsometricObjectResources.h"

using namespace cocos2d;

RegisterMarkerEdx* RegisterMarkerEdx::create()
{
    RegisterMarkerEdx* instance = new RegisterMarkerEdx();

    instance->autorelease();
    
    return instance;
}

RegisterMarkerEdx::RegisterMarkerEdx()
{
    this->marker = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_EdxMarker);

    this->addChild(this->marker);
}

RegisterMarkerEdx::~RegisterMarkerEdx()
{
}

int RegisterMarkerEdx::getRegisterIndex()
{
    return RegisterState::getRegisterEdx();
}