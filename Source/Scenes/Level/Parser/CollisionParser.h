#pragma once
#include "cocos2d.h"

#include "Objects/Objects.h"
#include "Objects/SerializableLayer.h"
#include "Resources.h"
#include "Utils/GameUtils.h"

#include "Keys/CollisionKeys.h"
#include "Keys/GeneralKeys.h"

using namespace cocos2d;

class CollisionParser
{
public:
static SerializableLayer* parse(TMXObjectGroup* objectGroup);

};
