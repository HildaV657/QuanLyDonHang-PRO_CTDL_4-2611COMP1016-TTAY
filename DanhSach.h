#ifndef DANHSACH_H_INCLUDED_
#define DANHSACH_H_INCLUDED_

template <class T>
class DanhSach
{
private:
	class Node
	{
	private:
		T _data;
		Node* _pNext;

	public:
		Node(const T& data) : _data(data), _pNext(nullptr)
		{
		}

		T& getData()
		{
			return this->_data;
		}

		const T& getData() const
		{
			return this->_data;
		}

		Node* getNext() const
		{
			return this->_pNext;
		}

		void setNext(Node* pNext)
		{
			this->_pNext = pNext;
		}
	};

	Node* _pHead;
	Node* _pTail;
	int _iSize;

	void sao(const DanhSach& other)
	{
		for (Node* pNode = other._pHead; pNode != nullptr; pNode = pNode->getNext())
		{
			this->themCuoi(pNode->getData());
		}
	}

public:

	DanhSach() : _pHead(nullptr), _pTail(nullptr), _iSize(0)
	{
	}

	DanhSach(const DanhSach& other) : _pHead(nullptr), _pTail(nullptr), _iSize(0)
	{
		this->sao(other);
	}

	~DanhSach()
	{
		this->xoaTatCa();
	}
	DanhSach& operator=(const DanhSach& other)
	{
		if (this != &other)
		{
			this->xoaTatCa();
			this->sao(other);
		}
		return *this;
	}

	void themCuoi(const T& data)
	{
		Node* pNew = new Node(data);
		if (this->_pHead == nullptr)
		{
			this->_pHead = pNew;
		}
		else
		{
			this->_pTail->setNext(pNew);
		}
		this->_pTail = pNew;
		++this->_iSize;
	}

	bool xoaTaiViTri(const int iViTri)
	{
		if (iViTri < 0 || iViTri >= this->_iSize)
		{
			return false;
		}
		Node* pPrev = nullptr;
		Node* pCurrent = this->_pHead;
		for (int iIndex = 0; iIndex < iViTri; ++iIndex)
		{
			pPrev = pCurrent;
			pCurrent = pCurrent->getNext();
		}
		if (pPrev == nullptr)
		{
			this->_pHead = pCurrent->getNext();
		}
		else
		{
			pPrev->setNext(pCurrent->getNext());
		}
		if (pCurrent == this->_pTail)
		{
			this->_pTail = pPrev;
		}
		delete pCurrent;
		--this->_iSize;
		return true;
	}

	template <class TDieuKien>
	T* timDau(TDieuKien dieuKien)
	{
		for (Node* pNode = this->_pHead; pNode != nullptr; pNode = pNode->getNext())
		{
			if (dieuKien(pNode->getData()))
			{
				return &pNode->getData();
			}
		}
		return nullptr;
	}

	template <class TDieuKien>
	const T* timDau(TDieuKien dieuKien) const
	{
		return const_cast<DanhSach*>(this)->timDau(dieuKien);
	}

	template <class TDieuKien>
	int timViTri(TDieuKien dieuKien) const
	{
		int iViTri = 0;
		for (const Node* pNode = this->_pHead; pNode != nullptr; pNode = pNode->getNext())
		{
			if (dieuKien(pNode->getData()))
			{
				return iViTri;
			}
			++iViTri;
		}
		return -1;
	}

	template <class THanhDong>
	void duyet(THanhDong hanhDong)
	{
		for (Node* pNode = this->_pHead; pNode != nullptr; pNode = pNode->getNext())
		{
			hanhDong(pNode->getData());
		}
	}

	template <class THanhDong>
	void duyet(THanhDong hanhDong) const
	{
		for (const Node* pNode = this->_pHead; pNode != nullptr; pNode = pNode->getNext())
		{
			hanhDong(pNode->getData());
		}
	}

	T* layTaiViTri(const int iViTri)
	{
		if (iViTri < 0 || iViTri >= this->_iSize)
		{
			return nullptr;
		}
		Node* pNode = this->_pHead;
		for (int iIndex = 0; iIndex < iViTri; ++iIndex)
		{
			pNode = pNode->getNext();
		}
		return &pNode->getData();
	}

	const T* layTaiViTri(const int iViTri) const
	{
		return const_cast<DanhSach*>(this)->layTaiViTri(iViTri);
	}

	T* layDau()
	{
		return (this->_pHead == nullptr) ? nullptr : &this->_pHead->getData();
	}

	const T* layDau() const
	{
		return const_cast<DanhSach*>(this)->layDau();
	}

	int getSize() const
	{
		return this->_iSize;
	}

	bool isEmpty() const
	{
		return this->_iSize == 0;
	}

	void xoaTatCa()
	{
		while (this->_pHead != nullptr)
		{
			Node* pNext = this->_pHead->getNext();
			delete this->_pHead;
			this->_pHead = pNext;
		}
		this->_pTail = nullptr;
		this->_iSize = 0;
	}
};

#endif
