#ifndef CHITIETDON_H_INCLUDED_
#define CHITIETDON_H_INCLUDED_

#include <string>

class ChiTietDon
{
private:
    std::string _strMaHang;
    int _iSoLuong;
    long long _lThanhTien;

public:
    ChiTietDon(const std::string& strMaHang = "", const int iSoLuong = 0, const long long lThanhTien = 0);
    ChiTietDon(const ChiTietDon& chiTiet);

    ~ChiTietDon();

    std::string getMaHang() const;
    int getSoLuong() const;
    long long getThanhTien() const;
};

#endif