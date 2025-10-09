#pragma once
#include <memory>
#include <string>

#include "Window.h"
#include "Utilities.h"

namespace MGL {
	class Renderer
	{
		friend class Texture;
	public:
		Renderer(Window *window);
		Renderer(const Renderer&) = default;
		~Renderer();
		void clear();
		void present();
		void setBackgroundColor(Color color);
		Color getBackgroundColor();


		void activeBlendMode();
		void deactiveBlendMode();

		void renderRectABS(Rect rect);

	protected:
		struct pimpl;
		inline pimpl* get() const { return pImpl.get(); }
	private:
		std::unique_ptr<pimpl> pImpl;
	};
}

