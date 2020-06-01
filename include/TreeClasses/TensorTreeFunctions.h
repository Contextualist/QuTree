//
// Created by Roman Ellerbrock on 5/24/20.
//

#ifndef TENSORTREEFUNCTIONS_H
#define TENSORTREEFUNCTIONS_H
#include "TreeClasses/SpectralDecompositionTree.h"

namespace TreeFunctions {
	/// Compress the TensorTree for a given accuracy.
	template <typename T>
	void Adjust(TensorTree<T>& Psi, Tree& tree,
		const SpectralDecompositionTree<T>& X, double eps);

	/// Perform a (generalized) sum of tensor trees. By default, a regular sum will be performed.
	template <typename T>
	void Sum(TensorTree<T>& Psi, Tree& tree, const TensorTree<T>& Chi,
		bool sharedLeafs = true, bool sumToplayer = true);

}

#endif //TENSORTREEFUNCTIONS_H
