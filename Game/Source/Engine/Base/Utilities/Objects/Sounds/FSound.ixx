export module fbc.FSound;

import fbc.FUtil;
import fbc.ILoadable;
import sdl;
import std;

export namespace fbc {
	export class FSound : public ILoadable {
	public:
		FSound(strv path) : path(path) {}
		FSound(const FSound&) = delete;
		~FSound() override {
			// Unload sound when destroyed
			if (sound && sdl::sdlEnabled()) {
				sdl::soundDestroy(sound);
				sound = nullptr;
			}
		}

		inline void play(int loops = 0, int time = -1) const { sdl::soundPlay(sound, loops, time); }
		inline void playFade(int fade, int loops = 0, int time = -1) const { sdl::soundPlayFade(sound, fade, loops, time); }

		void dispose() override;
		void reload() override;
	private:
		str path;
		sdl::Sound* sound;
	};

	void FSound::dispose()
	{
		sdl::soundDestroy(sound);
		sound = nullptr;
	}

	void FSound::reload()
	{
		if (sound) {
			sdl::soundDestroy(sound);
		}
		sound = sdl::soundLoad(path.data());
		if (sound == nullptr) {
			sdl::logError("Failed to load sound %s: %s", path, sdl::getError());
		}
	}
}