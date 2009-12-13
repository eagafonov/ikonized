#ifndef _SIZE_H_
#define _SIZE_H_

namespace libsizer 
{

class  wxSize
{
public:
    // members are public for compatibility, don't use them directly.
    int x, y;

    // constructors
    wxSize() : x(0), y(0) { }
    wxSize(int xx, int yy) : x(xx), y(yy) { }

    // no copy ctor or assignment operator - the defaults are ok

    bool operator==(const wxSize& sz) const { return x == sz.x && y == sz.y; }
    bool operator!=(const wxSize& sz) const { return x != sz.x || y != sz.y; }

    wxSize operator+(const wxSize& sz) const { return wxSize(x + sz.x, y + sz.y); }
    wxSize operator-(const wxSize& sz) const { return wxSize(x - sz.x, y - sz.y); }
    wxSize operator/(int i) const { return wxSize(x / i, y / i); }
    wxSize operator*(int i) const { return wxSize(x * i, y * i); }

    wxSize& operator+=(const wxSize& sz) { x += sz.x; y += sz.y; return *this; }
    wxSize& operator-=(const wxSize& sz) { x -= sz.x; y -= sz.y; return *this; }
    wxSize& operator/=(const int i) { x /= i; y /= i; return *this; }
    wxSize& operator*=(const int i) { x *= i; y *= i; return *this; }

    void IncTo(const wxSize& sz)
        { if ( sz.x > x ) x = sz.x; if ( sz.y > y ) y = sz.y; }
    void DecTo(const wxSize& sz)
        { if ( sz.x < x ) x = sz.x; if ( sz.y < y ) y = sz.y; }

    void IncBy(int dx, int dy) { x += dx; y += dy; }
    void IncBy(const wxSize& sz) { IncBy(sz.x, sz.y); }
    void IncBy(int d) { IncBy(d, d); }

    void DecBy(int dx, int dy) { IncBy(-dx, -dy); }
    void DecBy(const wxSize& sz) { DecBy(sz.x, sz.y); }
    void DecBy(int d) { DecBy(d, d); }


    wxSize& Scale(float xscale, float yscale)
        { x = (int)(x*xscale); y = (int)(y*yscale); return *this; }

    // accessors
    void Set(int xx, int yy) { x = xx; y = yy; }
    void SetWidth(int w) { x = w; }
    void SetHeight(int h) { y = h; }

    int GetWidth() const { return x; }
    int GetHeight() const { return y; }

    bool IsFullySpecified() const { return x != wxDefaultCoord && y != wxDefaultCoord; }

    // combine this size with the other one replacing the default (i.e. equal
    // to wxDefaultCoord) components of this object with those of the other
    void SetDefaults(const wxSize& size)
    {
        if ( x == wxDefaultCoord )
            x = size.x;
        if ( y == wxDefaultCoord )
            y = size.y;
    }

    // compatibility
    int GetX() const { return x; }
    int GetY() const { return y; }
}; 

extern wxSize wxDefaultSize;

class /*WXDLLEXPORT*/ wxPoint
{
public:
    int x, y;

    wxPoint() : x(0), y(0) { }
    wxPoint(int xx, int yy) : x(xx), y(yy) { }

    // no copy ctor or assignment operator - the defaults are ok

    // comparison
    bool operator==(const wxPoint& p) const { return x == p.x && y == p.y; }
    bool operator!=(const wxPoint& p) const { return !(*this == p); }

    // arithmetic operations (component wise)
    wxPoint operator+(const wxPoint& p) const { return wxPoint(x + p.x, y + p.y); }
    wxPoint operator-(const wxPoint& p) const { return wxPoint(x - p.x, y - p.y); }

    wxPoint& operator+=(const wxPoint& p) { x += p.x; y += p.y; return *this; }
    wxPoint& operator-=(const wxPoint& p) { x -= p.x; y -= p.y; return *this; }

    wxPoint& operator+=(const wxSize& s) { x += s.GetWidth(); y += s.GetHeight(); return *this; }
    wxPoint& operator-=(const wxSize& s) { x -= s.GetWidth(); y -= s.GetHeight(); return *this; }

    wxPoint operator+(const wxSize& s) const { return wxPoint(x + s.GetWidth(), y + s.GetHeight()); }
    wxPoint operator-(const wxSize& s) const { return wxPoint(x - s.GetWidth(), y - s.GetHeight()); }

    wxPoint operator-() const { return wxPoint(-x, -y); }
};

// ---------------------------------------------------------------------------
// wxRect
// ---------------------------------------------------------------------------

class wxRect
{
public:
    wxRect()
        : x(0), y(0), width(0), height(0)
        { }
    wxRect(int xx, int yy, int ww, int hh)
        : x(xx), y(yy), width(ww), height(hh)
        { }
    wxRect(const wxPoint& topLeft, const wxPoint& bottomRight);
    wxRect(const wxPoint& pt, const wxSize& size)
        : x(pt.x), y(pt.y), width(size.x), height(size.y)
        { }
    wxRect(const wxSize& size)
        : x(0), y(0), width(size.x), height(size.y)
        { }

    // default copy ctor and assignment operators ok

    int GetX() const { return x; }
    void SetX(int xx) { x = xx; }

    int GetY() const { return y; }
    void SetY(int yy) { y = yy; }

    int GetWidth() const { return width; }
    void SetWidth(int w) { width = w; }

    int GetHeight() const { return height; }
    void SetHeight(int h) { height = h; }

    wxPoint GetPosition() const { return wxPoint(x, y); }
    void SetPosition( const wxPoint &p ) { x = p.x; y = p.y; }

    wxSize GetSize() const { return wxSize(width, height); }
    void SetSize( const wxSize &s ) { width = s.GetWidth(); height = s.GetHeight(); }

    bool IsEmpty() const { return (width <= 0) || (height <= 0); }

    int GetLeft()   const { return x; }
    int GetTop()    const { return y; }
    int GetBottom() const { return y + height - 1; }
    int GetRight()  const { return x + width - 1; }

    void SetLeft(int left) { x = left; }
    void SetRight(int right) { width = right - x + 1; }
    void SetTop(int top) { y = top; }
    void SetBottom(int bottom) { height = bottom - y + 1; }

    wxPoint GetTopLeft() const { return GetPosition(); }
    wxPoint GetLeftTop() const { return GetTopLeft(); }
    void SetTopLeft(const wxPoint &p) { SetPosition(p); }
    void SetLeftTop(const wxPoint &p) { SetTopLeft(p); }

    wxPoint GetBottomRight() const { return wxPoint(GetRight(), GetBottom()); }
    wxPoint GetRightBottom() const { return GetBottomRight(); }
    void SetBottomRight(const wxPoint &p) { SetRight(p.x); SetBottom(p.y); }
    void SetRightBottom(const wxPoint &p) { SetBottomRight(p); }

    wxPoint GetTopRight() const { return wxPoint(GetRight(), GetTop()); }
    wxPoint GetRightTop() const { return GetTopRight(); }
    void SetTopRight(const wxPoint &p) { SetRight(p.x); SetTop(p.y); }
    void SetRightTop(const wxPoint &p) { SetTopLeft(p); }

    wxPoint GetBottomLeft() const { return wxPoint(GetLeft(), GetBottom()); }
    wxPoint GetLeftBottom() const { return GetBottomLeft(); }
    void SetBottomLeft(const wxPoint &p) { SetLeft(p.x); SetBottom(p.y); }
    void SetLeftBottom(const wxPoint &p) { SetBottomLeft(p); }

    // operations with rect
    wxRect& Inflate(wxCoord dx, wxCoord dy);
    wxRect& Inflate(const wxSize& d) { return Inflate(d.x, d.y); }
    wxRect& Inflate(wxCoord d) { return Inflate(d, d); }
    wxRect Inflate(wxCoord dx, wxCoord dy) const
    {
        wxRect r = *this;
        r.Inflate(dx, dy);
        return r;
    }

    wxRect& Deflate(wxCoord dx, wxCoord dy) { return Inflate(-dx, -dy); }
    wxRect& Deflate(const wxSize& d) { return Inflate(-d.x, -d.y); }
    wxRect& Deflate(wxCoord d) { return Inflate(-d); }
    wxRect Deflate(wxCoord dx, wxCoord dy) const
    {
        wxRect r = *this;
        r.Deflate(dx, dy);
        return r;
    }

    void Offset(wxCoord dx, wxCoord dy) { x += dx; y += dy; }
    void Offset(const wxPoint& pt) { Offset(pt.x, pt.y); }

    wxRect& Intersect(const wxRect& rect);
    wxRect Intersect(const wxRect& rect) const
    {
        wxRect r = *this;
        r.Intersect(rect);
        return r;
    }

    wxRect& Union(const wxRect& rect);
    wxRect Union(const wxRect& rect) const
    {
        wxRect r = *this;
        r.Union(rect);
        return r;
    }

    // compare rectangles
    bool operator==(const wxRect& rect) const;
    bool operator!=(const wxRect& rect) const { return !(*this == rect); }

    // return true if the point is (not strcitly) inside the rect
    bool Contains(int x, int y) const;
    bool Contains(const wxPoint& pt) const { return Contains(pt.x, pt.y); }
    // return true if the rectangle is (not strcitly) inside the rect
    bool Contains(const wxRect& rect) const;

    // return true if the rectangles have a non empty intersection
    bool Intersects(const wxRect& rect) const;


    // these are like Union() but don't ignore empty rectangles
    wxRect operator+(const wxRect& rect) const;
    wxRect& operator+=(const wxRect& rect)
    {
        *this = *this + rect;
        return *this;
    }


    // centre this rectangle in the given (usually, but not necessarily,
    // larger) one
    wxRect CentreIn(const wxRect& r, int dir = wxBOTH) const
    {
        return wxRect(dir & wxHORIZONTAL ? r.x + (r.width - width)/2 : x,
                      dir & wxVERTICAL ? r.y + (r.height - height)/2 : y,
                      width, height);
    }

    wxRect CenterIn(const wxRect& r, int dir = wxBOTH) const
    {
        return CentreIn(r, dir);
    }

public:
    int x, y, width, height;
};

} // end of namespace libsizer

#endif
