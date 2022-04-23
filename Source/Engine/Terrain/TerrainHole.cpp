#include "TerrainHole.h"

#include "cocos/base/CCValue.h"

#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

const std::string TerrainHole::MapKey = "terrain-hole";
const std::string TerrainHole::TerrainHoleTag = "hole-tag";

TerrainHole* TerrainHole::create(ValueMap& properties)
{
	TerrainHole* instance = new TerrainHole(properties);

	instance->autorelease();

	return instance;
}

TerrainHole::TerrainHole(ValueMap& properties) : super(properties)
{
	std::string terrainHoleTag = GameUtils::getKeyOrDefault(this->properties, TerrainHole::TerrainHoleTag, Value("")).asString();

	this->addTag(terrainHoleTag);
}

TerrainHole::~TerrainHole()
{
}
