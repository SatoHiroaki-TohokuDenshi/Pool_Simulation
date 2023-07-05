#pragma once
#include <cassert>
#include "Engine/GameObject.h"

//◆◆◆を管理するクラス
class Gauge : public GameObject
{
    int hPictGauge_;    //バーの中身
    int hPictFrame_;    //バーの外枠

    const float maxCharge_ = 1.0f;  //最大値
    float nowCharge_;               //現在の値
    float aniCharge_;               //アニメーション用
    float imgWidth_;
    float imgHeight_;
    bool isDraw;                    //表示するかどうか
public:
    static constexpr float MIN = 0.0f;
    static constexpr float MAX = 1.0f;
    //コンストラクタ
    Gauge(GameObject* parent);

    //デストラクタ
    ~Gauge();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    void SetPosition(float x, float y) {
        transform_.position_ = XMFLOAT3(x, y, 0.0f);
    }

    float GetValue() { return nowCharge_; };

    /// <summary>値を加減算する</summary>
    /// <param name="v">加減算する値</param>
    void AddValue(float v) { 
        nowCharge_ += v; 
        if (nowCharge_ < 0.0f)       nowCharge_ = 0.0f;
        if (nowCharge_ > maxCharge_) nowCharge_ = maxCharge_;
    };

    /// <summary>値を設定する</summary>
    /// <param name="now">設定したい値</param>
    void SetValue(float v) {
        assert(v >= 0.0f && v <= 1.0f);
        nowCharge_ = v;
        if (nowCharge_ < 0.0f)       nowCharge_ = 0.0f;
        if (nowCharge_ > maxCharge_) nowCharge_ = maxCharge_;
    };

    void DoDraw(bool f) { isDraw = f; };
};