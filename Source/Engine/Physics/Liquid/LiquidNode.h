#pragma once

#include "Engine/Maps/GameObject.h"

namespace cocos2d
{
    class DrawNode;
    class LayerColor;
}

class CollisionObject;
class LiquidTop;

typedef int CollisionType;

class LiquidNode : public GameObject
{
public:
    static LiquidNode* create(
        cocos2d::ValueMap& properties,
        float surfaceDepth,
        CollisionType collisionType,
        cocos2d::Color4B surfaceColor,
        cocos2d::Color4B bodyColor
    );

    void splash(float x, float speed, float splashRadius = 64.0f, float decay = 0.05f);

    static const std::string PropertyDisableWaves;
    static const std::string PropertyDisableEdges;
	static const float SplashSpacing;
	static const float WaterGravity;
	static const float WaterCollisionOffset;

protected:
    LiquidNode(
        cocos2d::ValueMap& properties,
        float surfaceDepth,
        CollisionType collisionType,
        cocos2d::Color4B surfaceColor,
        cocos2d::Color4B bodyColor
    );
    virtual ~LiquidNode();
    
	void onEnter() override;
    void initializePositions() override;
	void update(float dt) override;
	void runObjectSplash(CollisionObject* other, bool isExit);
	void runSplashes();
	void runSplash(int index);

	CollisionObject* liquidCollision = nullptr;

private:
    typedef GameObject super;

    cocos2d::CSize liquidSize;
    float surfaceDepth = 0.0f;
	int splashes = 0;
	float noSplashDelay = 1.0f;
	bool wavesDisabled = false;

    cocos2d::LayerColor* liquidBody = nullptr;
    LiquidTop* liquidTop = nullptr;
    cocos2d::DrawNode* edges = nullptr;
};
