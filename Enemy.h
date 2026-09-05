#pragma once
#include "Engine/GameObject.h"
#include<vector>

class Ground;

enum class Direction
{
	FORWARD,
	BACK,
	LEFT,
	RIGHT,
	SIZE
};

class Enemy :
	public GameObject
{
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Enemy(GameObject* parent);
	//初期化
	void Initialize() override;
	//更新
	void Update() override;
	//描画
	void Draw() override;
	//開放
	void Release() override;

	void SetGround(Ground* g) { ground = g; }
private:
	int hModel;
	Direction direction;
	int count;
	XMFLOAT3 front;

	Ground* ground;
private:
	bool HasBlockInDirection(Direction dir);
	bool CheckMap(XMFLOAT3 pos);
	Direction SelectMoveDirection();
	void Move();
};

