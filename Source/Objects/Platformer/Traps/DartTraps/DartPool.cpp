#include "DartPool.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Objects/Platformer/Traps/DartTraps/Dart.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

DartPool* DartPool::create(int capacity, float rotation, float speed, float visualRotation)
{
	DartPool* instance = new DartPool(capacity, rotation, speed, visualRotation);

	instance->autorelease();

	return instance;
}

DartPool::DartPool(int capacity, float rotation, float speed, float visualRotation) : super()
{
	this->darts = std::vector<Dart*>();
	this->dartIndex = 0;

	for (int index = 0; index < capacity; index++)
	{
		this->darts.push_back(Dart::create(rotation, speed, visualRotation));
	}

	for (auto it = this->darts.begin(); it != this->darts.end(); it++)
	{
		(*it)->setPhysicsEnabled(false);
		this->addChild(*it);
	}
}

DartPool::~DartPool()
{
}

Dart* DartPool::getNextDart()
{
	if (this->darts.size() <= 0)
	{
		return nullptr;
	}

	this->dartIndex = MathUtils::wrappingNormalize(this->dartIndex + 1, 0, this->darts.size() - 1);
	
	this->darts[dartIndex]->setPosition3D(Vec3::ZERO);
	this->darts[dartIndex]->setPhysicsEnabled(true);

	return this->darts[dartIndex];
}
