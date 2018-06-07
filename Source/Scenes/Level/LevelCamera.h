#pragma once
#include <algorithm>

#include "cocos2d.h"

#include "Resources.h"
#include "Utils/MathUtils.h"


using namespace cocos2d;

class LevelCamera : public Node
{
public:
	static LevelCamera* create();
	static LevelCamera* getInstance();

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
	LevelCamera();
	~LevelCamera();
	void update(float dt) override;

	std::stack<Node*>* targetStack;
	Vec2 cameraPosition;
	Rect cameraBounds;
	Vec2 cameraScrollOffset;
	Vec2 followSpeed;

	static LevelCamera* cameraInstance;
};

