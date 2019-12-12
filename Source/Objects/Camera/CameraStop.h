#pragma once

#include "Engine/Maps/GameObject.h"

namespace cocos2d
{
	class DrawNode;
}

class CameraStop : public GameObject
{
public:
	static CameraStop* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyCameraStop;
	static const std::string MapKeyPropertySoft;
	static const std::string MapKeyPropertyNoX;
	static const std::string MapKeyPropertyNoY;

private:
	typedef GameObject super;
	CameraStop(cocos2d::ValueMap& properties);
	virtual ~CameraStop();

	void onEnter() override;
	void update(float dt) override;
	void onDeveloperModeEnable(int debugLevel) override;
	void onDeveloperModeDisable() override;

	bool soft;
	bool noX;
	bool noY;

	cocos2d::DrawNode* debugDraw;
	cocos2d::Size stopSize;
};
