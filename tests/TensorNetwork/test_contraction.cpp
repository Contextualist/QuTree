//
// Created by Roman Ellerbrock on 12/14/21.
//

#include "UnitTest++/UnitTest++.h"
#include "TensorNetwork/contractions.h"
#include "Tree/TreeFactory.h"
#include "Util/GateOperators.h"


SUITE (contraction) {
	class Trees {
	public:
		Trees() {
			tree_ = balancedTree(4, 2, 2);
			psi_ = TensorTreecd(tree_, identitycd);
		}

		Tree tree_;
		TensorTreecd psi_;
	};

	double eps = 1e-10;

	TEST_FIXTURE (Trees, dotproduct) {
		TensorTreecd S = matrixTreecd(tree_);
		contraction(S, psi_, psi_);
		for (const Edge* edge : S.edges_) {
				CHECK_CLOSE(0., residual(S[edge], identitycd({2, 2})), eps);
		}
	}

	TEST_FIXTURE (Trees, ProductOperator) {
		ProductOperatorcd P(sigma_x(), 0);
		TensorTreecd S = matrixTreecd(tree_, P);
		contraction(S, psi_, psi_, P);
		for (const Edge* edge : S.edges_) {
			if (edge->isUpEdge()) {
				CHECK_CLOSE(0., residual(S[edge], sigma_x()), eps);
			} else {
				CHECK_CLOSE(0., residual(S[edge], identitycd({2, 2})), eps);
			}
		}
	}

	TEST_FIXTURE (Trees, ProductOperator2) {
		ProductOperatorcd P(sigma_x(), 0);
		P.push_back(identitycd({2, 2}), 2);
		TensorTreecd S = matrixTreecd(tree_, P);
		contraction(S, psi_, psi_, P);
		auto PPsi = P.apply(psi_);
		TensorTreecd S2 = matrixTreecd(tree_, P);
		contraction(S2, psi_, PPsi);
		/// Check consistency between two methods
		for (const Edge *edge : S.edges_) {
				CHECK_CLOSE(0., residual(S[edge], S2[edge]), eps);
		}
	}

	TEST_FIXTURE (Trees, SumOfProductOperators) {
		SOPcd cnot = CNot(1, 3);


	}
}
