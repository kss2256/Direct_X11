#pragma once
namespace ks
{
	class UIBase;
	class UiMgr
	{

	public:

		static void Update();



	private:

		static UIBase* getPriorityUI(UIBase* ui);


	private:

		static UIBase* mCurUI;
		static UIBase* mPriorityUI;

	
	};
}
