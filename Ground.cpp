#include "Ground.h"
#include"Engine/Model.h"
#include"Player.h"
#include"Enemy.h"
#include"Feed.h"
#include"Engine/CsvReader.h"

namespace
{
	int WALL_CSV = 1;
	int PLAYER_CSV = 2;
	int ENEMY_CSV = 3;
}

Ground::Ground(GameObject* parent)
	:GameObject(parent), hSilly(-1), hBlock(-1), mapHeight(-1), mapWidth(-1) 
{
	CsvReader csv;
	csv.Load("map.csv");
	mapWidth = csv.GetWidth();
	mapHeight = csv.GetHeight();
	map = std::vector<std::vector<int>>(mapHeight, std::vector<int>(mapWidth, 0));
	
	for (int y = 0;y < mapHeight;y++)
	{
		for (int x = 0;x < mapWidth;x++)
		{
			int value = csv.GetValue(x, y);
			map[y][x] = value;
			if (value != WALL_CSV)
			{
				XMFLOAT3 pos = CalculatePosition(x, y);
				Feed* f = Instantiate<Feed>(this);
				f->SetPosition(pos);

				if (value == PLAYER_CSV)
				{
					GameObject* p = FindObject("Player");
					p->SetPosition(pos);
				}
				else if (value == ENEMY_CSV)
				{
					GameObject* e = FindObject("Enemy");
					e->SetPosition(pos);
				}
			}
		}
	}
}

void Ground::Initialize()
{
	hSilly = Model::Load("Ground.fbx");
	hBlock = Model::Load("Block_Green.fbx");
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

XMFLOAT3 Ground::CalculatePosition(int x, int y)
{
	XMFLOAT3 pos;
	pos.x = (x - 5.0f) * 2 + 1;
	pos.y = 0.0f;
	pos.z = -(y - 5.0f) * 2 - 1;

	return pos;
}
