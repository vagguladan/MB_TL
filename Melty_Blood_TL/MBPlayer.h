#pragma once
#include "MBGameObject.h"
#include "MBPlayer.h"

namespace MB
{
	class Animator;
	class Rigidbody;
	class Collider;

	class Player : public GameObject
	{
	public:
		enum class eState
		{
			IDLE,
			MOVE,
			DODGE,
			ATTACK,
			CROUCH,
			CROUCH_ATT,
			CROUCH_UP,
			RUN_OFF,
			PARRY,
			JUMP,
			RUN_JUMP,
			JUMP_OFF,
			JUMP_ATT,
			FALL,
			FALL_MOVE,
			NONE

		};

		enum class eAttState
		{
			FIRST_SLASH,
			SECOND_SLASH,
			THIRD_SLASH,
			JUMP_FIRST_SLASH,
			JUMP_SECOND_SLASH,
			CROUCH_SLASH,
			NONE,
		};

		Player();
		virtual ~Player();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void InitAnimation();
		void UpdateAnimation();
		void UpdateState();

		void Idle();
		void Move();
		void Dodge();
		void Attack();
		void Crouch();
		void Crouch_Att();
		void Crouch_Up();
		void Run_Off();
		void Run_Jump();
		void Parry();
		void Jump();
		void Jump_Off();
		void Jump_Att();
		void Fall();
		void Fall_Move();

		void SetState(eState state) { _mCurState = state; }
		eState GetState() { return _mCurState; }
		eDir GetDir() { return _mDir; }

	private:
		Animator* _mAnimator;
		Rigidbody* _mRigidbody;
		Collider* _mCollider;

		eState _mCurState;
		eState _mPrvState;
		eAttState _mCurAttState;
		eAttState _mPrvAttState;
		eDir _mDir;
		eDir _mPrvDir;
		float _mAttTime;
		float _mAttDelay;

		UINT _mAttCount;
		UINT _mImgIdx;
	};
}