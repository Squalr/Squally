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
	static DartPool* create(int capacity, float rotation, float speed);

	Dart* getNextDart();

protected:
	DartPool(int capacity, float rotation, float speed);
	~DartPool();

private:
	typedef SmartNode super;

	std::vector<Dart*> darts;

	int dartIndex;
};
