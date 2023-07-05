#include "Gauge.h"
#include "Engine/Image.h"

//コンストラクタ
Gauge::Gauge(GameObject* parent)
    :GameObject(parent, "Gauge"), hPictGauge_(-1), hPictFrame_(-1),
    nowCharge_(0), aniCharge_(0), isDraw(false),
    imgHeight_(0.0f),imgWidth_(0.0f)
{
    transform_.position_.x = -0.95f;
    transform_.position_.y = 0.85f;
}

//デストラクタ
Gauge::~Gauge()
{
}

//初期化
void Gauge::Initialize()
{
    //画像データのロード
    hPictGauge_ = Image::Load("LifeGauge_v2.png");
    assert(hPictGauge_ >= 0);
    //画像データのロード
    hPictFrame_ = Image::Load("LifeGauge_Frame.png");
    assert(hPictFrame_ >= 0);

    imgHeight_ = (float)Image::GetHeight(hPictGauge_);
    imgWidth_ = (float)Image::GetWidth(hPictGauge_);
}

//更新
void Gauge::Update() {
}

//描画
void Gauge::Draw()
{
    if (isDraw) {
        //Transform transGauge = transform_;
        //transGauge.scale_.x = (float)aniCharge_ / (float)maxCharge_;

        int left = (int)(imgWidth_ / 2 - (imgWidth_ / 2) * nowCharge_);
        int width = (int)(imgWidth_ * nowCharge_);
        Image::SetRect(hPictGauge_, left, 0, width, (int)imgHeight_);

        Image::SetTransform(hPictGauge_, transform_);
        Image::Draw(hPictGauge_);

        Image::SetTransform(hPictFrame_, transform_);
        Image::Draw(hPictFrame_);
    }
}

//開放
void Gauge::Release()
{
}