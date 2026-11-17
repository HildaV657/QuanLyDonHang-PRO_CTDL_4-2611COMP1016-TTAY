#include "ChiTietDon.h"

using namespace std;

ChiTietDon::ChiTietDon(const string& strMaHang, const int iSoLuong, const long long lThanhTien)
    : _strMaHang(strMaHang), _iSoLuong(iSoLuong), _lThanhTien(lThanhTien)
{}

ChiTietDon::ChiTietDon(const ChiTietDon& chiTiet)
    : _strMaHang(chiTiet._strMaHang), _iSoLuong(chiTiet._iSoLuong), _lThanhTien(chiTiet._lThanhTien)
{}

ChiTietDon::~ChiTietDon() {}

string ChiTietDon::getMaHang() const
{
    return this->_strMaHang;
}
int ChiTietDon::getSoLuong() const
{
    return this->_iSoLuong;
}
long long ChiTietDon::getThanhTien() const
{
    return this->_lThanhTien;
}