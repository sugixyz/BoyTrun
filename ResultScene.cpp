#include "ResultScene.h"
#include"Engine/Text.h"
#include"Engine/Image.h"
#include"Engine/Input.h"
#include"Engine/Text.h"
#include"Engine/SceneManager.h"
#include"TestScene.h"

ResultScene::ResultScene(GameObject* parent)
	:GameObject(parent, "ResultScene"),hImage(-1),
	scoreT(nullptr),text(nullptr),titleT(nullptr), isWin(false),gameScore(0)
{
}

void ResultScene::Initialize()
{
	hImage = Image::Load("result.png");
	assert(hImage >= 0);

	scoreT = new Text();
	scoreT->Initialize();

	titleT = new Text();
	titleT->Initialize();

	text = new Text();
	text->Initialize();

	gameScore = TestScene::myScore;
}

void ResultScene::Update()
{
	if (Input::IsKeyDown(DIK_SPACE))
	{
		SceneManager* sceneManager = (SceneManager*)(this->GetParent());
		sceneManager->ChangeScene(SCENE_ID_TITLE);
	}
}

void ResultScene::Draw()
{
	Image::SetTransform(hImage,transform_);
	Image::Draw(hImage);

	if (isWin)titleT->Draw(640 - 100, 250, "GAME CLEAR");
	else if (!isWin)titleT->Draw(640 - 100, 250, "GAME OVER");

	char score[20];
	sprintf_s(score, sizeof(score), "SCORE:%2d", gameScore);
	scoreT->Draw(640 - 80, 350, score);

	text->Draw(640 - 160, 450, "PUSH SPACE TO TITLE");
}

void ResultScene::Release()
{
}
