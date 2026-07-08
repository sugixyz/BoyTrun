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

	//ラープの目標値
	float targetAngle = 0.0f;
	//ラープの初期値
	float initAngle = 0.0f;
	float turnFrame = 0.0f;
	//45度回転するのにかかるフレーム
	const float TURN_FRAME = 5.0f;
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

	if (pState == PLAYER_TURN)
	{
		static int frame = 0;
		frame++;
		float t = frame / turnFrame;
		transform_.rotate_.y = initAngle + (targetAngle - initAngle) * t;
		if (targetAngle == transform_.rotate_.y)
		{
			pState = PLAYER_WALK;
			frame = 0;
		}
		return;
	}

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
	if (abs(currentAngleY - prevAngleY) >= 45)
	{
		pState = PLAYER_TURN;
		targetAngle = currentAngleY;
		initAngle = prevAngleY;
		turnFrame = abs(currentAngleY - prevAngleY) * TURN_FRAME / 45 ;
	}

	if (pState == PLAYER_TURN)return;

	transform_.rotate_.y = currentAngleY;
	XMVECTOR vec = XMLoadFloat3(&move);
	vec = XMVector3Normalize(vec);

	pos = XMVectorAdd(pos, vec * SPEED);
	XMStoreFloat3(&transform_.position_, pos);
}

void Player::Draw()
{
	if (pState == PLAYER_IDLE)
	{
		Model::SetTransform(hIdleModel, transform_);
		Model::Draw(hIdleModel);
	}
	else if (pState == PLAYER_WALK || pState == PLAYER_TURN)
	{
		Model::SetTransform(hWalkModel, transform_);
		Model::Draw(hWalkModel);
	}
}


void Player::Release()
{
}
