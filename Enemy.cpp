#include "Enemy.h"
#include"Engine/Model.h"
#include<vector>
#include<random>
#include"Ground.h"
#include"Engine/SphereCollider.h"

namespace
{
	//移動速度
	const float SPEED = 2.0f;
	//移動間隔（フレーム）
	const int MOVE_INTERVAL = 40;

	std::vector < std::vector<int>> gMap;

	const float RADIUS = 1.0f;
}

Enemy::Enemy(GameObject* parent)
	:GameObject(parent,"Enemy"), hModel(-1),direction(Direction::FORWARD),count(0),ground(nullptr)
{
}

void Enemy::Initialize()
{
	hModel = Model::Load("Enemy.fbx");

	transform_.rotate_.y = 180;
	front = { 0.0f,0.0f,SPEED };

	SphereCollider* col = new SphereCollider(XMFLOAT3(0, 0, 0), RADIUS);
	AddCollider(col);
}

void Enemy::Update()
{
	count++;

	if (count >= MOVE_INTERVAL)
	{
		Move();
		count = 0;
	}
}

void Enemy::Draw()
{
	Model::SetTransform(hModel, transform_);
	Model::Draw(hModel);
}

void Enemy::Release()
{
}

bool Enemy::HasBlockInDirection(Direction dir)
{
	XMFLOAT3 checkDir;
	switch (dir)
	{
	case Direction::FORWARD:
		checkDir = front;
		break;
	case Direction::BACK:
		checkDir = XMFLOAT3(-front.x, 0.0f, -front.z);
		break;
	case Direction::LEFT:
		checkDir = XMFLOAT3(-front.z, 0.0f, front.x);
		break;
	case Direction::RIGHT:
		checkDir = XMFLOAT3(front.z, 0.0f, -front.x);
		break;
	}

	XMFLOAT3 pos = transform_.position_;
	XMFLOAT3 checkPos = { pos.x + checkDir.x,pos.y + checkDir.y ,pos.z + checkDir.z };
	return CheckMap(checkPos);
}

bool Enemy::CheckMap(XMFLOAT3 pos)
{
	gMap = ground->GetMapData();

	int x, z;
	x = (pos.x + 10) / 2;
	z = (-pos.z + 10) / 2;
	if (x < 0 || 9 < x)return false;
	if (z < 0 || 9 < z)return false;
	
	return gMap[z][x] == 1;
}

Direction Enemy::SelectMoveDirection()
{
	std::vector<Direction> dirVec;
	dirVec.clear();
	
	if (!HasBlockInDirection(Direction::FORWARD))dirVec.push_back(Direction::FORWARD);
	if (!HasBlockInDirection(Direction::LEFT))dirVec.push_back(Direction::LEFT);
	if (!HasBlockInDirection(Direction::RIGHT))dirVec.push_back(Direction::RIGHT);

	if (dirVec.size() == 0)return Direction::BACK;

	int randValue = std::rand() % dirVec.size();
	return dirVec[randValue];
}

void Enemy::Move()
{
	direction = SelectMoveDirection();

	switch (direction)
	{
	case Direction::FORWARD:
		break;
	case Direction::BACK:
		front = XMFLOAT3(-front.x, 0.0f, -front.z);
		transform_.rotate_.y += 180.0f;
		break;
	case Direction::LEFT:
		front = XMFLOAT3(-front.z, 0.0f, front.x);
		transform_.rotate_.y -= 90.0f;
		break;
	case Direction::RIGHT:
		front = XMFLOAT3(front.z, 0.0f, -front.x);
		transform_.rotate_.y += 90.0f;
		break;
	}

	if (transform_.rotate_.y >= 360.0f)transform_.rotate_.y -= 360.0f;
	if (transform_.rotate_.y < 0)transform_.rotate_.y += 360.0f;

	transform_.position_.x += front.x;
	transform_.position_.z += front.z;
}
