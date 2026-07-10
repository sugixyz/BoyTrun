#include "TestScene.h"
#include "Player.h"
#include"Ground.h"
#include"Engine/Camera.h"
//コンストラクタ
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//初期化
void TestScene::Initialize()
{	
	Ground* g = Instantiate<Ground>(this);
	Player* p = Instantiate <Player>(this);
	p->SetGround(g);

	Camera::SetPosition(XMFLOAT3(0, 12, -20));
	Camera::SetTarget(XMFLOAT3(0, 0, 0));
}

//更新
void TestScene::Update()
{
}

//描画
void TestScene::Draw()
{
}

//開放
void TestScene::Release()
{
}
