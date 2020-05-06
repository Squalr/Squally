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
	
	this->deserializers[ArabicDarkTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)ArabicDarkTerrain::create(properties); };
	this->deserializers[ArabicTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)ArabicTerrain::create(properties); };
	this->deserializers[BlueGrassTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)BlueGrassTerrain::create(properties); };
	this->deserializers[CastleTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)CastleTerrain::create(properties); };
	this->deserializers[CavernsTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)CavernsTerrain::create(properties); };
	this->deserializers[CaveTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)CaveTerrain::create(properties); };
	this->deserializers[DarkGrassTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)DarkGrassTerrain::create(properties); };
	this->deserializers[DryGrassTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)DryGrassTerrain::create(properties); };
	this->deserializers[DryTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)DryTerrain::create(properties); };
	this->deserializers[FrostTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)FrostTerrain::create(properties); };
	this->deserializers[GrassTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)GrassTerrain::create(properties); };
	this->deserializers[IceTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)IceTerrain::create(properties); };
	this->deserializers[JungleTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)JungleTerrain::create(properties); };
	this->deserializers[LavaTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)LavaTerrain::create(properties); };
	this->deserializers[LeafTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)LeafTerrain::create(properties); };
	this->deserializers[MarbleDarkTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MarbleDarkTerrain::create(properties); };
	this->deserializers[MarbleGrassTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MarbleGrassTerrain::create(properties); };
	this->deserializers[MarbleTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MarbleTerrain::create(properties); };
	this->deserializers[ShadeGrassTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)ShadeGrassTerrain::create(properties); };
	this->deserializers[ShipAltTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)ShipAltTerrain::create(properties); };
	this->deserializers[ShipTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)ShipTerrain::create(properties); };
	this->deserializers[TempleGreenTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)TempleGreenTerrain::create(properties); };
	this->deserializers[TempleDarkTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)TempleDarkTerrain::create(properties); };
	this->deserializers[TempleTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)TempleTerrain::create(properties); };
	this->deserializers[TrailTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)TrailTerrain::create(properties); };
	this->deserializers[WoodTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)WoodTerrain::create(properties); };
}

PlatformerTerrainDeserializer::~PlatformerTerrainDeserializer()
{
}

void PlatformerTerrainDeserializer::deserialize(ObjectDeserializer::ObjectDeserializationRequestArgs* args)
{
	ValueMap properties = args->properties;
	std::string name = GameUtils::getKeyOrDefault(properties, GameObject::PropertyName, Value("")).asString();

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
