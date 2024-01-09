#include "MiniMapTerrainDeserializer.h"

#include "cocos/base/CCValue.h"

#include "Engine/Maps/GameObject.h"
#include "Engine/Utils/LogUtils.h"
#include "Engine/Utils/GameUtils.h"
#include "Deserializers/Platformer/PlatformerComponentDeserializer.h"
#include "Deserializers/Platformer/PlatformerQuestDeserializer.h"
#include "Scenes/Platformer/Terrain/ArabicDarkTerrain.h"
#include "Scenes/Platformer/Terrain/ArabicTerrain.h"
#include "Scenes/Platformer/Terrain/BlueGrassTerrain.h"
#include "Scenes/Platformer/Terrain/CastleTerrain.h"
#include "Scenes/Platformer/Terrain/CavernsTerrain.h"
#include "Scenes/Platformer/Terrain/CatacombsTerrain.h"
#include "Scenes/Platformer/Terrain/CaveTerrain.h"
#include "Scenes/Platformer/Terrain/DarkGrassTerrain.h"
#include "Scenes/Platformer/Terrain/DryGrassTerrain.h"
#include "Scenes/Platformer/Terrain/DryTerrain.h"
#include "Scenes/Platformer/Terrain/FrostTerrain.h"
#include "Scenes/Platformer/Terrain/GrassTerrain.h"
#include "Scenes/Platformer/Terrain/IceTerrain.h"
#include "Scenes/Platformer/Terrain/InvisibleTerrain.h"
#include "Scenes/Platformer/Terrain/JungleTerrain.h"
#include "Scenes/Platformer/Terrain/LavaTerrain.h"
#include "Scenes/Platformer/Terrain/LeafTerrain.h"
#include "Scenes/Platformer/Terrain/MagmaTerrain.h"
#include "Scenes/Platformer/Terrain/MarbleDarkTerrain.h"
#include "Scenes/Platformer/Terrain/MarbleGrassTerrain.h"
#include "Scenes/Platformer/Terrain/MarbleTerrain.h"
#include "Scenes/Platformer/Terrain/MinesTerrain.h"
#include "Scenes/Platformer/Terrain/MiniMapTerrain.h"
#include "Scenes/Platformer/Terrain/ObsideanTerrain.h"
#include "Scenes/Platformer/Terrain/RailsTerrain.h"
#include "Scenes/Platformer/Terrain/RuinsGrayDarkTerrain.h"
#include "Scenes/Platformer/Terrain/RuinsGrayTerrain.h"
#include "Scenes/Platformer/Terrain/RuinsGrayThickTerrain.h"
#include "Scenes/Platformer/Terrain/RuinsTerrain.h"
#include "Scenes/Platformer/Terrain/RuinsThickTerrain.h"
#include "Scenes/Platformer/Terrain/ScifiTerrain.h"
#include "Scenes/Platformer/Terrain/ShadeGrassTerrain.h"
#include "Scenes/Platformer/Terrain/ShipAltTerrain.h"
#include "Scenes/Platformer/Terrain/ShipTerrain.h"
#include "Scenes/Platformer/Terrain/StoneDarkTerrain.h"
#include "Scenes/Platformer/Terrain/StoneTerrain.h"
#include "Scenes/Platformer/Terrain/TempleGreenTerrain.h"
#include "Scenes/Platformer/Terrain/TempleDarkTerrain.h"
#include "Scenes/Platformer/Terrain/TempleTerrain.h"
#include "Scenes/Platformer/Terrain/TrailTerrain.h"
#include "Scenes/Platformer/Terrain/WoodTerrain.h"
#include "Scenes/Platformer/Terrain/WoodBlackFillTerrain.h"
#include "Scenes/Platformer/Terrain/VinesTerrain.h"
#include "Scenes/Platformer/Terrain/VoidTerrain.h"

using namespace cocos2d;

const std::string MiniMapTerrainDeserializer::MapKeyTypeTerrain = "terrain";

MiniMapTerrainDeserializer* MiniMapTerrainDeserializer::create()
{
	MiniMapTerrainDeserializer* instance = new MiniMapTerrainDeserializer();

	instance->autorelease();

	return instance;
}

MiniMapTerrainDeserializer::MiniMapTerrainDeserializer() : super(MiniMapTerrainDeserializer::MapKeyTypeTerrain)
{
	this->deserializers = std::map<std::string, std::function<GameObject*(ValueMap)>>();

	this->deserializers[ArabicDarkTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapTerrain::create(properties, ArabicDarkTerrain::MiniMapColor); };
	this->deserializers[ArabicTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapTerrain::create(properties, ArabicTerrain::MiniMapColor); };
	this->deserializers[BlueGrassTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapTerrain::create(properties, BlueGrassTerrain::MiniMapColor); };
	this->deserializers[CastleTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapTerrain::create(properties, CastleTerrain::MiniMapColor); };
	this->deserializers[CatacombsTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapTerrain::create(properties, CatacombsTerrain::MiniMapColor); };
	this->deserializers[CavernsTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapTerrain::create(properties, CavernsTerrain::MiniMapColor); };
	this->deserializers[CaveTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapTerrain::create(properties, CaveTerrain::MiniMapColor); };
	this->deserializers[DarkGrassTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapTerrain::create(properties, DarkGrassTerrain::MiniMapColor); };
	this->deserializers[DryGrassTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapTerrain::create(properties, DryGrassTerrain::MiniMapColor); };
	this->deserializers[DryTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapTerrain::create(properties, DryTerrain::MiniMapColor); };
	this->deserializers[FrostTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapTerrain::create(properties, FrostTerrain::MiniMapColor); };
	this->deserializers[GrassTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapTerrain::create(properties, GrassTerrain::MiniMapColor); };
	this->deserializers[IceTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapTerrain::create(properties, IceTerrain::MiniMapColor); };
	this->deserializers[InvisibleTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapTerrain::create(properties, InvisibleTerrain::MiniMapColor); };
	this->deserializers[JungleTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapTerrain::create(properties, JungleTerrain::MiniMapColor); };
	this->deserializers[LavaTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapTerrain::create(properties, LavaTerrain::MiniMapColor); };
	this->deserializers[LeafTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapTerrain::create(properties, LeafTerrain::MiniMapColor); };
	this->deserializers[MagmaTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapTerrain::create(properties, MagmaTerrain::MiniMapColor); };
	this->deserializers[MarbleDarkTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapTerrain::create(properties, MarbleDarkTerrain::MiniMapColor); };
	this->deserializers[MarbleGrassTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapTerrain::create(properties, MarbleGrassTerrain::MiniMapColor); };
	this->deserializers[MarbleTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapTerrain::create(properties, MarbleTerrain::MiniMapColor); };
	this->deserializers[MinesTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapTerrain::create(properties, MinesTerrain::MiniMapColor); };
	this->deserializers[ObsideanTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapTerrain::create(properties, ObsideanTerrain::MiniMapColor); };
	this->deserializers[RailsTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapTerrain::create(properties, RailsTerrain::MiniMapColor); };
	this->deserializers[RuinsGrayDarkTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapTerrain::create(properties, RuinsGrayDarkTerrain::MiniMapColor); };
	this->deserializers[RuinsGrayTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapTerrain::create(properties, RuinsGrayTerrain::MiniMapColor); };
	this->deserializers[RuinsGrayThickTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapTerrain::create(properties, RuinsGrayThickTerrain::MiniMapColor); };
	this->deserializers[RuinsTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapTerrain::create(properties, RuinsTerrain::MiniMapColor); };
	this->deserializers[RuinsThickTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapTerrain::create(properties, RuinsThickTerrain::MiniMapColor); };
	this->deserializers[ScifiTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapTerrain::create(properties, ScifiTerrain::MiniMapColor); };
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
	this->deserializers[WoodBlackFillTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapTerrain::create(properties, WoodBlackFillTerrain::MiniMapColor); };
	// this->deserializers[VinesTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapTerrain::create(properties, VinesTerrain::MiniMapColor); };
	this->deserializers[VoidTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MiniMapTerrain::create(properties, VoidTerrain::MiniMapColor); };
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
