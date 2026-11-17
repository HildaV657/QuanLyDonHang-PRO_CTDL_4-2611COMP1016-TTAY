#include <exception>
#include <fstream>
#include <iostream>
#include <string>

#include "QuanLyBanHang.h"
#include "TienIch.h"

using namespace std;

const string FILE_HANG_HOA = "HangHoa.txt";
const string FILE_DON_HANG = "DonHang.txt";
const string FILE_ADMIN = "Admin.txt";
const string ADMIN_MAC_DINH = "admin";
const string MAT_KHAU_MAC_DINH = "123456";
const int SO_THU_TU_DAU_TIEN = 1;

// Các lựa chọn của từng menu
enum class MenuChinh
{
	KHONG_HOP_LE = -1,
	THOAT = 0,
	HIEN_THI_HANG_HOA = 1,
	TIM_KIEM_HANG_HOA = 2,
	DAT_HANG = 3,
	QUAN_LY = 4
};

template <class TMenu>
static TMenu chuyenSangMenu(const string& strNhap, const TMenu eNhoNhat, const TMenu eLonNhat)
{
	try
	{
		const int iLuaChon = stoi(strNhap);
		const bool bTrongMenu = iLuaChon >= static_cast<int>(eNhoNhat)
			&& iLuaChon <= static_cast<int>(eLonNhat);
		if (bTrongMenu && to_string(iLuaChon) == strNhap)
		{
			return static_cast<TMenu>(iLuaChon);
		}
	}
	catch (const exception&)
	{

	}
	return TMenu::KHONG_HOP_LE;
}
template <class T>
static void docDanhSachTuFile(const string& strTenFile, DanhSach<T>& danhSach)
{
	ifstream ifsFile(strTenFile);
	string strDong;
	while (getline(ifsFile, strDong))
	{
		strDong = TienIch::catKhoangTrang(strDong);
		T phanTu;
		if (!strDong.empty() && phanTu.docTuDong(strDong))
		{
			danhSach.themCuoi(phanTu);
		}
	}
	ifsFile.close();
}
template <class T>
static void ghiDanhSachRaFile(const string& strTenFile, const DanhSach<T>& danhSach)
{
	ofstream ofsFile(strTenFile);
	if (!ofsFile.is_open())
	{
		TienIch::inLoi("Không ghi được file " + strTenFile + ".");
		return;
	}
	for (int iIndex = 0; iIndex < danhSach.getSize(); iIndex++)
	{
		ofsFile << danhSach.layTaiViTri(iIndex)->chuyenThanhDong() << endl;
	}
	ofsFile.close();
}

QuanLyBanHang::QuanLyBanHang() : _iSoThuTuTiepTheo(SO_THU_TU_DAU_TIEN), _bDangChay(true)
{
	this->docFileHangHoa();
	this->docFileDonHang();
	this->docFileAdmin();
}

void QuanLyBanHang::chay()
{
	while (this->_bDangChay)
	{
		this->hienThiMenuChinh();
		const MenuChinh eLuaChon = chuyenSangMenu(TienIch::docLuaChon("Chọn chức năng: "),
			MenuChinh::THOAT, MenuChinh::QUAN_LY);
		switch (eLuaChon)
		{
			case MenuChinh::HIEN_THI_HANG_HOA:
				this->hienThiHangHoa();
				break;
			case MenuChinh::TIM_KIEM_HANG_HOA:
				this->timKiemHangHoa();
				break;
			case MenuChinh::DAT_HANG:
				this->datHang();
				break;
			case MenuChinh::QUAN_LY:
				this->quanLy();
				break;
			case MenuChinh::THOAT:
				this->_bDangChay = false;
				break;
			default:
				TienIch::inLoi("Lựa chọn không hợp lệ.");
				break;
		}
		if (this->_bDangChay)
		{
			TienIch::tamDung();
		}
	}
	TienIch::inThongBao("Kết thúc chương trình.", MAU_VANG);
}

// ==================== Đọc / ghi file ====================

void QuanLyBanHang::docFileHangHoa()
{
	docDanhSachTuFile(FILE_HANG_HOA, this->_danhSachHangHoa);
}
void QuanLyBanHang::docFileDonHang()
{
	ifstream ifsFile(FILE_DON_HANG);
	string strDong;
	while (getline(ifsFile, strDong))
	{
		strDong = TienIch::catKhoangTrang(strDong);
		DonHang donHang;
		if (strDong.empty() || !donHang.docTuDong(strDong))
		{
			continue;
		}
		this->_danhSachDonHang.themCuoi(donHang);
		if (donHang.getTrangThai() == CHO_XU_LY)
		{
			this->_hangDoiChoXuLy.enqueue(donHang.getSoThuTu());
		}
		if (donHang.getSoThuTu() >= this->_iSoThuTuTiepTheo)
		{
			this->_iSoThuTuTiepTheo = donHang.getSoThuTu() + 1;
		}
	}
	ifsFile.close();
}
void QuanLyBanHang::docFileAdmin()
{
	docDanhSachTuFile(FILE_ADMIN, this->_danhSachAdmin);
	if (this->_danhSachAdmin.isEmpty())
	{
		this->_danhSachAdmin.themCuoi(Admin(ADMIN_MAC_DINH, MAT_KHAU_MAC_DINH));
		this->ghiFileAdmin();
	}
}
void QuanLyBanHang::ghiFileHangHoa() const
{
	ghiDanhSachRaFile(FILE_HANG_HOA, this->_danhSachHangHoa);
}
void QuanLyBanHang::ghiFileDonHang() const
{
	ghiDanhSachRaFile(FILE_DON_HANG, this->_danhSachDonHang);
}
void QuanLyBanHang::ghiFileAdmin() const
{
	ghiDanhSachRaFile(FILE_ADMIN, this->_danhSachAdmin);
}

// ==================== Tìm kiếm nội bộ ====================
HangHoa* QuanLyBanHang::timHangHoa(const string& strMaHang)
{
	const QuanLyBanHang* pDoiTuongConst = this;
	return const_cast<HangHoa*>(pDoiTuongConst->timHangHoa(strMaHang));
}

const HangHoa* QuanLyBanHang::timHangHoa(const string& strMaHang) const
{
	const string strMaThuong = TienIch::chuThuong(strMaHang);
	for (int iIndex = 0; iIndex < this->_danhSachHangHoa.getSize(); iIndex++)
	{
		const HangHoa* pHangHoa = this->_danhSachHangHoa.layTaiViTri(iIndex);
		if (TienIch::chuThuong(pHangHoa->getMaHang()) == strMaThuong)
		{
			return pHangHoa;
		}
	}
	return nullptr;
}
DonHang* QuanLyBanHang::timDonHang(const int iSoThuTu)
{
	const QuanLyBanHang* pDoiTuongConst = this;
	return const_cast<DonHang*>(pDoiTuongConst->timDonHang(iSoThuTu));
}

const DonHang* QuanLyBanHang::timDonHang(const int iSoThuTu) const
{
	for (int iIndex = 0; iIndex < this->_danhSachDonHang.getSize(); iIndex++)
	{
		const DonHang* pDonHang = this->_danhSachDonHang.layTaiViTri(iIndex);
		if (pDonHang->getSoThuTu() == iSoThuTu)
		{
			return pDonHang;
		}
	}
	return nullptr;
}

// ==================== Menu chính ====================

void QuanLyBanHang::hienThiMenuChinh() const
{
	TienIch::xoaManHinh();
	TienIch::inThongBao("********** WEBSITE BÁN HÀNG ONLINE **********", MAU_VANG);
	TienIch::inThongBao("  1. Hiển thị thông tin hàng hóa", MAU_TRANG);
	TienIch::inThongBao("  2. Tìm kiếm thông tin hàng hóa", MAU_TRANG);
	TienIch::inThongBao("  3. Đặt hàng", MAU_TRANG);
	TienIch::inThongBao("  4. Quản lý", MAU_TRANG);
	TienIch::inThongBao("  0. Thoát chương trình", MAU_TRANG);
	TienIch::inThongBao("*********************************************", MAU_VANG);
}

void QuanLyBanHang::hienThiHangHoa() const
{
	TienIch::xoaManHinh();
	TienIch::inThongBao("=== DANH SÁCH HÀNG HÓA ===", MAU_VANG);
	if (this->_danhSachHangHoa.isEmpty())
	{
		TienIch::inThongBao("Hiện chưa có hàng hóa nào.", MAU_DO);
		return;
	}
	HangHoa::hienThiTieuDe();
	for (int iIndex = 0; iIndex < this->_danhSachHangHoa.getSize(); iIndex++)
	{
		this->_danhSachHangHoa.layTaiViTri(iIndex)->hienThi();
	}
}
void QuanLyBanHang::timKiemHangHoa() const
{
	TienIch::xoaManHinh();
	TienIch::inThongBao("=== TÌM KIẾM HÀNG HÓA ===", MAU_VANG);
	string strTuKhoa;
	if (!TienIch::docChuoi("Nhập tên hàng cần tìm: ", strTuKhoa))
	{
		return;
	}
	const string strTuKhoaThuong = TienIch::chuThuong(strTuKhoa);
	int iSoKetQua = 0;
	for (int iIndex = 0; iIndex < this->_danhSachHangHoa.getSize(); iIndex++)
	{
		const HangHoa* pHangHoa = this->_danhSachHangHoa.layTaiViTri(iIndex);
		if (TienIch::chuThuong(pHangHoa->getTenHang()).find(strTuKhoaThuong) == string::npos)
		{
			continue;
		}
		if (iSoKetQua == 0)
		{
			HangHoa::hienThiTieuDe();
		}
		pHangHoa->hienThi();
		++iSoKetQua;
	}
	if (iSoKetQua == 0)
	{
		TienIch::inLoi("Không tìm thấy hàng hóa nào có tên \"" + strTuKhoa + "\".");
	}
}