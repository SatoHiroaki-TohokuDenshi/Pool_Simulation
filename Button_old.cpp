/*
#include "Button.h"
#include "Engine/Direct3D.h"
#include "Engine/Image.h"

//コンストラクタ
Button::Button(GameObject* parent)
    :GameObject(parent, "Button"), isHover_(false),
	center_(0.0f, 0.0f, 0.0f), size_(0.0f, 0.0f, 0.0f)
{
}

//デストラクタ
Button::~Button()
{
}

//初期化
void Button::Initialize()
{
}

//更新
void Button::Update()
{
}

//描画
void Button::Draw()
{
	if (!isHover_) {
		Image::SetTransform(hPict_.at(0), transform_);
		Image::Draw(hPict_.at(0));
	}
	else {
		Image::SetTransform(hPict_.at(1), transform_);
		Image::Draw(hPict_.at(1));
	}
}

//開放
void Button::Release()
{
}

void Button::LoadFile(std::string fileName)
{
	//画像データのロード
	std::string fn[] = {
		fileName + ".png",
		fileName + "Disable.png"
	};

	for (int i = 0; i < 2; i++) {
		hPict_.push_back(Image::Load(fn[i]));
		assert(hPict_.at(i) >= 0);
	}
	Image::GetSize(hPict_.at(0));
}

void Button::SetPosition(int x, int y)
{
	transform_.position_.x = (float)(x - Direct3D::screenWidth_  / 2) / Direct3D::screenWidth_;
	transform_.position_.y = -(float)(y - Direct3D::screenHeight_ / 2) / Direct3D::screenHeight_;
	center_ = XMFLOAT3((float)x, (float)y, 0.0f);
}

void Button::Hovered(bool hovered)
{
	isHover_ = hovered;
}

bool Button::MouseInArea(XMFLOAT3 mousePos)
{
	if (abs(mousePos.x - center_.x) > size_.x / 2) return false;
	if (abs(mousePos.y - center_.x) > size_.y / 2) return false;
	return true;
}
*/