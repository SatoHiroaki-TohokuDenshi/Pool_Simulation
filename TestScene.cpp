#include "TestScene.h"
#include "Ball.h"
#include "Engine/Camera.h"

//�R���X�g���N�^
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//������
void TestScene::Initialize()
{
	Camera::SetPosition(XMFLOAT3(0, 50, 5));
	Camera::SetTarget(XMFLOAT3(0, 0, 0));
	for (int i = 0; i < 9; i++) {
		Ball* b =  Instantiate<Ball>(this);
		b->SetNumber(i);
		b->SetPosition((float)(i - 4) * 1.4f, 0, (float)(i - 4) * 1.4f);
	}
}

//�X�V
void TestScene::Update()
{
}

//�`��
void TestScene::Draw()
{
}

//�J��
void TestScene::Release()
{
}