#include "DonHang.h"
#include "TienIch.h"

#include <exception>
#include <iostream>
#include <vector>

using namespace std;

const size_t SO_TRUONG_CO_DINH = 8;
const size_t SO_TRUONG_MOI_CHI_TIET = 3;

/**********************************************************
* @Description Vị trí các trường cố định trong một dòng của file
**********************************************************/
const size_t VI_TRI_SO_THU_TU = 0;
const size_t VI_TRI_TRANG_THAI = 1;
const size_t VI_TRI_TEN_KHACH = 2;
const size_t VI_TRI_DIA_CHI = 3;
const size_t VI_TRI_SO_DIEN_THOAI = 4;
const size_t VI_TRI_NGAY_DAT = 5;
const size_t VI_TRI_TONG_TIEN = 6;
const size_t VI_TRI_SO_CHI_TIET = 7;

/**********************************************************
* @Description Vị trí các trường trong mỗi chi tiết, tính từ đầu chi tiết
**********************************************************/
const size_t VI_TRI_CT_MA_HANG = 0;
const size_t VI_TRI_CT_SO_LUONG = 1;
const size_t VI_TRI_CT_THANH_TIEN = 2;

DonHang::DonHang(const int iSoThuTu, const TrangThaiDon eTrangThai, const string& strTenKhach, const string& strDiaChi, const string& strSoDienThoai, const string& strNgayDat, const long long lTongTien)
    : _iSoThuTu(iSoThuTu), _eTrangThai(eTrangThai), _strTenKhach(strTenKhach), _strDiaChi(strDiaChi), _strSoDienThoai(strSoDienThoai), _strNgayDat(strNgayDat), _lTongTien(lTongTien)
{}

DonHang::DonHang(const DonHang& donHang)
    : _iSoThuTu(donHang._iSoThuTu), _eTrangThai(donHang._eTrangThai), _strTenKhach(donHang._strTenKhach), _strDiaChi(donHang._strDiaChi), _strSoDienThoai(donHang._strSoDienThoai), _strNgayDat(donHang._strNgayDat), _lTongTien(donHang._lTongTien), _dsChiTiet(donHang._dsChiTiet)
{}

DonHang::~DonHang() {}

int DonHang::getSoThuTu() const
{
    return this->_iSoThuTu;
}

TrangThaiDon DonHang::getTrangThai() const
{
    return this->_eTrangThai;
}

string DonHang::getTenKhach() const
{
    return this->_strTenKhach;
}

string DonHang::getDiaChi() const
{
    return this->_strDiaChi;
}

string DonHang::getSoDienThoai() const
{
    return this->_strSoDienThoai;
}

string DonHang::getNgayDat() const
{
    return this->_strNgayDat;
}

long long DonHang::getTongTien() const
{
    return this->_lTongTien;
}

const DanhSach<ChiTietDon>& DonHang::getDanhSachChiTiet() const
{
    return this->_dsChiTiet;
}

void DonHang::setSoThuTu(const int iSoThuTu)
{
    if (iSoThuTu >= 0)
    {
        this->_iSoThuTu = iSoThuTu;
    }
}

void DonHang::setTrangThai(const TrangThaiDon eTrangThai)
{
    if (eTrangThai >= CHO_XU_LY && eTrangThai <= DA_HUY)
    {
        this->_eTrangThai = eTrangThai;
    }
}

void DonHang::setThongTinKhach(const string& strTenKhach, const string& strDiaChi, const string& strSoDienThoai, const string& strNgayDat)
{
    this->_strTenKhach = strTenKhach;
    this->_strDiaChi = strDiaChi;
    this->_strSoDienThoai = strSoDienThoai;
    this->_strNgayDat = strNgayDat;
}

bool DonHang::coMaHang(const string& strMaHang) const
{
    string strMaCanTim = TienIch::chuThuong(strMaHang);

    for (int iIndex = 0; iIndex < this->_dsChiTiet.getSize(); iIndex++)
    {
        const ChiTietDon* pChiTiet = this->_dsChiTiet.layTaiViTri(iIndex);
        if (TienIch::chuThuong(pChiTiet->getMaHang()) == strMaCanTim)
        {
            return true;
        }
    }
    return false;
}

void DonHang::themChiTiet(const ChiTietDon& chiTiet)
{
    this->_dsChiTiet.themCuoi(chiTiet);

    this->capNhatTongTien();
}

void DonHang::capNhatTongTien()
{
    this->_lTongTien = 0;

    for (int iIndex = 0; iIndex < this->_dsChiTiet.getSize(); iIndex++)
    {
        const ChiTietDon* pChiTiet = this->_dsChiTiet.layTaiViTri(iIndex);
        this->_lTongTien += pChiTiet->getThanhTien();
    }
}

string DonHang::chuyenThanhDong() const
{
    string strDong = "";

    strDong = to_string(this->_iSoThuTu)
        + DAU_NGAN_CACH
        + to_string(static_cast<int>(this->_eTrangThai))
        + DAU_NGAN_CACH
        + this->_strTenKhach
        + DAU_NGAN_CACH
        + this->_strDiaChi
        + DAU_NGAN_CACH
        + this->_strSoDienThoai
        + DAU_NGAN_CACH
        + this->_strNgayDat
        + DAU_NGAN_CACH
        + to_string(this->_lTongTien)
        + DAU_NGAN_CACH
        + to_string(this->_dsChiTiet.getSize());

    for (int iIndex = 0; iIndex < this->_dsChiTiet.getSize(); iIndex++)
    {
        const ChiTietDon* pChiTiet = this->_dsChiTiet.layTaiViTri(iIndex);
        strDong += DAU_NGAN_CACH
            + pChiTiet->getMaHang()
            + DAU_NGAN_CACH
            + to_string(pChiTiet->getSoLuong())
            + DAU_NGAN_CACH
            + to_string(pChiTiet->getThanhTien());
    }

    return strDong;
}

bool DonHang::docTuDong(const string& strDong)
{
    vector<string> vecTruong = TienIch::tach(strDong, DAU_NGAN_CACH);

    if (vecTruong.size() < SO_TRUONG_CO_DINH)
    {
        return false;
    }

    try
    {
        int iSoThuTu = stoi(vecTruong[VI_TRI_SO_THU_TU]);
        int iTrangThai = stoi(vecTruong[VI_TRI_TRANG_THAI]);
        long long lTongTien = stoll(vecTruong[VI_TRI_TONG_TIEN]);
        int iSoChiTiet = stoi(vecTruong[VI_TRI_SO_CHI_TIET]);

        bool bGiaTriHopLe = iSoThuTu >= 0 && lTongTien >= 0 && iSoChiTiet >= 0
            && iTrangThai >= CHO_XU_LY && iTrangThai <= DA_HUY;
        size_t iSoTruongCanCo = SO_TRUONG_CO_DINH + SO_TRUONG_MOI_CHI_TIET * static_cast<size_t>(iSoChiTiet);

        if (!bGiaTriHopLe || vecTruong.size() != iSoTruongCanCo)
        {
            return false;
        }

        DanhSach<ChiTietDon> dsTam;
        long long lTongTienTinhDuoc = 0;

        for (int iIndex = 0; iIndex < iSoChiTiet; iIndex++)
        {
            size_t iViTri = SO_TRUONG_CO_DINH + iIndex * SO_TRUONG_MOI_CHI_TIET;
            string strMaHang = vecTruong[iViTri + VI_TRI_CT_MA_HANG];
            int iSoLuong = stoi(vecTruong[iViTri + VI_TRI_CT_SO_LUONG]);
            long long lThanhTien = stoll(vecTruong[iViTri + VI_TRI_CT_THANH_TIEN]);

            if (iSoLuong <= 0 || lThanhTien < 0)
            {
                return false;
            }
            dsTam.themCuoi(ChiTietDon(strMaHang, iSoLuong, lThanhTien));
            lTongTienTinhDuoc += lThanhTien;
        }

        if (lTongTienTinhDuoc != lTongTien)
        {
            return false;
        }

        this->_iSoThuTu = iSoThuTu;
        this->_eTrangThai = static_cast<TrangThaiDon>(iTrangThai);
        this->setThongTinKhach(vecTruong[VI_TRI_TEN_KHACH], vecTruong[VI_TRI_DIA_CHI], vecTruong[VI_TRI_SO_DIEN_THOAI], vecTruong[VI_TRI_NGAY_DAT]);
        this->_dsChiTiet = dsTam;
        this->_lTongTien = lTongTienTinhDuoc;
    }
    catch (const exception&)
    {
        return false;
    }

    return true;
}

void DonHang::hienThi() const
{
    string strTrangThai = "Đang chờ xử lý";

    switch (this->_eTrangThai)
    {
    case DA_XU_LY:
        strTrangThai = "Đã xử lý";
        break;

    case DA_HUY:
        strTrangThai = "Đã hủy (không đủ hàng)";
        break;

    default:
        break;
    }

    TienIch::datMau(MAU_XANH_DUONG);

    cout << "Đơn hàng số " << this->_iSoThuTu << " - " << strTrangThai << endl;

    TienIch::datMau(MAU_MAC_DINH);

    cout << "Khách hàng : " << this->_strTenKhach << endl;
    cout << "Địa chỉ    : " << this->_strDiaChi << endl;
    cout << "Điện thoại : " << this->_strSoDienThoai << endl;
    cout << "Ngày đặt   : " << this->_strNgayDat << endl;

    for (int iIndex = 0; iIndex < this->_dsChiTiet.getSize(); iIndex++)
    {
        const ChiTietDon* pChiTiet = this->_dsChiTiet.layTaiViTri(iIndex);
        cout << "  - Mã hàng " << pChiTiet->getMaHang() << ", số lượng " << pChiTiet->getSoLuong() << ", thành tiền " << TienIch::dinhDangTien(pChiTiet->getThanhTien()) << endl;
    }

    cout << "Tổng tiền  : " << TienIch::dinhDangTien(this->_lTongTien) << endl;
}