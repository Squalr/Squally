#include "PlatformerTerrainDeserializer.h"

#include "cocos/base/CCValue.h"

#include "Engine/Maps/GameObject.h"
#include "Engine/Utils/LogUtils.h"
#include "Engine/Utils/GameUtils.h"
#include "Deserializers/Platformer/PlatformerAttachedBehaviorDeserializer.h"
#include "Deserializers/Platformer/PlatformerQuestDeserializer.h"
#include "Scenes/Platformer/Terrain/PlatformerTerrain.h"

using namespace cocos2d;

const std::string PlatformerTerrainDeserializer::MapKeyTypeTerrain = "terrain";

PlatformerTerrainDeserializer* PlatformerTerrainDeserializer::create()
{
	PlatformerTerrainDeserializer* instance = new PlatformerTerrainDeserializer();

	instance->autorelease();

	return instance;
}

PlatformerTerrainDeserializer::PlatformerTerrainDeserializer() : super(PlatformerTerrainDeserializer::MapKeyTypeTerrain, { (PropertyDeserializer*)PlatformerAttachedBehaviorDeserializer::create(), (PropertyDeserializer*)PlatformerQuestDeserializer::create() })
{
	this->deserializers = std::map<std::string, std::function<GameObject*(ValueMap)>>();

	this->deserializers[BlueGrassTerrain::MapKeyTerrainType] = [=](ValueMap properties) { return (GameObject*)BlueGrassTerrain::create(properties); };
	this->deserializers[CastleTerrain::MapKeyTerrainType] = [=](ValueMap properties) { return (GameObject*)CastleTerrain::create(properties); };
	this->deserializers[CavernsTerrain::MapKeyTerrainType] = [=](ValueMap properties) { return (GameObject*)CavernsTerrain::create(properties); };
	this->deserializers[CaveTerrain::MapKeyTerrainType] = [=](ValueMap properties) { return (GameObject*)CaveTerrain::create(properties); };
	this->deserializers[DarkGrassTerrain::MapKeyTerrainType] = [=](ValueMap properties) { return (GameObject*)DarkGrassTerrain::create(properties); };
	this->deserializers[DryGrassTerrain::MapKeyTerrainType] = [=](ValueMap properties) { return (GameObject*)DryGrassTerrain::create(properties); };
	this->deserializers[DryTerrain::MapKeyTerrainType] = [=](ValueMap properties) { return (GameObject*)DryTerrain::create(properties); };
	this->deserializers[FrostTerrain::MapKeyTerrainType] = [=](ValueMap properties) { return (GameObject*)FrostTerrain::create(properties); };
	this->deserializers[GrassTerrain::MapKeyTerrainType] = [=](ValueMap properties) { return (GameObject*)GrassTerrain::create(properties); };
	this->deserializers[IceTerrain::MapKeyTerrainType] = [=](ValueMap properties) { return (GameObject*)IceTerrain::create(properties); };
	this->deserializers[JungleTerrain::MapKeyTerrainType] = [=](ValueMap properties) { return (GameObject*)JungleTerrain::create(properties); };
	this->deserializers[LavaTerrain::MapKeyTerrainType] = [=](ValueMap properties) { return (GameObject*)LavaTerrain::create(properties); };
	this->deserializers[LeafTerrain::MapKeyTerrainType] = [=](ValueMap properties) { return (GameObject*)LeafTerrain::create(properties); };
	this->deserializers[MarbleDarkTerrain::MapKeyTerrainType] = [=](ValueMap properties) { return (GameObject*)MarbleDarkTerrain::create(properties); };
	this->deserializers[MarbleGrassTerrain::MapKeyTerrainType] = [=](ValueMap properties) { return (GameObject*)MarbleGrassTerrain::create(properties); };
	this->deserializers[MarbleTerrain::MapKeyTerrainType] = [=](ValueMap properties) { return (GameObject*)MarbleTerrain::create(properties); };
	this->deserializers[ShadeGrassTerrain::MapKeyTerrainType] = [=](ValueMap properties) { return (GameObject*)ShadeGrassTerrain::create(properties); };
	this->deserializers[ShipAltTerrain::MapKeyTerrainType] = [=](ValueMap properties) { return (GameObject*)ShipAltTerrain::create(properties); };
	this->deserializers[ShipTerrain::MapKeyTerrainType] = [=](ValueMap properties) { return (GameObject*)ShipTerrain::create(properties); };
	this->deserializers[TempleGreenTerrain::MapKeyTerrainType] = [=](ValueMap properties) { return (GameObject*)TempleGreenTerrain::create(properties); };
	this->deserializers[TempleDarkTerrain::MapKeyTerrainType] = [=](ValueMap properties) { return (GameObject*)TempleDarkTerrain::create(properties); };
	this->deserializers[TempleTerrain::MapKeyTerrainType] = [=](ValueMap properties) { return (GameObject*)TempleTerrain::create(properties); };
	this->deserializers[TrailTerrain::MapKeyTerrainType] = [=](ValueMap properties) { return (GameObject*)TrailTerrain::create(properties); };
	this->deserializers[WoodTerrain::MapKeyTerrainType] = [=](ValueMap properties) { return (GameObject*)WoodTerrain::create(properties); };
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
		GameObject* terrain = this->deserializers[name](properties);

		this->deserializeProperties(terrain, properties);

		args->onDeserializeCallback(ObjectDeserializer::ObjectDeserializationArgs(terrain));
	}
	else
	{
		LogUtils::logError("Unknown terrain encountered:" + name);
	}
}
