#pragma once
#include "ksComponent.h"
#include "ksAnimation.h"

namespace ks
{
	class Animator : public Component
	{
	public:
		struct Events
		{
			struct Event
			{
				void operator=(std::function<void()> func)
				{
					mEvent = std::move(func);
				}
				void operator()()
				{
					if (mEvent)
						mEvent();
				}

				std::function<void()> mEvent;
			};

			Event mStartEvent;
			Event mCompleteEvent;
			Event mEndEvent;

			std::vector<Event> mEvents;
		};

		Animator();
		~Animator();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		void Create(const std::wstring& name, std::shared_ptr<Texture> atlas
			, Vector2 leftTop, Vector2 size, Vector2 offset
			, UINT spriteLegth, float duration);

		void CreateAfter(std::vector<Sprite> sprites, std::shared_ptr<Texture> atlas);

		Animation* FindAnimation(const std::wstring& name);
		Events* FindEvents(const std::wstring& name);
		void Play(const std::wstring& name, bool loop = true, bool save = false);

		void Binds();
		void Clear();

		std::function<void()>& GetStartEvent(const std::wstring& name);
		std::function<void()>& GetCompleteEvent(const std::wstring& name);
		std::function<void()>& GetEndEvent(const std::wstring& name);
		std::function<void()>& GetEvent(const std::wstring& name, UINT index);

		void SetSpriteSheet(Sprite sheet) { mSheetSave.push_back(sheet); }
		Sprite GetSpriteSheet();
		std::vector<Sprite>& GetSprite() { return mSheetSave; }
		void ClearSpriteSheet();

	private:

		std::map<std::wstring, Animation*> mAnimations;
		std::map<std::wstring, Events*> mEvents;
		std::vector<Sprite> mSheetSave;
		
		Animation* mActiveAnimation;
		bool mbLoop;
	};
}