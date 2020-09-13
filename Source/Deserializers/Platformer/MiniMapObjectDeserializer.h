#pragma once

#include "Engine/Deserializers/Objects/ObjectDeserializer.h"

class MiniMapObjectDeserializer : public ObjectDeserializer
{
public:
	static MiniMapObjectDeserializer* create();

	static const std::string MapKeyTypeObject;

	static const cocos2d::Color4B NoColor;
	static const cocos2d::Color4B WarpColor;
	static const cocos2d::Color4B PortalColor;
	static const cocos2d::Color4B WaterColor;
	static const cocos2d::Color4B WindColor;
	static const cocos2d::Color4B DestroyableColor;
	static const cocos2d::Color4B InteractableColor;
	static const cocos2d::Color4B ShrineColor;

private:
	typedef ObjectDeserializer super;

	MiniMapObjectDeserializer();
	virtual ~MiniMapObjectDeserializer();
};
