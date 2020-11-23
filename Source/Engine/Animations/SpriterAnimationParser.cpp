#include "SpriterAnimationParser.h"

#include "cocos/platform/CCFileUtils.h"

#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/StrUtils.h"

using namespace cocos2d;

SpriterAnimationParser* SpriterAnimationParser::Instance = nullptr;
SpriterData SpriterAnimationParser::CurrentParse;
std::stack<SpriterAnimationParser::AttributeFocus> SpriterAnimationParser::FocusStack = std::stack<AttributeFocus>();

const std::string SpriterAnimationParser::AttributeSpriterData = "spriter_data";
const std::string SpriterAnimationParser::AttributeFolder = "folder";
const std::string SpriterAnimationParser::AttributeFile = "file";
const std::string SpriterAnimationParser::AttributeEntity = "entity";
const std::string SpriterAnimationParser::AttributeObjectInfo = "obj_info";
const std::string SpriterAnimationParser::AttributeAnimation = "animation";
const std::string SpriterAnimationParser::AttributeMainline = "mainline";
const std::string SpriterAnimationParser::AttributeTimeline = "timeline";
const std::string SpriterAnimationParser::AttributeKey = "key";
const std::string SpriterAnimationParser::AttributeObject = "object";
const std::string SpriterAnimationParser::AttributeObjectRef = "object_ref";
const std::string SpriterAnimationParser::AttributeBone = "bone";
const std::string SpriterAnimationParser::AttributeBoneRef = "bone_ref";

SpriterData SpriterAnimationParser::Parse(std::string animationResource)
{
	if (SpriterAnimationParser::Instance == nullptr)
	{
		SpriterAnimationParser::Instance = new SpriterAnimationParser();
	}

	SpriterAnimationParser::ParseXMLFile(animationResource);

	return SpriterAnimationParser::CurrentParse;
}

SpriterAnimationParser::SpriterAnimationParser()
{
}

SpriterAnimationParser::~SpriterAnimationParser()
{
}


bool SpriterAnimationParser::ParseXMLFile(const std::string& xmlFilename)
{
    SAXParser parser;
    
    if (!parser.init("UTF-8"))
    {
        return false;
    }
    
    parser.setDelegator(SpriterAnimationParser::Instance);

	// Clear current parse
	SpriterAnimationParser::CurrentParse = SpriterData();

    return parser.parse(FileUtils::getInstance()->fullPathForFilename(xmlFilename));
}

void SpriterAnimationParser::startElement(void* ctx, const char* name, const char** atts)
{
	ValueMap attributes = ValueMap();

    if (atts && atts[0])
    {
        for (int i = 0; atts[i]; i += 2)
        {
            std::string key = atts[i];
            std::string value = atts[i+1];

            attributes[key] = Value(value);
        }
    }

	if (name == SpriterAnimationParser::AttributeSpriterData)
	{
		SpriterAnimationParser::FocusStack.push(AttributeFocus::Data);
	}
	else if (name == SpriterAnimationParser::AttributeFolder)
	{
		SpriterAnimationParser::FocusStack.push(AttributeFocus::Folder);

		SpriterAnimationParser::CurrentParse.folders.push_back(SpriterFolder(
			std::stoi(GameUtils::getKeyOrDefault(attributes, "id", Value("")).asString())
		));
	}
	else if (name == SpriterAnimationParser::AttributeFile)
	{
		SpriterAnimationParser::FocusStack.push(AttributeFocus::File);

		if (SpriterAnimationParser::CurrentParse.folders.empty())
		{
			return;
		}

		SpriterAnimationParser::CurrentParse.folders.back().files.push_back(SpriterFile(
			std::stoi(GameUtils::getKeyOrDefault(attributes, "id", Value("")).asString()),
			GameUtils::getKeyOrDefault(attributes, "name", Value("")).asString(),
			Vec2(std::stof(GameUtils::getKeyOrDefault(attributes, "width", Value("0")).asString()), std::stof(GameUtils::getKeyOrDefault(attributes, "height", Value("0")).asString())),
			Vec2(std::stof(GameUtils::getKeyOrDefault(attributes, "pivot_x", Value("0")).asString()), std::stof(GameUtils::getKeyOrDefault(attributes, "pivot_y", Value("0")).asString()))
		));
	}
	else if (name == SpriterAnimationParser::AttributeEntity)
	{
		SpriterAnimationParser::FocusStack.push(AttributeFocus::Entity);
	}
	else if (name == SpriterAnimationParser::AttributeObjectInfo)
	{
		SpriterAnimationParser::FocusStack.push(AttributeFocus::ObjectInfo);
	}
	else if (name == SpriterAnimationParser::AttributeAnimation)
	{
		SpriterAnimationParser::FocusStack.push(AttributeFocus::Animation);
	}
	else if (name == SpriterAnimationParser::AttributeMainline)
	{
		SpriterAnimationParser::FocusStack.push(AttributeFocus::Mainline);
	}
	else if (name == SpriterAnimationParser::AttributeTimeline)
	{
		SpriterAnimationParser::FocusStack.push(AttributeFocus::Timeline);
	}
	else if (name == SpriterAnimationParser::AttributeKey)
	{
		SpriterAnimationParser::FocusStack.push(AttributeFocus::Key);
	}
	else if (name == SpriterAnimationParser::AttributeObject)
	{
		SpriterAnimationParser::FocusStack.push(AttributeFocus::Object);
	}
	else if (name == SpriterAnimationParser::AttributeObjectRef)
	{
		SpriterAnimationParser::FocusStack.push(AttributeFocus::ObjectRef);
	}
	else if (name == SpriterAnimationParser::AttributeBone)
	{
		SpriterAnimationParser::FocusStack.push(AttributeFocus::Bone);
	}
	else if (name == SpriterAnimationParser::AttributeBoneRef)
	{
		SpriterAnimationParser::FocusStack.push(AttributeFocus::BoneRef);
	}
}

void SpriterAnimationParser::endElement(void* ctx, const char* name)
{
	SpriterAnimationParser::FocusStack.pop();
}

void SpriterAnimationParser::textHandler(void* ctx, const char* ch, size_t len)
{
}
