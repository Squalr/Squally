#include "MiniMapTerrainDeserializer.h"

#include "cocos/base/CCValue.h"

#include "Engine/Maps/GameObject.h"
#include "Engine/Utils/LogUtils.h"
#include "Engine/Utils/GameUtils.h"
#include "Deserializers/Platformer/PlatformerAttachedBehaviorDeserializer.h"
#include "Deserializers/Platformer/PlatformerQuestDeserializer.h"
#include "Scenes/Platformer/Terrain/PlatformerTerrain.h"

using namespace cocos2d;

const std::string MiniMapTerrainDeserializer::MapKeyTypeTerrain = "terrain";

MiniMapTerrainDeserializer* MiniMapTerrainDeserializer::create()
{
	MiniMapTerrainDeserializer* instance = new MiniMapTerrainDeserializer();

	instance->autorelease();

	return instance;
}

MiniMapTerrainDeserializer::MiniMapTerrainDeserializer() : super(MiniMapTerrainDeserializer::MapKeyTypeTerrain, { (PropertyDeserializer*)PlatformerAttachedBehaviorDeserializer::create(), (PropertyDeserializer*)PlatformerQuestDeserializer::create() })
{
	this->deserializers = std::map<std::string, std::function<GameObject*(ValueMap)>>();
	
	this->deserializers[ArabicDarkTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapTerrain::create(properties, ArabicDarkTerrain::MiniMapColor); };
	this->deserializers[ArabicTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapTerrain::create(properties, ArabicTerrain::MiniMapColor); };
	this->deserializers[BlueGrassTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapTerrain::create(properties, BlueGrassTerrain::MiniMapColor); };
	this->deserializers[CastleTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapTerrain::create(properties, CastleTerrain::MiniMapColor); };
	this->deserializers[CavernsTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapTerrain::create(properties, CavernsTerrain::MiniMapColor); };
	this->deserializers[CaveTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapTerrain::create(properties, CaveTerrain::MiniMapColor); };
	this->deserializers[DarkGrassTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapTerrain::create(properties, DarkGrassTerrain::MiniMapColor); };
	this->deserializers[DryGrassTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapTerrain::create(properties, DryGrassTerrain::MiniMapColor); };
	this->deserializers[DryTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapTerrain::create(properties, DryTerrain::MiniMapColor); };
	this->deserializers[FrostTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapTerrain::create(properties, FrostTerrain::MiniMapColor); };
	this->deserializers[GrassTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapTerrain::create(properties, GrassTerrain::MiniMapColor); };
	this->deserializers[IceTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapTerrain::create(properties, IceTerrain::MiniMapColor); };
	this->deserializers[JungleTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapTerrain::create(properties, JungleTerrain::MiniMapColor); };
	this->deserializers[LavaTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapTerrain::create(properties, LavaTerrain::MiniMapColor); };
	this->deserializers[LeafTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapTerrain::create(properties, LeafTerrain::MiniMapColor); };
	this->deserializers[MarbleDarkTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapTerrain::create(properties, MarbleDarkTerrain::MiniMapColor); };
	this->deserializers[MarbleGrassTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapTerrain::create(properties, MarbleGrassTerrain::MiniMapColor); };
	this->deserializers[MarbleTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapTerrain::create(properties, MarbleTerrain::MiniMapColor); };
	this->deserializers[MinesTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapTerrain::create(properties, MinesTerrain::MiniMapColor); };
	this->deserializers[RailsTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapTerrain::create(properties, RailsTerrain::MiniMapColor); };
	this->deserializers[RuinsGrayDarkTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapTerrain::create(properties, RuinsGrayDarkTerrain::MiniMapColor); };
	this->deserializers[RuinsGrayTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapTerrain::create(properties, RuinsGrayTerrain::MiniMapColor); };
	this->deserializers[RuinsGrayThickTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapTerrain::create(properties, RuinsGrayThickTerrain::MiniMapColor); };
	this->deserializers[RuinsTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapTerrain::create(properties, RuinsTerrain::MiniMapColor); };
	this->deserializers[RuinsThickTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapTerrain::create(properties, RuinsThickTerrain::MiniMapColor); };
	this->deserializers[ShadeGrassTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapTerrain::create(properties, ShadeGrassTerrain::MiniMapColor); };
	this->deserializers[ShipAltTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapTerrain::create(properties, ShipAltTerrain::MiniMapColor); };
	this->deserializers[ShipTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapTerrain::create(properties, ShipTerrain::MiniMapColor); };
	this->deserializers[StoneTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapTerrain::create(properties, StoneTerrain::MiniMapColor); };
	this->deserializers[StoneDarkTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapTerrain::create(properties, StoneDarkTerrain::MiniMapColor); };
	this->deserializers[TempleGreenTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapTerrain::create(properties, TempleGreenTerrain::MiniMapColor); };
	this->deserializers[TempleDarkTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapTerrain::create(properties, TempleDarkTerrain::MiniMapColor); };
	this->deserializers[TempleTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapTerrain::create(properties, TempleTerrain::MiniMapColor); };
	this->deserializers[TrailTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapTerrain::create(properties, TrailTerrain::MiniMapColor); };
	this->deserializers[WoodTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapTerrain::create(properties, WoodTerrain::MiniMapColor); };
}

MiniMapTerrainDeserializer::~MiniMapTerrainDeserializer()
{
}

void MiniMapTerrainDeserializer::deserialize(ObjectDeserializer::ObjectDeserializationRequestArgs* args)
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
