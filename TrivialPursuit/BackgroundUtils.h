#pragma once

#include <afxwin.h>

// This helper class will manage drawing a tiled bitmap background for a dialog.
class CBackgroundManager
{
public:
    CBackgroundManager() : m_pBrush(nullptr) {}
    ~CBackgroundManager()
    {
        if (m_pBrush)
        {
            delete m_pBrush;
            m_pBrush = nullptr;
        }
    }

    // Call this in your dialog's OnInitDialog to load the bitmap
    void Initialize(UINT nBitmapID)
    {
        if (m_bitmap.LoadBitmap(nBitmapID))
        {
            m_pBrush = new CBrush(&m_bitmap);
        }
    }

    // Call this from your dialog's OnEraseBkgnd handler
    BOOL EraseBkgnd(CDC* pDC)
    {
        if (!m_pBrush)
        {
            return FALSE; // Let the default handler do the work
        }

        CRect rect;
        pDC->GetClipBox(&rect);

        // Tile the background
        BITMAP bm;
        m_bitmap.GetBitmap(&bm);
        int x = 0, y = 0;
        while (y < rect.bottom)
        {
            x = 0;
            while (x < rect.right)
            {
                pDC->BitBlt(x, y, bm.bmWidth, bm.bmHeight, pDC, 0, 0, SRCCOPY);
                CBrush* pOldBrush = pDC->SelectObject(m_pBrush);
                pDC->PatBlt(rect.left, rect.top, rect.Width(), rect.Height(), PATCOPY);
                pDC->SelectObject(pOldBrush);
                x += bm.bmWidth;
            }
            y += bm.bmHeight;
        }
        return TRUE;
    }

    // Call this from your dialog's OnCtlColor handler to make static controls transparent
    HBRUSH CtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
    {
        if (nCtlColor == CTLCOLOR_STATIC)
        {
            pDC->SetBkMode(TRANSPARENT);
            // Return a handle to a hollow brush
            return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
        }
        // For other controls, return a NULL_BRUSH to use the default
        return (HBRUSH)GetStockObject(NULL_BRUSH);
    }


private:
    CBitmap m_bitmap;
    CBrush* m_pBrush;
};
