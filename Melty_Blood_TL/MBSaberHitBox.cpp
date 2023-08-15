#include "MBSaberHitBox.h"
#include "MBSaber.h"
#include "MBAnimator.h"
#include "MBTransform.h"
#include "MBCollider.h"
#include "MBCollisionManager.h"
#include "MBObject.h"
#include "MBTime.h"


namespace MB
{
	SaberHitBox::SaberHitBox():
		mSaber(nullptr)
		,mTime(0.f)
	{
	}
	SaberHitBox::~SaberHitBox()
	{
	}
	void SaberHitBox::Initialize()
	{
		mCollider = AddComponent<Collider>();
	}
	void SaberHitBox::Update()
	{
		GameObject::Update();
		mTime += Time::DeltaTime();
		if (mTime > 0.15f)
		{
			Destroy(this);
		}
	}
	void SaberHitBox::SaberHitboxCollider()
	{
		mCollider->SetNotColColor(RGB(255, 50, 50));

	}

	void SaberHitBox::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void SaberHitBox::OnCollisionEnter(Collider* other)
	{
	}
	void SaberHitBox::OnCollisionStay(Collider* other)
	{
	}
	void SaberHitBox::OnCollisionExit(Collider* other)
	{
	}

}