//원형 버퍼 구조 구현
/*
고정된 크기의 원형 버퍼를 나타내는 데이터 구조
원형 버퍼는 버퍼가 고정된 크기 이상으로 채워지면 존재하는 원소를 덮어씀

아래 조건을 충족 시켜야함
- 기본 생성자 호출 불가
- 특정한 크기의 객체 생성 지원
- 버퍼의 수용량과 상태 확인 지원
- 잠재적으로 가장 오래된 원소부터 덮어쓴느 원소 추가 연산
- 버퍼에서 가장 오래된 원소들을 제거하는 연산
- 원소 순회 지원
*/

#include <iostream>
#include <vector>
#include <assert.h>

template <class T>
class circular_buffer;

template <class T>
class circular_buffer_iterator
{
   typedef circular_buffer_iterator          self_type;
   typedef T                                 value_type;
   typedef T&                                reference;
   typedef T const&                          const_reference;
   typedef T*                                pointer;
   typedef std::random_access_iterator_tag   iterator_category;
   typedef ptrdiff_t                         difference_type;
public:
   circular_buffer_iterator(circular_buffer<T> const & buf, size_t const pos, bool const last) :
      buffer_(buf), index_(pos), last_(last)
   {}

   self_type & operator++ ()
   {
      if (last_)
         throw std::out_of_range("Iterator cannot be incremented past the end of range.");
      index_ = (index_ + 1) % buffer_.data_.size();
      last_ = index_ == buffer_.next_pos();
      return *this;
   }

   self_type operator++ (int)
   {
      self_type tmp = *this;
      ++*this;
      return tmp;
   }

   bool operator== (self_type const & other) const
   {
      assert(compatible(other));
      return index_ == other.index_ && last_ == other.last_;
   }

   bool operator!= (self_type const & other) const
   {
      return !(*this == other);
   }

   const_reference operator* () const
   {
      return buffer_.data_[index_];
   }

   const_reference operator-> () const
   {
      return buffer_.data_[index_];
   }
private:

   bool compatible(self_type const & other) const
   {
      return &buffer_ == &other.buffer_;
   }

   circular_buffer<T> const & buffer_;
   size_t index_;
   bool last_;
};

template <class T>
class circular_buffer
{
   typedef circular_buffer_iterator<T> const_iterator;

   circular_buffer() = delete;
public:
   explicit circular_buffer(size_t const size) :data_(size)
   {}

   bool clear() noexcept { head_ = -1; size_ = 0; }

   bool empty() const noexcept { return size_ == 0; }
   bool full() const noexcept { return size_ == data_.size(); }
   size_t capacity() const noexcept { return data_.size(); }
   size_t size() const noexcept { return size_; }

   void push(T const item)
   {
      head_ = next_pos();
      data_[head_] = item;
      if (size_ < data_.size()) size_++;
   }

   T pop()
   {
      if (empty()) throw std::runtime_error("empty buffer");

      auto pos = first_pos();
      size_--;
      return data_[pos];
   }

   const_iterator begin() const
   {
      return const_iterator(*this, first_pos(), empty());
   }

   const_iterator end() const
   {
      return const_iterator(*this, next_pos(), true);
   }

private:
   std::vector<T> data_;
   size_t head_ = -1;
   size_t size_ = 0;

   size_t next_pos() const noexcept { return size_ == 0 ? 0 : (head_ + 1) % data_.size(); }
   size_t first_pos() const noexcept { return size_ == 0 ? 0 : (head_ + data_.size() - size_ + 1) % data_.size(); }

   friend class circular_buffer_iterator<T>;
};


template <typename T>
void print(circular_buffer<T> & buf)
{
   for (auto & e : buf)
   {
      std::cout << e << ' ';
   }

   std::cout << std::endl;
}


int main()
{
   circular_buffer<int> cbuf(5);
   assert(cbuf.empty());
   assert(!cbuf.full());
   assert(cbuf.size() == 0);
   print(cbuf);

   cbuf.push(1);
   cbuf.push(2);
   cbuf.push(3);
   assert(!cbuf.empty());
   assert(!cbuf.full());
   assert(cbuf.size() == 3);
   print(cbuf);

   auto item = cbuf.pop();
   assert(item == 1);
   assert(!cbuf.empty());
   assert(!cbuf.full());
   assert(cbuf.size() == 2);

   cbuf.push(4);
   cbuf.push(5);
   cbuf.push(6);
   assert(!cbuf.empty());
   assert(cbuf.full());
   assert(cbuf.size() == 5);
   print(cbuf);

   cbuf.push(7);
   cbuf.push(8);
   assert(!cbuf.empty());
   assert(cbuf.full());
   assert(cbuf.size() == 5);
   print(cbuf);

   item = cbuf.pop();
   assert(item == 4);
   item = cbuf.pop();
   assert(item == 5);
   item = cbuf.pop();
   assert(item == 6);

   assert(!cbuf.empty());
   assert(!cbuf.full());
   assert(cbuf.size() == 2);
   print(cbuf);

   item = cbuf.pop();
   assert(item == 7);
   item = cbuf.pop();
   assert(item == 8);

   assert(cbuf.empty());
   assert(!cbuf.full());
   assert(cbuf.size() == 0);
   print(cbuf);

   cbuf.push(9);
   assert(!cbuf.empty());
   assert(!cbuf.full());
   assert(cbuf.size() == 1);
   print(cbuf);
}
