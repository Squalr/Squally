#pragma once
#include <stack>

#include "cocos/base/CCValue.h"
#include "cocos/math/Vec2.h"
#include "cocos/platform/CCSAXParser.h"

struct SpriterBone
{
	cocos2d::Vec2 position;
	cocos2d::Vec2 scale;
	float angle;
};

struct SpriterObject
{
	int folderId;
	int fileId;
	cocos2d::Vec2 position;
	cocos2d::Vec2 scale;
	float angle;
};

struct SpriterKey
{
	int id;
	int spin;
	float time;
	std::vector<SpriterObject> objects;
	std::vector<SpriterBone> bones;
};

struct SpriterTimeline
{
	int id;
	int object;
	std::string name;
	std::string objectType;
	std::vector<SpriterKey> spriterKeys;
};

struct SpriterMainline
{
	std::vector<SpriterKey> spriterKeys;
};

struct SpriterAnimation
{
	int id;
	std::string name;
	float length;
	float interval;
	SpriterMainline mainline;
	std::vector<SpriterTimeline> timelines;
};

struct SpriterObjectInfo
{
	std::string name;
	std::string type;
	cocos2d::Vec2 size;
};

struct SpriterEntity
{
	int id;
	std::string name;
	std::vector<SpriterObjectInfo> objectInfo;
	std::vector<SpriterAnimation> animations;
};

struct SpriterFile
{
	int id;
	std::string name;
	cocos2d::Vec2 size;
	cocos2d::Vec2 anchor;

	SpriterFile(int id, std::string name, cocos2d::Vec2 size, cocos2d::Vec2 anchor)
		: id(id), name(name), size(size), anchor(anchor) { }
};

struct SpriterFolder
{
	int id;
	std::vector<SpriterFile> files;

	SpriterFolder(int id) : id(id), files(std::vector<SpriterFile>()) { }
};

struct SpriterData
{
	std::vector<SpriterFolder> folders;
	std::vector<SpriterEntity> entities;
};

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
