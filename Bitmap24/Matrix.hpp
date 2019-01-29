#pragma once
#include <vector>
#include <cstdint>
#include <istream>
#include <ostream>

template <typename T>
class Matrix {

	public:
		Matrix() = default;
		explicit Matrix(uint32_t rows, uint32_t cols);

		Matrix<T> & resize(uint32_t r, uint32_t c);

		uint32_t rows() const noexcept;
		Matrix<T> & rows(uint32_t r);

		uint32_t cols() const noexcept;
		Matrix<T> & cols(uint32_t c);

		T & operator()(uint32_t r, uint32_t c);

		// true if row_size bytes are readed from is
		bool row_mem_fill(uint32_t r, std::istream &is);
		bool row_mem_write(uint32_t r, std::ostream &os) const;

	private:
		std::vector<std::vector<T>> m_mtx;
};

template<typename T>
Matrix<T>::Matrix(uint32_t rows, uint32_t cols) {
	this->rows(rows).cols(cols);
}

template<typename T>
uint32_t Matrix<T>::rows() const noexcept {
	return m_mtx.size();
}

template<typename T>
uint32_t Matrix<T>::cols() const noexcept {
	return m_mtx[0].size();
}

template<typename T>
Matrix<T> & Matrix<T>::resize(uint32_t rows, uint32_t cols) {
	return this->rows(rows).cols(cols);
}

template<typename T>
Matrix<T> & Matrix<T>::rows(uint32_t rows) {
	return m_mtx.resize(rows), *this;
}

template<typename T>
Matrix<T> & Matrix<T>::cols(uint32_t cols) {

	for (uint32_t i = 0; i < rows(); ++i)
		m_mtx[i].resize(cols);

	return *this;
}

template<typename T>
T & Matrix<T>::operator()(uint32_t r, uint32_t c) {
	return m_mtx.at(r).at(c);
}

template<typename T>
bool Matrix<T>::row_mem_fill(uint32_t r, std::istream &is) {
	return (bool)is.read((char *)m_mtx.at(r).data(), m_mtx[0].size() * sizeof(T));
}

template<typename T>
bool Matrix<T>::row_mem_write(uint32_t r, std::ostream &os) const {
	return (bool)os.write((char *)m_mtx.at(r).data(), m_mtx[0].size() * sizeof(T));
}