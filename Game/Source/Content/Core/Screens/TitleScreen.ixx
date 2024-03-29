export module fbc.titleScreen;

import fbc.coreContent;
import fbc.canvasScreen;
import fbc.screenHitbox;
import fbc.screenManager;
import fbc.setupScreen;
import fbc.uiTextButton;
import fbc.futil;
import std;

export namespace fbc {
	export class TitleScreen : public CanvasScreen {
	public:
		TitleScreen() {
			UITextButton& b = canvas.addElement(std::make_unique<UITextButton>(
				new ScreenHitbox(0.5f, 0.5f, 150, 100),
				cct.images.smallPanel(),
				cct.fontRegular(),
				cct.strings.screen_title_header()));
			b.setOnClick([](UIButton& i) {
				screenManager::openScreen(std::make_unique<SetupScreen>());
				});
		}

		void close() {

		}

		void open() {

		}
	};
}