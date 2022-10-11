#pragma once
#include <map>
#include <stack>

#include "cocos/base/CCValue.h"
#include "cocos/math/Vec2.h"
#include "cocos/platform/CCSAXParser.h"

#include "Engine/Animations/Spriter/SpriterStructs.h"

class SpriterAnimationParser : public cocos2d::SAXDelegator
{
public:
	static SpriterData Parse(std::string animationResource);

protected:
	SpriterAnimationParser();
	virtual ~SpriterAnimationParser();

	static bool ParseXMLFile(const std::string& xmlFilename);
    void startElement(void* ctx, const char* name, const char** atts) override;
    void endElement(void* ctx, const char* name) override;
    void textHandler(void* ctx, const char* ch, size_t len) override;

private:
	static SpriterData CurrentParse;
	static SpriterAnimationParser* Instance;
	
	static SpriterCurveType StringToCurveType(const std::string& curveTypeStr, SpriterCurveType defaultCurveType);
	
	enum class AttributeFocus
	{
		Data,
		Folder,
		File,
		Entity,
		ObjectInfo,
		Animation,
		Mainline,
		Timeline,
		Key,
		Object,
		ObjectRef,
		Bone,
		BoneRef,
	};

	static std::stack<AttributeFocus> FocusStack;
	static std::map<std::string, SpriterData> SpriterDataCache;

	static const std::string AttributeSpriterData;
	static const std::string AttributeFolder;
	static const std::string AttributeFile;
	static const std::string AttributeEntity;
	static const std::string AttributeObjectInfo;
	static const std::string AttributeAnimation;
	static const std::string AttributeMainline;
	static const std::string AttributeTimeline;
	static const std::string AttributeKey;
	static const std::string AttributeObject;
	static const std::string AttributeObjectRef;
	static const std::string AttributeBone;
	static const std::string AttributeBoneRef;
};
