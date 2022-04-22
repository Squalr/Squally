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
	
	if (this->polylinePoints.empty())
	{
		CSize size = CSize(
			GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyWidth, Value(0.0f)).asFloat(),
			GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyHeight, Value(0.0f)).asFloat()
		);

		this->polylinePoints = std::vector<Vec2>({
			Vec2(-size.width / 2.0f, -size.height / 2.0f),
			Vec2(-size.width / 2.0f, size.height / 2.0f),
			Vec2(size.width / 2.0f, size.height / 2.0f),
			Vec2(size.width / 2.0f, -size.height / 2.0f)
		});
	}
}

TerrainHole::~TerrainHole()
{
}
