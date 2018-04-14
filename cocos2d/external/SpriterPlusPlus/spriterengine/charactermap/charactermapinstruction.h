#ifndef CHARACTERMAPINSTRUCTION_H
#define CHARACTERMAPINSTRUCTION_H

#include <vector>

namespace SpriterEngine
{

	class File;
	class FileReference;

	typedef std::vector<FileReference*> FileReferenceVector;

	class CharacterMapInstruction
	{
	public:
		CharacterMapInstruction(int initialFileToReplaceIndex, File *initialReplacementFile);

		void applyMapInstruction(FileReferenceVector *mappedFiles);

	private:
		int fileToReplace;
		File *replacementFile;
	};

}

#endif // CHARACTERMAPINSTRUCTION_H
