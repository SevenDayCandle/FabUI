export module fbc.ftexture;

import fbc.futil;
import fbc.iDrawable;
import sdl;
import std;

export namespace fbc {
	export class FTexture : public IDrawable {
    public:
        FTexture(strv path) {
            texture = sdl::textureLoad(path.data());
            if (texture == nullptr) {
                sdl::logError("Failed to load texture %s: %s", path.data(), sdl::getError());
            }
            sdl::textureQuery(texture, &format, &access, &dim.w, &dim.h);
        }
        FTexture(const FTexture&) = delete;
        ~FTexture() {
            // Unload texture when destroyed
            if (texture) {
                sdl::textureDestroy(texture);
                texture = nullptr;
            }
        }

        inline sdl::RectI* getBaseRec() override { return &dim; }
        inline float getHeight() override { return dim.h; }
        inline float getWidth() override { return dim.w; }

        void dispose();
        void drawBase(const sdl::RectI* sourceRec, const sdl::RectF* destRec, const sdl::Point& origin, float rotation, sdl::RendererFlip flip) override;
        void setDrawBlend(const sdl::BlendMode bl) override;
        void setDrawColor(const sdl::Color& tint) override;
    private:
        sdl::RectI dim;
        sdl::Texture* texture;
        std::uint32_t format;
        int access;
	};

    void FTexture::dispose()
    {
        sdl::textureDestroy(texture);
        texture = nullptr;
    }

    void FTexture::drawBase(const sdl::RectI* sourceRec, const sdl::RectF* destRec, const sdl::Point& origin, float rotation, sdl::RendererFlip flip)
    {
        sdl::renderCopyEx(texture, &dim, destRec, rotation, &origin, flip);
    }

    void FTexture::setDrawBlend(const sdl::BlendMode bl)
    {
        sdl::textureSetBlendMode(texture, bl);
    }

    void FTexture::setDrawColor(const sdl::Color& tint)
    {
        sdl::textureSetColorMod(texture, tint.r, tint.g, tint.b);
        sdl::textureSetAlphaMod(texture, tint.a);
    }
}