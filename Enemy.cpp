#include "Enemy.h"
#include"Engine/Model.h"

Enemy::Enemy(GameObject* parent)
	:GameObject(parent), hModel(-1)
{
}

void Enemy::Initialize()
{
	hModel = Model::Load("Enemy.fbx");
}

void Enemy::Update()
{
}

void Enemy::Draw()
{
	Model::SetTransform(hModel, transform_);
	Model::Draw(hModel);
}

void Enemy::Release()
{
}
