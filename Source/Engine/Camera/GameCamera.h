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

class ClickableNode;
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
	float getCameraZoom();
	void setCameraZoom(float zoom);
	cocos2d::Vec2 getCameraPosition();
	cocos2d::Vec3 getCameraPosition3();
	void setCameraPosition(cocos2d::Vec2 position, bool addTrackOffset = false);
	void setCameraPosition3(cocos2d::Vec3 position, bool addTrackOffset = false);
	void setCameraPositionToTrackedTarget();
	cocos2d::Rect getBounds();
	void setBounds(cocos2d::Rect bounds);
	void shakeCamera(float magnitude, float shakesPerSecond, float duration);
	CameraTrackingData* getCurrentTrackingData();
	void setTarget(CameraTrackingData trackingData, bool immediatelyTrack = false);
	void pushTarget(CameraTrackingData trackingData, bool immediatelyTrack = false);
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
	cocos2d::Vec2 boundCameraByEllipses();
	cocos2d::Vec2 boundCameraByRectangle();
	void updateCameraDebugLabels();

	std::stack<CameraTrackingData> targetStack;
	cocos2d::Rect cameraBounds;
	CameraTrackingData currentTrackingData;
	float defaultDistance;

	Hud* hud;
	ClickableNode* debugScrollHitbox;
	LocalizedLabel* debugCameraLabelX;
	LocalizedLabel* debugCameraLabelY;
	LocalizedLabel* debugCameraLabelZoom;
	ConstantString* debugCameraStringX;
	ConstantString* debugCameraStringY;
	ConstantString* debugCameraStringZoom;
	cocos2d::DrawNode* debugCameraRectangle;

	static GameCamera* cameraInstance;
	static const std::string SchedulerKeyCameraShake;
};
