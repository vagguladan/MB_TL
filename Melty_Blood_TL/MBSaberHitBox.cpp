#include "MBSaberHitBox.h"
#include "MBTransform.h"
#include "MBSaber.h"
#include "MBCollider.h"

#include "MBCollisionManager.h"



namespace MB
{
	SaberHitBox::SaberHitBox()
	{
	}
	SaberHitBox::~SaberHitBox()
	{
	}
	void SaberHitBox::Initialize()
	{
		GetComponent<Collider>()->SetLineColor(RGB(0, 0, 255));
	}
	void SaberHitBox::Update()
	{
		GameObject::Update();

		Saber* saber = dynamic_cast<Saber*>(GetOwner());

		if (saber != nullptr)
		{
			math::Vector2 size = GetOwner()->GetComponent<Collider>()->GetSize();

			

		}
	}
	void SaberHitBox::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}
	void SaberHitBox::MakeAnimation()
	{
	}
	void SaberHitBox::OnCollisionEnter(Collider* _other)
	{
	}
	void SaberHitBox::OnCollisionStay(Collider* _other)
	{
	}
	void SaberHitBox::OnCollisionExit(Collider* _other)
	{
	}
}