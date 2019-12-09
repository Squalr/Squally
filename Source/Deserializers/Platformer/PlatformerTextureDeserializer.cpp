#include "PlatformerTextureDeserializer.h"

#include "cocos/base/CCValue.h"

#include "Engine/Maps/GameObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Platformer/Textures/PlatformerTextures.h"

using namespace cocos2d;

const std::string PlatformerTextureDeserializer::MapKeyTypeTexture = "texture";

PlatformerTextureDeserializer* PlatformerTextureDeserializer::create()
{
	PlatformerTextureDeserializer* instance = new PlatformerTextureDeserializer();

	instance->autorelease();

	return instance;
}

PlatformerTextureDeserializer::PlatformerTextureDeserializer() : super(PlatformerTextureDeserializer::MapKeyTypeTexture)
{
	this->deserializers = std::map<std::string, std::function<GameObject*(ValueMap)>>();

	this->deserializers[BlueGrassTexture::MapKeyTextureType] = [=](ValueMap properties) { return (GameObject*)BlueGrassTexture::create(properties); };
	this->deserializers[BrickInteriorTexture::MapKeyTextureType] = [=](ValueMap properties) { return (GameObject*)BrickInteriorTexture::create(properties); };
	this->deserializers[CastleTexture::MapKeyTextureType] = [=](ValueMap properties) { return (GameObject*)CastleTexture::create(properties); };
	this->deserializers[CavernsTexture::MapKeyTextureType] = [=](ValueMap properties) { return (GameObject*)CavernsTexture::create(properties); };
	this->deserializers[CaveTexture::MapKeyTextureType] = [=](ValueMap properties) { return (GameObject*)CaveTexture::create(properties); };
	this->deserializers[DarkGrassTexture::MapKeyTextureType] = [=](ValueMap properties) { return (GameObject*)DarkGrassTexture::create(properties); };
	this->deserializers[DryGrassTexture::MapKeyTextureType] = [=](ValueMap properties) { return (GameObject*)DryGrassTexture::create(properties); };
	this->deserializers[DryTexture::MapKeyTextureType] = [=](ValueMap properties) { return (GameObject*)DryTexture::create(properties); };
	this->deserializers[FrostTexture::MapKeyTextureType] = [=](ValueMap properties) { return (GameObject*)FrostTexture::create(properties); };
	this->deserializers[GrassTexture::MapKeyTextureType] = [=](ValueMap properties) { return (GameObject*)GrassTexture::create(properties); };
	this->deserializers[IceTexture::MapKeyTextureType] = [=](ValueMap properties) { return (GameObject*)IceTexture::create(properties); };
	this->deserializers[JungleTexture::MapKeyTextureType] = [=](ValueMap properties) { return (GameObject*)JungleTexture::create(properties); };
	this->deserializers[LavaTexture::MapKeyTextureType] = [=](ValueMap properties) { return (GameObject*)LavaTexture::create(properties); };
	this->deserializers[LeafTexture::MapKeyTextureType] = [=](ValueMap properties) { return (GameObject*)LeafTexture::create(properties); };
	this->deserializers[MarbleDarkTexture::MapKeyTextureType] = [=](ValueMap properties) { return (GameObject*)MarbleDarkTexture::create(properties); };
	this->deserializers[MarbleGrassTexture::MapKeyTextureType] = [=](ValueMap properties) { return (GameObject*)MarbleGrassTexture::create(properties); };
	this->deserializers[MarbleTexture::MapKeyTextureType] = [=](ValueMap properties) { return (GameObject*)MarbleTexture::create(properties); };
	this->deserializers[ShadeGrassTexture::MapKeyTextureType] = [=](ValueMap properties) { return (GameObject*)ShadeGrassTexture::create(properties); };
	this->deserializers[ShipAltTexture::MapKeyTextureType] = [=](ValueMap properties) { return (GameObject*)ShipAltTexture::create(properties); };
	this->deserializers[ShipTexture::MapKeyTextureType] = [=](ValueMap properties) { return (GameObject*)ShipTexture::create(properties); };
	this->deserializers[TempleDarkTexture::MapKeyTextureType] = [=](ValueMap properties) { return (GameObject*)TempleDarkTexture::create(properties); };
	this->deserializers[TempleTexture::MapKeyTextureType] = [=](ValueMap properties) { return (GameObject*)TempleTexture::create(properties); };
	this->deserializers[TrailTexture::MapKeyTextureType] = [=](ValueMap properties) { return (GameObject*)TrailTexture::create(properties); };
	this->deserializers[WoodTexture::MapKeyTextureType] = [=](ValueMap properties) { return (GameObject*)WoodTexture::create(properties); };
}

PlatformerTextureDeserializer::~PlatformerTextureDeserializer()
{
}

void PlatformerTextureDeserializer::deserialize(ObjectDeserializer::ObjectDeserializationRequestArgs* args)
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
