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

	static const std::string MapKey;
	static const std::string PropertySoft;
	static const std::string PropertyNoX;
	static const std::string PropertyNoY;

protected:
	CameraStop(cocos2d::ValueMap& properties);
	virtual ~CameraStop();

	void onEnter() override;
	void update(float dt) override;
	void pause() override;
	void onDeveloperModeEnable(int debugLevel) override;
	void onDeveloperModeDisable() override;

private:
	typedef GameObject super;

	bool soft;
	bool noX;
	bool noY;

	cocos2d::DrawNode* debugDraw;
	cocos2d::Size stopSize;
};
