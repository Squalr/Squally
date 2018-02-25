#pragma once
#include <cereal/types/unordered_map.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/archives/binary.hpp>
#include "cocos2d.h"
#include "Resources.h"
#include "Utils/GameUtils.h"

using namespace cocos2d;

class SaveManager
{
public:
	static void setActiveSave(int index);
	static void save();

	struct MyRecord
	{
		uint8_t x, y;
		float z;

		template <class Archive>
		void serialize(Archive & ar)
		{
			ar(x, y, z);
		}
	};

private:
	static SaveManager * getInstance();
	SaveManager();
	~SaveManager();

	// binn* saveData;
	std::string saveFile;

	static SaveManager * configManagerInstance;
	static const std::string musicVolumeKey;
};
