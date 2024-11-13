/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2015-2015.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_INTRUSIVE_DETAIL_INT_HOLDER_HPP
#define BOOST_INTRUSIVE_DETAIL_INT_HOLDER_HPP

//GCC has some false array_bounds warnings starting in GCC 12
#if defined(BOOST_CLANG) || (defined(BOOST_GCC) && (BOOST_GCC >= 120000))
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Warray-bounds"
#endif

struct int_holder
{
   explicit int_holder(int value = 0)
      : int_(value)
   {}

   int_holder &operator=(int value)
   {  int_ = value;  return *this;  }

   int int_value() const
   {  return int_;  }

   friend bool operator==(const int_holder &l, const int_holder &r)
   {  return l.int_ == r.int_;  }

   friend bool operator!=(const int_holder &l, const int_holder &r)
   {  return l.int_ != r.int_;  }

   friend bool operator<(const int_holder &l, const int_holder &r)
   {  return l.int_ < r.int_;  }

   friend bool operator>(const int_holder &l, const int_holder &r)
   {  return l.int_ > r.int_;  }

   friend bool operator<=(const int_holder &l, const int_holder &r)
   {  return l.int_ <= r.int_;  }

   friend bool operator>=(const int_holder &l, const int_holder &r)
   {  return l.int_ >= r.int_;  }

///
   friend bool operator==(int l, const int_holder &r)
   {  return l == r.int_;  }

   friend bool operator!=(int l, const int_holder &r)
   {  return l != r.int_;  }

   friend bool operator<(int l, const int_holder &r)
   {  return l < r.int_;  }

   friend bool operator>(int l, const int_holder &r)
   {  return l > r.int_;  }

   friend bool operator<=(int l, const int_holder &r)
   {  return l <= r.int_;  }

   friend bool operator>=(int l, const int_holder &r)
   {  return l >= r.int_;  }

   bool operator< (int i) const
   {  return int_ < i;   }

   bool operator> (int i) const
   {  return int_ > i;   }

   bool operator<= (int i) const
   {  return int_ <= i;   }

   bool operator>= (int i) const
   {  return int_ >= i;   }

   bool operator== (int i) const
   {  return int_ == i;   }

   bool operator!= (int i) const
   {  return int_ != i;   }

   friend std::size_t hash_value(const int_holder &t)
   {  return  std::size_t((&t)->int_value());  }

   int int_;
};

template<class ValueType>
struct int_holder_key_of_value
{
   typedef int_holder type;

   type operator()(const ValueType &tv) const
   {  return tv.get_int_holder();  }
};

template<class ValueType>
struct int_priority_of_value
{
   typedef int type;

   type operator()(const ValueType &tv) const
   {  return tv.int_value();  }
};

//GCC has some false array_bounds warnings starting in GCC 12
#if defined(BOOST_CLANG) || (defined(BOOST_GCC) && (BOOST_GCC >= 120000))
#pragma GCC diagnostic pop
#endif

#endif   //BOOST_INTRUSIVE_DETAIL_INT_HOLDER_HPP
