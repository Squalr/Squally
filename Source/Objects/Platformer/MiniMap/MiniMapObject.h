#pragma once

#include "Engine/Maps/GameObject.h"

namespace cocos2d
{
	class DrawNode;
};

class MiniMapObject : public GameObject
{
public:
	static MiniMapObject* create(cocos2d::ValueMap& properties, cocos2d::Color4B defaultColor = cocos2d::Color4B(147, 83, 87, 255));

	static const std::string MapKey;
	static const std::string PropertyColor;
	static const std::string PropertyShape;
	static const std::string TagMiniMapObject;

protected:
	MiniMapObject(cocos2d::ValueMap& properties, cocos2d::Color4B defaultColor);
	virtual ~MiniMapObject();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef GameObject super;
	
	cocos2d::DrawNode* miniMapObject;
	cocos2d::Color4B drawColor;
};
