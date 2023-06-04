#include "ksMonster.h"



namespace ks
{


	Monster::Monster()
		: mStep(eStep::None)
		, mCheak(false)
		, mDirectionCheak(false)
		, mAttackCool(false)
		, mTime(0.f)
		, mDetection(false)
		, mShakeTime(0.f)
		, mBossHit(false)
		, mOnceCheak(false)
	{
	}
	Monster::~Monster()
	{

		/*for (size_t i = 0; i < mSvaeSprite.size(); i++)
		{
			mSvaeSprite.clear();
		}


		for (size_t i = 0; i < mSprites.size(); i++)
		{
			mSprites.clear();
		}*/

	}
	void Monster::Initalize()
	{


		GameObject::Initalize();

	}
	void Monster::Update()
	{


		GameObject::Update();
	}
	void Monster::FixedUpdate()
	{


		GameObject::FixedUpdate();
	}
	void Monster::Render()
	{


		GameObject::Render();
	}
	void Monster::SetMonsterHp(float value)
	{

		 mHp -= value; 
		 if (mHp <= 0)
		 {
			 mStateInfo.situation = eSituation::Death;
		 }


	}
	void Monster::CreateAnimation(const std::wstring& name, std::shared_ptr<Texture> texture, Animator* animaotr
		, Vec2 scale, Vector2 offset, std::vector<UINT> numbers, float duration)
	{


		// ���� ���� 		
		Vec2 value = Vec2(texture->GetWidth() / scale.x, texture->GetHeight() / scale.y);
		UINT Col = (UINT)value.x;					//3��?
		UINT Row = (UINT)value.y;					//10��?

		UINT textureeLegth = (UINT)(value.x * value.y);		//�� ���� 30��

		//���� ���� �̰� 10��
		for (UINT i = 0; i < Row; i++)
		{
			//���� ���� �̰� 3��
			for (UINT j = 0; j < Col; j++)
			{
				Sprite animation;

				animation.AnimationName = name;
				animation.atlasSize = scale;
				animation.duration = duration;
				animation.leftTop = Vec2(j * scale.x, i * scale.y);
				animation.offset = offset;
				//animation.pos = mTransform->GetPosition(); // �̰� �ʿ� ���µ� ? �ʿ��ҋ� ��뿹�� �������� �޾ƿ;���
				animation.size = scale;


				mSvaeSprite.push_back(animation);
			}
		}

		for (size_t i = 0; i < numbers.size(); i++)
		{
			std::vector<UINT>::iterator iter = numbers.begin();

			mSprites.push_back(mSvaeSprite[iter[i]]);
		}


		for (size_t i = 0; i < mSprites.size(); i++)
		{
			mSprites[i].leftTop = Vector2((mSprites[i].leftTop.x / texture->GetWidth()), (mSprites[i].leftTop.y) / texture->GetHeight());
			mSprites[i].size = Vector2(mSprites[i].size.x / texture->GetWidth(), mSprites[i].size.y / texture->GetHeight());
			mSprites[i].offset = mSprites[i].offset;
			mSprites[i].duration = mSprites[i].duration;
			mSprites[i].atlasSize = Vector2(400.0f / texture->GetWidth(), 400.0f / texture->GetHeight());
			mSprites[i].AnimationName = mSprites[i].AnimationName;
		}



		animaotr->CreateAfter(mSprites, texture);
		mSvaeSprite.clear();
		mSprites.clear();
	}
	bool Monster::Range()
	{
		if (mPlayer != nullptr)
			mTargetPos = mPlayer->GetComponent<Transform>()->GetPosition();

		mMonsterPos = mTransform->GetPosition();
		if (mTargetPos.x - 5.1f >= mMonsterPos.x || mTargetPos.x + 5.1f <= mMonsterPos.x
			|| mTargetPos.y - 4.1f >= mMonsterPos.y || mTargetPos.y + 4.1f <= mMonsterPos.y)
			return false;

		return true;

	}
	void Monster::Patrol()
	{

		//�ָ� ������ ������ ������ �ٰ��� Ž�� ���� ���� �÷��̾�� �̵� 
		if (mPlayer != nullptr)
			mTargetPos = mPlayer->GetComponent<Transform>()->GetPosition();

		mMonsterPos = mTransform->GetPosition();
		Vec3 pos = mTransform->GetPosition();

		AngleDirection();

		if (!mDirectionCheak && mStateInfo.situation == eSituation::Patrol)
		{
			directionAnimation(L"Move", true);
		}

		if (mStateInfo.situation == eSituation::Patrol)
		{
			if (mTargetPos.x - 5.1f >= mMonsterPos.x || mTargetPos.x + 5.1f <= mMonsterPos.x
				|| mTargetPos.y - 4.1f >= mMonsterPos.y || mTargetPos.y + 4.1f <= mMonsterPos.y)
			{
				mMovePos = mTargetPos - mMonsterPos;
				mMovePos.Normalize();

				pos += mMovePos * 1.6f * Time::DeltaTime();
			}

			else
			{
				mStateInfo.situation = eSituation::Attack;
			}
		}

		mTransform->SetPosition(pos);
	}

	void Monster::AngleDirection()
	{

		Transform* tr = mPlayer->GetComponent<Transform>();
		Vec3 Pos = mTransform->GetPosition();

		Vector3 distance = Vector3(tr->GetPosition().x - Pos.x, tr->GetPosition().y - Pos.y, 1.0f);



		float dir = atan2(distance.y, distance.x);

		float angle = (float)((dir * 180) / 3.14159265);

		tStateInfo previnfo = mStateInfo;
		//���� ������ ���� atan2 �Լ��� ���� ���� (180~ -180)���� ������

		//Right	
		if (angle <= 22.5 && angle > -22.5)
			mStateInfo.direction = eDirection::Right;
		//UpRight
		else if (angle <= 67.5 && angle > 22.5)
			mStateInfo.direction = eDirection::UpRight;
		//Up
		else if (angle <= 112.5 && angle > 67.5)
			mStateInfo.direction = eDirection::Up;
		//UpLeft
		else if (angle <= 157.5 && angle > 112.5)
			mStateInfo.direction = eDirection::UpLeft;
		//Left
		else if (angle <= -157.5 || angle > 157.5)
			mStateInfo.direction = eDirection::Left;
		//DownLeft
		else if (angle <= -112.5 && angle > -157.5)
			mStateInfo.direction = eDirection::DownLeft;
		//Down
		else if (angle <= -67.5 && angle > -112.5)
			mStateInfo.direction = eDirection::Down;
		//DownRight
		else if (angle <= -22.5 && angle > -67.5)
			mStateInfo.direction = eDirection::DownRight;

		if (mStateInfo.direction == previnfo.direction)
			mDirectionCheak = true;
		else
			mDirectionCheak = false;

	}
	void Monster::directionAnimation(const std::wstring& name, bool loop)
	{
		std::wstring aniname;

		switch (mStateInfo.direction)
		{
		case ks::eDirection::Left:
		{
			aniname = name + L"_Left";
			mAnimator->Play(aniname, loop);
		}
		break;
		case ks::eDirection::Right:
		{
			aniname = name + L"_Right";
			mAnimator->Play(aniname, loop);
		}
		break;
		case ks::eDirection::Up:
		{
			aniname = name + L"_Up";
			mAnimator->Play(aniname, loop);
		}
		break;
		case ks::eDirection::Down:
		{
			aniname = name + L"_Down";
			mAnimator->Play(aniname, loop);
		}
		break;
		case ks::eDirection::UpLeft:
		{
			aniname = name + L"_Up";
			mAnimator->Play(aniname, loop);
		}
		break;
		case ks::eDirection::UpRight:
		{
			aniname = name + L"_Right";
			mAnimator->Play(aniname, loop);
		}
		break;
		case ks::eDirection::DownLeft:
		{
			aniname = name + L"_Left";
			mAnimator->Play(aniname, loop);
		}
		break;
		case ks::eDirection::DownRight:
		{
			aniname = name + L"_Down";
			mAnimator->Play(aniname, loop);
		}
		break;

		}


	}
	void Monster::oneDirectionAnimation(const std::wstring& name, eDirection dir, bool loop)
	{
		std::wstring aniname;

		switch (dir)
		{
		case ks::eDirection::Left:
		{
			aniname = name + L"_Left";
			mAnimator->Play(aniname, loop);
		}
		break;
		case ks::eDirection::Right:
		{
			aniname = name + L"_Right";
			mAnimator->Play(aniname, loop);
		}
		break;
		case ks::eDirection::Up:
		{
			aniname = name + L"_Up";
			mAnimator->Play(aniname, loop);
		}
		break;
		case ks::eDirection::Down:
		{
			aniname = name + L"_Down";
			mAnimator->Play(aniname, loop);
		}
		break;
		case ks::eDirection::UpLeft:
		{
			aniname = name + L"_Up";
			mAnimator->Play(aniname, loop);
		}
		break;
		case ks::eDirection::UpRight:
		{
			aniname = name + L"_Right";
			mAnimator->Play(aniname, loop);
		}
		break;
		case ks::eDirection::DownLeft:
		{
			aniname = name + L"_Left";
			mAnimator->Play(aniname, loop);
		}
		break;
		case ks::eDirection::DownRight:
		{
			aniname = name + L"_Down";
			mAnimator->Play(aniname, loop);
		}
		break;
		}

	}

	void Monster::hit(float time, float distance, float speed)
	{

		if (mStateInfo.situation == eSituation::Hit)
		{
			mShakeTime += Time::DeltaTime();
			if (mShakeTime >= time)
			{
				mStateInfo.situation = eSituation::None;
				mStep = eStep::None;
				mAttackCool = true;
				mCheak = false;
				mTime = 0.0f;
				mShakeTime = 0.0f;
				//mTransform->SetPosition(mFixPos);
			}

			if (mStep == eStep::None)
			{
				if (mTransform != nullptr)
				{
					mShakePos = mTransform->GetPosition();
					mFixPos = mShakePos;
					mStep = eStep::Step_1;
				}
			}

			else if (mStep == eStep::Step_1)
			{	

				mShakePos = mTransform->GetPosition();

				if (mFixPos.x - distance < mShakePos.x && mShakePos.x < mFixPos.x + distance)
				{
					// ���ʰ� ���������� �����ư��� �̵�
					if (mShakePos.x > mFixPos.x)
						mShakePos.x -= speed * Time::DeltaTime();
					else
						mShakePos.x += speed * Time::DeltaTime();
				}

				mTransform->SetPosition(mShakePos);
			}


		



		}
	}

	void Monster::boss_hit(float time, float distance, float speed)
	{	

		mShakeTime += Time::DeltaTime();
		if (mShakeTime >= time)
		{
			mShakeTime = 0.0f;
			mBossHit = false;
			mOnceCheak = false;
			mTransform->SetPosition(mFixPos);
		}

		if (!mOnceCheak)
		{
			if (mTransform != nullptr)
			{
				mShakePos = mTransform->GetPosition();
				mFixPos = mShakePos;
				mOnceCheak = true;
			}
		}

		else
		{
			mShakePos = mTransform->GetPosition();

			if (mFixPos.x - distance < mShakePos.x && mShakePos.x < mFixPos.x + distance)
			{
				// ���ʰ� ���������� �����ư��� �̵�
				if (mShakePos.x > mFixPos.x)
					mShakePos.x -= speed * Time::DeltaTime();
				else
					mShakePos.x += speed * Time::DeltaTime();
			}

			mTransform->SetPosition(mShakePos);
		}		

	}






}
