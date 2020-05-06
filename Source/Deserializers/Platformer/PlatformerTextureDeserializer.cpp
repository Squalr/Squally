#include "PlatformerTextureDeserializer.h"

#include "cocos/base/CCValue.h"

#include "Engine/Maps/GameObject.h"
#include "Engine/Utils/LogUtils.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Platformer/Textures/PlatformerTextures.h"

using namespace cocos2d;

const std::string PlatformerTextureDeserializer::MapKeyTypeTexture = "texture";
std::map<std::string, std::function<GameObject*(cocos2d::ValueMap)>> PlatformerTextureDeserializer::Deserializers = std::map<std::string, std::function<GameObject*(cocos2d::ValueMap)>>();

PlatformerTextureDeserializer* PlatformerTextureDeserializer::create()
{
	PlatformerTextureDeserializer* instance = new PlatformerTextureDeserializer();

	instance->autorelease();

	return instance;
}

PlatformerTextureDeserializer::PlatformerTextureDeserializer() : super(PlatformerTextureDeserializer::MapKeyTypeTexture)
{
	static bool hasInitialized = false;

	if (!hasInitialized)
	{
		hasInitialized = true;
		
		PlatformerTextureDeserializer::Deserializers[ArabicDarkTexture::MapKey] = [=](ValueMap properties) { return (GameObject*)ArabicDarkTexture::create(properties); };
		PlatformerTextureDeserializer::Deserializers[ArabicStarTexture::MapKey] = [=](ValueMap properties) { return (GameObject*)ArabicStarTexture::create(properties); };
		PlatformerTextureDeserializer::Deserializers[ArabicTexture::MapKey] = [=](ValueMap properties) { return (GameObject*)ArabicTexture::create(properties); };
		PlatformerTextureDeserializer::Deserializers[BlueGrassTexture::MapKey] = [=](ValueMap properties) { return (GameObject*)BlueGrassTexture::create(properties); };
		PlatformerTextureDeserializer::Deserializers[BrickInteriorTexture::MapKey] = [=](ValueMap properties) { return (GameObject*)BrickInteriorTexture::create(properties); };
		PlatformerTextureDeserializer::Deserializers[CastleTexture::MapKey] = [=](ValueMap properties) { return (GameObject*)CastleTexture::create(properties); };
		PlatformerTextureDeserializer::Deserializers[CavernsTexture::MapKey] = [=](ValueMap properties) { return (GameObject*)CavernsTexture::create(properties); };
		PlatformerTextureDeserializer::Deserializers[CaveTexture::MapKey] = [=](ValueMap properties) { return (GameObject*)CaveTexture::create(properties); };
		PlatformerTextureDeserializer::Deserializers[DarkGrassTexture::MapKey] = [=](ValueMap properties) { return (GameObject*)DarkGrassTexture::create(properties); };
		PlatformerTextureDeserializer::Deserializers[DryGrassTexture::MapKey] = [=](ValueMap properties) { return (GameObject*)DryGrassTexture::create(properties); };
		PlatformerTextureDeserializer::Deserializers[DryTexture::MapKey] = [=](ValueMap properties) { return (GameObject*)DryTexture::create(properties); };
		PlatformerTextureDeserializer::Deserializers[FrostTexture::MapKey] = [=](ValueMap properties) { return (GameObject*)FrostTexture::create(properties); };
		PlatformerTextureDeserializer::Deserializers[GrassTexture::MapKey] = [=](ValueMap properties) { return (GameObject*)GrassTexture::create(properties); };
		PlatformerTextureDeserializer::Deserializers[IceTexture::MapKey] = [=](ValueMap properties) { return (GameObject*)IceTexture::create(properties); };
		PlatformerTextureDeserializer::Deserializers[JungleTexture::MapKey] = [=](ValueMap properties) { return (GameObject*)JungleTexture::create(properties); };
		PlatformerTextureDeserializer::Deserializers[LavaTexture::MapKey] = [=](ValueMap properties) { return (GameObject*)LavaTexture::create(properties); };
		PlatformerTextureDeserializer::Deserializers[LeafTexture::MapKey] = [=](ValueMap properties) { return (GameObject*)LeafTexture::create(properties); };
		PlatformerTextureDeserializer::Deserializers[MarbleDarkTexture::MapKey] = [=](ValueMap properties) { return (GameObject*)MarbleDarkTexture::create(properties); };
		PlatformerTextureDeserializer::Deserializers[MarbleGrassTexture::MapKey] = [=](ValueMap properties) { return (GameObject*)MarbleGrassTexture::create(properties); };
		PlatformerTextureDeserializer::Deserializers[MarbleTexture::MapKey] = [=](ValueMap properties) { return (GameObject*)MarbleTexture::create(properties); };
		PlatformerTextureDeserializer::Deserializers[ShadeGrassTexture::MapKey] = [=](ValueMap properties) { return (GameObject*)ShadeGrassTexture::create(properties); };
		PlatformerTextureDeserializer::Deserializers[ShipAltTexture::MapKey] = [=](ValueMap properties) { return (GameObject*)ShipAltTexture::create(properties); };
		PlatformerTextureDeserializer::Deserializers[ShipDarkTexture::MapKey] = [=](ValueMap properties) { return (GameObject*)ShipDarkTexture::create(properties); };
		PlatformerTextureDeserializer::Deserializers[ShipTexture::MapKey] = [=](ValueMap properties) { return (GameObject*)ShipTexture::create(properties); };
		PlatformerTextureDeserializer::Deserializers[TempleDarkTexture::MapKey] = [=](ValueMap properties) { return (GameObject*)TempleDarkTexture::create(properties); };
		PlatformerTextureDeserializer::Deserializers[TempleGreenTexture::MapKey] = [=](ValueMap properties) { return (GameObject*)TempleGreenTexture::create(properties); };
		PlatformerTextureDeserializer::Deserializers[TempleGreenDarkTexture::MapKey] = [=](ValueMap properties) { return (GameObject*)TempleGreenDarkTexture::create(properties); };
		PlatformerTextureDeserializer::Deserializers[TempleTexture::MapKey] = [=](ValueMap properties) { return (GameObject*)TempleTexture::create(properties); };
		PlatformerTextureDeserializer::Deserializers[TrailTexture::MapKey] = [=](ValueMap properties) { return (GameObject*)TrailTexture::create(properties); };
		PlatformerTextureDeserializer::Deserializers[WoodTexture::MapKey] = [=](ValueMap properties) { return (GameObject*)WoodTexture::create(properties); };
	}
}

PlatformerTextureDeserializer::~PlatformerTextureDeserializer()
{
}

void PlatformerTextureDeserializer::deserialize(ObjectDeserializer::ObjectDeserializationRequestArgs* args)
{
	ValueMap properties = args->properties;
	std::string name = GameUtils::getKeyOrDefault(properties, GameObject::PropertyName, Value("")).asString();

	if (PlatformerTextureDeserializer::Deserializers.find(name) != PlatformerTextureDeserializer::Deserializers.end())
	{
		args->onDeserializeCallback(ObjectDeserializer::ObjectDeserializationArgs(PlatformerTextureDeserializer::Deserializers[name](properties)));
	}
	else
	{
		LogUtils::logError("Unknown texture encountered:" + name);
	}
}
