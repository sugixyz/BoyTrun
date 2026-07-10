#include "Ground.h"
#include"Engine/Model.h"

Ground::Ground(GameObject* parent)
	:GameObject(parent), hSilly(-1),hBlock(-1) {
}

void Ground::Initialize()
{
	hSilly = Model::Load("UV_Check.fbx");
	hBlock = Model::Load("Block.fbx");
}

void Ground::Update()
{
}

void Ground::Draw()
{
	Model::SetTransform(hSilly, transform_);
	Model::Draw(hSilly);

	Transform bt;
	bt.position_ = { -1,0,-1 };
	Model::SetTransform(hBlock, bt);
	Model::Draw(hBlock);
}

void Ground::Release()
{
}
