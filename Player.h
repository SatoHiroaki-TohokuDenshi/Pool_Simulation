#pragma once
#include "Gauge.h"
#include "Engine/GameObject.h"

class Ball;

//ゴルフ風に使う状態遷移
enum SHOT_STATE{
    S_ROTATE = 0,
    S_POWER,
    S_MOVE,
    S_MAX,
};

//Playerを管理するクラス
class Player : public GameObject
{
    Ball* myBall_;      //自玉を表すポインタ
    float direction_;   //玉を打つ方向（Y回転のラジアン角）
    float power_;       //力の強さ
    int hModel_;        //モデル番号

    //モンスト風
    bool isPull_;       //引いているかどうか
    XMFLOAT3 pullBegin_;//開始地点
    XMFLOAT3 pullEnd_;  //終了地点

    //ゴルフ風
    Gauge* pGauge;      //チャージバー
    float chargeMax_;   //最大値
    float chargeLv_;    //現在値
    int state_;
    bool isCharge_;     //チャージしているか
    bool isCountUp;     //チャージが増大しているか
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