#pragma once
#include "Engine/GameObject.h"

//���������Ǘ�����N���X
class Gauge : public GameObject
{
    int hPictGauge_;    //�o�[�̒��g
    int hPictFrame_;    //�o�[�̊O�g

    float maxCharge_;
    float nowCharge_;
    float aniCharge_;
public:
    //�R���X�g���N�^
    Gauge(GameObject* parent);

    //�f�X�g���N�^
    ~Gauge();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    void SetValue(float max, float now) {
        maxCharge_ = max;
        nowCharge_ = now;
        aniCharge_ = (aniCharge_ * 9 + nowCharge_) / 10;
    };
};