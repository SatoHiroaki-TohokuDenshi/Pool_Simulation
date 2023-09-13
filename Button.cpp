#include "Button.h"

#include <vector>
#include "Engine/Image.h"
#include "Engine/Direct3D.h"

namespace {
	XMFLOAT3 startPos;	//開始座標
	XMFLOAT3 endPos;	//終了座標
	float totalTime;	//移動時間（秒）
	float currentTime;	//現在の時間

	int seqLine;		//今実行している行
	float seqTime;		//シーケンスを実行している時間
	enum ACT {			//やることをコマンド化
		A_SLIDEIN = 1,
		A_WAIT,
		A_SLIDEOUT,
		A_END
	};
	struct Sequence {
		float time;		//時間
		ACT action;		//やること
		float param;	//必要な値
	};
	std::vector<Sequence> tbl = {
		{ 0.0f, A_SLIDEIN,	 5.0f },	//まずはスライドイン
		{ 3.0f, A_WAIT,		 0.0f},		//1秒待ってから
		{ 4.0f, A_SLIDEOUT, -5.0f },	//スライドアウト
		{ 5.0f, A_END,		 0.0f}		//ここで消える
	};
	ACT currentAction;		// 今実行しているアクション
	bool canMove;			// 移動できる
};

Button::Button(GameObject* parent)
	: GameObject(parent, "Button"), hImage_(-1), hPush_(-1), pushed_(false),
	center_(0.0f, 0.0f, 0.0f), size_(0.0f, 0.0f, 0.0)
{
	seqLine = -1;
	seqTime = 0.0f;
	canMove = false;
	currentTime = 0.0f;
	totalTime = 0.0f;
}

Button::~Button()
{
}

void Button::Initialize()
{
}

void Button::Update()
{
	seqTime += 1.0f / 60.0f;
	if (currentTime >= totalTime) {
		SetPosition((int)endPos.x, (int)endPos.y);
	}
	else {
		float x = (endPos.x - startPos.x) * (currentTime / totalTime) + startPos.x;
		float y = (endPos.y - startPos.y) * (currentTime / totalTime) + startPos.y;
		SetPosition((int)x, (int)y);
	}
}

void Button::Draw()
{

	if (pushed_) {
		Image::SetTransform(hPush_, transform_);
		Image::Draw(hPush_);
	}
	else {
		Image::SetTransform(hImage_, transform_);
		Image::Draw(hImage_);
	}
}

void Button::Release()
{
}

bool Button::Finished()
{
	return canMove;
}

void Button::SetImage(std::string normal, std::string pushed)
{
	hImage_ = Image::Load((normal + ".png").c_str());
	hPush_ = Image::Load((pushed + ".png").c_str());
	size_ = Image::GetSize(hImage_);
}

void Button::SetPosition(int x, int y)
{
	transform_.position_.x = (float)(x - Direct3D::screenWidth_ / 2) / Direct3D::screenWidth_;
	transform_.position_.y = -(float)(y - Direct3D::screenHeight_ / 2) / (Direct3D::screenHeight_ / 2);
	center_ = XMFLOAT3((float)x, (float)y, 0.0f);
}

void Button::Push(bool pushed)
{
	this->pushed_ = pushed;
}

bool Button::MouseInArea(XMFLOAT3 mousePos)
{
	if (abs(mousePos.x - center_.x) > size_.x / 2)
		return false;
	if (abs(mousePos.y - center_.y) > size_.y / 2)
		return false;
	return true;
}

void Button::SetMovePosition(int toX, int toY, float seconds)
{
	startPos = center_;
	endPos = XMFLOAT3((float)toX, (float)toY, 0.0f);
	totalTime = seconds;
	currentTime = 0.0f;
}

bool Button::isMoving()
{
	return (currentTime >= totalTime);
}

void Button::ForceMoveEnd()
{
	if (isMoving()) {
		SetPosition((int)endPos.x, (int)endPos.y);
		currentTime = totalTime;
	}
}