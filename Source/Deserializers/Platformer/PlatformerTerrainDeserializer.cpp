#include "PlatformerTerrainDeserializer.h"

#include "cocos/base/CCValue.h"

#include "Engine/Maps/GameObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Terrain/PlatformerTerrain.h"

using namespace cocos2d;

const std::string PlatformerTerrainDeserializer::MapKeyTypeTerrain = "terrain";

PlatformerTerrainDeserializer* PlatformerTerrainDeserializer::create()
{
	PlatformerTerrainDeserializer* instance = new PlatformerTerrainDeserializer();

	instance->autorelease();

	return instance;
}

PlatformerTerrainDeserializer::PlatformerTerrainDeserializer() : super(PlatformerTerrainDeserializer::MapKeyTypeTerrain)
{
	this->deserializers = std::map<std::string, std::function<GameObject*(ValueMap)>>();

	this->deserializers[BlueGrassTerrain::MapKeyTerrainTypeBlueGrass] = [=](ValueMap properties) { return (GameObject*)BlueGrassTerrain::create(properties); };
	this->deserializers[CastleTerrain::MapKeyTerrainTypeCastle] = [=](ValueMap properties) { return (GameObject*)CastleTerrain::create(properties); };
	this->deserializers[CavernsTerrain::MapKeyTerrainTypeCaverns] = [=](ValueMap properties) { return (GameObject*)CavernsTerrain::create(properties); };
	this->deserializers[CaveTerrain::MapKeyTerrainTypeCave] = [=](ValueMap properties) { return (GameObject*)CaveTerrain::create(properties); };
	this->deserializers[DarkGrassTerrain::MapKeyTerrainTypeDarkGrass] = [=](ValueMap properties) { return (GameObject*)DarkGrassTerrain::create(properties); };
	this->deserializers[DryGrassTerrain::MapKeyTerrainTypeDryGrass] = [=](ValueMap properties) { return (GameObject*)DryGrassTerrain::create(properties); };
	this->deserializers[DryTerrain::MapKeyTerrainTypeDry] = [=](ValueMap properties) { return (GameObject*)DryTerrain::create(properties); };
	this->deserializers[FrostTerrain::MapKeyTerrainTypeFrost] = [=](ValueMap properties) { return (GameObject*)FrostTerrain::create(properties); };
	this->deserializers[GrassTerrain::MapKeyTerrainTypeGrass] = [=](ValueMap properties) { return (GameObject*)GrassTerrain::create(properties); };
	this->deserializers[IceTerrain::MapKeyTerrainTypeIce] = [=](ValueMap properties) { return (GameObject*)IceTerrain::create(properties); };
	this->deserializers[JungleTerrain::MapKeyTerrainTypeJungle] = [=](ValueMap properties) { return (GameObject*)JungleTerrain::create(properties); };
	this->deserializers[LeafTerrain::MapKeyTerrainTypeLeaf] = [=](ValueMap properties) { return (GameObject*)LeafTerrain::create(properties); };
	this->deserializers[MarbleGrassTerrain::MapKeyTerrainTypeMarbleGrass] = [=](ValueMap properties) { return (GameObject*)MarbleGrassTerrain::create(properties); };
	this->deserializers[MarbleTerrain::MapKeyTerrainTypeMarble] = [=](ValueMap properties) { return (GameObject*)MarbleTerrain::create(properties); };
	this->deserializers[ShadeGrassTerrain::MapKeyTerrainTypeShadeGrass] = [=](ValueMap properties) { return (GameObject*)ShadeGrassTerrain::create(properties); };
	this->deserializers[TrailTerrain::MapKeyTerrainTypeTrail] = [=](ValueMap properties) { return (GameObject*)TrailTerrain::create(properties); };
	this->deserializers[WoodTerrain::MapKeyTerrainTypeWood] = [=](ValueMap properties) { return (GameObject*)WoodTerrain::create(properties); };
}

PlatformerTerrainDeserializer::~PlatformerTerrainDeserializer()
{
}

void PlatformerTerrainDeserializer::deserialize(ObjectDeserializer::ObjectDeserializationRequestArgs* args)
{
	ValueMap properties = args->properties;
	std::string name = GameUtils::getKeyOrDefault(properties, GameObject::MapKeyPropertyName, Value("")).asString();

	if (this->deserializers.find(name) != this->deserializers.end())
	{
		args->onDeserializeCallback(ObjectDeserializer::ObjectDeserializationArgs(this->deserializers[name](properties)));
	}
	else
	{
		CCLOG("Unknown terrain encountered: %s", name.c_str());
	}
}
