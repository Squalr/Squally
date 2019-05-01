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
	JmpMarker(cocos2d::ValueMap& initProperties);
	~JmpMarker();

	void onEnter() override;
	void initializePositions() override;
	void buildJmpString(LocalizedString* registerString);
	void buildJmpPtrString(LocalizedString* registerString);
	int getOffset();

	cocos2d::Node* markerNode;
	LocalizedString* assemblyString;

	static const std::string MapKeyOffset;

private:
	typedef GridObject super;

	LocalizedLabel* assemblyLabel;
	int offset;
};
