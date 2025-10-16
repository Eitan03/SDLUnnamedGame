#pragma once
#include <memory>
#include <string>

#include "Texture.h"

namespace MGL {

	class Font
	{
		friend struct Texture::pimpl;
	public:
		Font(std::string fontPath, int fontSize);
	protected:
		struct pimpl;
		inline pimpl* get() const { return pImpl.get(); }
		int size;
	private:
		std::unique_ptr<pimpl> pImpl;
	};
}

