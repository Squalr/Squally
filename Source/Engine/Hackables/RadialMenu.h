#pragma once
#include <functional>
#include "cocos/math/Vec2.h"

#include "Engine/Events/HackableEvents.h"
#include "Engine/GlobalHud.h"

namespace cocos2d
{
	class EventCustom;
	class LayerColor;
	class Sprite;
}

class ClickableNode;
class CodeEditor;
class HackableAttribute;
class HackableCode;
class HackableData;
class HackableObject;
class LocalizedString;

class RadialMenu : public GlobalHud
{
public:
	static RadialMenu* create();

protected:
	RadialMenu();
	virtual ~RadialMenu();

	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef SmartNode super;

	void onHackableAttributeEdit(HackableAttribute* attribute);
	void close();
	void buildRadialMenu(HackableEvents::HackableObjectOpenArgs* args);
	ClickableNode* createRadialNode(std::string iconResource, int requiredLevel, cocos2d::Vec2 nodePosition, float angle, LocalizedString* text, std::function<void()> clickCallback);

	HackableObject* activeHackableObject;
	cocos2d::LayerColor* layerColor;
	cocos2d::Sprite* background;
	cocos2d::Node* previewNode;
	cocos2d::Node* radialMenuItems;

	static const float Radius;
	static const float IconRadius;
};
