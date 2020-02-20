//
// Created by Roman Ellerbrock on 2/12/20.
//

#ifndef SPARSEMATRIXTREEFUNCTIONS_H
#define SPARSEMATRIXTREEFUNCTIONS_H
#include "TreeClasses/SparseMatrixTree.h"

namespace SparseMatrixTreeFunctions {
/**
 * \namespace SparseMatrixTreeFunctions
 *
 * \ingroup Tree
 *
 * \brief This class provides functions to build SparseMatrixTrees.
 *
 * SparseMatrixTrees typically appear when representing operators
 * in a tensortree basis. Similar to MatrixTree, a SparseMatrixTree
 * can be build bottom-up or top-down in a tree. A SparsematrixTree is
 * build bottom-up if an operator is represented and top-down if
 * the representation of the operator is represented.
 * */

////////////////////////////////////////////////////////////////////////
/// Build SparseMatrixTree Bottom-parent (Forward)
////////////////////////////////////////////////////////////////////////

	template<typename T>
	void RepresentLayer(SparseMatrixTree<T>& mats, const Tensor<T>& Bra,
		const Tensor<T>& Ket, const MLO<T>& M, const Node& node);

	template<typename T>
	void Represent(SparseMatrixTree<T>& hmat,
		const MLO<T>& M, const TensorTree<T>& Bra, const TensorTree<T>& Ket,
		const Tree& tree);

	template<typename T>
	SparseMatrixTree<T> Represent(const MLO<T>& M, const TensorTree<T>& Bra,
		const TensorTree<T>& Ket, const Tree& tree);

	template<typename T>
	void Represent(SparseMatrixTree<T>& hmat, const MLO<T>& M,
		const TensorTree<T>& Psi, const Tree& tree);

	template<typename T>
	SparseMatrixTree<T> Represent(const MLO<T>& M, const TensorTree<T>& Psi,
		const Tree& tree);

////////////////////////////////////////////////////////////////////////
/// Build SparseMatrixTree Top-child (Backward)
////////////////////////////////////////////////////////////////////////

	template<typename T>
	void Contraction(SparseMatrixTree<T>& holes, const TensorTree<T>& Bra,
		const TensorTree<T>& Ket, const SparseMatrixTree<T>& mats,
		const Tree& tree);

	template<typename T>
	void Contraction(SparseMatrixTree<T>& holes, const TensorTree<T>& Psi,
		const SparseMatrixTree<T>& mats, const Tree& tree);

////////////////////////////////////////////////////////////////////////
/// Apply MatrixTree
////////////////////////////////////////////////////////////////////////

	template<typename T>
	Tensorcd Apply(SparseMatrixTree<T>& mat, const Tensorcd& Phi, const MLO<T>& M, const Node& node);

	template<typename T>
	Tensorcd ApplyUpper(SparseMatrixTree<T>& mat, Tensorcd Phi, const Node& node);

	template<typename T>
	Tensorcd ApplyHole(SparseMatrixTree<T>& holes, Tensorcd Phi, const Node& hole_node);

}

#endif //SPARSEMATRIXTREEFUNCTIONS_H
