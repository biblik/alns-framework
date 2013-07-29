/* ALNS_Framework - a framework to develop ALNS based solvers
 *
 * Copyright (C) 2012 Renaud Masson
 *
 * This library is free software; you can redistribute it and/or
 * modify it either under the terms of the GNU Lesser General Public
 * License version 3 as published by the Free Software Foundation
 * (the "LGPL"). If you do not alter this notice, a recipient may use
 * your version of this file under the LGPL.
 *
 * You should have received a copy of the LGPL along with this library
 * in the file COPYING-LGPL-3; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Suite 500, Boston, MA 02110-1335, USA
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY
 * OF ANY KIND, either express or implied. See the LGPL for
 * the specific language governing rights and limitations.
 *
 * The Original Code is the ALNS_Framework library.
 *
 *
 * Contributor(s):
 *	Renaud Masson
 */

#ifndef TSPSOLUTION_H_
#define TSPSOLUTION_H_

#include <vector>
#include "ALNS_inc.h"

class TSPSolution: public ISolution {
public:
	//! Constructor
	TSPSolution(double** distances, int nbNodes);
	//! Destructor.
	virtual ~TSPSolution();
	//! A getter for the value of the objective function.
	//! \return the value of the objective function of this solution.
	virtual double getObjectiveValue();
	//! \return a penalized version of the objective value if the solution
	//! is infeasible.
	virtual double getPenalizedObjectiveValue();
	//! A getter for the feasibility of the current solution.
	//! \return true if the solution is feasible, false otherwise.
	virtual bool isFeasible();
	//! A comparator.
	//! \return true if this solution is "better" than the solution it is compared to.
	virtual bool operator<(ISolution&);
	//! Compute the "distance" between solution.
	//! This feature can be used as part of the ALNS to favor the
	//! diversification process. If you do not plan to use this feature
	//! just implement a method returning 0.
	virtual int distance(ISolution&);
	//! This method create a copy of the solution.
	virtual ISolution* getCopy();
	//! Compute a hash key of the solution.
	virtual long long getHash();
	//! Simple getter.
	std::vector<int>& getCustomerSequence(){return customerSequence;};
	std::vector<int>& getNonInserted(){return nonInserted;};
	void recomputeCost();
	void insert(int node, size_t pos);
	void remove(size_t pos);
	double evaluateInsert(int node, size_t pos);
	double evaluateRemove(size_t pos);
private:
	int nbNodes;
	double** distanceMatrix;
	double cost;
	std::vector<int> customerSequence;
	std::vector<int> nonInserted;
};

#endif /* TSPSOLUTION_H_ */
