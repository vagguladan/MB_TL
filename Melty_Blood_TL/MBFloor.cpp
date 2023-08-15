#include "MBFloor.h"
#include "MBSaber.h"
#include "MBCollider.h"
#include "MBRigidBody.h"
#include "MBTransform.h"
#include "MBPlayer.h"

namespace MB
{
	Floor::Floor()
	{
	}
	Floor::~Floor()
	{
	}
	void Floor::Initialize()
	{
	}
	void Floor::Update()
	{
		GameObject::Update();
	}
	void Floor::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Floor::OnCollisionEnter(Collider* other)
	{
		Saber* saber = dynamic_cast<Saber*>(other->GetOwner());
		Player* player = dynamic_cast<Player*>(other->GetOwner());

		Transform* tr = nullptr;
		Rigidbody* rb = nullptr;

		if (player != nullptr)
		{
			Transform* tr = player->GetComponent<Transform>();
			Rigidbody* rb = player->GetComponent<Rigidbody>();

			float len = fabs(other->GetPosition().y - this->GetComponent<Collider>()->GetPosition().y);
			float scale = fabs(other->GetSize().y / 2.0f + this->GetComponent<Collider>()->GetSize().y / 2.0f);

			if (len < scale)
			{
				Vector2 playerPos = tr->GetPosition();
				playerPos.y -= (scale - len) - 1.0f;
				tr->SetPosition(playerPos);
			}

			rb->SetGround(true);
		}

		if (saber != nullptr)
		{
			Transform* tr = saber->GetComponent<Transform>();
			Rigidbody* rb = saber->GetComponent<Rigidbody>();

			float len = fabs(other->GetPosition().y - this->GetComponent<Collider>()->GetPosition().y);
			float scale = fabs(other->GetSize().y / 2.0f + this->GetComponent<Collider>()->GetSize().y / 2.0f);

			if (len < scale)
			{
				Vector2 playerPos = tr->GetPosition();
				playerPos.y -= (scale - len) - 1.0f;
				tr->SetPosition(playerPos);
			}

			rb->SetGround(true);
		}
	}
	void Floor::OnCollisionStay(Collider* other)
	{
	}
	void Floor::OnCollisionExit(Collider* other)
	{

	}
}