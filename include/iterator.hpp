/**
 * @file      iterator.hpp
 * @brief     wrappers of iterators
 * @version   0.1
 * @author    dragon-archer (dragon-archer@outlook.com)
 *
 * @copyright Copyright (c) 2022
 */

#ifndef _LIBDA_ITERATOR_HPP_
#define _LIBDA_ITERATOR_HPP_

#include "config.hpp"
#include <iterator>

namespace da {
	template<typename Iter, typename Container>
	class normal_iterator {
	protected:
		Iter m_iter;
		template<typename It>
		using convertible_from = std::enable_if_t<std::is_convertible<It, Iter>::value>;

		typedef normal_iterator Self;

	public:
		typedef std::iterator_traits<Iter>			  traits_type;
		typedef Iter								  iterator_type;
		typedef std::random_access_iterator_tag		  iterator_catagory;
		typedef typename traits_type::value_type	  value_type;
		typedef typename traits_type::difference_type difference_type;
		typedef typename traits_type::reference		  reference;
		typedef typename traits_type::pointer		  pointer;

		constexpr normal_iterator() noexcept
			: m_iter(Iter()) { }

		explicit constexpr normal_iterator(const Iter& i) noexcept
			: m_iter(i) { }

		template<typename It, typename = convertible_from<It>>
		explicit constexpr normal_iterator(const It& i) noexcept
			: m_iter(i.base()) { }

		constexpr const Iter& base() const noexcept {
			return m_iter;
		}

		constexpr reference operator*() noexcept {
			return *m_iter;
		}

		constexpr pointer operator->() noexcept {
			return m_iter;
		}

		// Use comma expression to make this compile under C++11
		constexpr Self& operator++() noexcept {
			return (++m_iter, *this);
		}

		constexpr Self operator++(int) noexcept {
			return Self(m_iter++);
		}

		constexpr Self& operator--() noexcept {
			return (--m_iter, *this);
		}

		constexpr Self operator--(int) noexcept {
			return Self(m_iter--);
		}

		constexpr reference operator[](difference_type n) const {
			return m_iter[n];
		}

		constexpr Self& operator+=(difference_type n) {
			return (m_iter += n, *this);
		}

		constexpr Self operator+(difference_type n) const {
			return Self(m_iter + n);
		}

		constexpr Self& operator-=(difference_type n) {
			return (m_iter -= n, *this);
		}

		constexpr Self operator-(difference_type n) const {
			return Self(m_iter - n);
		}
	};

	template<typename Iter, typename Container>
	constexpr bool operator==(const normal_iterator<Iter, Container>& x,
							  const normal_iterator<Iter, Container>& y) noexcept {
		return x.base() == y.base();
	}

	template<typename Iter1, typename Iter2, typename Container>
	constexpr bool operator==(const normal_iterator<Iter1, Container>& x,
							  const normal_iterator<Iter2, Container>& y) noexcept {
		return x.base() == y.base();
	}

	template<typename Iter, typename Container>
	constexpr bool operator!=(const normal_iterator<Iter, Container>& x,
							  const normal_iterator<Iter, Container>& y) noexcept {
		return x.base() != y.base();
	}

	template<typename Iter1, typename Iter2, typename Container>
	constexpr bool operator!=(const normal_iterator<Iter1, Container>& x,
							  const normal_iterator<Iter2, Container>& y) noexcept {
		return x.base() != y.base();
	}

	template<typename Iter, typename Container>
	constexpr bool operator<(const normal_iterator<Iter, Container>& x,
							 const normal_iterator<Iter, Container>& y) noexcept {
		return x.base() < y.base();
	}

	template<typename Iter1, typename Iter2, typename Container>
	constexpr bool operator<(const normal_iterator<Iter1, Container>& x,
							 const normal_iterator<Iter2, Container>& y) noexcept {
		return x.base() < y.base();
	}

	template<typename Iter, typename Container>
	constexpr bool operator>(const normal_iterator<Iter, Container>& x,
							 const normal_iterator<Iter, Container>& y) noexcept {
		return x.base() > y.base();
	}

	template<typename Iter1, typename Iter2, typename Container>
	constexpr bool operator>(const normal_iterator<Iter1, Container>& x,
							 const normal_iterator<Iter2, Container>& y) noexcept {
		return x.base() > y.base();
	}

	template<typename Iter, typename Container>
	constexpr bool operator<=(const normal_iterator<Iter, Container>& x,
							  const normal_iterator<Iter, Container>& y) noexcept {
		return x.base() <= y.base();
	}

	template<typename Iter1, typename Iter2, typename Container>
	constexpr bool operator<=(const normal_iterator<Iter1, Container>& x,
							  const normal_iterator<Iter2, Container>& y) noexcept {
		return x.base() <= y.base();
	}

	template<typename Iter, typename Container>
	constexpr bool operator>=(const normal_iterator<Iter, Container>& x,
							  const normal_iterator<Iter, Container>& y) noexcept {
		return x.base() >= y.base();
	}

	template<typename Iter1, typename Iter2, typename Container>
	constexpr bool operator>=(const normal_iterator<Iter1, Container>& x,
							  const normal_iterator<Iter2, Container>& y) noexcept {
		return x.base() >= y.base();
	}

	template<typename Iter>
	struct is_input_iterator
		: public std::is_convertible<typename Iter::iterator_category, std::input_iterator_tag> { };

	template<typename Iter>
	struct is_output_iterator
		: public std::is_convertible<typename Iter::iterator_category, std::output_iterator_tag> { };

	template<typename Iter>
	struct is_forward_iterator
		: public std::is_convertible<typename Iter::iterator_category, std::forward_iterator_tag> { };

	template<typename Iter>
	struct is_bidirectional_iterator
		: public std::is_convertible<typename Iter::iterator_category, std::bidirectional_iterator_tag> { };

	template<typename Iter>
	struct is_random_access_iterator
		: public std::is_convertible<typename Iter::iterator_category, std::random_access_iterator_tag> { };

	template<typename Iter>
	using require_input_iterator = std::enable_if_t<is_input_iterator<Iter>::value, Iter>;

	template<typename Iter>
	using require_output_iterator = std::enable_if_t<is_output_iterator<Iter>::value, Iter>;

	template<typename Iter>
	using require_forward_iterator = std::enable_if_t<is_forward_iterator<Iter>::value, Iter>;

	template<typename Iter>
	using require_bidirectional_iterator = std::enable_if_t<is_bidirectional_iterator<Iter>::value, Iter>;

	template<typename Iter>
	using require_random_access_iterator = std::enable_if_t<is_random_access_iterator<Iter>::value, Iter>;
} // namespace da

#endif // _LIBDA_ITERATOR_HPP_
