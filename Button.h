#pragma once
#include "Engine/GameObject.h"

class Button : public GameObject {
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Button(GameObject* parent);

	//�f�X�g���N�^
	~Button();

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

public:
	void SetImage(std::string normal, std::string pushed);
	void SetPosition(int x, int y);
	void Push(bool pushed);
	bool MouseInArea(XMFLOAT3 mousePos);

	void SetMovePosition(int toX, int toY, float seconds);
	bool Finished(); // Button���I�������true

	//�{�^���𓮂����Ă���ۂ̑����t�p
	bool isMoving();
	void ForceMoveEnd();

private:
	int hImage_;
	int hPush_;
	bool pushed_;
	XMFLOAT3 center_;
	XMFLOAT3 size_;
};