#include "SpriterAnimationParser.h"

#include "cocos/platform/CCFileUtils.h"

#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/StrUtils.h"

using namespace cocos2d;

SpriterAnimationParser* SpriterAnimationParser::Instance = nullptr;
SpriterData SpriterAnimationParser::CurrentParse;
std::stack<SpriterAnimationParser::AttributeFocus> SpriterAnimationParser::FocusStack = std::stack<AttributeFocus>();
std::map<std::string, SpriterData> SpriterAnimationParser::SpriterDataCache = std::map<std::string, SpriterData>();

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

	// Check if data has already been parsed in cache
	if (SpriterAnimationParser::SpriterDataCache.find(animationResource) != SpriterAnimationParser::SpriterDataCache.end())
	{
		return SpriterAnimationParser::SpriterDataCache[animationResource];
	}

	// Do parse, cache on success
	if (SpriterAnimationParser::ParseXMLFile(animationResource))
	{
		SpriterAnimationParser::SpriterDataCache[animationResource] = SpriterAnimationParser::CurrentParse;
	}

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
        for (int i = 0; atts[i] != nullptr; i += 2)
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
			std::stoi(GameUtils::getKeyOrDefault(attributes, "id", Value("0")).asString())
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
			std::stoi(GameUtils::getKeyOrDefault(attributes, "id", Value("0")).asString()),
			GameUtils::getKeyOrDefault(attributes, "name", Value("")).asString(),
			Vec2(std::stof(GameUtils::getKeyOrDefault(attributes, "width", Value("0")).asString()), std::stof(GameUtils::getKeyOrDefault(attributes, "height", Value("0")).asString())),
			Vec2(std::stof(GameUtils::getKeyOrDefault(attributes, "pivot_x", Value("0")).asString()), std::stof(GameUtils::getKeyOrDefault(attributes, "pivot_y", Value("0")).asString()))
		));
	}
	else if (name == SpriterAnimationParser::AttributeEntity)
	{
		SpriterAnimationParser::FocusStack.push(AttributeFocus::Entity);

		SpriterAnimationParser::CurrentParse.entities.push_back(SpriterEntity(
			std::stoi(GameUtils::getKeyOrDefault(attributes, "id", Value("0")).asString()),
			GameUtils::getKeyOrDefault(attributes, "name", Value("")).asString()
		));
	}
	else if (name == SpriterAnimationParser::AttributeObjectInfo)
	{
		SpriterAnimationParser::FocusStack.push(AttributeFocus::ObjectInfo);

		if (SpriterAnimationParser::CurrentParse.entities.empty())
		{
			return;
		}

		SpriterAnimationParser::CurrentParse.entities.back().objectInfo.push_back(SpriterObjectInfo(
			GameUtils::getKeyOrDefault(attributes, "name", Value("")).asString(),
			GameUtils::getKeyOrDefault(attributes, "type", Value("")).asString(),
			Vec2(std::stof(GameUtils::getKeyOrDefault(attributes, "w", Value("0")).asString()), std::stof(GameUtils::getKeyOrDefault(attributes, "h", Value("0")).asString()))
		));
	}
	else if (name == SpriterAnimationParser::AttributeAnimation)
	{
		SpriterAnimationParser::FocusStack.push(AttributeFocus::Animation);
		
		if (SpriterAnimationParser::CurrentParse.entities.empty())
		{
			return;
		}

		SpriterAnimationParser::CurrentParse.entities.back().animations.push_back(SpriterAnimation(
			std::stoi(GameUtils::getKeyOrDefault(attributes, "id", Value("0")).asString()),
			GameUtils::getKeyOrDefault(attributes, "name", Value("")).asString(),
			std::stof(GameUtils::getKeyOrDefault(attributes, "length", Value("0")).asString()),
			std::stof(GameUtils::getKeyOrDefault(attributes, "interval", Value("0")).asString()),
			(GameUtils::getKeyOrDefault(attributes, "looping", Value("")).asString() == "false" ? false : true)
		));
	}
	else if (name == SpriterAnimationParser::AttributeMainline)
	{
		SpriterAnimationParser::FocusStack.push(AttributeFocus::Mainline);
		
		if (SpriterAnimationParser::CurrentParse.entities.empty()
			|| SpriterAnimationParser::CurrentParse.entities.back().animations.empty())
		{
			return;
		}

		SpriterAnimationParser::CurrentParse.entities.back().animations.back().mainline = SpriterMainline();
	}
	else if (name == SpriterAnimationParser::AttributeTimeline)
	{
		SpriterAnimationParser::FocusStack.push(AttributeFocus::Timeline);
		
		if (SpriterAnimationParser::CurrentParse.entities.empty()
			|| SpriterAnimationParser::CurrentParse.entities.back().animations.empty())
		{
			return;
		}

		SpriterAnimationParser::CurrentParse.entities.back().animations.back().timelines.push_back(SpriterTimeline(
			std::stoi(GameUtils::getKeyOrDefault(attributes, "id", Value("0")).asString()),
			std::stoi(GameUtils::getKeyOrDefault(attributes, "object", Value("0")).asString()),
			GameUtils::getKeyOrDefault(attributes, "name", Value("")).asString(),
			GameUtils::getKeyOrDefault(attributes, "object_type", Value("")).asString()
		));
	}
	else if (name == SpriterAnimationParser::AttributeKey)
	{
		if (SpriterAnimationParser::FocusStack.empty()
			|| SpriterAnimationParser::CurrentParse.entities.empty()
			|| SpriterAnimationParser::CurrentParse.entities.back().animations.empty())
		{
			SpriterAnimationParser::FocusStack.push(AttributeFocus::Key);
			return;
		}

		switch(SpriterAnimationParser::FocusStack.top())
		{
			case AttributeFocus::Mainline:
			{
				SpriterCurveType curveType = SpriterCurveType::Linear;
				std::string curveTypeStr = GameUtils::getKeyOrDefault(attributes, "curve_type", Value("")).asString();

				if (curveTypeStr == "instant")
				{
					curveType = SpriterCurveType::Instant;
				}
				else if (curveTypeStr == "quadrtaic")
				{
					curveType = SpriterCurveType::Quadratic;
				}
				else if (curveTypeStr == "cubic")
				{
					curveType = SpriterCurveType::Cubic;
				}
				else if (curveTypeStr == "quartic")
				{
					curveType = SpriterCurveType::Quartic;
				}
				else if (curveTypeStr == "quintic")
				{
					curveType = SpriterCurveType::Quintic;
				}
				else if (curveTypeStr == "bezier")
				{
					curveType = SpriterCurveType::Bezier;
				}

				SpriterAnimationParser::CurrentParse.entities.back().animations.back().mainline.keys.push_back(SpriterMainlineKey(
					std::stoi(GameUtils::getKeyOrDefault(attributes, "id", Value("0")).asString()),
					std::stof(GameUtils::getKeyOrDefault(attributes, "time", Value("0")).asString()),
					curveType,
					std::stof(GameUtils::getKeyOrDefault(attributes, "c1", Value("0")).asString()),
					std::stof(GameUtils::getKeyOrDefault(attributes, "c2", Value("0")).asString()),
					std::stof(GameUtils::getKeyOrDefault(attributes, "c3", Value("0")).asString()),
					std::stof(GameUtils::getKeyOrDefault(attributes, "c4", Value("0")).asString())
				));
				break;
			}
			case AttributeFocus::Timeline:
			{
				if (SpriterAnimationParser::CurrentParse.entities.back().animations.back().timelines.empty())
				{
					break;
				}

				SpriterAnimationParser::CurrentParse.entities.back().animations.back().timelines.back().keys.push_back(SpriterTimelineKey(
					std::stoi(GameUtils::getKeyOrDefault(attributes, "id", Value("0")).asString()),
					std::stoi(GameUtils::getKeyOrDefault(attributes, "spin", Value("0")).asString()),
					std::stof(GameUtils::getKeyOrDefault(attributes, "time", Value("0")).asString())
				));

				break;
			}
			default:
			{
				break;
			}
		}

		SpriterAnimationParser::FocusStack.push(AttributeFocus::Key);
	}
	else if (name == SpriterAnimationParser::AttributeObject)
	{
		SpriterAnimationParser::FocusStack.push(AttributeFocus::Object);
		
		if (SpriterAnimationParser::CurrentParse.entities.empty()
			|| SpriterAnimationParser::CurrentParse.entities.back().animations.empty()
			|| SpriterAnimationParser::CurrentParse.entities.back().animations.back().timelines.empty()
			|| SpriterAnimationParser::CurrentParse.entities.back().animations.back().timelines.back().keys.empty())
		{
			return;
		}

		SpriterAnimationParser::CurrentParse.entities.back().animations.back().timelines.back().keys.back().objects.push_back(SpriterObject(
			std::stoi(GameUtils::getKeyOrDefault(attributes, "folder", Value("0")).asString()),
			std::stoi(GameUtils::getKeyOrDefault(attributes, "file", Value("0")).asString()),
			Vec2(std::stof(GameUtils::getKeyOrDefault(attributes, "x", Value("0")).asString()), std::stof(GameUtils::getKeyOrDefault(attributes, "y", Value("0")).asString())),
			Vec2(std::stof(GameUtils::getKeyOrDefault(attributes, "scale_x", Value("1")).asString()), std::stof(GameUtils::getKeyOrDefault(attributes, "scale_y", Value("1")).asString())),
			std::stof(GameUtils::getKeyOrDefault(attributes, "angle", Value("0")).asString())
		));
	}
	else if (name == SpriterAnimationParser::AttributeObjectRef)
	{
		SpriterAnimationParser::FocusStack.push(AttributeFocus::ObjectRef);
		
		if (SpriterAnimationParser::CurrentParse.entities.empty()
			|| SpriterAnimationParser::CurrentParse.entities.back().animations.empty()
			|| SpriterAnimationParser::CurrentParse.entities.back().animations.back().mainline.keys.empty())
		{
			return;
		}

		SpriterAnimationParser::CurrentParse.entities.back().animations.back().mainline.keys.back().objectRefs.push_back(SpriterObjectRef(
			std::stoi(GameUtils::getKeyOrDefault(attributes, "id", Value("0")).asString()),
			std::stoi(GameUtils::getKeyOrDefault(attributes, "parent", Value("0")).asString()),
			std::stoi(GameUtils::getKeyOrDefault(attributes, "timeline", Value("0")).asString()),
			std::stoi(GameUtils::getKeyOrDefault(attributes, "key", Value("0")).asString()),
			std::stoi(GameUtils::getKeyOrDefault(attributes, "z_index", Value("0")).asString())
		));
	}
	else if (name == SpriterAnimationParser::AttributeBone)
	{
		SpriterAnimationParser::FocusStack.push(AttributeFocus::Bone);
		
		if (SpriterAnimationParser::CurrentParse.entities.empty()
			|| SpriterAnimationParser::CurrentParse.entities.back().animations.empty()
			|| SpriterAnimationParser::CurrentParse.entities.back().animations.back().timelines.empty()
			|| SpriterAnimationParser::CurrentParse.entities.back().animations.back().timelines.back().keys.empty())
		{
			return;
		}

		SpriterAnimationParser::CurrentParse.entities.back().animations.back().timelines.back().keys.back().bones.push_back(SpriterBone(
			Vec2(std::stof(GameUtils::getKeyOrDefault(attributes, "x", Value("0")).asString()), std::stof(GameUtils::getKeyOrDefault(attributes, "y", Value("0")).asString())),
			Vec2(std::stof(GameUtils::getKeyOrDefault(attributes, "scale_x", Value("1")).asString()), std::stof(GameUtils::getKeyOrDefault(attributes, "scale_y", Value("1")).asString())),
			std::stof(GameUtils::getKeyOrDefault(attributes, "angle", Value("0")).asString())
		));
	}
	else if (name == SpriterAnimationParser::AttributeBoneRef)
	{
		SpriterAnimationParser::FocusStack.push(AttributeFocus::BoneRef);
		
		if (SpriterAnimationParser::CurrentParse.entities.empty()
			|| SpriterAnimationParser::CurrentParse.entities.back().animations.empty()
			|| SpriterAnimationParser::CurrentParse.entities.back().animations.back().mainline.keys.empty())
		{
			return;
		}

		SpriterAnimationParser::CurrentParse.entities.back().animations.back().mainline.keys.back().boneRefs.push_back(SpriterBoneRef(
			std::stoi(GameUtils::getKeyOrDefault(attributes, "id", Value("0")).asString()),
			std::stoi(GameUtils::getKeyOrDefault(attributes, "parent", Value("-1")).asString()),
			std::stoi(GameUtils::getKeyOrDefault(attributes, "timeline", Value("0")).asString()),
			std::stoi(GameUtils::getKeyOrDefault(attributes, "key", Value("0")).asString())
		));
	}
}

void SpriterAnimationParser::endElement(void* ctx, const char* name)
{
	SpriterAnimationParser::FocusStack.pop();
}

void SpriterAnimationParser::textHandler(void* ctx, const char* ch, size_t len)
{
}
