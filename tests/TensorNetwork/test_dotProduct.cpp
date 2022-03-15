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
			tree_ = balancedTree(4, 3, 2);
			psi_ = TensorTreecd(tree_, deltacd);
		}

		Tree tree_;
		TensorTreecd psi_;
	};

	double eps = 1e-10;

	TEST_FIXTURE (Trees, dotproduct) {
		TensorTreecd S = matrixTreecd(tree_, {});
		contraction(S, psi_, psi_);
		for (const Edge& edge : tree_.edges()) {
				CHECK_CLOSE(0., residual(S[edge], identitycd({2, 2})), eps);
		}
	}

	TEST_FIXTURE(Trees, CNotMatrices) {
		ProductOperatorcd P(sigma_x(), 0);
		auto S = matrixTreecd(tree_, P.targetLeaves());
		contraction(S, psi_, psi_, P);
		cout << "S:\n";
		S.print();
	}

/*	TEST_FIXTURE(Trees, fullContraction) {
		TensorTreecd S(tree_);
		dotProduct(S, psi_, psi_);
		TensorTreecd tr = fullContraction(psi_, S, psi_);
		Tensorcd h({1});
		h(0) = 1;
		for (const Node* node : psi_.nodes_) {
			CHECK_CLOSE(0., residual(h, tr[node]), eps);
		}
	}
*/
}