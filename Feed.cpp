#include "Feed.h"
#include"Engine/Model.h"
#include"Engine/Collider.h"

Feed::Feed(GameObject* parent)
	:GameObject(parent,"Feed"), hModel(-1),score(1)
{
}

void Feed::Initialize()
{
	hModel = Model::Load("Feed.fbx");

	SphereCollider* col = new SphereCollider(XMFLOAT3(0, 0, 0), 0.2f);
	AddCollider(col);
}

void Feed::Update()
{
}

void Feed::Draw()
{
	Model::SetTransform(hModel, transform_);
	Model::Draw(hModel);
}

void Feed::Release()
{
}

void Feed::OnCollision(GameObject* pTarget)
{
	if (pTarget->GetObjectName() == "Player")
	{
		KillMe();
	}
}
