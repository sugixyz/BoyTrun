#pragma once
#include "Engine/GameObject.h"
#include<vector>

class PowerFeed :
	public GameObject
{
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	PowerFeed(GameObject* parent);
	//初期化
	void Initialize() override;
	//更新
	void Update() override;
	//描画
	void Draw() override;
	//開放
	void Release() override;
	void OnCollision(GameObject* pTarget) override;
private:
	int hModel;
	int score;
};

