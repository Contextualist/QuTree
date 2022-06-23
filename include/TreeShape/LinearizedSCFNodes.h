#pragma once

#ifndef LINEARIZEDSCFNODES_H
#define LINEARIZEDSCFNODES_H

#include "Node.h"
#include "Tree.h"

class LinearizedSCFNodes
	/**
	 * \class LinearizedSCFNodes
	 * \ingroup TTBasis
	 * \brief The class holds a vector of pointers to the leaves in the TTBasis.
	 */
{
public:
    LinearizedSCFNodes() = default;
	~LinearizedSCFNodes() = default;

    void linearize(Tree& tree);

    std::vector<int> getAddresses() const;
    std::vector<Node*> getNodes() const;

private:
	std::vector<int> addresses_;
    std::vector<Node*> pointers_;
};

#endif // LINEARIZEDSCFNODES_H