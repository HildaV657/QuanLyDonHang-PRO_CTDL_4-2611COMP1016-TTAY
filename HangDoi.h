#ifndef HANGDOI_H_INCLUDED_
#define HANGDOI_H_INCLUDED_

#include "DanhSach.h"

template <class T>
class HangDoi
{
private:
	DanhSach<T> _danhSachPhanTu;

public:
	void enqueue(const T& data)
	{
		this->_danhSachPhanTu.themCuoi(data);
	}

	bool dequeue()
	{
		return this->_danhSachPhanTu.xoaTaiViTri(0);
	}

	T* front()
	{
		return this->_danhSachPhanTu.layDau();
	}

	const T* front() const
	{
		return this->_danhSachPhanTu.layDau();
	}


	template <class TDieuKien>
	T* timDau(TDieuKien dieuKien)
	{
		return this->_danhSachPhanTu.timDau(dieuKien);
	}

	template <class TDieuKien>
	const T* timDau(TDieuKien dieuKien) const
	{
		return this->_danhSachPhanTu.timDau(dieuKien);
	}

	template <class THanhDong>
	void duyet(THanhDong hanhDong)
	{
		this->_danhSachPhanTu.duyet(hanhDong);
	}

	template <class THanhDong>
	void duyet(THanhDong hanhDong) const
	{
		this->_danhSachPhanTu.duyet(hanhDong);
	}

	bool isEmpty() const
	{
		return this->_danhSachPhanTu.isEmpty();
	}

	int getSize() const
	{
		return this->_danhSachPhanTu.getSize();
	}

	void xoaTatCa()
	{
		this->_danhSachPhanTu.xoaTatCa();
	}
};

#endif