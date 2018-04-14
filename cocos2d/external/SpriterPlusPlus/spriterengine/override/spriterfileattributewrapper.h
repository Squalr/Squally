#ifndef SPRITERFILEATTRIBUTEWRAPPER_H
#define SPRITERFILEATTRIBUTEWRAPPER_H

#include "../global/global.h"

#include <string>

namespace SpriterEngine
{
	class SpriterFileAttributeWrapper
	{
	public:
		SpriterFileAttributeWrapper();
		virtual ~SpriterFileAttributeWrapper();

		virtual std::string getName() = 0;

		virtual bool isValid() = 0;

		virtual real getRealValue() = 0;
		virtual int getIntValue() = 0;
		virtual std::string getStringValue() = 0;

		virtual void advanceToNextAttribute() = 0;
	};

}

#endif // SPRITERFILEATTRIBUTEWRAPPER_H