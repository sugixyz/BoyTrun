#include "Ground.h"
#include"Engine/Model.h"

Ground::Ground(GameObject* parent)
	:GameObject(parent), hSilly(-1) {
}

void Ground::Initialize()
{
	hSilly = Model::Load("UV_Check.fbx");
}

void Ground::Update()
{
}

void Ground::Draw()
{
	Model::SetTransform(hSilly, transform_);
	Model::Draw(hSilly);
}

void Ground::Release()
{
}
