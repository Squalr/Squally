#pragma once

#include "Objects/Isometric/PointerTrace/GridObject.h"

namespace cocos2d
{
	class Sprite;
}

class LocalizedString;
class LocalizedLabel;

class JmpMarker : public GridObject
{
protected:
	JmpMarker(cocos2d::ValueMap& properties);
	virtual ~JmpMarker();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float dt) override;
	void buildJmpString(LocalizedString* registerString);
	void buildJmpPtrString(LocalizedString* registerString);
	int getOffset();
	virtual int getJumpDestination() = 0;

	cocos2d::Node* markerNode = nullptr;
	LocalizedString* assemblyString = nullptr;

	static const std::string PropertyOffset;

private:
	typedef GridObject super;

	LocalizedLabel* assemblyLabel = nullptr;
	int offset = 0;
};
