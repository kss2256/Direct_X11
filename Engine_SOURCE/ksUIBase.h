#pragma once
#include "ksGameObject.h"


namespace ks
{
	class UIBase : public GameObject
	{

	public:
		UIBase();
		virtual ~UIBase();


		virtual void Initalize() = 0;
		virtual void Update();
		virtual void FixedUpdate() = 0;
		virtual void Render() = 0;


		void AddChild(UIBase* uiBase)
		{
			uiBase->mParent = this;
			mChilds.push_back(uiBase);
		}

		eUIType GetUIType() { return mType; }

		void SetParent(UIBase* parent) { mParent = parent; }
		void SetPos(Vector3 pos) { mPos = pos; }
		Vector3 GetPos() { return mPos; }
		void SetSize(Vector3 size) { mSize = size; }
		Vector3 GetSize() { return mSize; }
		void SetCmrAfctd(bool cmr) { mCmrAfctd = cmr; }
		void SetUIType(eUIType type) { mType = type; }


		bool IsMouseOn() { return mMouseOn; }
		bool IsLbtnDown() { return mLbtnDown; }
		bool IsLbtnUp() { return mLbtnUp; }
		bool IsLbtnPressed() { return mLbtnPressed; }

		virtual void MouseLbtnDown() { mLbtnDown = true; };
		virtual void MouseLbtnUp() { mLbtnUp = true; };
		virtual void MousePressed() { mLbtnPressed = true; };



		virtual void MouseOn() { mMouseOn = true; };
		virtual void MouseOff() { mMouseOn = false; };


	protected:

		UIBase* mParent;

		Vector3 mPos;
		Vector3 mSize;
		Vector3 mScreenPos;


		bool					mOneCheak;

	private:

		void MouseOnCheak();


	private:

		std::vector<UIBase*>	mChilds;

		eUIType					mType;

		bool					mLbtnDown;
		bool					mLbtnUp;
		bool					mLbtnPressed;
		bool					mMouseOn;
		bool					mCmrAfctd;

		friend class UiMgr;

	};

}