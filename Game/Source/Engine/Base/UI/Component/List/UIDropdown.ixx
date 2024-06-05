export module fbc.UIDropdown;

import fbc.CoreConfig;
import fbc.CoreContent;
import fbc.FFont;
import fbc.FUtil;
import fbc.Hitbox;
import fbc.IDrawable;
import fbc.UITitledInteractable;
import fbc.IOverlay;
import fbc.ScreenManager;
import fbc.TextInfo;
import fbc.UIEntry;
import fbc.UIInteractable;
import fbc.UIMenu;
import fbc.ScaleHitbox;
import sdl;
import std;

export namespace fbc {
	export template <typename T> class UIDropdown : public UITitledInteractable, public TextInfo {
	public:

		UIDropdown(Hitbox* hb, 
			UIMenu<T>* menu, 
			IDrawable& image = cct.images.panel,
			IDrawable& arrow = cct.images.uiArrowSmall,
			IDrawable& clear = cct.images.uiClearSmall,
			FFont& textFont = cct.fontRegular(),
			func<str(vec<const UIEntry<T>*>&)> buttonLabelFunc = {}
		): UITitledInteractable(hb, image), TextInfo(textFont), menu(menu), buttonLabelFunc(buttonLabelFunc), arrow(arrow), clear(clear) {
			init();
		}
		UIDropdown(Hitbox* hb,
			uptr<UIMenu<T>> menu,
			IDrawable& image = cct.images.panel,
			IDrawable& arrow = cct.images.uiArrowSmall,
			IDrawable& clear = cct.images.uiClearSmall,
			FFont& textFont = cct.fontRegular(),
			func<str(vec<const UIEntry<T>*>&)> buttonLabelFunc = {}
		): UITitledInteractable(hb, image), TextInfo(textFont), menu(std::move(menu)), buttonLabelFunc(buttonLabelFunc), arrow(arrow), clear(clear) {
			init();
		}
		virtual ~UIDropdown() override{}

		uptr<UIMenu<T>> menu;

		inline void clearItems() { menu->clearItems(); }
		inline bool isOpen() { return proxy != nullptr; }
		inline int selectedSize() const { return menu->selectedSize(); }
		inline UIDropdown& setEntryFunc(func<UIEntry<T>*(UIMenu<T>&, T&, str&, int)> entryFunc) { return menu->setEntryFunc(entryFunc), *this; }
		inline UIDropdown& setOnChange(func<void(vec<const T*>)> onChange) { return menu->setOnChange(onChange), * this; }
		inline virtual UIDropdown& setOnClose(func<void()> onClose) { return this->onClose = onClose, *this; }
		inline UIDropdown& setOnOpen(func<void()> onOpen) { return this->onOpen = onOpen, *this; }
		inline int size() { return menu->size(); }
		inline UIDropdown& setItemFont(FFont& itemFont) { return menu->setItemFont(itemFont), * this; }
		inline UIDropdown& setMaxRows(int rows) { return menu->setMaxRows(rows), * this; }
		inline vec<T*> getAllItems() { return menu->getAllItems(); }
		inline vec<T*> getSelectedItems() { return menu->getSelectedItems(); }
		inline void clearSelection() { menu->clearSelection(); }
		inline void selectSingle(T item) { menu->selectSingle(item); }
		inline void selectSingle(T* item) { menu->selectSingle(item); }
		inline void updateSingle(T item) { menu->updateSingle(item); }
		inline void updateSingle(T* item) { menu->updateSingle(item); }
		template <c_itr<int> Iterable> inline void selectIndices(Iterable& indices) { menu->selectIndices(indices); }
		template <c_itr<T> Iterable> inline void selectSelection(Iterable& items) { menu->selectSelection(items); }
		template <c_itr<T*> Iterable> inline void selectSelection(Iterable& items) { menu->selectSelection(items); }
		template <c_varg<T>... Args> inline void selectSelection(Args&&... items) { menu->selectSelection(items); }
		template <c_varg<T*>... Args> inline void selectSelection(Args&&... items) { menu->selectSelection(items); }
		template <c_itr<int> Iterable> inline void updateIndices(Iterable& indices) { menu->updateIndices(indices); }
		template <c_itr<T> Iterable> inline void updateSelection(Iterable& items) { menu->updateSelection(items); }
		template <c_itr<T*> Iterable> inline void updateSelection(Iterable& items) { menu->updateSelection(items); }
		template <c_varg<T>... Args> inline void updateSelection(Args&&... items) { menu->updateSelection(items); }
		template <c_varg<T*>... Args> inline void updateSelection(Args&&... items) { menu->updateSelection(items); }

		template <c_itr<T> Iterable> UIDropdown& addItems(const Iterable& items);
		template <c_itr<T*> Iterable> UIDropdown& addItems(const Iterable& items);
		template <c_varg<T>... Args> UIDropdown& addItems(Args&&... items);
		template <c_varg<T*>... Args> UIDropdown& addItems(Args&&... items);
		template <c_itr<T> Iterable> UIDropdown& setItems(const Iterable& items);
		template <c_itr<T*> Iterable> UIDropdown& setItems(const Iterable& items);
		template <c_varg<T>... Args> UIDropdown& setItems(Args&&... items);
		template <c_varg<T*>... Args> UIDropdown& setItems(Args&&... items);
		void forceClosePopup();
		virtual void onSizeUpdated() override;
		virtual void openPopup();
		virtual void refreshHb() override;
		virtual void renderImpl() override;
		virtual void updateImpl() override;
		virtual void unsetProxy();

		static uptr<UIDropdown> multiMenu(Hitbox* hb, 
			func<str(const T&)> labelFunc = [](const T& item) { return futil::toString(item); },
			func<str(vec<const UIEntry<T>*>&)> buttonLabelFunc = {},
			FFont& itemFont = cct.fontRegular(),
			FFont& textFont = cct.fontRegular(),
			IDrawable& background = cct.images.darkPanelRound,
			IDrawable& image = cct.images.panel,
			IDrawable& arrow = cct.images.uiArrowSmall,
			IDrawable& clear = cct.images.uiClearSmall);
		static uptr<UIDropdown> singleMenu(Hitbox* hb, 
			func<str(const T&)> labelFunc = [](const T& item) { return futil::toString(item); },
			func<str(vec<const UIEntry<T>*>&)> buttonLabelFunc = {},
			FFont& itemFont = cct.fontRegular(),
			FFont& textFont = cct.fontRegular(),
			IDrawable& background = cct.images.darkPanelRound,
			IDrawable& image = cct.images.panel,
			IDrawable& arrow = cct.images.uiArrowSmall,
			IDrawable& clear = cct.images.uiClearSmall);
	protected:
		IDrawable& arrow;
		IDrawable& clear;
		sdl::RectF arrowRect;

		str getButtonText(vec<const UIEntry<T>*>& items);
		virtual void clickLeftEvent() override;
		virtual inline void onChangeItems() {}
		virtual void onSelectionUpdate(vec<const UIEntry<T>*>& items);
	private:
		func<str(vec<const UIEntry<T>*>&)> buttonLabelFunc;
		func<void()> onClose;
		func<void()> onOpen;
		IOverlay* proxy;

		void init();
	};

	export template <typename T> class UIDropdownProxy : public IOverlay {
	public:
		UIDropdownProxy(UIDropdown<T>& menu) : dropdown(menu) {}
		UIDropdown<T>& dropdown;

		void dispose() override;
		void render() override;
		void update() override;
	};

	template<typename T> void UIDropdown<T>::forceClosePopup() {
		if (proxy != nullptr) { screenManager::closeOverlay(proxy); }
	}

	template<typename T> void UIDropdown<T>::refreshHb() {
		UITitledInteractable::refreshHb();
		this->menu->refreshHb();
	}

	template<typename T> void UIDropdown<T>::unsetProxy() {
		proxy = nullptr;
		if (onClose) {
			onClose();
		}
	}

	template<typename T> void UIDropdown<T>::onSizeUpdated()
	{
		TextInfo::setPos(cfg.renderScale(24), hb->h * 0.25f);
		arrowRect.w = arrowRect.h = hb->h * 0.5f;
	}

	// When opened, move the menu directly below this button, unless there isn't enough room (in which case it should appear above this button)
	template<typename T> void UIDropdown<T>::openPopup() {
		int bottom = hb->y + hb->h;
		if (bottom + menu->hb->h > cfg.getScreenYSize()) {
			menu->hb->setExactPos(hb->x, hb->y - menu->hb->h);
		}
		else {
			menu->hb->setExactPos(hb->x, bottom);
		}
		if (proxy == nullptr) {
			screenManager::openOverlay(std::make_unique<UIDropdownProxy<T>>(*this));
			proxy = screenManager::getActiveOverlay();
			if (onOpen) {
				onOpen();
			}
		}
	}

	template<typename T> void UIDropdown<T>::renderImpl() {
		UITitledInteractable::renderImpl();
		if (this->selectedSize() > 0) {
			clear.draw(&arrowRect, UIImage::color, origin, rotation);
		}
		else {
			arrow.draw(&arrowRect, UIImage::color, origin, rotation, menu->isOpen() ? sdl::FlipMode::SDL_FLIP_VERTICAL : flip);
		}
		TextInfo::drawText(hb->x, hb->y);
	}

	template<typename T> void UIDropdown<T>::updateImpl() {
		UIInteractable::updateImpl();
		arrowRect.x = hb->x + hb->w - arrowRect.w * 1.5f;
		arrowRect.y = hb->y + hb->h * 0.25f;
	}

	// Updates the text shown on the button by default, this may be overriden in derivative types
	template<typename T> void UIDropdown<T>::onSelectionUpdate(vec<const UIEntry<T>*>& items) {
		setText(getButtonText(items));
	}

	template<typename T> void UIDropdown<T>::init()
	{
		this->menu->setOnSelectionUpdate([this](vec<const UIEntry<T>*>& items) { this->onSelectionUpdate(items); });
		this->menu->hb->setExactPos(hb->x, hb->y);
		UIDropdown<T>::onSizeUpdated();
	}

	template<typename T> uptr<UIDropdown<T>> UIDropdown<T>::multiMenu(
		Hitbox* hb, func<str(const T&)> labelFunc, func<str(vec<const UIEntry<T>*>&)> buttonLabelFunc, FFont& itemFont, FFont& textFont, IDrawable& background, IDrawable& image, IDrawable& arrow, IDrawable& clear)
	{
		return std::make_unique<UIDropdown<T>>(
			hb,
			UIMenu<T>::multiMenu(new ScaleHitbox(hb->getOffsetSizeX(), hb->getOffsetSizeY()), labelFunc, itemFont, background),
			image,
			arrow,
			clear,
			textFont,
			buttonLabelFunc
		);
	}

	template<typename T> uptr<UIDropdown<T>> UIDropdown<T>::singleMenu(
		Hitbox* hb, func<str(const T&)> labelFunc, func<str(vec<const UIEntry<T>*>&)> buttonLabelFunc, FFont& itemFont, FFont& textFont, IDrawable& background, IDrawable& image, IDrawable& arrow, IDrawable& clear)
	{
		return std::make_unique<UIDropdown<T>>(
			hb,
			UIMenu<T>::singleMenu(new ScaleHitbox(hb->getOffsetSizeX(), hb->getOffsetSizeY()), labelFunc, itemFont, background),
			image,
			arrow,
			clear,
			textFont,
			buttonLabelFunc
		);
	}

	// The text on the dropdown should reflect the contents of the selected menu items.
	// If no button label function is set, this will default to joining the string representations of each entry. If this text is too long, the displayed text will instead show the number of items selected
	template<typename T> str UIDropdown<T>::getButtonText(vec<const UIEntry<T>*>& items)
	{
		if (buttonLabelFunc) {
			return buttonLabelFunc(items);
		}
		else {
			str displayText = (futil::joinStrMap(", ", items, [](const UIEntry<T>* entry) {return entry->getText(); }));
			if (this->font.measureW(displayText) > hb->w) {
				return cct.strings.ui_items(this->selectedSize());
			}
			else {
				return displayText;
			}
		}
	}

	// When clicked, open the menu if closed. Otherwise, dispose the menu
	template<typename T> void UIDropdown<T>::clickLeftEvent() {
		if (this->selectedSize() > 0 && sdl::mouseGetX() >= arrowRect.x) {
			clearSelection();
		}
		else if (isOpen()) {
			menu->forceClosePopup();
		}
		else {
			openPopup();
		}
	}

	template<typename T> template<c_itr<T> Iterable> UIDropdown<T>& UIDropdown<T>::addItems(const Iterable& items)
	{
		this->menu->addItems(items);
		onChangeItems();
		return *this;
	}

	template<typename T> template<c_itr<T*> Iterable> UIDropdown<T>& UIDropdown<T>::addItems(const Iterable& items)
	{
		this->menu->addItems(items);
		onChangeItems();
		return *this;
	}


	template<typename T> template<c_varg<T> ...Args> UIDropdown<T>& UIDropdown<T>::addItems(Args&&... items)
	{
		this->menu->addItems(items);
		onChangeItems();
		return *this;
	}


	template<typename T> template<c_varg<T*> ...Args> UIDropdown<T>& UIDropdown<T>::addItems(Args&&... items)
	{
		this->menu->addItems(items);
		onChangeItems();
		return *this;
	}

	template<typename T> template<c_itr<T> Iterable> UIDropdown<T>& UIDropdown<T>::setItems(const Iterable& items)
	{
		this->menu->setItems(items);
		onChangeItems();
		return *this;
	}

	template<typename T> template<c_itr<T*> Iterable> UIDropdown<T>& UIDropdown<T>::setItems(const Iterable& items)
	{
		this->menu->setItems(items);
		onChangeItems();
		return *this;
	}

	template<typename T> template<c_varg<T> ...Args> UIDropdown<T>& UIDropdown<T>::setItems(Args&&... items)
	{
		this->menu->addItems(items);
		onChangeItems();
		return *this;
	}


	template<typename T> template<c_varg<T*> ...Args> UIDropdown<T>& UIDropdown<T>::setItems(Args&&... items)
	{
		this->menu->addItems(items);
		onChangeItems();
		return *this;
	}

	/*
	 * UIDropdownProxy Implementations
	 */

	// When closed, unlink this from its menu
	template <typename T> void UIDropdownProxy<T>::dispose() { dropdown.unsetProxy(); }

	template<typename T> void UIDropdownProxy<T>::render() {
		dropdown.menu->renderImpl();
	}

	// Close the menu if the user clicks outside the menu
	template <typename T> void UIDropdownProxy<T>::update() {
		dropdown.updateImpl();
		dropdown.menu->updateImpl();
		if ((sdl::mouseIsLeftJustClicked() && !dropdown.menu->isHovered() && !dropdown.isHovered()) || sdl::keyboardJustPressedEsc()) { screenManager::closeOverlay(this); }
	}

}