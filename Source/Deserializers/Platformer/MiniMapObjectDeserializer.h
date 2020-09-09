#pragma once

#include "Engine/Deserializers/Objects/ObjectDeserializer.h"

class MiniMapObjectDeserializer : public ObjectDeserializer
{
public:
	static MiniMapObjectDeserializer* create();

	static const std::string MapKeyTypeObject;

	static const cocos2d::Color4B WarpColor;
	static const cocos2d::Color4B PortalColor;
	static const cocos2d::Color4B WaterColor;
	static const cocos2d::Color4B DestroyableColor;
	static const cocos2d::Color4B InteractableColor;

private:
	typedef ObjectDeserializer super;

	MiniMapObjectDeserializer();
	virtual ~MiniMapObjectDeserializer();
};
