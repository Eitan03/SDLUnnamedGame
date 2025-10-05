#pragma once
#include <memory>
#include <string>
#include <iostream>
#include "Utilities.h"

namespace MGL {
	class Window
	{
		friend class Renderer;
	public:
		Window(std::string name, int width, int height);
		Window(const Window&) = default;
		~Window();
	protected:
		struct pimpl;
		inline pimpl* get() const { return pImpl.get(); }
	private:
		std::unique_ptr<pimpl> pImpl;
		int width;
		int height;
	};
}

