#include "Ground.h"
#include"Engine/Model.h"

namespace
{
	std::vector<std::vector<int>> mapData =
	{
		{0,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,1,0,0,0,0,1},
		{1,0,1,0,1,0,1,1,0,1},
		{1,0,1,0,0,0,1,0,0,1},
		{1,0,1,1,1,1,1,0,1,1},
		{1,0,0,0,0,0,1,0,0,1},
		{1,1,1,1,1,0,1,1,0,1},
		{1,0,0,0,1,0,0,1,0,1},
		{1,0,1,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1}
	};
}

Ground::Ground(GameObject* parent)
	:GameObject(parent), hSilly(-1),hBlock(-1) {
}

void Ground::Initialize()
{
	hSilly = Model::Load("Ground.fbx");
	hBlock = Model::Load("Block_Green.fbx");
	map = mapData;
}

void Ground::Update()
{
}

void Ground::Draw()
{
	Model::SetTransform(hSilly, transform_);
	Model::Draw(hSilly);

	Transform bt;
	for (int z = 0;z < 10;z++)
	{
		for (int x = 0; x < 10;x++)
		{
			if(map[z][x] == 1)
			{
				bt.position_.x = (x - 5.0f) * 2 + 1;
				bt.position_.z = -(z - 5.0f) * 2 - 1;
				Model::SetTransform(hBlock, bt);
				Model::Draw(hBlock);
			}
		}
	}
}

void Ground::Release()
{
}
