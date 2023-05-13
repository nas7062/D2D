#pragma once
class Button : public GameObject
{
public: 
	void   Update(Matrix V, Matrix P)  override;
	void   Render() override;

public:
	void   SetSelect(bool value) { m_bSelect = value; }
	void   SetButtonString(wstring value) { m_strButton = value; }
	void   SetCallback(function<void(int)> cbFunction) { m_fpButtonCallBack = cbFunction; }
private:

private:
	Texture      *m_pButton = nullptr;
	bool          m_bSelect = true;
	wstring       m_strButton;
	function<void(int)>    m_fpButtonCallBack = nullptr;
public:
	Button();
	~Button();
};