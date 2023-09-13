/*
#include "TitleScene.h"

#include <string>
#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/Debug.h"
#include "Button.h"

//�R���X�g���N�^
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene"), pButtonStart_(nullptr), pButtonBack_(nullptr),
	state_(0), selected_(SELECT::NONE)
{
}

//������
void TitleScene::Initialize()
{
	//�摜�f�[�^�̃��[�h
	std::string fileName[] = {
		"FoodButtonGive",
		"CommonButtonBack",
	};

	pButtonStart_ = Instantiate<Button>(this);
	pButtonStart_->LoadFile(fileName[0]);
	pButtonStart_->SetPosition(640, 360 - 300);
	pButtonBack_ = Instantiate<Button>(this);
	pButtonBack_->LoadFile(fileName[1]);
	pButtonBack_->SetPosition(640, 360 + 300);
}

//�X�V
void TitleScene::Update()
{
	XMFLOAT3 mousePos = Input::GetMousePosition();

	Debug::Log("mouse  = (");
	Debug::Log(mousePos.x);
	Debug::Log(", ");
	Debug::Log(mousePos.y);
	Debug::Log(")", true);

	if (pButtonStart_->MouseInArea(mousePos)){
		pButtonStart_->Hovered(true);
		pButtonBack_->Hovered(false);
		selected_ = SELECT::START;
	}
	else if (pButtonBack_->MouseInArea(mousePos)) {
		pButtonStart_->Hovered(false);
		pButtonBack_->Hovered(true);
		selected_ = SELECT::BACK;
	}
	else {
		pButtonStart_->Hovered(false);
		pButtonBack_->Hovered(false);
		selected_ = SELECT::NONE;
	}

	if (Input::IsMouseButtonDown(0)) {
		if (selected_ == SELECT::START) {
			SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
			pSceneManager->ChangeScene(SCENE_ID_TEST);
		}
	}
}

//�`��
void TitleScene::Draw()
{
}

//�J��
void TitleScene::Release()
{
}
*/