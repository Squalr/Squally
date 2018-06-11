#pragma once
#include "cocos2d.h"

#include "Engine/Maps/SerializableMap.h"
#include "Resources.h"
#include "Utils/GameUtils.h"
#include "Utils/StrUtils.h"

#include "CollisionParser.h"
#include "DecorParser.h"
#include "EntityParser.h"
#include "EnvironmentParser.h"
#include "ObjectParser.h"
#include "ParallaxParser.h"
#include "TileParser.h"

using namespace cocos2d;

class Parser
{
public:
	static SerializableMap* parseMap(std::string levelFile);
};
