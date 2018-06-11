#pragma once
#include "cocos2d.h"

#include "Engine/Maps/SerializableLayer.h"
#include "Engine/Maps/Keys/CollisionKeys.h"
#include "Engine/Maps/Keys/GeneralKeys.h"
#include "Objects/Objects.h"
#include "Resources.h"
#include "Utils/GameUtils.h"

using namespace cocos2d;

class CollisionParser
{
public:
static SerializableLayer* parse(TMXObjectGroup* objectGroup);

};
