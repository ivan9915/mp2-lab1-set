// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП 
// 
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001 
// Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015) 
// 
// Множество - реализация через битовые поля 

#include "tset.h" 

TSet::TSet(int mp) : BitField(mp) 
{ 
	MaxPower = mp; 
} 

// конструктор копирования 
TSet::TSet(const TSet &s) : BitField(s.BitField) 
{ 
	MaxPower = s.MaxPower;
} 

// конструктор преобразования типа 
TSet::TSet(const TBitField &bf) : BitField(bf) 
{ 
	MaxPower = bf.GetLength();

} 

TSet::operator TBitField() // от множества к битовому полю 
{ 
	TBitField a (MaxPower);
	a = BitField; 
	return a; 
} 

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов 
{ 
	return MaxPower; 
} 

int TSet::IsMember(const int Elem) const // элемент множества? 
{ 
	int i; 
	if ((Elem >= 0) && (Elem < MaxPower)) 
	{ 
		i = BitField.GetBit(Elem); 
		return i; 
	} 
	else 
		throw"";
} 

void TSet::InsElem(const int Elem) // включение элемента множества (проверка на область множства, выдать ошибку) 
{ 
	if ((Elem >= 0) && (Elem < MaxPower)) 
		BitField.SetBit(Elem); 
	else 
		throw""; 
} 

void TSet::DelElem(const int Elem) // исключение элемента множества 
{ 
	if ((Elem >= 0) && (Elem < MaxPower)) 
		BitField.ClrBit(Elem); 
	else 
		throw""; 
} 

// теоретико-множественные операции 

TSet& TSet::operator=(const TSet &s) // присваивание 
{ 
	if ( this != &s) 
	{ 
		~BitField; 
		MaxPower = s.MaxPower; 
		BitField = s.BitField; 
	} 

	return *this; 
} 

int TSet::operator==(const TSet &s) const // сравнение 
{ 
	if (MaxPower != s.MaxPower) 
		return 0; 
	else 
	{ 
		if (BitField != s.BitField) 
			return 0; 
		else 
			return 1; 
	} 
} 

int TSet::operator!=(const TSet &s) const // сравнение 
{ 
	if (MaxPower != s.MaxPower) 
		return 1; 
	else 
	{ 
		if (BitField != s.BitField) 
			return 1; 
		else 
			return 0; 
	} 
} 

TSet TSet::operator+(const TSet &s) // объединение 
{ 
	int Maxlen; 

	if ( MaxPower > s.MaxPower) 
		Maxlen = MaxPower; 
	else 
		Maxlen = s.MaxPower; 

	TSet res (Maxlen); 

	res.BitField = BitField | s.BitField; 

	return res; 
} 

TSet TSet::operator+(const int Elem) // объединение с элементом 
{ 
	TSet res(*this);
	res.InsElem (Elem); 
	return res; 
} 

TSet TSet::operator-(const int Elem) // разность с элементом 
{ 
	TSet res(*this);
	res.DelElem (Elem); 
	return res; 
} 

TSet TSet::operator*(const TSet &s) // пересечение 
{ 
	int Maxlen; 

	if ( MaxPower > s.MaxPower) 
		Maxlen = MaxPower; 
	else 
		Maxlen = s.MaxPower; 

	TSet res (Maxlen); 

	res.BitField = BitField & s.BitField; 

	return res; 
} 

TSet TSet::operator~(void) // дополнение 
{ 
	BitField = ~BitField; 
	return *this; 
} 

// перегрузка ввода/вывода 

istream &operator>>(istream &istr, TSet &s) // ввод элемента, а не 1 или 0, если не влезает то выдать ошибку 
{ 
	int i; 
	istr >> i; 
	s.InsElem(i); 
	return istr; 
} 

ostream& operator<<(ostream &ostr, const TSet &s) // вывод элемента 
{ 
	int Elem; 
	for (int i = 0; i < s.MaxPower; i++) 
	{ 
		Elem = s.BitField.GetBit(i); 
		if (Elem == 1) 
			ostr << i << " "; 
	} 
	return ostr; 
}
