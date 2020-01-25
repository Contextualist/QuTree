#pragma once

#include "Tensor.h"
#include "TensorTreeBasis.h"
#include "TensorTree.h"
#include "SingleParticleOperator.h"
#include "SingleParticleOperatorFunction.h"
#include "PotentialOperator.h"

class MultiParticleOperator
	/*!
	 * \brief A MultiParticleOperator (MPO) is a product of general single-particle operators
	 *
	 * A MultiParticleOperator is one summand in a SumofProducts
	 * operator. It can be applied to a mctdhWavefunction resulting in
	 * a wavefunction with a different SPF-basis. The MPO is central for building hamiltonians.
	 *
	 * Please note:
	 * - The recommended operator to build MPO is RefSPO (due to performance)
	 * - SPO initialization might be removed in the future
	 * - mctdhWavfunctions with different SPF-basis
	 * functions cannot be added without loss of information.
	 */
{
public:
	/// Constructor without memory allocation
	MultiParticleOperator();

	/// Default destructor
	~MultiParticleOperator() = default;

	/// Construct a MPO from a single SPO
	MultiParticleOperator(const SPO& h, int mode_x)
		: MultiParticleOperator() {
		push_back(h, mode_x);
	}

	/// Construct a MPO from a single RefSPO
	MultiParticleOperator(const SPOf& h, int mode_x)
		: MultiParticleOperator() {
		push_back(h, mode_x);
	}

	/// This routine manages how to apply a MPO
	Tensorcd ApplyBottomLayer(Tensorcd Acoeffs,
		const Leaf& phys) const;

	/// This routine manages how to apply a MPO
	Tensorcd ApplyBottomLayer(Tensorcd Acoeffs,
		const vector<int>& list, const PrimitiveBasis& grid) const;

	/// Push back a SPO to the MPO
	void push_back(shared_ptr<SPO> h, int mode_x) {
		SingParOp.push_back(h);
		mode_.push_back(mode_x);
	}

	/// Push back a RefSPO to the MPO
	void push_back(const SPO& h, int mode_x) {
/*		auto *spo = new StandardSPO;
		spo->Initialize(h);
		SingParOp.push_back(shared_ptr<SPO>(spo));
		mode.push_back(mode_x);
		*/
		assert(0);
	}

	/// Push back a RefSPO to the MPO
	void push_back(const SPOf& h, int mode_x) {
		auto *spo = new SPOf(h);
		SingParOp.push_back(shared_ptr<SPO>(spo));
		mode_.push_back(mode_x);
	}

	/// Access the i-th SPO in the MPO
	shared_ptr<SPO> operator()(size_t i) {
		assert(i >= 0);
		assert(i < SingParOp.size());
		return SingParOp[i];
	}

	/// The number of SPOs in the MPO
	size_t size() const { return mode_.size(); }

	/// Access the i-th SPO in the MPO
	shared_ptr<SPO> operator[](size_t i) const {
		assert(i < mode_.size());
		assert(i >= 0);
		return SingParOp[i];
	}

	/// Check whether a SPO acts on mode "mode_x"
	bool ModeIsActive(size_t mode_x) const {
		for (size_t i = 0; i < mode_.size(); i++) {
			if (mode_[i] == mode_x) { return true; }
		}
		return false;
	}

	/// Check whether the "part"-th SPO acts on mode "mode_x"
	bool ModeIsActive(size_t part, size_t mode_x) const {
		if (mode_[part] == mode_x) { return true; }
		return false;
	}

	/// Apply a MPO to a wavefunction. This routine is not optimized for performance.
	template<typename T>
	TensorTree<T> Apply(TensorTree<T> Psi, const TTBasis& basis) const;

	/// On which mode does the "part"-th SPO act?
	size_t Mode(size_t part) const {
		assert(part < size());
		return mode_[part];
	}

	/// Multiply two MPOs.
	friend MultiParticleOperator operator*(const MultiParticleOperator& A,
		const MultiParticleOperator& B) {
		MultiParticleOperator M = B;

		for (size_t i = 0; i < A.size(); i++) {
			M.push_back(A[i], A.Mode(i));
		}

		return M;
	}

	/// Check whether a Potential operator is included in the MPO. Important for CDVR.
	bool HasV() const { return hasV; }

	/// Get a reference to the PotentialOperator
	PotentialOperator& V() {
		return v;
	}

	/// Get a reference to the PotentialOperator
	const PotentialOperator& V() const {
		return v;
	}

	/// Set the PotentialOperator
	void SetV(const PotentialOperator& V);

protected:
	/// These are the SPOs
	vector<shared_ptr<SPO>> SingParOp;
	/// These are the modes the SPOs act on
	vector<int> mode_;
	/// The potential operator
	PotentialOperator v;
	/// Is there a PotentialOperator?
	bool hasV;
};

typedef MultiParticleOperator MPO;

