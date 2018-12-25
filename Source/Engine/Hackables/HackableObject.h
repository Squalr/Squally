#pragma once
#include <map>
#include <string>

#include "cocos/math/CCGeometry.h"

#include "Engine/Maps/SerializableObject.h"

class HackableData;
class HackButton;
class MenuSprite;

namespace cocos2d
{
	class Renderer;
	class Value;
	typedef std::map<std::string, Value> ValueMap;
}

class HackableObject : public SerializableObject
{
public:
	void onHackableClick(MenuSprite* backButton);

	cocos2d::Size size;
	std::vector<HackableData*> dataList;

	HackButton* hackButton;

protected:
	HackableObject(cocos2d::ValueMap* initProperties);
	virtual ~HackableObject();

	void pause() override;
	void onEnterTransitionDidFinish() override;
	virtual cocos2d::Vec2 getButtonOffset();
	void registerData(HackableData* hackableData);

	void visit(cocos2d::Renderer *renderer, const cocos2d::Mat4& parentTransform, uint32_t parentFlags) override;

private:
	cocos2d::Vec2 buttonOffset;
};
