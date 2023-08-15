#pragma once
#include "MBGameObject.h"
#include "MBSaber.h"
#include "MBPlayer.h"

namespace MB
{
	class Animator;
	class Collider;

	class SaberHitBox : public GameObject
	{
	public:
		SaberHitBox();
		virtual ~SaberHitBox();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		__forceinline void SetPlayer(Saber* saber)
		{
		
			mSaber = saber;
		}

		__forceinline void SetPlayer(Player* player)
		{

			mPlayer = player;
		}

		__forceinline GameObject* GetOwner() { return mSaber; }
		void SaberHitboxCollider();

	private:
		Animator* mAnimator;
		Collider* mCollider;
		Saber* mSaber;
		Player* mPlayer;

		float mTime;
	};
}