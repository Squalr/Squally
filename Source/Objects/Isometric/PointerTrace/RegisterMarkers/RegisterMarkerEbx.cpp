#include "RegisterMarkerEbx.h"

#include "cocos/2d/CCSprite.h"

#include "Objects/Isometric/PointerTrace/MemoryGrid.h"
#include "Scenes/PointerTrace/RegisterState.h"

#include "Resources/IsometricObjectResources.h"

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

    this->addChild(this->marker);
}

RegisterMarkerEbx::~RegisterMarkerEbx()
{
}

int RegisterMarkerEbx::getRegisterIndex()
{
    return RegisterState::getRegisterEbx();
}