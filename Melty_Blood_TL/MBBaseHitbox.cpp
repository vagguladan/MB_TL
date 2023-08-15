#include "MBBaseHitbox.h"

namespace MB
{
	HitBox::HitBox()
		: mOwner(nullptr)
		, mOwnerPos(math::Vector2::Zero)
		, mOwnerState(0)
		, mOwnerDirection(0)
		, mOffset(math::Vector2::Zero)
	{
	}
	HitBox::~HitBox()
	{
	}
	void HitBox::Initialize()
	{
	}
	void HitBox::Update()
	{
	}
	void HitBox::Render(HDC hdc)
	{
	}
	void HitBox::MakeAnimation()
	{
	}
	void HitBox::OnCollisionEnter(Collider* other)
	{
	}
	void HitBox::OnCollisionStay(Collider* other)
	{
	}
	void HitBox::OnCollisionExit(Collider* other)
	{
	}
}