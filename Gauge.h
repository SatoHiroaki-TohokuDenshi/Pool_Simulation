#pragma once
#include "Engine/GameObject.h"

//◆◆◆を管理するクラス
class Gauge : public GameObject
{
    int hPictGauge_;    //バーの中身
    int hPictFrame_;    //バーの外枠

    float maxCharge_;
    float nowCharge_;
    float aniCharge_;
public:
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

    void SetValue(float max, float now) {
        maxCharge_ = max;
        nowCharge_ = now;
        aniCharge_ = (aniCharge_ * 9 + nowCharge_) / 10;
    };
};