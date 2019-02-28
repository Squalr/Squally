#pragma once
#include <functional>
#include <stack>

#include "cocos/math/CCGeometry.h"

#include "Engine/Camera/CameraTrackingData.h"
#include "Engine/GlobalNode.h"

namespace cocos2d
{
	class DrawNode;
	class Node;
	class Vec2;
}

class ConstantString;
class Hud;
class LocalizedLabel;

class GameCamera : public GlobalNode
{
public:
	static void registerGlobalNode();
	static GameCamera* getInstance();

	float getCameraDistance();
	void setCameraDistance(float distance);
	cocos2d::Vec2 getCameraPosition();
	void setCameraPosition(cocos2d::Vec2 position, bool addTrackOffset = false);
	cocos2d::Rect getBounds();
	void setBounds(cocos2d::Rect bounds);
	void shakeCamera(float magnitude, float shakesPerSecond, float duration);
	CameraTrackingData* getCurrentTrackingData();
	void setTarget(CameraTrackingData trackingData);
	void pushTarget(CameraTrackingData trackingData);
	void popTarget();
	void clearTargets();

private:
	typedef GlobalNode super;
	GameCamera();
	virtual ~GameCamera();
	void onEnter() override;
	void onDeveloperModeEnable() override;
	void onDeveloperModeDisable() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float dt) override;
	void beforeSceneChange();
	void setCameraPositionWorkAround();
	void setCameraPositionReal(cocos2d::Vec2 position, bool addTrackOffset = false);
	cocos2d::Vec2 boundCameraByEllipses();
	cocos2d::Vec2 boundCameraByRectangle();
	void updateCameraDebugLabels();

	std::stack<CameraTrackingData> targetStack;
	cocos2d::Rect cameraBounds;
	CameraTrackingData currentTrackingData;
	float defaultDistance;

	// Variables for working around cocos bugs
	cocos2d::Vec2 storedNextCameraPosition;
	bool useStoredNextCameraPosition;

	Hud* hud;
	LocalizedLabel* debugCameraLabelX;
	LocalizedLabel* debugCameraLabelY;
	ConstantString* debugCameraStringX;
	ConstantString* debugCameraStringY;
	cocos2d::DrawNode* debugCameraRectangle;

	static GameCamera* cameraInstance;
	static const std::string SchedulerKeyCameraShake;
};
