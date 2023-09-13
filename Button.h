#pragma once
#include "Engine/GameObject.h"

class Button : public GameObject {
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Button(GameObject* parent);

	//デストラクタ
	~Button();

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

public:
	void SetImage(std::string normal, std::string pushed);
	void SetPosition(int x, int y);
	void Push(bool pushed);
	bool MouseInArea(XMFLOAT3 mousePos);

	void SetMovePosition(int toX, int toY, float seconds);
	bool Finished(); // Buttonが終わったらtrue

	//ボタンを動かしている際の操作受付用
	bool isMoving();
	void ForceMoveEnd();

private:
	int hImage_;
	int hPush_;
	bool pushed_;
	XMFLOAT3 center_;
	XMFLOAT3 size_;
};