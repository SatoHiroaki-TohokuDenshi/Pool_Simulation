/*
#pragma once
#include "Engine/GameObject.h"

//�O���錾
class Button;

namespace {
	enum SELECT {
		NONE = 0,
		START,
		BACK,
		MAX,
	};
}

//Title�V�[�����Ǘ�����N���X
class TitleScene : public GameObject
{
private:
	Button* pButtonStart_;
	Button* pButtonBack_;

	int state_;

	SELECT selected_;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	TitleScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};
*/