//
// Created by Roman Ellerbrock on 12/3/21.
//
#include "TensorNetwork/TensorTree.h"
#include "UnitTest++/UnitTest++.h"
#include "Tree/TreeFactory.h"
#include "TensorNetwork/DotProduct.h"

SUITE (TensorTree) {

	class Trees {
	public:
		Trees() {
			tree_ = balancedTree(4, 3, 2);
		}

		Tree tree_;
	};

	double eps = 1e-10;

	TEST_FIXTURE (Trees, construct) {
		TensorTreecd Psi(tree_);
			CHECK_EQUAL(7, Psi.nodes_.size());
			CHECK_EQUAL(6, Psi.upEdges_.size());
			CHECK_EQUAL(6, Psi.downEdges_.size());
	}

	TEST_FIXTURE (Trees, TensorShapes) {
		TensorTreecd Psi(tree_, deltacd);
		for (const Node& node : tree_) {
				CHECK_EQUAL(node.shape_, Psi[node].shape_);
		}

		for (const Edge& edge : tree_.edges()) {
				CHECK_EQUAL(edge.from().shape_, Psi[edge].shape_);
		}
	}

	TEST_FIXTURE (Trees, gen) {
		TensorTreecd Psi(tree_, deltacd);
		for (const Node& node : tree_) {
				CHECK_CLOSE(0., residual(deltacd(node.shape_), Psi[node]), eps);
		}

		for (const Edge& edge : tree_.edges()) {
			const Tensorcd& phi = Psi[edge];
			auto delta = contraction(phi, phi, edge);
				CHECK_CLOSE(0., residual(delta, identitycd(delta.shape_)), eps);
		}
	}
}

