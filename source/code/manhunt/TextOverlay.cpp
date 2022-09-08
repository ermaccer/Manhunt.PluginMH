#include "TextOverlay.h"
#include "core.h"

CTextOverlay& COverlayMgr::m_textOverlay = *(CTextOverlay*)0x71D2D4;
CTextOverlay& COverlayMgr::m_textPickUpOverlay = *(CTextOverlay*)0x71ECBC;
CTextOverlay& COverlayMgr::m_textProducerOverlay = *(CTextOverlay*)0x7206A4;
CTextOverlay& COverlayMgr::m_textPeripheralOverlay = *(CTextOverlay*)0x72208C;

void CTextOverlay::DisplayText16(wchar_t* text, int unk)
{
	CallMethod<0x48AD90, CTextOverlay*, wchar_t*, int>(this, text, unk);
}

void CTextOverlay::SetCurrentTextDisplaying(bool display)
{
	CallMethod<0x48B350, CTextOverlay*, bool>(this, display);
}
