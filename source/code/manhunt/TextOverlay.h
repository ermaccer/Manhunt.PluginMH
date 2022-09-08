#pragma once

class CTextOverlay {
public:
	void DisplayText16(wchar_t* text, int unk);
	void SetCurrentTextDisplaying(bool display);
};


class COverlayMgr {
public:
	static CTextOverlay& m_textOverlay;
	static CTextOverlay& m_textPickUpOverlay;
	static CTextOverlay& m_textProducerOverlay;
	static CTextOverlay& m_textPeripheralOverlay;
};