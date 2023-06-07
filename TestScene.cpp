#include "TestScene.h"
#include "Ball.h"
#include "Player.h"
#include "Engine/Camera.h"

//コンストラクタ
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//初期化
void TestScene::Initialize()
{
	Camera::SetPosition(XMFLOAT3(0, 50, 0));
	Camera::SetTarget(XMFLOAT3(0, 0, 0));
	for (int i = 1; i < 9; i++) {
		Ball* b =  Instantiate<Ball>(this);
		b->SetNumber(i);
		b->SetPosition((float)(i - 4) * 1.4f, 0, (float)(i - 4) * 1.4f);
	}
	Player* p = Instantiate<Player>(this);
	Ball* b = Instantiate<Ball>(this);
	b->SetNumber(0);		//白玉
	p->SetMyBall(b);
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
