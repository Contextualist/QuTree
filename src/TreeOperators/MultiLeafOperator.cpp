#include "MultiLeafOperator.h"


template <typename T>
MultiLeafOperator<T>::MultiLeafOperator()
	: hasV_(false) {
	targetLeaves_.clear();
}

template <typename T>
Tensor<T> MultiLeafOperator<T>::ApplyBottomLayer(Tensor<T> Phi,
	const Leaf& Phy) const {
	Tensor<T> hPhi(Phi.Dim());
	size_t mode_x = Phy.Mode();
	const LeafInterface& grid = Phy.PrimitiveGrid();
	bool switchbool = true;

	// Applying the MLO uses switching of the result Tensor to increase performance.
	for (size_t l = 0; l < leafOperators_.size(); ++l) {
		if (mode_x != targetLeaves_[l]) { continue; }

		shared_ptr<LeafOperator<T>> spo = operator[](l);
		// apply it
		if (switchbool) {
			spo->Apply(grid, hPhi, Phi);
		} else {
			spo->Apply(grid, Phi, hPhi);
		}
		switchbool = !switchbool;
	}

	if (switchbool) {
		return Phi;
	} else {
		return hPhi;
	}
}

template <typename T>
Tensor<T> MultiLeafOperator<T>::ApplyBottomLayer(Tensor<T> Acoeffs,
	const vector<int>& list, const LeafInterface& grid) const {
	Tensor<T> hAcoeff(Acoeffs.Dim());
	bool switchbool = true;
	// Applying the MLO uses switching of the result Tensor to increase performance.
	for (size_t l = 0; l < list.size(); l++) {
		// get the active_ part in the MLO
		int part = list[l];
		shared_ptr<LeafOperator<T>> spo = operator[](part);

		// apply it
		if (switchbool) {
			spo->Apply(grid, hAcoeff, Acoeffs);
		} else {
			spo->Apply(grid, Acoeffs, hAcoeff);
		}
		switchbool = !switchbool;
	}

	if (switchbool) {
		return Acoeffs;
	} else {
		return hAcoeff;
	}
}

template<typename T>
TensorTree<T> MultiLeafOperator<T>::Apply(TensorTree<T> Psi,
	const Tree& basis) const {
	for (size_t i = 0; i < basis.nNodes(); i++) {
		const Node& node = basis.GetNode(i);
		if (node.IsBottomlayer()) {
			const Leaf& phy = node.PhysCoord();
			const LeafInterface& grid = phy.PrimitiveGrid();
			int coord = phy.Mode();

			// build list with active_ parts
			vector<int> activelayerparts;
			for (size_t l = 0; l < leafOperators_.size(); l++) {
				if (targetLeaves_[l] == coord) {
					activelayerparts.push_back(l);
				}
			}

			Tensor<T>& Acoeff = Psi[node];
			Acoeff = ApplyBottomLayer(Acoeff, activelayerparts, grid);
		}
	}
	return Psi;
}

template <typename T>
void MultiLeafOperator<T>::SetV(const PotentialOperator& V_) {
    v_ = V_;
    hasV_ = true;
}

template class MultiLeafOperator<complex<double>>;
template class MultiLeafOperator<double>;
