#include "HangHoa.h"
#include "TienIch.h"
#include <iostream>
#include <vector>

using namespace std;

/**********************************************************
* @Description 7 trường thông tin: Ma, Ten, NoiSX, MauSac, Gia, NgayNhap, SoLuong
**********************************************************/
const size_t SO_TRUONG_HANG_HOA = 7;

/**********************************************************
* @Description Vị trí các trường trong một dòng của file
**********************************************************/
const size_t VI_TRI_MA_HANG = 0;
const size_t VI_TRI_TEN_HANG = 1;
const size_t VI_TRI_NOI_SAN_XUAT = 2;
const size_t VI_TRI_MAU_SAC = 3;
const size_t VI_TRI_GIA_BAN = 4;
const size_t VI_TRI_NGAY_NHAP_KHO = 5;
const size_t VI_TRI_SO_LUONG = 6;

/**********************************************************
* @Description Độ rộng các cột khi in bảng hàng hóa
**********************************************************/
const int DO_RONG_MA_HANG = 9;
const int DO_RONG_TEN_HANG = 32;
const int DO_RONG_NOI_SAN_XUAT = 16;
const int DO_RONG_MAU_SAC = 12;
const int DO_RONG_GIA_BAN = 14;
const int DO_RONG_NGAY_NHAP_KHO = 12;
const size_t DO_DAI_DUONG_KE = 106;

HangHoa::HangHoa(const string& strMaHang, const string& strTenHang,
    const string& strNoiSanXuat, const string& strMauSac,
    const long long lGiaBan, const string& strNgayNhapKho, const int iSoLuong)
    : _strMaHang(strMaHang), _strTenHang(strTenHang), _strNoiSanXuat(strNoiSanXuat),
    _strMauSac(strMauSac), _lGiaBan(lGiaBan), _strNgayNhapKho(strNgayNhapKho), _iSoLuong(iSoLuong)
{}

HangHoa::HangHoa(const HangHoa& hangHoa)
    : _strMaHang(hangHoa._strMaHang), _strTenHang(hangHoa._strTenHang), _strNoiSanXuat(hangHoa._strNoiSanXuat),
    _strMauSac(hangHoa._strMauSac), _lGiaBan(hangHoa._lGiaBan), _strNgayNhapKho(hangHoa._strNgayNhapKho), _iSoLuong(hangHoa._iSoLuong)
{}

HangHoa::~HangHoa() {}

string HangHoa::getMaHang() const
{
    return this->_strMaHang;
}

string HangHoa::getTenHang() const
{
    return this->_strTenHang;
}

long long HangHoa::getGiaBan() const
{
    return this->_lGiaBan;
}

int HangHoa::getSoLuong() const
{
    return this->_iSoLuong;
}

void HangHoa::setSoLuong(const int iSoLuong)
{
    this->_iSoLuong = iSoLuong;
}

/**********************************************************
* @Description Chuyển hàng hóa thành một dòng để ghi file
* @attention Định dạng: Ma|Ten|NoiSX|MauSac|Gia|NgayNhap|SoLuong
**********************************************************/
string HangHoa::chuyenThanhDong() const
{
    return this->_strMaHang + DAU_NGAN_CACH + this->_strTenHang + DAU_NGAN_CACH + this->_strNoiSanXuat + DAU_NGAN_CACH + this->_strMauSac + DAU_NGAN_CACH + to_string(this->_lGiaBan) + DAU_NGAN_CACH + this->_strNgayNhapKho + DAU_NGAN_CACH + to_string(this->_iSoLuong);
}

/**********************************************************
* @Description Đọc hàng hóa từ một dòng của file
* @return false nếu dòng sai định dạng
**********************************************************/
bool HangHoa::docTuDong(const string& strDong)
{
    vector<string> vecTruong = TienIch::tach(strDong, DAU_NGAN_CACH);
    if (vecTruong.size() != SO_TRUONG_HANG_HOA || !TienIch::laSoNguyen(vecTruong[VI_TRI_GIA_BAN]) || !TienIch::laSoNguyen(vecTruong[VI_TRI_SO_LUONG]))
    {
        return false;
    }
    this->_strMaHang = vecTruong[VI_TRI_MA_HANG];
    this->_strTenHang = vecTruong[VI_TRI_TEN_HANG];
    this->_strNoiSanXuat = vecTruong[VI_TRI_NOI_SAN_XUAT];
    this->_strMauSac = vecTruong[VI_TRI_MAU_SAC];
    this->_lGiaBan = stoll(vecTruong[VI_TRI_GIA_BAN]);
    this->_strNgayNhapKho = vecTruong[VI_TRI_NGAY_NHAP_KHO];
    this->_iSoLuong = stoi(vecTruong[VI_TRI_SO_LUONG]);
    return true;
}

/**********************************************************
* @Description In dòng tiêu đề của bảng hàng hóa kèm đường kẻ ngang bên dưới
**********************************************************/
void HangHoa::hienThiTieuDe()
{
    TienIch::datMau(MAU_VANG);
    cout << TienIch::canTrai("Mã hàng", DO_RONG_MA_HANG) 
        << TienIch::canTrai("Tên hàng", DO_RONG_TEN_HANG) 
        << TienIch::canTrai("Nơi sản xuất", DO_RONG_NOI_SAN_XUAT) 
        << TienIch::canTrai("Màu sắc", DO_RONG_MAU_SAC) 
        << TienIch::canTrai("Giá bán", DO_RONG_GIA_BAN) 
        << TienIch::canTrai("Ngày nhập", DO_RONG_NGAY_NHAP_KHO) 
        << "Số lượng" << endl;
    cout << string(DO_DAI_DUONG_KE, '-') << endl;
    TienIch::datMau(MAU_MAC_DINH);
}

/**********************************************************
* @Description In một dòng thông tin hàng hóa, thẳng cột với dòng tiêu đề
*               của hienThiTieuDe
**********************************************************/
void HangHoa::hienThi() const
{
    TienIch::datMau(MAU_XANH_DUONG);
    cout << TienIch::canTrai(this->_strMaHang, DO_RONG_MA_HANG);
    TienIch::datMau(MAU_MAC_DINH);
    cout << TienIch::canTrai(this->_strTenHang, DO_RONG_TEN_HANG) 
        << TienIch::canTrai(this->_strNoiSanXuat, DO_RONG_NOI_SAN_XUAT) 
        << TienIch::canTrai(this->_strMauSac, DO_RONG_MAU_SAC) 
        << TienIch::canTrai(TienIch::dinhDangTien(this->_lGiaBan), DO_RONG_GIA_BAN) 
        << TienIch::canTrai(this->_strNgayNhapKho, DO_RONG_NGAY_NHAP_KHO) 
        << this->_iSoLuong << endl;
}