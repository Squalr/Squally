#pragma once
#include <string>

#include "Menus/Minigames/Hexus/ChapterSelect/HexusChapterPreview.h"

class HexusChapterPreviewTraining : public HexusChapterPreview
{
public:
	static HexusChapterPreviewTraining * create();

	static const std::string SaveKeyChapterName;

protected:
	HexusChapterPreviewTraining();
	~HexusChapterPreviewTraining();

private:
	void initializePositions() override;
};
