#pragma once
#include <string>

#include "Menus/Hexus/ChapterSelect/HexusChapterPreview.h"

class HexusChapterPreviewTraining : public HexusChapterPreview
{
public:
	static HexusChapterPreviewTraining * create();

	static const std::string SaveKeyChapterName;

protected:
	HexusChapterPreviewTraining();
	~HexusChapterPreviewTraining();

private:
	typedef HexusChapterPreview super;
	void initializePositions() override;
};
