#pragma once

#include "Engine/Maps/GameObject.h"

namespace cocos2d
{
	class Sprite;
}

class MineWheel : public GameObject
{
public:
	static MineWheel* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	MineWheel(cocos2d::ValueMap& properties);
	virtual ~MineWheel();

	void onEnter() override;
	void update(float dt) override;
	void initializePositions() override;

private:
	typedef GameObject super;

	enum class BucketType
	{
		Empty,
		Fill1,
		Fill2,
		Fill3,
		MIN = Empty,
		MAX = Fill3,
	};

	std::vector<BucketType> createOrdering(int count);
	cocos2d::Node* createBucket(BucketType bucketType);
	void positionBuckets();

	float speed;
	float elapsed;
	cocos2d::Sprite* wheel;
	std::vector<cocos2d::Node*> cranes;

	static const int BucketCount;
	static const std::string PropertySpeed;
};
