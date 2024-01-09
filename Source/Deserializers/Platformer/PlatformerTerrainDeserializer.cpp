#include "PlatformerTerrainDeserializer.h"

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

const std::string PlatformerTerrainDeserializer::MapKeyTypeTerrain = "terrain";

PlatformerTerrainDeserializer* PlatformerTerrainDeserializer::create()
{
	PlatformerTerrainDeserializer* instance = new PlatformerTerrainDeserializer();

	instance->autorelease();

	return instance;
}

PlatformerTerrainDeserializer::PlatformerTerrainDeserializer() : super(PlatformerTerrainDeserializer::MapKeyTypeTerrain, { (PropertyDeserializer*)PlatformerComponentDeserializer::create(), (PropertyDeserializer*)PlatformerQuestDeserializer::create() })
{
	this->deserializers = std::map<std::string, std::function<GameObject*(ValueMap)>>();
	
	this->deserializers[ArabicDarkTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)ArabicDarkTerrain::create(properties); };
	this->deserializers[ArabicTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)ArabicTerrain::create(properties); };
	this->deserializers[BlueGrassTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)BlueGrassTerrain::create(properties); };
	this->deserializers[CastleTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)CastleTerrain::create(properties); };
	this->deserializers[CatacombsTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)CatacombsTerrain::create(properties); };
	this->deserializers[CavernsTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)CavernsTerrain::create(properties); };
	this->deserializers[CaveTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)CaveTerrain::create(properties); };
	this->deserializers[DarkGrassTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)DarkGrassTerrain::create(properties); };
	this->deserializers[DryGrassTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)DryGrassTerrain::create(properties); };
	this->deserializers[DryTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)DryTerrain::create(properties); };
	this->deserializers[FrostTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)FrostTerrain::create(properties); };
	this->deserializers[GrassTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)GrassTerrain::create(properties); };
	this->deserializers[IceTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)IceTerrain::create(properties); };
	this->deserializers[InvisibleTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)InvisibleTerrain::create(properties); };
	this->deserializers[JungleTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)JungleTerrain::create(properties); };
	this->deserializers[LavaTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)LavaTerrain::create(properties); };
	this->deserializers[LeafTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)LeafTerrain::create(properties); };
	this->deserializers[MagmaTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MagmaTerrain::create(properties); };
	this->deserializers[MarbleDarkTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MarbleDarkTerrain::create(properties); };
	this->deserializers[MarbleGrassTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MarbleGrassTerrain::create(properties); };
	this->deserializers[MarbleTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MarbleTerrain::create(properties); };
	this->deserializers[MinesTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)MinesTerrain::create(properties); };
	this->deserializers[ObsideanTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)ObsideanTerrain::create(properties); };
	this->deserializers[RailsTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)RailsTerrain::create(properties); };
	this->deserializers[RuinsGrayDarkTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)RuinsGrayDarkTerrain::create(properties); };
	this->deserializers[RuinsGrayTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)RuinsGrayTerrain::create(properties); };
	this->deserializers[RuinsGrayThickTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)RuinsGrayThickTerrain::create(properties); };
	this->deserializers[RuinsTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)RuinsTerrain::create(properties); };
	this->deserializers[RuinsThickTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)RuinsThickTerrain::create(properties); };
	this->deserializers[ScifiTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)ScifiTerrain::create(properties); };
	this->deserializers[ShadeGrassTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)ShadeGrassTerrain::create(properties); };
	this->deserializers[ShipAltTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)ShipAltTerrain::create(properties); };
	this->deserializers[ShipTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)ShipTerrain::create(properties); };
	this->deserializers[StoneTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)StoneTerrain::create(properties); };
	this->deserializers[StoneDarkTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)StoneDarkTerrain::create(properties); };
	this->deserializers[TempleGreenTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)TempleGreenTerrain::create(properties); };
	this->deserializers[TempleDarkTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)TempleDarkTerrain::create(properties); };
	this->deserializers[TempleTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)TempleTerrain::create(properties); };
	this->deserializers[TrailTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)TrailTerrain::create(properties); };
	this->deserializers[WoodTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)WoodTerrain::create(properties); };
	this->deserializers[WoodBlackFillTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)WoodBlackFillTerrain::create(properties); };
	this->deserializers[VinesTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)VinesTerrain::create(properties); };
	this->deserializers[VoidTerrain::MapKey] = [=](ValueMap properties) { return (GameObject*)VoidTerrain::create(properties); };
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
