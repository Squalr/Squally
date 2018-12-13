#pragma once
#include <stack>

#include "cocos/math/CCGeometry.h"

#include "Engine/GlobalNode.h"

namespace cocos2d
{
	class Node;
}

class GameCamera : public GlobalNode
{
public:
	static void registerGlobalNode();
	static GameCamera* getInstance();

	float getCameraDistance();
	void setCameraDistance(float distance);
	cocos2d::Vec2 getCameraPosition();
	void setCameraPosition(cocos2d::Vec2 position, bool addTrackOffset = false);
	cocos2d::Vec2 getScrollOffset();
	void setScrollOffset(cocos2d::Vec2 offset);
	cocos2d::Rect getBounds();
	void setBounds(cocos2d::Rect bounds);
	cocos2d::Vec2 getTrackOffset();
	void setTrackOffset(cocos2d::Vec2 position);
	cocos2d::Vec2 getFollowSpeed();
	void setFollowSpeed(cocos2d::Vec2 speed);

	void setTarget(cocos2d::Node* newTarget, cocos2d::Vec2 trackOffset = cocos2d::Vec2::ZERO);
	void pushTarget(cocos2d::Node* newTarget);
	void popTarget();
	void clearTargets();

private:
	GameCamera();
	virtual ~GameCamera();
	void onEnter() override;
	void initializeListeners() override;
	void update(float dt) override;
	void beforeSceneChange();

	std::stack<cocos2d::Node*> targetStack;
	float defaultDistance;
	cocos2d::Vec2 cameraPosition;
	cocos2d::Rect cameraBounds;
	cocos2d::Vec2 cameraScrollOffset;
	cocos2d::Vec2 trackOffset;
	cocos2d::Vec2 followSpeed;

	static GameCamera* cameraInstance;
};

