#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class Dart;

class DartPool : public SmartNode
{
public:
	static DartPool* create(int capacity, float rotation, float speed, float visualRotation);

	Dart* getNextDart();

protected:
	DartPool(int capacity, float rotation, float speed, float visualRotation);
	~DartPool();

private:
	typedef SmartNode super;

	std::vector<Dart*> darts;

	int dartIndex;
};
