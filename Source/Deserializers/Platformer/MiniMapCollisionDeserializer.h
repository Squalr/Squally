#pragma once

#include "Engine/Deserializers/Objects/ObjectDeserializer.h"

class MiniMapCollisionDeserializer : public ObjectDeserializer
{
public:
	static MiniMapCollisionDeserializer* create();

	void deserialize(ObjectDeserializer::ObjectDeserializationRequestArgs* args) override;

	static const std::string MapKeyTypeCollision;

	static const std::string PropertyMiniMapVisible;
	static const cocos2d::Color4B PassThroughColor;
	static const cocos2d::Color4B SolidColor;

private:
	typedef ObjectDeserializer super;

	MiniMapCollisionDeserializer();
	virtual ~MiniMapCollisionDeserializer();
};
