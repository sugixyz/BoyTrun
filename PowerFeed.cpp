#include "PowerFeed.h"
#include"Engine/Model.h"
#include"TestScene.h"

PowerFeed::PowerFeed(GameObject* parent)
	:GameObject(parent, "PowerFeed"), hModel(-1),score(5)
{
}

void PowerFeed::Initialize()
{
	hModel = Model::Load("Feed.fbx");
	transform_.scale_ = { 3,3,3 };

	SphereCollider* col = new SphereCollider(XMFLOAT3(0, 0, 0), 0.6f);
	AddCollider(col);
}

void PowerFeed::Update()
{
}

void PowerFeed::Draw()
{
	Model::SetTransform(hModel, transform_);
	Model::Draw(hModel);
}

void PowerFeed::Release()
{
}

void PowerFeed::OnCollision(GameObject* pTarget)
{
	if (pTarget->GetObjectName() == "Player")
	{
		KillMe();
		TestScene* test = dynamic_cast<TestScene*>(FindObject("TestScene"));
		test->AddScore(score);
	}
}
