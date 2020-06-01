//
// Created by Roman Ellerbrock on 2020-01-24.
//

#include "TreeOperators/LeafMatrix.h"

template<typename T>
void LeafMatrix<T>::Apply(const LeafInterface& grid, Tensor<T>& hAcoeff,
	const Tensor<T>& Acoeff) const {
	MatrixTensor(hAcoeff, h_, Acoeff, 0, true);
}

template<typename T>
LeafMatrix<T>::LeafMatrix(Matrix<T> h, bool adjoint)
: h_(move(h)) {
	if (adjoint) {
		h_ = h.Adjoint();
	}
}

template
class LeafMatrix<complex<double>>;

template
class LeafMatrix<double>;

