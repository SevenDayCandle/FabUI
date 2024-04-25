export module fbc.uiToggle;

import fbc.coreContent;
import fbc.ffont;
import fbc.hitbox;
import fbc.iDrawable;
import fbc.uiImage;
import fbc.screenManager;
import fbc.textInfo;
import fbc.futil;
import sdl;

export namespace fbc {
	export class UIToggle : public UIImage, public TextInfo {
	public:
		UIToggle(Hitbox* hb, str text, IDrawable& image = cct.images.checkboxEmpty(), IDrawable& checkImage = cct.images.checkboxFilled(), FFont& f = cct.fontRegular()):
			UIImage(hb, image), checkImage(checkImage), TextInfo(f, text) {}
		virtual ~UIToggle() {}

		bool interactable = true;
		bool toggled = false;
		IDrawable& checkImage;

		inline UIToggle& setInteractable(bool val) { return this->interactable = val, *this; }
		inline UIToggle& setOnClick(const func<void(UIToggle&)>& onClick) { return this->onClick = onClick, *this; }
		inline UIToggle& setToggleState(bool val) { return this->toggled = val, *this; }

		void renderImpl() override;
		void toggle(bool val);
		void updateImpl() override;
	private:
		func<void(UIToggle&)> onClick;
	};

	void UIToggle::renderImpl()
	{
		if (toggled) {
			checkImage.draw(hb.get(), UIImage::color, origin, rotation, flip);
			if (hb->isHovered()) {
				checkImage.draw(hb.get(), sdl::BlendMode::SDL_BLENDMODE_ADD, UIImage::color, origin, rotation, flip);
			}
		}
		else {
			image.draw(hb.get(), UIImage::color, origin, rotation, flip);
			if (hb->isHovered()) {
				image.draw(hb.get(), sdl::BlendMode::SDL_BLENDMODE_ADD, UIImage::color, origin, rotation, flip);
			}
		}

		float textX = hb->x + hb->w * 1.5f;
		float textY = hb->y + hb->h * 0.5f;
		TextInfo::drawText(textX, textY);
	}

	void UIToggle::toggle(bool val)
	{
		toggled = val;
		if (onClick) {
			onClick(*this);
		}
	}

	void UIToggle::updateImpl()
	{
		UIImage::updateImpl();

		if (hb->isHovered()) {
			if (screenManager::activeElement == nullptr && interactable) {
				if (hb->isJust()) {
					// TODO play sound
				}

				if (sdl::mouseIsLeftJustClicked()) {
					screenManager::activeElement = this;
				}
			}
			else if (screenManager::activeElement == this && sdl::mouseIsLeftJustReleased()) {
				toggle(!toggled);
				screenManager::activeElement = nullptr;
			}
		}
		else if (screenManager::activeElement == this && (sdl::mouseIsLeftJustReleased())) {
			screenManager::activeElement = nullptr;
		}
	}
}