#include <cstddef>
#include <iostream>

template< class T >
struct BiList
{
  T val;
  BiList<T> * next;
  BiList<T> * prev;
};


template< class T >
BiList<T> * fake(BiList<T> * h);

template< class T >
BiList<T> * rmfake(BiList<T> * h) noexcept;

template< class T >
BiList<T> * add(BiList<T> * h, const T & data);

template< class T >
BiList<T> * insert(BiList<T> * h, const T & data);

template< class T >
BiList<T> * cut(BiList<T> * h) noexcept;

template< class T >
BiList<T> * erase(BiList<T> * h) noexcept;

template< class T >
BiList<T> * clear(BiList<T> * h, BiList<T> * e) noexcept;



template< class T >
BiList<T> * fake(BiList<T> * h)
{
  BiList<T> * r = static_cast< BiList<T> * >(::operator new (sizeof(BiList<T> *)));
  r->next = h;
  h->prev = r;
  return r;
}

template< class T >
BiList<T> * rmfake(BiList<T> * h) noexcept
{
  BiList<T> * temp = h->next;
  if (temp)
  {
    temp->prev = nullptr;
  }
  ::operator delete(h);
  return temp;
}

template< class T >
BiList<T> * add(BiList<T> * h, const T & data)
{
  BiList<T> * node = new BiList<T>{data, h, h->prev};
  h->prev->next = node;
  h->prev = node;
  return node;
}

template<class T>
BiList<T> * insert(BiList<T> * h, const T & data)
{
  BiList<T> * temp = h->next;
  BiList<T> * node = new BiList<T>{data, temp, h};
  h->next = node;
  if (temp)
  {
    temp->prev = node;
  }
  return node;
}

template< class T >
BiList<T> * cut(BiList<T> * h) noexcept
{
  BiList<T> * temp = h->next;
  h->prev->next = h->next;
  if (h->next)
  {
    h->next->prev = h->prev;
  }
  delete h;
  return temp;
}

template< class T >
BiList<T> * erase(BiList<T> * h) noexcept
{
  if (!h->next)
  {
    return nullptr;
  }
  return h->next = cut(h->next);
}

template< class T >
BiList<T> * clear(BiList<T> * h, BiList<T> * e) noexcept
{
  while (h != e)
  {
    h = cut(h);
  }
  return h;
}

template<class T>
BiList<T> * array_to_list(const T * a, size_t n)
{
  if (n == 0)
  {
    return nullptr;
  }

  BiList<T> * head = new BiList<T>{a[0], nullptr, nullptr};

  BiList<T> * tail = head;
  for (size_t i = 1; i < n; ++i)
  {
    tail = insert(tail, a[i]);
  }
  return head;
}


int main()
{
  int arr[] = {10, 20, 30, 40};
  size_t n = 4;

  BiList<int> * head = array_to_list(arr, n);
  if (!head)
  {
    return 0;
  }
  BiList<int> * f = fake(head);

  BiList<int> * p = f->next;
  while (p)
  {
    std::cout << p->val << '\n';
    p = p->next;
  }

  clear<int>(f->next, nullptr);
  rmfake(f);
}

/*
НЕЯВНЫЙ интерфейс для T:
- T::T(const T&) конструктор копирования
- T::~T() деструктор
*/