#pragma once
#include "MBGameObject.h"

namespace MB
{
	class HitBox : public GameObject
	{
	public:
		HitBox();
		virtual ~HitBox();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void MakeAnimation() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		__forceinline GameObject* GetOwner() { return mOwner; }
		__forceinline void SetOwner(GameObject* _owner) { mOwner = _owner; }

		__forceinline math::Vector2 GetOwnerPos() { return mOwnerPos; }
		__forceinline void SetOwnerPos(math::Vector2 _pos) { mOwnerPos = _pos; }

		__forceinline UINT GetOwnerState() { return mOwnerState; }
		__forceinline void SetOwnerState(UINT _state) { mOwnerState = _state; }

		__forceinline UINT GetOwnerDirection() { return mOwnerDirection; }
		__forceinline void SetOwnerDirection(UINT _direction) { mOwnerDirection = _direction; }

		__forceinline math::Vector2 GetOffset() { return mOffset; }


	private:
		GameObject* mOwner;			// �ش� Ŭ������ ����� �����ϰ��ִ� Ŭ������ �ּ� ����
		math::Vector2 mOwnerPos;	// �������� ��ġ�� ����
		UINT mOwnerState;			// �������� ���� ����
		UINT mOwnerDirection;		// �����ڰ� �ٶ󺸰� �ִ� ���� ����
		math::Vector2 mOffset;		// Collider�� �������� ��ġ �������� �����Ǿ�� �� ��ġ ��

	};
}
