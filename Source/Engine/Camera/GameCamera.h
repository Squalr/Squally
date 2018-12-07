#pragma once
#include <algorithm>

#include "cocos2d.h"

#include "Engine/GlobalDirector.h"
#include "Engine/GlobalNode.h"
#include "Engine/Utils/MathUtils.h"

using namespace cocos2d;

class GameCamera : public GlobalNode
{
public:
	static void registerGlobalNode();
	static GameCamera* getInstance();

	float getCameraDistance();
	void setCameraDistance(float distance);
	Vec2 getCameraPosition();
	void setCameraPosition(Vec2 position, bool addTrackOffset = false);
	Vec2 getScrollOffset();
	void setScrollOffset(Vec2 offset);
	Rect getBounds();
	void setBounds(Rect bounds);
	Vec2 getTrackOffset();
	void setTrackOffset(Vec2 position);
	Vec2 getFollowSpeed();
	void setFollowSpeed(Vec2 speed);

	void setTarget(Node* newTarget, Vec2 trackOffset = Vec2::ZERO);
	void pushTarget(Node* newTarget);
	void popTarget();
	void clearTargets();

private:
	GameCamera();
	~GameCamera();
	void onEnter() override;
	void update(float dt) override;

	std::stack<Node*> targetStack;
	float defaultDistance;
	Vec2 cameraPosition;
	Rect cameraBounds;
	Vec2 cameraScrollOffset;
	Vec2 trackOffset;
	Vec2 followSpeed;

	static GameCamera* cameraInstance;
};

