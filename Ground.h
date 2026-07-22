#pragma once
#include "Engine/GameObject.h"
#include<vector>

class Ground :
	public GameObject
{
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Ground(GameObject* parent);
	//初期化
	void Initialize() override;
	//更新
	void Update() override;
	//描画
	void Draw() override;
	//開放
	void Release() override;
	std::vector<std::vector<int>>& GetMapData() { return map; }
	void EatFeed() { feedCount--; }
	void EatPowerFeed() { powerFeedCount--; }
private:
	int hSilly;
	int hBlock;
	std::vector<std::vector<int>> map;
	int mapWidth;
	int mapHeight;
private:
	XMFLOAT3 CalculatePosition(int x, int y);
	int feedCount;
	int powerFeedCount;
};

