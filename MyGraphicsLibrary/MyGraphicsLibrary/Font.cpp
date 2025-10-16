#include "Font.h"

#include "pimpl.h"


namespace MGL {

	Font::Font(std::string path, int fontSize)
		: pImpl(std::unique_ptr<Font::pimpl>(Font::pimpl::fromPath(path, fontSize))), size(fontSize)
	{
	}
}
