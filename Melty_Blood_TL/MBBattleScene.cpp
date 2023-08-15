#include "MBBattleScene.h"
#include "MBSaber.h"
#include "MBSpriteRender.h"
#include "MBObject.h"
#include "MBInput.h"
#include "MBTexture.h"
#include "MBTransform.h"
#include "MBResources.h"
#include "MBCamera.h"
#include "MBAnimator.h"
#include "MBBackGround.h"
#include "MBFloor.h"
#include "MBRigidBody.h"
#include "MBCollider.h"
#include "MBCollisionManager.h"
#include "MBGameObject.h"
#include "MBPlayer.h"


namespace MB
{
	BattleScene1::BattleScene1()
	{
	}
	BattleScene1::~BattleScene1()
	{
	}
	void BattleScene1::Initialize()
	{
		//배경화면
		Texture* BGimage = Resources::Load<Texture>(L"BattleBackGroundImgae"
			, L"..\\Resources\\Image\\BackGround\\Lessons_CS_Screenshot_01.png");

		BackGround* bg = object::Instantiate<BackGround>(eLayerType::BackGround);
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();
		bgsr->SetImage(BGimage);
		bgsr->SetScale(Vector2(2.0f, 1.8f));
		bgsr->SetAffectCamera(false);
		bg->GetComponent<Transform>()->SetPosition(Vector2(640.0f, 360.0f));


		//플레이어블.

		Saber* saber = object::Instantiate<Saber>(eLayerType::Player);
		Transform* tr2 = saber->GetComponent<Transform>();
		tr2->SetPosition(Vector2(640.0f, 360.0f));
		saber->GetComponent<Animator>()->SetAffectedCamera(true);


		Floor* floor = object::Instantiate<Floor>(eLayerType::Floor);
		Collider* col = floor->AddComponent<Collider>();
		col->SetSize(Vector2(2000.0f, 100.0f));
		tr2 = floor->GetComponent<Transform>();

		tr2->SetPosition(Vector2(640.0f, 700.0f));

		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Floor, true);
		Camera::SetTarget(saber);
	}
	void BattleScene1::Update()
	{
		if (Input::GetKeyUp(eKeyCode::N))
		{
			Camera::SetTarget(nullptr);
			Camera::Initialize();
			SceneManager::LoadScene(L"TitleScene");
		}

		Scene::Update();
	}
	void BattleScene1::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
}