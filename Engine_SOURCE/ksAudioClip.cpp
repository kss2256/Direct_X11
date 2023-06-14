#include "ksAudioClip.h"
#include "ksTransform.h"

namespace ks
{

	AudioClip::AudioClip()
		: Resource(eResourceType::AudioClip)
		, mSound(nullptr)
		, mChannel(nullptr)
		, mMinDistance(1.0f)
		, mMaxDistance(1000.0f)
		, mbLoop(false)
	{
	}

	AudioClip::~AudioClip()
	{
		//shader_Ptr ����ϴϱ� ������ ���ص� �Ǵµ�
		//mSound->release();
		//mSound = nullptr;
		
	}

	HRESULT AudioClip::Load(const std::wstring& path)
	{
		std::filesystem::path parentPath = std::filesystem::current_path().parent_path();
		std::wstring fullPath = parentPath.wstring() + L"\\Resources\\" + path;

		std::string cPath(path.begin(), path.end());
		if (!Fmod::CreateSound(cPath, &mSound))
			return S_FALSE;

		mSound->set3DMinMaxDistance(mMinDistance, mMaxDistance);

		return S_OK;
	}

	void AudioClip::Play()
	{
		if (mbLoop)
			mSound->setMode(FMOD_LOOP_NORMAL);
		else
			mSound->setMode(FMOD_LOOP_OFF);

		Fmod::SoundPlay(mSound, &mChannel);
		
	}

	void AudioClip::Play(float volume)
	{
		if (mbLoop)
			mSound->setMode(FMOD_LOOP_NORMAL);
		else
			mSound->setMode(FMOD_LOOP_OFF);


		Fmod::SoundPlay(mSound, &mChannel);

		mChannel->setVolume(volume);


	}

	void AudioClip::Stop()
	{
		mChannel->stop();
	}

	void AudioClip::Set3DAttributes(const Vector3 pos, const Vector3 vel)
	{
		FMOD_VECTOR fmodPos(pos.x, pos.y, pos.z);
		FMOD_VECTOR fmodVel(vel.x, vel.y, vel.z);

		mChannel->set3DAttributes(&fmodPos, &fmodVel);
	}

}