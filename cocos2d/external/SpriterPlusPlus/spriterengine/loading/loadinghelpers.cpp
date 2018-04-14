#include "loadinghelpers.h"

#include "../global/settings.h"

#include "../timeinfo/instanteasingcurve.h"
#include "../timeinfo/lineareasingcurve.h"
#include "../timeinfo/quadraticeasingcurve.h"
#include "../timeinfo/cubiceasingcurve.h"
#include "../timeinfo/quarticeasingcurve.h"
#include "../timeinfo/quinticeasingcurve.h"
#include "../timeinfo/beziereasingcurve.h"

namespace SpriterEngine
{
	Object::ObjectType objectTypeNameToType(std::string typeName)
	{
		if (typeName == "sprite")
		{
			return Object::OBJECTTYPE_SPRITE;
		}
		else if (typeName == "bone")
		{
			return Object::OBJECTTYPE_BONE;
		}
		else if (typeName == "box")
		{
			return Object::OBJECTTYPE_BOX;
		}
		else if (typeName == "point")
		{
			return Object::OBJECTTYPE_POINT;
		}
		else if (typeName == "entity")
		{
			return Object::OBJECTTYPE_ENTITY;
		}
		else if (typeName == "sound")
		{
			return Object::OBJECTTYPE_SOUND;
		}
		else if (typeName == "event")
		{
			return Object::OBJECTTYPE_TRIGGER;
		}
		else
		{
			Settings::error("loadinghelpers - objectTypeNameToType - unrecognized object type name : \"" + typeName + "\"");
			return Object::OBJECTTYPE_NONE;
		}
	}

	CurveType curveTypeNameToType(std::string typeName)
	{
		if (typeName == "instant")
		{
			return CURVETYPE_INSTANT;
		}
		else if (typeName == "linear")
		{
			return CURVETYPE_LINEAR;
		}
		else if (typeName == "quadratic")
		{
			return CURVETYPE_QUADRATIC;
		}
		else if (typeName == "cubic")
		{
			return CURVETYPE_CUBIC;
		}
		else if (typeName == "quartic")
		{
			return CURVETYPE_QUARTIC;
		}
		else if (typeName == "quintic")
		{
			return CURVETYPE_QUINTIC;
		}
		else if (typeName == "bezier")
		{
			return CURVETYPE_BEZIER;
		}
		else
		{
			Settings::error("loadinghelpers - curveTypeNameToType - unrecognized curve type name : \"" + typeName + "\"");
			return CURVETYPE_NONE;
		}
	}

	EasingCurveInterface *getNewEasingCurve(CurveType curveType, ControlPointArray *controlPoints)
	{
		switch (curveType)
		{
		case CURVETYPE_INSTANT:
			return new InstantEasingCurve();

		case CURVETYPE_LINEAR:
			return new LinearEasingCurve();

		case CURVETYPE_QUADRATIC:
			return new QuadraticEasingCurve((*controlPoints)[0]);

		case CURVETYPE_CUBIC:
			return new CubicEasingCurve((*controlPoints)[0], (*controlPoints)[1]);

		case CURVETYPE_QUARTIC:
			return new QuarticEasingCurve((*controlPoints)[0], (*controlPoints)[1], (*controlPoints)[2]);

		case CURVETYPE_QUINTIC:
			return new QuinticEasingCurve((*controlPoints)[0], (*controlPoints)[1], (*controlPoints)[2], (*controlPoints)[3]);

		case CURVETYPE_BEZIER:
			return new BezierEasingCurve((*controlPoints)[0], (*controlPoints)[1], (*controlPoints)[2], (*controlPoints)[3]);

		default:
			Settings::error("loadinghelpers - getNewEasingCurve - invalid curve type : falling back on linear easing curve");
			return new LinearEasingCurve();
		}
	}

	std::string extractFilePath(std::string fileName)
	{
		size_t lastSlash = fileName.find_last_of("\\/");
		if (lastSlash != std::string::npos)
		{
			return fileName.substr(0, lastSlash + 1);
		}
		else
		{
			return "";
		}
	}

	FileFlattener::FileFlattener() :
		fileCount(0)
	{
	}

	void FileFlattener::appendFolder()
	{
		folders.push_back(IntVector());
	}

	void FileFlattener::appendFile()
	{
		if (folders.size())
		{
			folders.back().push_back(fileCount++);
		}
		else
		{
			Settings::error("FileFlatter::appendFile - attempting to append file when no folders exist yet");
		}
	}

	int FileFlattener::getFlattenedIndex(int folderIndex, int fileIndex)
	{
		if (folderIndex >= 0 && folderIndex < folders.size())
		{
			IntVector *files = &folders.at(folderIndex);
			if (fileIndex >= 0 && fileIndex < files->size())
			{
				return files->at(fileIndex);
			}
			else
			{
				return NO_FILE;
			}
		}
		else
		{
			return NO_FILE;
		}
	}
}