#include "MBPlayer.h"
#include "MBTransform.h"
#include "MBTime.h"
#include "MBInput.h"
#include "MBResources.h"
#include "MBAnimator.h"
#include "MBRigidBody.h"
#include "MBCollider.h"
#include "MBObject.h"

namespace MB
{
	Player::Player() :
		_mCurState(eState::IDLE)
		, _mPrvState(eState::NONE)
		, _mAnimator(nullptr)
		, _mRigidbody(nullptr)
		, _mCollider(nullptr)
		, _mDir(eDir::Right)
		, _mPrvDir(eDir::None)
		, _mCurAttState(eAttState::NONE)
		, _mPrvAttState(eAttState::NONE)
		, _mAttTime(0.0f)
		, _mAttCount(0)
		, _mAttDelay(0.4f)
		, _mImgIdx(0)
	{
	}
	Player::~Player()
	{
	}

	void Player::Initialize()
	{
		_mAnimator = AddComponent<Animator>();
		_mRigidbody = AddComponent<Rigidbody>();
		_mCollider = AddComponent<Collider>();

		_mCollider->SetSize(Vector2(-200.0f, 400.0f));
		_mCollider->SetOffset(Vector2(0.0f, 185.0f));

		_mAnimator->SetScale(Vector2(1.0f, 1.0f));
		//_mAnimator->SetAffectedCamera(true);

		InitAnimation();
		_mAnimator->PlayAnimation(L"Idle_right", true);
		_mCurState = eState::IDLE;
	}

	void Player::InitAnimation()
	{

		Animator* at = GetComponent<Animator>();

		Texture* Idle = Resources::Load<Texture>(L"Idle", L"..\\Resources\\Image\\Test\\image\\Idle.bmp");
		Texture* run = Resources::Load<Texture>(L"run", L"..\\Resources\\Image\\Test\\image\\penitent_run.bmp");
		Texture* stoprun = Resources::Load<Texture>(L"stop_run_right", L"..\\Resources\\Image\\Test\\image\\toprun.bmp");
		Texture* crouch = Resources::Load<Texture>(L"crouch", L"..\\Resources\\Image\\Test\\image\\penitent_crouch.bmp");
		Texture* crouchup = Resources::Load<Texture>(L"crouchup", L"..\\Resources\\Image\\Test\\image\\penitent_crouchup.bmp");
		Texture* crouch_attack = Resources::Load<Texture>(L"crouch_attack", L"..\\Resources\\Image\\Test\\image\\crouch_attack.bmp");
		Texture* parry = Resources::Load<Texture>(L"parry", L"..\\Resources\\image\\parry.bmp");
		Texture* attack = Resources::Load<Texture>(L"attack", L"..\\Resources\\image\\attack_combo1.bmp");
		Texture* dodge = Resources::Load<Texture>(L"dodge", L"..\\Resources\\image\\dodge.bmp");
		Texture* jump = Resources::Load<Texture>(L"jump", L"..\\Resources\\Image\\image\\Test\\jump.bmp");
		Texture* jump_attack = Resources::Load<Texture>(L"jump_attack", L"..\\Resources\\Image\\image\\Test\\jumpattack.bmp");

		at->CreateAnimationFolder(L"Test", L"..\\Resources\\Image\\Test\\image\\Standing");

		_mAnimator->CreateAnimation(L"Idle_right", Idle, Vector2(0.0f, 0.0f), Vector2(80.0f, 80.0f), 13, Vector2(-30.0f, 175.0f), 0.1f);
		_mAnimator->CreateAnimation(L"Idle_left", Idle, Vector2(0.0f, 80.0f), Vector2(80.0f, 80.0f), 13, Vector2(30.0f, 175.0f), 0.1f);

		_mAnimator->CreateAnimation(L"Run_right", run, Vector2(0.0f, 0.0f), Vector2(80.0f, 80.0f), 14, Vector2(-40.0f, 175.0f), 0.05f);
		_mAnimator->CreateAnimation(L"Run_left", run, Vector2(0.0f, 80.0f), Vector2(80.0f, 80.0f), 14, Vector2(40.0f, 175.0f), 0.055f);

		_mAnimator->CreateAnimation(L"Stop_run_right", stoprun, Vector2(0.0f, 0.0f), Vector2(120.0f, 80.0f), 7, Vector2(0.0f, 175.0f), 0.04f);
		_mAnimator->CreateAnimation(L"Stop_run_left", stoprun, Vector2(0.0f, 80.0f), Vector2(120.0f, 80.0f), 7, Vector2(0.0f, 175.0f), 0.04f);

		_mAnimator->CreateAnimation(L"Crouch_down_right", crouch, Vector2(0.0f, 0.0f), Vector2(90.0f, 80.0f), 7, Vector2(-40.0f, 175.0f), 0.07f);
		_mAnimator->CreateAnimation(L"Crouch_down_left", crouch, Vector2(0.0f, 80.0f), Vector2(90.0f, 80.0f), 7, Vector2(40.0f, 175.0f), 0.07f);

		_mAnimator->CreateAnimation(L"Crouch_Up_right", crouchup, Vector2(0.0f, 0.0f), Vector2(81.0f, 80.0f), 5, Vector2(-40.0f, 175.0f), 0.07f);
		_mAnimator->CreateAnimation(L"Crouch_Up_left", crouchup, Vector2(0.0f, 80.0f), Vector2(81.0f, 80.0f), 5, Vector2(40.0f, 175.0f), 0.07f);

		_mAnimator->CreateAnimation(L"Crouch_attack_right", crouch_attack, Vector2(0.0f, 0.0f), Vector2(150.0f, 90.0f), 13, Vector2(27.0f, 173.0f), 0.05f);
		_mAnimator->CreateAnimation(L"Crouch_attack_left", crouch_attack, Vector2(0.0f, 90.0f), Vector2(150.0f, 90.0f), 13, Vector2(-27.0f, 173.0f), 0.05f);

		_mAnimator->CreateAnimation(L"Parry_right", parry, Vector2(0.0f, 0.0f), Vector2(90.0f, 80.0f), 10, Vector2(-30.0f, 175.0f), 0.06f);
		_mAnimator->CreateAnimation(L"Parry_left", parry, Vector2(0.0f, 80.0f), Vector2(90.0f, 80.0f), 10, Vector2(30.0f, 175.0f), 0.06f);

		_mAnimator->CreateAnimation(L"Attack1_right", attack, Vector2(0.0f, 0.0f), Vector2(200.0f, 80.0f), 8, Vector2(0.0f, 175.0f), 0.05f);
		_mAnimator->CreateAnimation(L"Attack1_left", attack, Vector2(0.0f, 80.0f), Vector2(200.0f, 80.0f), 8, Vector2(0.0f, 175.0f), 0.05f);

		_mAnimator->CreateAnimation(L"Dodge_right", dodge, Vector2(0.0f, 0.0f), Vector2(100.0f, 80.0f), 13, Vector2(-30.0f, 175.0f), 0.07f);
		_mAnimator->CreateAnimation(L"Dodge_left", dodge, Vector2(0.0f, 80.0f), Vector2(100.0f, 80.0f), 13, Vector2(30.0f, 175.0f), 0.07f);

		_mAnimator->CreateAnimation(L"Jump_right", jump, Vector2(0.0f, 00.0f), Vector2(90.0f, 90.0f), 4, Vector2(-20.0f, 175.0f), 0.08f);
		_mAnimator->CreateAnimation(L"Jump_left", jump, Vector2(0.0f, 90.0f), Vector2(90.0f, 90.0f), 4, Vector2(20.0f, 175.0f), 0.08f);

		_mAnimator->CreateAnimation(L"Run_Jump_right", jump, Vector2(0.0f, 180.0f), Vector2(90.0f, 90.0f), 8, Vector2(0.0f, 175.0f), 0.1f);
		_mAnimator->CreateAnimation(L"Run_Jump_left", jump, Vector2(0.0f, 360.0f), Vector2(90.0f, 90.0f), 8, Vector2(0.0f, 175.0f), 0.1f);

		_mAnimator->CreateAnimation(L"Run_Fall_right", jump, Vector2(720.0f, 180.0f), Vector2(90.0f, 90.0f), 4, Vector2(-20.0f, 175.0f), 0.1f);
		_mAnimator->CreateAnimation(L"Run_Fall_left", jump, Vector2(720.0f, 360.0f), Vector2(90.0f, 90.0f), 4, Vector2(20.0f, 175.0f), 0.1f);

		_mAnimator->CreateAnimation(L"Jumploop_right", jump, Vector2(450.0f, 0.0f), Vector2(90.0f, 90.0f), 3, Vector2(-20.0f, 175.0f), 0.08f);
		_mAnimator->CreateAnimation(L"Jumploop_left", jump, Vector2(450.0f, 90.0f), Vector2(90.0f, 90.0f), 3, Vector2(20.0f, 175.0f), 0.08f);

		_mAnimator->CreateAnimation(L"Land_right", jump, Vector2(720.0f, 00.0f), Vector2(90.0f, 90.0f), 3, Vector2(-30.0f, 165.0f), 0.06f);
		_mAnimator->CreateAnimation(L"Land_left", jump, Vector2(720.0f, 90.0f), Vector2(90.0f, 90.0f), 3, Vector2(30.0f, 165.0f), 0.06f);

		_mAnimator->CreateAnimation(L"Jump_Attack_right", jump_attack, Vector2(0.0f, 0.0f), Vector2(155.0f, 100.0f), 5, Vector2(5.0f, 165.0f), 0.065f);
		_mAnimator->CreateAnimation(L"Jump_Attack_left", jump_attack, Vector2(0.0f, 100.0f), Vector2(155.0f, 100.0f), 5, Vector2(-5.0f, 165.0f), 0.065f);

		_mAnimator->CreateAnimation(L"Jump_Attack2_right", jump_attack, Vector2(0.0f, 200.0f), Vector2(155.0f, 100.0f), 5, Vector2(5.0f, 165.0f), 0.065f);
		_mAnimator->CreateAnimation(L"Jump_Attack2_left", jump_attack, Vector2(0.0f, 300.0f), Vector2(155.0f, 100.0f), 5, Vector2(-5.0f, 165.0f), 0.065f);
	}

	void Player::Update()
	{
		GameObject::Update();

		_mPrvDir = _mDir;
		_mPrvState = _mCurState;
		_mPrvAttState = _mCurAttState;

		if (_mCurAttState == eAttState::NONE)
			_mAttTime = 0.0f;
		else
			_mAttTime += Time::DeltaTime();

		UpdateState();
		UpdateAnimation();
	}

	void Player::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}


	void Player::Idle()
	{
		Vector2 velocity = _mRigidbody->GetVelocity();

		if (Input::GetKeyDown(eKeyCode::Shift))
		{
			_mCurState = eState::DODGE;
		}

		if (Input::GetKeyDown(eKeyCode::K))
		{
			_mCurState = eState::ATTACK;
		}

		if (Input::GetKeyDown(eKeyCode::J))
		{
			_mCurState = eState::PARRY;
		}

		if (Input::GetKeyDown(eKeyCode::Space))
		{
			velocity.y = -1000.0f;
			_mRigidbody->SetVelocity(velocity);
			_mRigidbody->SetGround(false);
			_mCurState = eState::JUMP;
		}

		// 플레이어 이동
		if (Input::GetKey(eKeyCode::A) && !(Input::GetKey(eKeyCode::D)))
		{
			_mCurState = eState::MOVE;
		}
		if (Input::GetKey(eKeyCode::D) && !(Input::GetKey(eKeyCode::A)))
		{
			_mCurState = eState::MOVE;
		}

		if (Input::GetKey(eKeyCode::S))
		{
			_mCurState = eState::CROUCH;
		}

	}

	void Player::Move()
	{
		Vector2 velocity = _mRigidbody->GetVelocity();

		if (Input::GetKey(eKeyCode::A))
		{
			_mDir = eDir::Left;
			velocity.x = -300.0f;
			_mRigidbody->SetVelocity(velocity);
		}

		if (Input::GetKey(eKeyCode::D))
		{
			_mDir = eDir::Right;
			velocity.x = 300.0f;
			_mRigidbody->SetVelocity(velocity);
		}

		if (Input::GetKeyDown(eKeyCode::Shift))
		{
			_mCurState = eState::DODGE;
		}

		if (Input::GetKeyDown(eKeyCode::K))
		{
			_mCurState = eState::ATTACK;
		}

		if (Input::GetKeyDown(eKeyCode::J))
		{
			_mCurState = eState::PARRY;
		}

		if (Input::GetKeyDown(eKeyCode::Space))
		{
			velocity.y = -1000.0f;
			_mRigidbody->SetVelocity(velocity);
			_mRigidbody->SetGround(false);

			_mCurState = eState::RUN_JUMP;
		}

		if (Input::GetKeyUp(eKeyCode::A))
		{
			_mCurState = eState::RUN_OFF;
		}

		if (Input::GetKeyUp(eKeyCode::D))
		{
			_mCurState = eState::RUN_OFF;
		}

		// 좌우 동시입력시 이동제한
		if (Input::GetKey(eKeyCode::A) && Input::GetKeyDown(eKeyCode::D))
		{
			_mCurState = eState::RUN_OFF;
		}
		else if (Input::GetKey(eKeyCode::D) && Input::GetKeyDown(eKeyCode::A))
		{
			_mCurState = eState::RUN_OFF;
		}
	}

	void Player::Dodge()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		if (!((_mAnimator->IsActiveAnimationComplete())) && (_mDir == eDir::Right))
			pos.x += 450.0f * Time::DeltaTime();
		else if (!((_mAnimator->IsActiveAnimationComplete())) && (_mDir == eDir::Left))
			pos.x -= 450.0f * Time::DeltaTime();

		tr->SetPosition(pos);

		if (_mAnimator->IsActiveAnimationComplete())
			_mCurState = eState::IDLE;
	}

	void Player::Attack()
	{
		if (_mAnimator->GetActiveAnime()->GetIndex() == 4)
		{
			Transform* tr = GetComponent<Transform>();
		}
		if (_mAnimator->IsActiveAnimationComplete())
		{
			_mCurState = eState::IDLE;
		}
	}

	void Player::Crouch()
	{
		if (Input::GetKeyDown(eKeyCode::Shift))
		{
			_mCurState = eState::DODGE;
		}

		if (Input::GetKeyDown(eKeyCode::K))
		{
			_mCurState = eState::CROUCH_ATT;
		}

		// 앉은상태에서 방향 전환
		if (Input::GetKeyDown(eKeyCode::A) && (_mDir == eDir::Right))
		{
			if (_mAnimator->IsActiveAnimationComplete())
			{
				_mDir = eDir::Left;
			}
		}
		else if (Input::GetKeyDown(eKeyCode::D) && (_mDir == eDir::Left))
		{
			if (_mAnimator->IsActiveAnimationComplete())
			{
				_mDir = eDir::Right;
			}
		}

		if (Input::GetKeyUp(eKeyCode::S))
		{
			_mCurState = eState::CROUCH_UP;
		}
	}
	void Player::Crouch_Att()
	{
		if (Input::GetKeyUp(eKeyCode::S))
		{
			_mCurState = eState::CROUCH_UP;
		}

		if (_mAnimator->IsActiveAnimationComplete())
			_mCurState = eState::CROUCH;
	}
	void Player::Crouch_Up()
	{
		if (_mAnimator->IsActiveAnimationComplete())
			_mCurState = eState::IDLE;
	}

	void Player::Parry()
	{
		if (_mAnimator->IsActiveAnimationComplete())
			_mCurState = eState::IDLE;
	}

	void Player::Run_Off()
	{

		if (Input::GetKeyDown(eKeyCode::K))
		{
			_mCurState = eState::ATTACK;
		}
		// 방향 바로 전환 가능
		if (Input::GetKeyUp(eKeyCode::A))
		{
			_mCurState = eState::MOVE;
		}
		else if (Input::GetKeyUp(eKeyCode::D))
		{
			_mCurState = eState::MOVE;
		}
		if (_mAnimator->IsActiveAnimationComplete())
			_mCurState = eState::IDLE;
	}

	void Player::Jump_Att()
	{
		if (_mRigidbody->GetGround())
		{
			_mCurState = eState::JUMP_OFF;
		}

		if (_mAttDelay <= _mAttTime)
		{
			_mAttTime = 0;
			_mAttCount = 0;
			_mCurAttState = eAttState::NONE;
		}

		if (_mAttCount == 1)
		{
			_mAttTime = 0;
			_mCurAttState = eAttState::JUMP_FIRST_SLASH;
		}
		else if (_mAttCount == 2)
		{
			_mAttTime = 0;
			_mCurAttState = eAttState::JUMP_SECOND_SLASH;
		}

		if (_mAnimator->IsActiveAnimationComplete())
			_mCurState = eState::FALL;
	}

	void Player::Jump()
	{
		Vector2 velocity = _mRigidbody->GetVelocity();

		_mRigidbody->SetVelocity(velocity);

		if ((!(_mRigidbody->GetGround()) && _mRigidbody->GetVelocity().y >= 0))
		{
			_mCurState = eState::FALL;
		}

		if (_mRigidbody->GetGround())
		{
			_mCurState = eState::JUMP_OFF;
		}

		if (Input::GetKeyDown(eKeyCode::A) && (_mDir == eDir::Right))
		{
			_mImgIdx = _mAnimator->GetActiveAnime()->GetIndex();
			_mDir = eDir::Left;
		}
		else if (Input::GetKeyDown(eKeyCode::D) && (_mDir == eDir::Left))
		{
			_mImgIdx = _mAnimator->GetActiveAnime()->GetIndex();
			_mDir = eDir::Right;
		}

		if (Input::GetKeyDown(eKeyCode::K))
		{
			_mAttCount++;
			if (_mAttCount == 3)
			{
				_mAttCount = 1;
			}
			_mCurState = eState::JUMP_ATT;
		}

	}
	void Player::Jump_Off() // 바로움직일수잇게 나중에 수정해야
	{
		Vector2 velocity = _mRigidbody->GetVelocity();

		_mAttCount = 0;
		_mCurAttState = eAttState::NONE;

		if (Input::GetKeyDown(eKeyCode::Shift))
		{
			_mCurState = eState::DODGE;
		}

		if (Input::GetKeyDown(eKeyCode::K))
		{
			_mCurState = eState::ATTACK;
		}

		if (Input::GetKey(eKeyCode::A) && !(Input::GetKey(eKeyCode::D)))
		{
			_mCurState = eState::MOVE;
		}
		if (Input::GetKey(eKeyCode::D) && !(Input::GetKey(eKeyCode::A)))
		{
			_mCurState = eState::MOVE;
		}

		if (Input::GetKeyDown(eKeyCode::Space))
		{
			velocity.y = -1000.0f;
			_mRigidbody->SetVelocity(velocity);
			_mRigidbody->SetGround(false);
			_mCurState = eState::JUMP;
		}

		if (_mAnimator->IsActiveAnimationComplete())
			_mCurState = eState::IDLE;
	}

	void Player::Run_Jump()
	{
		Vector2 velocity = _mRigidbody->GetVelocity();

		_mRigidbody->SetVelocity(velocity);

		if (Input::GetKey(eKeyCode::A))
		{
			_mImgIdx = _mAnimator->GetActiveAnime()->GetIndex();
			_mDir = eDir::Left;
			velocity.x = -300.0f;
			_mRigidbody->SetVelocity(velocity);
		}

		if (Input::GetKey(eKeyCode::D))
		{
			_mImgIdx = _mAnimator->GetActiveAnime()->GetIndex();
			_mDir = eDir::Right;
			velocity.x = 300.0f;
			_mRigidbody->SetVelocity(velocity);
		}

		if (Input::GetKeyDown(eKeyCode::K))
		{
			_mAttCount++;
			if (_mAttCount == 3)
			{
				_mAttCount = 1;
			}
			_mCurState = eState::JUMP_ATT;
		}

		if ((!(_mRigidbody->GetGround()) && _mRigidbody->GetVelocity().y >= 0))
		{
			_mCurState = eState::FALL;
		}
	}

	void Player::Fall()
	{
		Vector2 velocity = _mRigidbody->GetVelocity();

		if (_mRigidbody->GetGround())
		{
			_mCurState = eState::JUMP_OFF;
		}

		if (Input::GetKeyDown(eKeyCode::A) && (_mDir == eDir::Right))
		{
			_mImgIdx = _mAnimator->GetActiveAnime()->GetIndex();
			_mDir = eDir::Left;
		}
		else if (Input::GetKeyDown(eKeyCode::D) && (_mDir == eDir::Left))
		{
			_mImgIdx = _mAnimator->GetActiveAnime()->GetIndex();
			_mDir = eDir::Right;
		}

		// 낙하 이동
		if (Input::GetKey(eKeyCode::A))
		{
			_mCurState = eState::FALL_MOVE;
		}

		if (Input::GetKey(eKeyCode::D))
		{
			_mCurState = eState::FALL_MOVE;
		}

		if (Input::GetKeyDown(eKeyCode::K))
		{
			_mAttCount++;
			if (_mAttCount == 3)
			{
				_mAttCount = 1;
			}
			_mCurState = eState::JUMP_ATT;
		}
	}
	void Player::Fall_Move()
	{
		Vector2 velocity = _mRigidbody->GetVelocity();

		if (_mRigidbody->GetGround())
		{
			_mCurState = eState::JUMP_OFF;
		}

		if (Input::GetKey(eKeyCode::A))
		{
			_mDir = eDir::Left;
			velocity.x = -300.0f;
			_mRigidbody->SetVelocity(velocity);
		}

		if (Input::GetKey(eKeyCode::D))
		{
			_mDir = eDir::Right;
			velocity.x = 300.0f;
			_mRigidbody->SetVelocity(velocity);
		}

		if (Input::GetKeyUp(eKeyCode::A))
		{
			_mCurState = eState::FALL;
		}

		if (Input::GetKeyUp(eKeyCode::D))
		{
			_mCurState = eState::FALL;
		}

		if (Input::GetKeyDown(eKeyCode::K))
		{
			_mAttCount++;
			if (_mAttCount == 3)
			{
				_mAttCount = 1;
			}
			_mCurState = eState::JUMP_ATT;
		}
	}

	void Player::UpdateState()
	{
		switch (_mCurState)
		{
		case MB::Player::eState::IDLE:
			_mCollider->SetSize(Vector2(50.0f, 140.0f));
			_mCollider->SetOffset(Vector2(0.0f, 185.0f));
			Idle();
			break;
		case MB::Player::eState::MOVE:
			Move();
			break;
		case MB::Player::eState::DODGE:
			_mCollider->SetSize(Vector2(70.0f, 70.0f));
			_mCollider->SetOffset(Vector2(0.0f, 220.0f));
			Dodge();
			break;
		case MB::Player::eState::ATTACK:
			Attack();
			break;
		case MB::Player::eState::CROUCH:
			Crouch();
			break;
		case MB::Player::eState::CROUCH_ATT:
			Crouch_Att();
			break;
		case MB::Player::eState::CROUCH_UP:
			Crouch_Up();
			break;
		case MB::Player::eState::PARRY:
			Parry();
			break;
		case MB::Player::eState::RUN_OFF:
			Run_Off();
			break;
		case MB::Player::eState::JUMP:
			Jump();
			break;
		case MB::Player::eState::RUN_JUMP:
			Run_Jump();
			break;
		case MB::Player::eState::JUMP_OFF:
			Jump_Off();
			break;
		case MB::Player::eState::JUMP_ATT:
			Jump_Att();
			break;
		case MB::Player::eState::FALL:
			Fall();
			break;
		case MB::Player::eState::FALL_MOVE:
			Fall_Move();
			break;
		}
	}


	void Player::UpdateAnimation()
	{
		if (_mPrvState == _mCurState && _mPrvAttState == _mCurAttState && _mPrvDir == _mDir)
		{
			return;
		}

		switch (_mCurState)
		{
		case MB::Player::eState::IDLE:
			if (_mAnimator->IsActiveAnimationComplete() && (_mDir == eDir::Right))
				_mAnimator->PlayAnimation(L"Test", true);
			else if (_mAnimator->IsActiveAnimationComplete() && (_mDir == eDir::Left))
				_mAnimator->PlayAnimation(L"Test", true);
			break;
		case MB::Player::eState::MOVE:
			if (_mDir == eDir::Right)
				_mAnimator->PlayAnimation(L"Run_right", true);
			else if ((_mDir == eDir::Left))
				_mAnimator->PlayAnimation(L"Run_left", true);
			break;
	
		case MB::Player::eState::ATTACK:
			if (_mDir == eDir::Right)
				_mAnimator->PlayAnimation(L"Attack1_right", false);
			else if ((_mDir == eDir::Left))
				_mAnimator->PlayAnimation(L"Attack1_left", false);
			break;
		case MB::Player::eState::CROUCH:
			if (_mDir == eDir::Right)
				_mAnimator->PlayAnimation(L"Crouch_down_right", false);
			else if (_mDir == eDir::Left)
				_mAnimator->PlayAnimation(L"Crouch_down_left", false);

			// 앉은상태에서 방향전환
			if (_mPrvDir != _mDir)
			{
				_mAnimator->GetActiveAnime()->SetIndex(6);
			}
			// 공격후 앉은자세
			if (_mPrvState == eState::CROUCH_ATT)
			{
				_mAnimator->GetActiveAnime()->SetIndex(6);
			}
			break;
		case MB::Player::eState::CROUCH_ATT:
			if ((_mDir == eDir::Right))
				_mAnimator->PlayAnimation(L"Crouch_attack_right", false);
			else if (_mDir == eDir::Left)
				_mAnimator->PlayAnimation(L"Crouch_attack_left", false);
			break;
		case MB::Player::eState::CROUCH_UP:
			if ((_mDir == eDir::Right))
				_mAnimator->PlayAnimation(L"Crouch_Up_right", false);
			else if (_mDir == eDir::Left)
				_mAnimator->PlayAnimation(L"Crouch_Up_left", false);
			break;
		case MB::Player::eState::PARRY:
			if (_mDir == eDir::Right)
				_mAnimator->PlayAnimation(L"Parry_right", false);
			else if ((_mDir == eDir::Left))
				_mAnimator->PlayAnimation(L"Parry_left", false);
			break;
		case MB::Player::eState::RUN_OFF:
			if (_mDir == eDir::Right)
				_mAnimator->PlayAnimation(L"Stop_run_right", false);
			else if ((_mDir == eDir::Left))
				_mAnimator->PlayAnimation(L"Stop_run_left", false);
			break;
		case MB::Player::eState::JUMP:
			if (_mPrvDir != _mDir && _mPrvState == _mCurState)
			{
				if (Input::GetKeyDown(eKeyCode::A) && (_mDir == eDir::Right))
				{
					_mAnimator->PlayAnimation(L"Jump_left", false);
					_mAnimator->GetActiveAnime()->SetIndex(_mImgIdx);
				}
				else if (Input::GetKeyDown(eKeyCode::D) && (_mDir == eDir::Left))
				{
					_mAnimator->PlayAnimation(L"Jump_right", false);
					_mAnimator->GetActiveAnime()->SetIndex(_mImgIdx);
				}
			}
			if ((_mDir == eDir::Right))
				_mAnimator->PlayAnimation(L"Jump_right", false);
			else if (_mDir == eDir::Left)
				_mAnimator->PlayAnimation(L"Jump_left", false);
			break;
		case MB::Player::eState::RUN_JUMP:
			if (_mPrvDir != _mDir && _mPrvState == _mCurState)
			{
				if (Input::GetKeyDown(eKeyCode::A) && (_mDir == eDir::Right))
				{
					_mAnimator->PlayAnimation(L"Run_Jump_left", false);
					_mAnimator->GetActiveAnime()->SetIndex(_mImgIdx);
				}
				else if (Input::GetKeyDown(eKeyCode::D) && (_mDir == eDir::Left))
				{
					_mAnimator->PlayAnimation(L"Run_Jump_right", false);
					_mAnimator->GetActiveAnime()->SetIndex(_mImgIdx);
				}
			}
			if ((_mDir == eDir::Right))
				_mAnimator->PlayAnimation(L"Run_Jump_right", false);
			else if (_mDir == eDir::Left)
				_mAnimator->PlayAnimation(L"Run_Jump_left", false);
			break;
		case MB::Player::eState::JUMP_OFF:
			if ((_mDir == eDir::Right))
				_mAnimator->PlayAnimation(L"Land_right", false);
			else if (_mDir == eDir::Left)
				_mAnimator->PlayAnimation(L"Land_left", false);
			break;
		case MB::Player::eState::JUMP_ATT:
			//_mImgIdx =_mAnimator->GetActiveAnime()->GetIndex();
			if (_mAttCount == 1)
			{
				if ((_mDir == eDir::Right))
					_mAnimator->PlayAnimation(L"Jump_Attack_right", false);
				else if (_mDir == eDir::Left)
					_mAnimator->PlayAnimation(L"Jump_Attack_left", false);
			}
			else if (_mAttCount == 2)
			{
				if ((_mDir == eDir::Right))
					_mAnimator->PlayAnimation(L"Jump_Attack2_right", false);
				else if (_mDir == eDir::Left)
					_mAnimator->PlayAnimation(L"Jump_Attack2_left", false);
			}
			break;
		case MB::Player::eState::FALL:
			if (_mPrvDir != _mDir && _mPrvState == _mCurState)
			{
				if (Input::GetKeyDown(eKeyCode::A) && (_mDir == eDir::Right))
				{
					_mAnimator->PlayAnimation(L"Jumploop_left", false);
					_mAnimator->GetActiveAnime()->SetIndex(_mImgIdx);
				}
				else if (Input::GetKeyDown(eKeyCode::D) && (_mDir == eDir::Left))
				{
					_mAnimator->PlayAnimation(L"Jumploop_right", false);
					_mAnimator->GetActiveAnime()->SetIndex(_mImgIdx);
				}
			}
			if ((_mDir == eDir::Right))
				_mAnimator->PlayAnimation(L"Jumploop_right", true);
			else if ((_mDir == eDir::Left))
				_mAnimator->PlayAnimation(L"Jumploop_left", true);
			break;
		case MB::Player::eState::FALL_MOVE:
			if (_mPrvDir != _mDir && _mPrvState == _mCurState)
			{
				if (Input::GetKeyDown(eKeyCode::A) && (_mDir == eDir::Right))
				{
					_mAnimator->PlayAnimation(L"Run_Fall_right", false);
					_mAnimator->GetActiveAnime()->SetIndex(_mImgIdx);
				}
				else if (Input::GetKeyDown(eKeyCode::D) && (_mDir == eDir::Left))
				{
					_mAnimator->PlayAnimation(L"Run_Fall_left", false);
					_mAnimator->GetActiveAnime()->SetIndex(_mImgIdx);
				}
			}
			if ((_mDir == eDir::Right))
				_mAnimator->PlayAnimation(L"Run_Fall_right", true);
			else if ((_mDir == eDir::Left))
				_mAnimator->PlayAnimation(L"Run_Fall_left", true);
			break;
		}
	}


	void Player::OnCollisionEnter(Collider* other)
	{
		// 충돌시 동작
	}

	void Player::OnCollisionStay(Collider* other)
	{
		// 총돌 도중 동작
	}

	void Player::OnCollisionExit(Collider* other)
	{
		// 충돌 빠져나올시 동작
	}
}