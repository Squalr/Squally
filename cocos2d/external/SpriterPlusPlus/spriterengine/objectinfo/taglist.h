#ifndef TAGLIST_H
#define TAGLIST_H

#include <vector>
#include <string>

namespace SpriterEngine
{

	typedef std::vector<const std::string*> StringRefVector;

	class TagList
	{
	public:
		TagList();

		bool tagIsActive(std::string tag) const;

		void pushBackTag(const std::string *tag);

	private:
		StringRefVector tags;
	};

}

#endif // TAGLIST_H
