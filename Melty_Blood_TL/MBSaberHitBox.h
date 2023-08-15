#pragma once
#include "MBBaseHitbox.h"

namespace MB
{
	class SaberHitBox : public HitBox
	{
	public:
		SaberHitBox();
		virtual ~SaberHitBox();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
		virtual void MakeAnimation() override;

		virtual void OnCollisionEnter(class Collider* _other) override;
		virtual void OnCollisionStay(class Collider* _other) override;
		virtual void OnCollisionExit(class Collider* _other) override;

		__forceinline std::set<GameObject*>* GetAttackList() { return &attackList; }

	private:
		std::set <GameObject*> attackList;
		bool mbCombo;						
	};
}