#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include <algorithm>

using namespace cocos2d;

class LevelCamera : public Node
{
public:
	static LevelCamera* create();
	static LevelCamera* getInstance();

	Vec2 getCameraPosition();
	void setBounds(Rect bounds);
	void setScrollOffset(Vec2 offset);
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

	static LevelCamera* cameraInstance;
};

