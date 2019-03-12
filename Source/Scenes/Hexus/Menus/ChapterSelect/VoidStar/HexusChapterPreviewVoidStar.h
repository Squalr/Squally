#pragma once

#include "Scenes/Hexus/Menus/ChapterSelect/HexusChapterPreview.h"

class HexusChapterPreviewVoidStar : public HexusChapterPreview
{
public:
	static HexusChapterPreviewVoidStar* create();

	static const std::string SaveKeyChapterName;

protected:
	HexusChapterPreviewVoidStar();
	~HexusChapterPreviewVoidStar();

private:
	typedef HexusChapterPreview super;
	void initializePositions() override;
};
