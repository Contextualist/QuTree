#include "FermionNumberBasis.h"

FermionNumberBasis::FermionNumberBasis(int dim_):NumberBasis(dim_,true){
	assert(dim_<=2);
}

FermionNumberBasis::~FermionNumberBasis(){}

Tensorcd FermionNumberBasis::ApplyX2(const Tensorcd& phi)const
{
	TensorDim tdim = phi.Dim();
	// check that its really a bottom-layer_ tensor
	assert(tdim.F() == 1);

	Tensorcd psi(phi.Dim());

	int active = tdim.getdimpart();
	assert(active == dim);

	for (int n = 0; n < tdim.getntensor(); n++){
		psi(0, n) =  1.0;
		psi(1, n) = -1.0;
	}
	return psi;
}

Tensorcd FermionNumberBasis::pauliX(const Tensorcd& phi)const
{
	TensorDim tdim = phi.Dim();
	// check that its really a bottom-layer_ tensor
	assert(tdim.F() == 1);

	Tensorcd psi(phi.Dim());

	int active = tdim.getdimpart();
	assert(active == dim);

	for (int n = 0; n < tdim.getntensor(); n++){
		psi(1, n) =phi(0, n);
		psi(0, n) =phi(1, n);
	}
	return psi;
}

Tensorcd FermionNumberBasis::pauliY(const Tensorcd& phi)const
{
	TensorDim tdim = phi.Dim();
	// check that its really a bottom-layer_ tensor
	assert(tdim.F() == 1);

	Tensorcd psi(phi.Dim());

	int active = tdim.getdimpart();
	assert(active == dim);

	complex<double> im(0.0,1.0);
	for (int n = 0; n < tdim.getntensor(); n++){
		psi(1, n) = im*phi(0, n);
		psi(0, n) =-im*phi(1, n);
	}
	return psi;
}

Tensorcd FermionNumberBasis::pauliZ(const Tensorcd& phi)const
{
	TensorDim tdim = phi.Dim();
	// check that its really a bottom-layer_ tensor
	assert(tdim.F() == 1);

	Tensorcd psi(phi.Dim());

	int active = tdim.getdimpart();
	assert(active == dim);

	for (int n = 0; n < tdim.getntensor(); n++){
		psi(1, n) = phi(1, n);
		psi(0, n) =-phi(0, n);
	}
	return psi;
}
