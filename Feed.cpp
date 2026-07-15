#include "Feed.h"
#include"Engine/Model.h"

Feed::Feed(GameObject* parent)
	:GameObject(parent,"Feed"), hModel(-1)
{
	transform_.position_.y = 0.1f;
}


void Feed::Initialize()
{
	hModel = Model::Load("Feed.fbx");
}

void Feed::Update()
{
	transform_.position_.y = 0.5f;
}

void Feed::Draw()
{
	Model::SetTransform(hModel, transform_);
	Model::Draw(hModel);
}

void Feed::Release()
{
}
