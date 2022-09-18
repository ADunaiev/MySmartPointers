#include<iostream>
using namespace std;

//Задание 1.
//Создайте пользовательские классы умных указателей.Один
//из классов должен повторять функциональность стандартного класса unique_ptr, 
//а другой shared_ptr.Напишите
//код по тестированию ваших классов.

template<typename T>
class Uni_Ptr
{
	T* ptr;
	int size;
public:
	Uni_Ptr(T* ptrP);
	Uni_Ptr(T* ptrP, int sizeP);
	Uni_Ptr();
	~Uni_Ptr();
	T& operator*();
	Uni_Ptr(Uni_Ptr& object) = delete;
	Uni_Ptr& operator=(Uni_Ptr& object) = delete;
	Uni_Ptr(Uni_Ptr&& object);
	Uni_Ptr& operator=(Uni_Ptr&& object);
	void show();
};

template<typename T>
Uni_Ptr<T>::Uni_Ptr(T* ptrP, int sizeP) : ptr{ new T[sizeP] }, size{ sizeP }
{
	for (size_t i = 0; i < size; i++)
	{
		*(ptr+i) = *(ptrP + i);
	}
}
template<typename T>
Uni_Ptr<T>::Uni_Ptr(T* ptrP) : Uni_Ptr(ptrP, 1){}
template<typename T>
Uni_Ptr<T>::Uni_Ptr()
{
	ptr = nullptr;
	size = 0;
	//cout << "Uni_Ptr constructed: " << ptr << endl;
}
template<typename T>
Uni_Ptr<T>::~Uni_Ptr()
{
	//cout << "Uni_Ptr destucted: " << ptr << endl;
	delete[] ptr;
}
template<typename T>
Uni_Ptr<T>::Uni_Ptr(Uni_Ptr&& object)
{
	size = object.size;
	ptr = new T[size];
	if (size > 0)
	{
		for (int i = 0; i < size; i++)
			*(ptr+i) = *(object.ptr+i);
	}
	else
		ptr = nullptr;

	object.ptr = nullptr;
	object.size = 0;
}
template<typename T>
T& Uni_Ptr<T>::operator*()
{
	return *ptr;
}
template<typename T>
Uni_Ptr<T>& Uni_Ptr<T>::operator=(Uni_Ptr&& object)
{
	if (!(ptr == object.ptr && size == object.size))
	{
		if (ptr != nullptr)
			delete[] ptr;

		size = object.size;
		ptr = new T[size];
		for (size_t i = 0; i < size; i++)
			*(ptr+i) = *(object.ptr + i);

		object.ptr = nullptr;
		object.size = 0;
	}
	return *this;
}
template<typename T>
void Uni_Ptr<T>::show()
{
	for (size_t i = 0; i < size; i++)
	{
		cout << *(ptr+i) << "\t";
	}
	cout << endl;
}

template<typename T>
class Sha_Ptr
{
	T* ptr;
	int size;
	int count;
public:
	Sha_Ptr(T* ptrP);
	Sha_Ptr(T* ptrP, int sizeP);
	Sha_Ptr();
	~Sha_Ptr();
	T& operator*();
	Sha_Ptr(Sha_Ptr& object) = delete;
	Sha_Ptr& operator=(Sha_Ptr& object) = delete;
	Sha_Ptr(Sha_Ptr&& object);
	Sha_Ptr& operator=(Sha_Ptr&& object);
	void show();
};

template<typename T>
Sha_Ptr<T>::Sha_Ptr(T* ptrP, int sizeP) 
	: ptr{ new T[sizeP] }, size{ sizeP }, count{1}
{
	for (size_t i = 0; i < size; i++)
		*(ptr + i) = *(ptrP + i);	
}
template<typename T>
Sha_Ptr<T>::Sha_Ptr(T* ptrP) : Sha_Ptr(ptrP, 1) {}
template<typename T>
Sha_Ptr<T>::Sha_Ptr()
{
	ptr = nullptr;
	size = 0;
	count = 0;
	//cout << "Uni_Ptr constructed: " << ptr << endl;
}
template<typename T>
Sha_Ptr<T>::~Sha_Ptr()
{
	//cout << "Uni_Ptr destucted: " << ptr << endl;
	if (count == 1)
		delete[] ptr;
	else
		ptr = nullptr;
}
template<typename T>
Sha_Ptr<T>::Sha_Ptr(Sha_Ptr&& object)
{
	size = object.size;
	ptr = new T[size];
	if (size > 0)
	{
		for (int i = 0; i < size; i++)
			*(ptr + i) = *(object.ptr + i);
	}
	else
		ptr = nullptr;

	object.ptr = nullptr;
	object.size = 0;
}
template<typename T>
T& Sha_Ptr<T>::operator*()
{
	return *ptr;
}
template<typename T>
Sha_Ptr<T>& Sha_Ptr<T>::operator=(Sha_Ptr&& object)
{
	if (!(ptr == object.ptr && size == object.size))
	{
		if (ptr != nullptr)
			delete[] ptr;

		size = object.size;
		ptr = new T[size];
		for (size_t i = 0; i < size; i++)
			*(ptr + i) = *(object.ptr + i);

		object.ptr = nullptr;
		object.size = 0;
	}
	return *this;
}
template<typename T>
void Sha_Ptr<T>::show()
{
	for (size_t i = 0; i < size; i++)
	{
		cout << *(ptr + i) << "\t";
	}
	cout << endl;
}

int main()
{
	int size = 5;
	int* arr = new int[size] {1, 2, 3, 4, 5};
	Uni_Ptr<int> u1(arr, 5);
	cout << "u1:\t";
	u1.show();

	Uni_Ptr<int> u2;
	u2 = move(u1);
	cout << "u2:\t";
	u2.show();

	int size2 = 5;
	int* arr2 = new int[size2] {6, 7, 8, 9, 10};
	Sha_Ptr<int> s1(arr2, 5);
	cout << "s1:\t";
	s1.show();

	Sha_Ptr<int> s2;
	s2 = move(s1);
	cout << "s2:\t";
	s2.show();

	return 0;
}