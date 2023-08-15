#include "MBSaber.h"
#include "MBTransform.h"
#include "MBTime.h"
#include "MBResources.h"
#include "MBAnimator.h"
#include "MBRigidBody.h"
#include "MBCollider.h"
#include "MBObject.h"
#include "MBInput.h"
#include "MBSaberHitBox.h"

namespace MB
{
	Saber::Saber()
		: mCurState(eState::Idle)
		, mPrvState(eState::Idle)
		, mAnimator(nullptr)
		, mRigidbody(nullptr)
		, mCollider(nullptr)
		, mPrvDir(eDir::None)
		, mAttTime(0.0f)
		, mAttCount(0)
		, mAttDelay(0.4f)
		, mImgIdx(0)
		, mSaber_Attack(Saber_Attack::None)
	{
	}
	Saber::~Saber()
	{
	}
	void Saber::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		mRigidbody = AddComponent<Rigidbody>();
		mCollider = AddComponent<Collider>();

		mCollider->SetSize(Vector2(-200.0f, 400.0f));
		mCollider->SetOffset(Vector2(0.0f, 25.0f));

		mAnimator->SetScale(Vector2(1.0f, 1.0f));

		InitAnimation();
		mAnimator->PlayAnimation(L"Saber_Idle", true);
		mCurState = eState::Idle;
	}
	void Saber::InitAnimation()
	{
		Animator* at = GetComponent<Animator>();

		at->CreateAnimationFolder(L"Saber_Idle", L"..\\Resources\\Image\\Player\\Saber\\Standing", Vector2(0.0f, -60.0f));
		at->CreateAnimationFolder(L"Saber_AAttack", L"..\\Resources\\Image\\Player\\Saber\\AAttack", Vector2(0.0f, -60.0f));
		at->CreateAnimationFolder(L"Saber_BAttack", L"..\\Resources\\Image\\Player\\Saber\\BAttack", Vector2(0.0f, -60.0f));
		at->CreateAnimationFolder(L"Saber_CAttack", L"..\\Resources\\Image\\Player\\Saber\\CAttack", Vector2(0.0f, -60.0f));
		at->CreateAnimationFolder(L"Saber_JumpAAttack", L"..\\Resources\\Image\\Player\\Saber\\JumpAAttack", Vector2(0.0f, -60.0f));
		at->CreateAnimationFolder(L"Saber_JumpBAttack", L"..\\Resources\\Image\\Player\\Saber\\JumpBAttack", Vector2(0.0f, -60.0f));
		at->CreateAnimationFolder(L"Saber_JumpCAttack", L"..\\Resources\\Image\\Player\\Saber\\JumpCAttack", Vector2(0.0f, -60.0f));
		at->CreateAnimationFolder(L"Saber_BackJump", L"..\\Resources\\Image\\Player\\Saber\\BackJump", Vector2(0.0f, -60.0f));
		at->CreateAnimationFolder(L"Saber_Sit", L"..\\Resources\\Image\\Player\\Saber\\Sit", Vector2(0.0f, -60.0f));
		at->CreateAnimationFolder(L"Saber_SitAAttack", L"..\\Resources\\Image\\Player\\Saber\\SitAAttack", Vector2(0.0f, -60.0f));
		at->CreateAnimationFolder(L"Saber_SitBAttack", L"..\\Resources\\Image\\Player\\Saber\\SitBAttack", Vector2(0.0f, -60.0f));
		at->CreateAnimationFolder(L"Saber_SitCAttack", L"..\\Resources\\Image\\Player\\Saber\\SitCAttack", Vector2(0.0f, -60.0f));
		at->CreateAnimationFolder(L"Saber_StandtoSit", L"..\\Resources\\Image\\Player\\Saber\\StandToSit", Vector2(0.0f, -60.0f));
		at->CreateAnimationFolder(L"Saber_JumpToUp", L"..\\Resources\\Image\\Player\\Saber\\JumpUp", Vector2(0.0f, -60.0f));
		at->CreateAnimationFolder(L"Saber_JumpToDown", L"..\\Resources\\Image\\Player\\Saber\\JumpDown", Vector2(0.0f, -60.0f));
		at->CreateAnimationFolder(L"Saber_FrontMove", L"..\\Resources\\Image\\Player\\Saber\\FrontMove", Vector2(0.0f, -60.0f));
		at->CreateAnimationFolder(L"Saber_BackMove", L"..\\Resources\\Image\\Player\\Saber\\BackMove", Vector2(0.0f, -60.0f));

	}

	void Saber::Update()
	{
		GameObject::Update();


		switch (mState)
		{
		case MB::Saber::eState::Idle:
			Idle();
			break;
		case MB::Saber::eState::Move:
			Move();
			break;
		case MB::Saber::eState::Double_Jump:
			Double_Jump();
			break;
		case MB::Saber::eState::Attack:
			Attack();
			break;
		case MB::Saber::eState::Jump_Attack:
			Jump_Attack();
			break;
		case MB::Saber::eState::JumpToUp:
			JumpToUp();
			break;
		case MB::Saber::eState::JumpToFall:
			JumpToFall();
			break;
		case MB::Saber::eState::Hit:
			Hit();
			break;
		case MB::Saber::eState::End:
			break;
		case MB::Saber::eState::Sit:
			Sit();
			break;
		case MB::Saber::eState::SItAttack:
			SitAttack();
			break;
		case MB::Saber::eState::StandToSit:
			StandToSit();
			break;
		default:
			break;
		}

	}
	void Saber::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}



	void Saber::Idle()
	{
		Animator* animator = GetComponent<Animator>();
		mSaberDownMove = false;

		if (Input::GetKeyDown(eKeyCode::W))
		{
			animator->PlayAnimation(L"Saber_JumpToUp", false);
			Rigidbody* rb = GetComponent<Rigidbody>();
			Vector2 velocity = rb->GetVelocity();
			velocity.y = -500.0f;
			rb->SetVelocity(velocity);
			rb->SetGround(false);

			mState = eState::JumpToUp;
		}

		if (Input::GetKey(eKeyCode::D))
		{
			animator->PlayAnimation(L"Saber_FrontMove", true);
			mState = eState::Move;
		}
		if (Input::GetKey(eKeyCode::S))
		{
			animator->PlayAnimation(L"Saber_Sit", true);
			mState = eState::Sit;
		}
		if (Input::GetKey(eKeyCode::A))
		{
			animator->PlayAnimation(L"Saber_BackMove", true);
			mState = eState::Move;
		}

		if (Input::GetKey(eKeyCode::H))
		{
			Transform* tr = GetComponent<Transform>();
			animator->PlayAnimation(L"Saber_AAttack", false);
			mState = eState::Attack;
		}

		if (Input::GetKey(eKeyCode::J))
		{
			Transform* tr = GetComponent<Transform>();



			animator->PlayAnimation(L"Saber_BAttack", false);
			mState = eState::Attack;
		}
		if (Input::GetKey(eKeyCode::Y))
		{
			Transform* tr = GetComponent<Transform>();


			animator->PlayAnimation(L"Saber_CAttack", false);
			mState = eState::Attack;
		}


	}
	void Saber::Move()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		Animator* animator = GetComponent<Animator>();

		if (Input::GetKeyDown(eKeyCode::W))
		{
			animator->PlayAnimation(L"Saber_JumpToUp", false);
			Rigidbody* rb = GetComponent<Rigidbody>();
			Vector2 velocity = rb->GetVelocity();
			velocity.y = -500.0f;
			rb->SetVelocity(velocity);
			rb->SetGround(false);

			mState = eState::JumpToUp;
		}

		if (Input::GetKey(eKeyCode::A))
		{
			pos.x -= 300.0f * Time::DeltaTime();
			//GetComponent<Rigidbody>()->AddForce(Vector2(-200.0f, 0.0f));
		}
		if (Input::GetKey(eKeyCode::S))
		{
			//if (pos.y < 480.0f)
			//pos.y += 300.0f * Time::DeltaTime();

			GetComponent<Rigidbody>()->AddForce(Vector2(0.0f, 200.0f));
		}
		if (Input::GetKey(eKeyCode::D))
		{
			pos.x += 300.0f * Time::DeltaTime();
			//GetComponent<Rigidbody>()->AddForce(Vector2(200.0f, 0.0f));
		}
		tr->SetPosition(pos);

		if (Input::GetKeyUp(eKeyCode::W)
			|| Input::GetKeyUp(eKeyCode::A)
			|| Input::GetKeyUp(eKeyCode::S)
			|| Input::GetKeyUp(eKeyCode::D))
		{
			Animator* animator = GetComponent<Animator>();
			animator->PlayAnimation(L"Saber_Idle", true);
			mState = eState::Idle;
		}
	}
	void Saber::BackMove()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 velocity = mRigidbody->GetVelocity();
		Vector2 pos = tr->GetPosition();

		if (Input::GetKey(eKeyCode::A))
		{
			pos.x -= 300.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		if (Input::GetKeyDown(eKeyCode::H) || Input::GetKeyDown(eKeyCode::J) || Input::GetKeyDown(eKeyCode::U))
		{
			mCurState = eState::Attack;
		}

		if (Input::GetKeyUp(eKeyCode::A)
		)
		{

			mAnimator->PlayAnimation(L"Saber_Idle", true);
			mState = eState::Idle;
		}
	}
	void Saber::Attack()
	{
		if (mAnimator->GetActiveAnime()->GetIndex() == 4)
		{
			Transform* tr = GetComponent<Transform>();
			SaberHitBox* Saber_Hitbox = object::Instantiate<SaberHitBox>(eLayerType::HitBox, tr->GetPosition());
			Saber_Hitbox->SetPlayer(this);
			Saber_Hitbox->SaberHitboxCollider();
		}
		if (mAnimator->IsActiveAnimationComplete())
		{
			mCurState = eState::None;
		}

	}
	void Saber::Jump_Attack()
	{
	}
	void Saber::Hit()
	{
	}
	void Saber::JumpToUp()
	{
	}
	void Saber::JumpToFall()
	{
	}
	void Saber::Double_Jump()
	{
	}
	void Saber::Sit()
	{
	}
	void Saber::SitAttack()
	{
	}
	void Saber::StandToSit()
	{
	}

	void Saber::OnCollisionEnter(Collider* other)
	{
	}
	void Saber::OnCollisionStay(Collider* other)
	{
	}
	void Saber::OnCollisionExit(Collider* other)
	{
	}
}