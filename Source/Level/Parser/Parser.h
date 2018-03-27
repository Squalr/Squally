#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Utils/GameUtils.h"
#include "Utils/StrUtils.h"
#include "Level/LevelMap.h"
#include "Level/Parser/CollisionParser.h"
#include "Level/Parser/DecorParser.h"
#include "Level/Parser/EntityParser.h"
#include "Level/Parser/EnvironmentParser.h"
#include "Level/Parser/ObjectParser.h"
#include "Level/Parser/ParallaxParser.h"
#include "Level/Parser/TileParser.h"

using namespace cocos2d;

class Parser
{
public:
	static LevelMap* parseMap(cocos_experimental::TMXTiledMap* mapRaw);
};
