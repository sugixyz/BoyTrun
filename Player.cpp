#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Debug.h"
#include "TestScene.h"
#include"Engine/Input.h"

namespace
{
	enum PlayerState
	{
		PLAYER_IDLE,
		PLAYER_WALK,
		PLAYER_TURN,
		STATE_MAX
	};
	PlayerState pState = PLAYER_IDLE;

	float targetAngle = 0.0f;
	//回転にかかるフレーム
	const float TURN_FRAME = 30.0f;
}

Player::Player(GameObject* parent)
	:GameObject(parent), hWalkModel(-1),hIdleModel(-1){
	//swordDirには、初期方向として、ローカルモデルの剣の根っこから
	//先端までのベクトルとして（0,1,0)を代入しておく
	//初期位置は原点
}

void Player::Initialize()
{
	hIdleModel = Model::Load("Idle.fbx");
	Model::SetAnimFrame(hIdleModel, 0, 117, 1.0);

	hWalkModel = Model::Load("Walking.fbx");
	Model::SetAnimFrame(hWalkModel, 0, 57, 1.0);
}

void Player::Update()
{
	//transform_.rotate_.y +=1;
	//static float angle = 0.0;
	//angle = angle + 0.3f;
	//XMMATRIX scale = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	//XMMATRIX rotateX = XMMatrixRotationX(XMConvertToRadians(angle));
	//XMMATRIX rotate = XMMatrixRotationY(XMConvertToRadians(angle));
	//XMMATRIX translate = XMMatrixTranslation(1.0f, 0.0f, 0.0f);

	//SetWorldMatrix(scale *  rotate * translate);

	XMVECTOR pos = XMLoadFloat3(&transform_.position_);
	XMFLOAT3 move = XMFLOAT3(0, 0, 0);
	const float SPEED = 0.05f;
	pState = PLAYER_IDLE;

	float prevAngleY = transform_.rotate_.y;

	if (Input::IsKey(DIK_W))
	{
		move.z = 1;
		pState = PLAYER_WALK;
	}
	if (Input::IsKey(DIK_S))
	{
		move.z = -1;
		pState = PLAYER_WALK;
	}
	if (Input::IsKey(DIK_A))
	{
		move.x = -1;
		pState = PLAYER_WALK;
	}
	if (Input::IsKey(DIK_D))
	{
		move.x = 1;
		pState = PLAYER_WALK;
	}

	if (pState == PLAYER_IDLE)return;

	float currentAngleY = atan2f(move.x, move.z) * 180 / XM_PI + 180;
	if (currentAngleY != prevAngleY)
	{
		pState = PLAYER_TURN;
		targetAngle = currentAngleY - prevAngleY;
	}
	if (pState == PLAYER_TURN)
	{
		static int count = 0;
		count++;
		transform_.rotate_.y += targetAngle / 30;
		if (count >= 30)pState == PLAYER_IDLE; count = 0;
		return;
	}

	transform_.rotate_.y = currentAngleY;
	XMVECTOR vec = XMLoadFloat3(&move);
	vec = XMVector3Normalize(vec);

	pos = XMVectorAdd(pos, vec * SPEED);
	XMStoreFloat3(&transform_.position_, pos);
}

void Player::Draw()
{
	if (pState == PLAYER_IDLE || pState == PLAYER_TURN)
	{
		Model::SetTransform(hIdleModel, transform_);
		Model::Draw(hIdleModel);
	}
	else if (pState == PLAYER_WALK)
	{
		Model::SetTransform(hWalkModel, transform_);
		Model::Draw(hWalkModel);
	}
}


void Player::Release()
{
}
