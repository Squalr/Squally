#pragma once

#include "Entities/Isometric/IsometricEntity.h"

class GridEntity : public IsometricEntity
{
public:
	void lockMovement();
	void unlockMovement();
	bool isMovementLocked();
	int getGridIndex();
	void setGridIndex(int gridIndex);

protected:
	GridEntity(cocos2d::ValueMap& initProperties,
		std::string scmlResource,
		float scale = 1.0f,
		cocos2d::Vec2 offset = cocos2d::Vec2(0.0f, 0.0f),
		cocos2d::Size size = cocos2d::Size(256.0f, 128.0f));
	~GridEntity();

	void onEnter() override;
	void moveLeft(float speed);
	void moveRight(float speed);
	void moveUp(float speed);
	void moveDown(float speed);

private:
	typedef IsometricEntity super;

	bool movementLocked;
	int gridIndex;
};
