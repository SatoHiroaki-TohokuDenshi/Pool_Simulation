/*
#pragma once
#include "Engine/GameObject.h"

//前方宣言
class Button;

namespace {
	enum SELECT {
		NONE = 0,
		START,
		BACK,
		MAX,
	};
}

//Titleシーンを管理するクラス
class TitleScene : public GameObject
{
private:
	Button* pButtonStart_;
	Button* pButtonBack_;

	int state_;

	SELECT selected_;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	TitleScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};
*/