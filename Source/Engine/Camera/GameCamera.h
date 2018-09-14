#pragma once
#include <algorithm>

#include "cocos2d.h"

#include "Engine/SmartNode.h"
#include "Engine/Utils/MathUtils.h"
#include "Resources.h"


using namespace cocos2d;

class GameCamera : public SmartNode
{
public:
	static GameCamera* create();
	static GameCamera* getInstance();

	float getCameraDistance();
	void setCameraDistance(float distance);
	Vec2 getCameraPosition();
	void setCameraPosition(Vec2 position);
	Vec2 getScrollOffset();
	void setScrollOffset(Vec2 offset);
	Rect getBounds();
	void setBounds(Rect bounds);
	Vec2 getFollowSpeed();
	void setFollowSpeed(Vec2 speed);

	void setTarget(Node* newTarget);
	void pushTarget(Node* newTarget);
	void popTarget();
	void clearTargets();

private:
	GameCamera();
	~GameCamera();
	void onEnter() override;
	void update(float dt) override;

	std::stack<Node*>* targetStack;
	float defaultDistance;
	Vec2 cameraPosition;
	Rect cameraBounds;
	Vec2 cameraScrollOffset;
	Vec2 followSpeed;

	static GameCamera* cameraInstance;
};

