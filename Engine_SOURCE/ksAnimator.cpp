#include "ksAnimator.h"


namespace ks
{
	Animator::Animator()
		: Component(eComponentType::Animator)
		, mAnimations{}
		, mEvents{}
		, mActiveAnimation(nullptr)
		, mbLoop(false)
	{

	}
	Animator::~Animator()
	{
		for (auto anim : mAnimations)
		{
			delete anim.second;
			anim.second = nullptr;
		}

		for (auto evt : mEvents)
		{
			delete evt.second;
			evt.second = nullptr;
		}
	}
	void Animator::Initalize()
	{
	}
	void Animator::Update()
	{
		if (mActiveAnimation == nullptr)
			return;

		Events* events
			= FindEvents(mActiveAnimation->AnimationName());
		if (mActiveAnimation->IsComplete())
		{
			if (events)
				events->mCompleteEvent();

			if (mbLoop)
				mActiveAnimation->Reset();
		}

		UINT spriteIndex = mActiveAnimation->Update();
		if (spriteIndex != -1 &&
			events->mEvents[spriteIndex].mEvent)
		{
			events->mEvents[spriteIndex].mEvent();
		}

	}
	void Animator::FixedUpdate()
	{
	}
	void Animator::Render()
	{
	}

	void Animator::Create(const std::wstring& name, std::shared_ptr<Texture> atlas
		, Vector2 leftTop, Vector2 size, Vector2 offset
		, UINT spriteLegth, float duration)
	{
		if (atlas == nullptr)
			return;

		Animation* animation = FindAnimation(name);
		if (animation != nullptr)
			return;

		animation = new Animation();
		animation->Create(name, atlas, leftTop
			, size, offset
			, spriteLegth, duration);

		mAnimations.insert(std::make_pair(name, animation));
		
		


		Events* events = new Events();
		events->mEvents.resize(spriteLegth);
		mEvents.insert(std::make_pair(name, events));
	}

	void Animator::CreateAfter(std::vector<Sprite> sprites , std::shared_ptr<Texture> atlas)
	{
		if (atlas == nullptr)
			return;


		Animation* animation = new Animation();
		animation->CreateAfter(sprites, atlas);
		Events* events = new Events();
		events->mEvents.resize(sprites.size());
		for (size_t i = 0; i < sprites.size(); i++)
		{
		mAnimations.insert(std::make_pair(sprites[i].AnimationName, animation));
		mEvents.insert(std::make_pair(sprites[i].AnimationName, events));
		}
		
		
		
	

	}

	Animation* Animator::FindAnimation(const std::wstring& name)
	{
		std::map<std::wstring, Animation*>::iterator iter
			= mAnimations.find(name);

		if (iter == mAnimations.end())
		{
			return nullptr;
		}

		return iter->second;
	}
	Animator::Events* Animator::FindEvents(const std::wstring& name)
	{
		std::map<std::wstring, Events*>::iterator iter
			= mEvents.find(name);

		if (iter == mEvents.end())
		{
			return nullptr;
		}

		return iter->second;
	}
	void Animator::Play(const std::wstring& name, bool loop, bool save)
	{
		Animation* prevAnimation = mActiveAnimation;
		Events* events = nullptr;
		if (prevAnimation)
			events = FindEvents(prevAnimation->AnimationName());

		if (events)
			events->mEndEvent();

		mActiveAnimation = FindAnimation(name);
		mActiveAnimation->Reset();
		mbLoop = loop;

		events = FindEvents(mActiveAnimation->AnimationName());

		if (events)
			events->mStartEvent();

		if (save)
		{
			for (size_t i = 0; i < mActiveAnimation->GetSpriteSheet().size(); i++)
			{				
				mSheetSave.push_back(mActiveAnimation->GetSpriteSheet()[i]);
			}			
		}

	}


	void Animator::Binds()
	{
		if (mActiveAnimation == nullptr)
			return;

		mActiveAnimation->BindShader();
	}

	void Animator::Clear()
	{
		if (mActiveAnimation == nullptr)
			return;

		mActiveAnimation->Clear();
	}

	std::function<void()>& Animator::GetStartEvent(const std::wstring& name)
	{
		Events* events = FindEvents(name);

		return events->mStartEvent.mEvent;
	}
	std::function<void()>& Animator::GetCompleteEvent(const std::wstring& name)
	{
		Events* events = FindEvents(name);

		return events->mCompleteEvent.mEvent;
	}
	std::function<void()>& Animator::GetEndEvent(const std::wstring& name)
	{
		Events* events = FindEvents(name);

		return events->mEndEvent.mEvent;
	}
	std::function<void()>& Animator::GetEvent(const std::wstring& name, UINT index)
	{
		Events* events = FindEvents(name);

		return events->mEvents[index].mEvent;
	}
	Sprite Animator::GetSpriteSheet()
	{
		Sprite sheet = mSheetSave[mActiveAnimation->GetIndex()];

		return sheet;
	}

	void Animator::ClearSpriteSheet()
	{
		mSheetSave.clear();
	}

}
