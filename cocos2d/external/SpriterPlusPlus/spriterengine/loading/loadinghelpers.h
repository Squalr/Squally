#ifndef LOADINGHELPERS_H
#define LOADINGHELPERS_H

#include <string>
#include <map>

#include "../entity/object.h"
#include "../global/global.h"

namespace SpriterEngine
{
	class EasingCurveInterface;

	static const int NO_FILE = -1;

	struct SpriteKeyFileInfo
	{
		bool useDefaultPivot;
		int fileIndex;
	};

	struct SubEntityKeyInfo
	{
		int entityId;
		int animationIndex;
	};

	typedef std::vector<SpriteKeyFileInfo> SpriteKeyFileInfoVector;
	typedef std::map<int, SpriteKeyFileInfoVector> SpriteKeyFileInfoObjectIdMap;

	typedef std::vector<SubEntityKeyInfo> SubEntityKeyInfoVector;
	typedef std::map<int, SubEntityKeyInfoVector> SubEntityKeyInfoMap;

	typedef std::vector<int> IntVector;
	typedef std::vector < IntVector> Int2DVector;

	typedef std::map<int, point> PointMap;

	typedef std::vector<bool> BooleanVector;

	const int MAX_CONTROL_POINTS = 4;
	typedef real ControlPointArray[MAX_CONTROL_POINTS];

	enum CurveType
	{
		CURVETYPE_NONE,
		CURVETYPE_INSTANT,
		CURVETYPE_LINEAR,
		CURVETYPE_QUADRATIC,
		CURVETYPE_CUBIC,
		CURVETYPE_QUARTIC,
		CURVETYPE_QUINTIC,
		CURVETYPE_BEZIER
	};

	Object::ObjectType objectTypeNameToType(std::string typeName);

	CurveType curveTypeNameToType(std::string typeName);

	EasingCurveInterface *getNewEasingCurve(CurveType curveType, ControlPointArray *controlPoints);

	std::string extractFilePath(std::string fileName);

	class FileFlattener
	{
	public:
		FileFlattener();

		void appendFolder();
		void appendFile();
		int getFlattenedIndex(int folderIndex, int fileIndex);

	private:
		Int2DVector folders;
		int fileCount;
	};

}

#endif // LOADINGHELPERS_H
