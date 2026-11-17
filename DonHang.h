#ifndef DONHANG_H_INCLUDED_
#define DONHANG_H_INCLUDED_

#include <string>

#include "ChiTietDon.h"
#include "DanhSach.h"

enum TrangThaiDon
{
    CHO_XU_LY = 0,
    DA_XU_LY = 1,
    DA_HUY = 2
};

class DonHang
{
private:

    int _iSoThuTu;
    TrangThaiDon _eTrangThai;

    std::string _strTenKhach;
    std::string _strDiaChi;
    std::string _strSoDienThoai;
    std::string _strNgayDat;

    long long _lTongTien;
    DanhSach<ChiTietDon> _dsChiTiet;


public:

    DonHang(const int iSoThuTu = 0, const TrangThaiDon eTrangThai = CHO_XU_LY, const std::string& strTenKhach = "", const std::string& strDiaChi = "", const std::string& strSoDienThoai = "", const std::string& strNgayDat = "", const long long lTongTien = 0);
    DonHang(const DonHang& donHang);

    ~DonHang();

    int getSoThuTu() const;
    TrangThaiDon getTrangThai() const;
    std::string getTenKhach() const;
    std::string getDiaChi() const;
    std::string getSoDienThoai() const;
    std::string getNgayDat() const;
    long long getTongTien() const;
    const DanhSach<ChiTietDon>& getDanhSachChiTiet() const;

    void setSoThuTu(const int iSoThuTu);
    void setTrangThai(const TrangThaiDon eTrangThai);
    void setThongTinKhach(const std::string& strTenKhach, const std::string& strDiaChi, const std::string& strSoDienThoai, const std::string& strNgayDat);

    bool coMaHang(const std::string& strMaHang) const;
    
    void themChiTiet(const ChiTietDon& chiTiet);

    void capNhatTongTien();

    std::string chuyenThanhDong() const;

    bool docTuDong(const std::string& strDong);

    void hienThi() const;
};

#endif