#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Debug.h"
#include "TestScene.h"
#include"Engine/Input.h"
#include"Ground.h"
#include"Engine/Debug.h"

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

	std::vector < std::vector<int>> gMap;
}

Player::Player(GameObject* parent)
	:GameObject(parent,"Player"), hWalkModel(-1), hIdleModel(-1) {
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
		float angle = targetAngle - initAngle;
		if (angle > 180)angle = angle - 360;
		else if (angle < -180)angle = angle + 360;
		transform_.rotate_.y = initAngle + angle * t;
		if (frame >= turnFrame)
		{
			pState = PLAYER_WALK;
			transform_.rotate_.y = targetAngle;
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
		float angle = abs(currentAngleY - prevAngleY);
		if (angle > 180)angle = angle - 180;
		turnFrame = angle * TURN_FRAME / 45 ;
	}

	if (pState == PLAYER_TURN)return;

	transform_.rotate_.y = currentAngleY;
	XMVECTOR vec = XMLoadFloat3(&move);
	vec = XMVector3Normalize(vec);

	pos = XMVectorAdd(pos, vec * SPEED);
	if (CheckMap(pos))pos = XMVectorSubtract(pos, vec * SPEED);
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

bool Player::CheckMap(const XMVECTOR& newPos)
{
	gMap = ground->GetMapData();

	XMFLOAT3 nPos;
	XMStoreFloat3(&nPos, newPos);
	int x, z;
	x = (nPos.x + 10) / 2;
	z = (-nPos.z +  10) / 2;
	if (x < 0 || 9 < x)return false;
	if (z < 0 || 9 < z)return false;
	//char str[50];
	//sprintf_s(str, sizeof(str), "( %d , %d )", x, z);
	//Debug::Log(str);

	return gMap[z][x] == 1;

}
