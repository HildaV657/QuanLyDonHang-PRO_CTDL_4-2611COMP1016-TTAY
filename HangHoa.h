#ifndef HANGHOA_H_INCLUDED_
#define HANGHOA_H_INCLUDED_

#include <string>

class HangHoa
{
private:
    std::string _strMaHang;
    std::string _strTenHang;
    std::string _strNoiSanXuat;
    std::string _strMauSac;
    long long _lGiaBan;
    std::string _strNgayNhapKho;
    int _iSoLuong;

public:
    HangHoa(const std::string& strMaHang = "", const std::string& strTenHang = "",
        const std::string& strNoiSanXuat = "", const std::string& strMauSac = "",
        const long long lGiaBan = 0, const std::string& strNgayNhapKho = "", const int iSoLuong = 0);
    HangHoa(const HangHoa& hangHoa);
    ~HangHoa();

    std::string getMaHang() const;
    std::string getTenHang() const;
    long long getGiaBan() const;
    int getSoLuong() const;
    void setSoLuong(const int iSoLuong);

    std::string chuyenThanhDong() const;
    bool docTuDong(const std::string& strDong);
    void hienThi() const;
    static void hienThiTieuDe();
};

#endif