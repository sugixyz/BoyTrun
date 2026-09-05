#pragma once
#pragma once
#include "Engine/GameObject.h"

class Text;

//テストシーンを管理するクラス
class ResultScene : public GameObject
{
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	ResultScene(GameObject* parent);
	//初期化
	void Initialize() override;
	//更新
	void Update() override;
	//描画
	void Draw() override;
	//開放
	void Release() override;
	void Win() { isWin = true; }
	void Lose() { isWin = false; }
private:
	int hImage;
	Text* scoreT;
	Text* text;
	Text* titleT;
	int gameScore;

	bool isWin;
};