#ifndef DANHSACH_H_INCLUDED_
#define DANHSACH_H_INCLUDED_

template <class T>
class DanhSach
{
private:
	class Node
	{
	private:
		T m_data;
		Node* m_pNext;

	public:
		Node(const T& data) : m_data(data), m_pNext(nullptr)
		{
		}

		T& getData()
		{
			return this->m_data;
		}

		const T& getData() const
		{
			return this->m_data;
		}

		Node* getNext() const
		{
			return this->m_pNext;
		}

		void setNext(Node* pNext)
		{
			this->m_pNext = pNext;
		}
	};

	Node* m_pHead;
	Node* m_pTail;
	int m_iSize;

	void sao(const DanhSach& other)
	{
		for (Node* pNode = other.m_pHead; pNode != nullptr; pNode = pNode->getNext())
		{
			this->themCuoi(pNode->getData());
		}
	}

public:

	DanhSach() : m_pHead(nullptr), m_pTail(nullptr), m_iSize(0)
	{
	}

	DanhSach(const DanhSach& other) : m_pHead(nullptr), m_pTail(nullptr), m_iSize(0)
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
		if (this->m_pHead == nullptr)
		{
			this->m_pHead = pNew;
		}
		else
		{
			this->m_pTail->setNext(pNew);
		}
		this->m_pTail = pNew;
		++this->m_iSize;
	}

	bool xoaTaiViTri(const int iViTri)
	{
		if (iViTri < 0 || iViTri >= this->m_iSize)
		{
			return false;
		}
		Node* pPrev = nullptr;
		Node* pCurrent = this->m_pHead;
		for (int iIndex = 0; iIndex < iViTri; ++iIndex)
		{
			pPrev = pCurrent;
			pCurrent = pCurrent->getNext();
		}
		if (pPrev == nullptr)
		{
			this->m_pHead = pCurrent->getNext();
		}
		else
		{
			pPrev->setNext(pCurrent->getNext());
		}
		if (pCurrent == this->m_pTail)
		{
			this->m_pTail = pPrev;
		}
		delete pCurrent;
		--this->m_iSize;
		return true;
	}

	template <class TDieuKien>
	T* timDau(TDieuKien dieuKien)
	{
		for (Node* pNode = this->m_pHead; pNode != nullptr; pNode = pNode->getNext())
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
		for (const Node* pNode = this->m_pHead; pNode != nullptr; pNode = pNode->getNext())
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
		for (Node* pNode = this->m_pHead; pNode != nullptr; pNode = pNode->getNext())
		{
			hanhDong(pNode->getData());
		}
	}

	template <class THanhDong>
	void duyet(THanhDong hanhDong) const
	{
		for (const Node* pNode = this->m_pHead; pNode != nullptr; pNode = pNode->getNext())
		{
			hanhDong(pNode->getData());
		}
	}

	T* layTaiViTri(const int iViTri)
	{
		if (iViTri < 0 || iViTri >= this->m_iSize)
		{
			return nullptr;
		}
		Node* pNode = this->m_pHead;
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
		return (this->m_pHead == nullptr) ? nullptr : &this->m_pHead->getData();
	}

	const T* layDau() const
	{
		return const_cast<DanhSach*>(this)->layDau();
	}

	int getSize() const
	{
		return this->m_iSize;
	}

	bool isEmpty() const
	{
		return this->m_iSize == 0;
	}

	void xoaTatCa()
	{
		while (this->m_pHead != nullptr)
		{
			Node* pNext = this->m_pHead->getNext();
			delete this->m_pHead;
			this->m_pHead = pNext;
		}
		this->m_pTail = nullptr;
		this->m_iSize = 0;
	}
};

#endif
