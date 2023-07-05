#pragma once
#include <cassert>
#include "Engine/GameObject.h"

//���������Ǘ�����N���X
class Gauge : public GameObject
{
    int hPictGauge_;    //�o�[�̒��g
    int hPictFrame_;    //�o�[�̊O�g

    const float maxCharge_ = 1.0f;  //�ő�l
    float nowCharge_;               //���݂̒l
    float aniCharge_;               //�A�j���[�V�����p
    float imgWidth_;
    float imgHeight_;
    bool isDraw;                    //�\�����邩�ǂ���
public:
    static constexpr float MIN = 0.0f;
    static constexpr float MAX = 1.0f;
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

    void SetPosition(float x, float y) {
        transform_.position_ = XMFLOAT3(x, y, 0.0f);
    }

    float GetValue() { return nowCharge_; };

    /// <summary>�l�������Z����</summary>
    /// <param name="v">�����Z����l</param>
    void AddValue(float v) { 
        nowCharge_ += v; 
        if (nowCharge_ < 0.0f)       nowCharge_ = 0.0f;
        if (nowCharge_ > maxCharge_) nowCharge_ = maxCharge_;
    };

    /// <summary>�l��ݒ肷��</summary>
    /// <param name="now">�ݒ肵�����l</param>
    void SetValue(float v) {
        assert(v >= 0.0f && v <= 1.0f);
        nowCharge_ = v;
        if (nowCharge_ < 0.0f)       nowCharge_ = 0.0f;
        if (nowCharge_ > maxCharge_) nowCharge_ = maxCharge_;
    };

    void DoDraw(bool f) { isDraw = f; };
};