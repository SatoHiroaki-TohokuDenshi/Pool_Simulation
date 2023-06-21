#pragma once
#include "Engine/GameObject.h"

class Ball;

//Playerを管理するクラス
class Player : public GameObject
{
    Ball* myBall_;      //自玉を表すポインタ
    float direction_;   //玉を打つ方向（Y回転のラジアン角）
    float power_;       //力の強さ
    int hModel_;        //モデル番号

    bool isPull_;
    XMFLOAT3 pullBegin_;
    XMFLOAT3 pullEnd_;

    bool isCharge_;
    bool isCountUp;
public:
    //コンストラクタ
    Player(GameObject* parent);

    //デストラクタ
    ~Player();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    //プレイヤーが操作する玉の設定
    void SetMyBall(Ball* ball) { myBall_ = ball; };
};