export module fbc.CombatTurnRenderable;

import fbc.CombatTurn;
import fbc.CoreContent;
import fbc.FUtil;
import fbc.Hitbox;
import fbc.IDrawable;
import fbc.UIInteractable;
import sdl;
import std;

namespace fbc {
	export class CombatTurnRenderable : public UIInteractable {
	public:
		CombatTurnRenderable(const CombatTurn& turn, Hitbox* hb) : UIInteractable(hb, cct.images.uiDarkPanelRound), portrait(turn.source.getImagePortrait()) {}

		IDrawable& portrait;

		virtual void renderImpl(sdl::GpuCommandBuffer* cd, sdl::GpuRenderPass* rp) override;

		// TODO highlight turn owner when hovered
	};

	void CombatTurnRenderable::renderImpl(sdl::GpuCommandBuffer* cd, sdl::GpuRenderPass* rp)
	{
		UIInteractable::renderImpl(cd, rp);
		sdl::RectF portraitRect = { hb->x + hb->w / 8, hb->y + hb->h * 0.15f, hb->w / 2, hb->h * 0.7f };
		portrait.draw(&portraitRect, color, origin, rotation, flip);
	}
}