//
// Created by Roman Ellerbrock on 12/3/21.
//

#ifndef TENSORTREE_H
#define TENSORTREE_H
#include "SubTreeAttribute.h"

template<typename T>
class TensorTree: public SubTreeAttribute<Tensor<T>> {
public:
	TensorTree() = default;
	~TensorTree() = default;

	explicit TensorTree(const Tree& tree,
		function<Tensor<T>(const TensorShape&)> generator = randomGen<T>);

	explicit TensorTree(const SubTree& subTree) : SubTreeAttribute<Tensor<T>>(subTree) {
	}

	void normalize(double eps = 1e-10);

	void print() const override;
};

typedef TensorTree<complex<double>> TensorTreecd;

typedef TensorTree<double> TensorTreed;

template<typename T>
Tensor<T> normalize(const Tensor<T>& phi, const Edge* edge, double eps = 1e-10);

template<typename T>
ostream& operator<<(ostream& os, const TensorTree<T>& A);

#endif //TENSORTREE_H
