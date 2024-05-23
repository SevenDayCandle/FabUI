export module fbc.EmptyDrawable;

import fbc.FUtil;
import fbc.IDrawable;
import sdl;
import std;

export namespace fbc {
	constexpr sdl::RectF EMPTY = { 0,0,0,0 };

	export class EmptyDrawable : public IDrawable {
	public:
		EmptyDrawable() {}

		inline const sdl::RectF* getBaseRec() override { return &EMPTY; }
		inline float getHeight() override { return 0; }
		inline float getWidth() override { return 0; }
		inline void drawBase(const sdl::RectF* sourceRec, const sdl::RectF* destRec, const sdl::Point& origin, float rotation, sdl::FlipMode flip) override {}
		inline void setDrawBlend(const sdl::BlendMode bl) override {}
		inline void setDrawColor(const sdl::Color& tint) override {}
	};
}