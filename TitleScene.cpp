#include "TitleScene.h"
#include "Engine/Camera.h"
#include "Engine/Sprite.h"
#include "Engine/Input.h"
#include "Button.h"
#include "Engine/SceneManager.h"
//コンストラクタ
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene"), start_(nullptr), back_(nullptr), selected_(NONE)
{
}

//初期化
void TitleScene::Initialize()
{
	Camera::SetPosition(XMFLOAT3(0, 50, 0));
	Camera::SetTarget(XMFLOAT3(0, 0, 0));

	start_ = Instantiate<Button>(this);
	start_->SetImage("FoodButtonGive", "FoodButtonGiveDisable");
	start_->SetPosition(1920, 360 - 150);
	start_->SetMovePosition(640, 360 - 150, 1.0f);

	back_ = Instantiate<Button>(this);
	back_->SetImage("CommonButtonBack", "CommonButtonBackDisable");
	back_->SetPosition(1920, 360 + 150);
	back_->SetMovePosition(640, 360 + 150, 1.0f);
}

//更新
void TitleScene::Update()
{
	if (Input::IsMouseButtonDown(0)) {
		bool moving = false;
		if (start_->isMoving()) {
			start_->ForceMoveEnd();
				moving = true;
		}
		if (back_->isMoving()) {
			back_->ForceMoveEnd();
			moving = true;
		}
		if (moving) {
			if (selected_ == START) {
				SceneManager* scene = dynamic_cast<SceneManager*>(FindObject("SceneManager"));
				scene->ChangeScene(SCENE_ID_TEST);
			}
		}
	}
	XMFLOAT3 pos = Input::GetMousePosition();
	if (start_->MouseInArea(pos)) {
		start_->Push(true);
		back_->Push(false);
		selected_ = START;
	}
	else if (back_->MouseInArea(pos)) {
		back_->Push(true);
		start_->Push(false);
		selected_ = BACK;
	}
	else {
		start_->Push(false);
		back_->Push(false);
		selected_ = NONE;
	}
}

//描画
void TitleScene::Draw()
{
}

//開放
void TitleScene::Release()
{
}
