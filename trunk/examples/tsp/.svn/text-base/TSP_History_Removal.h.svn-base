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

#ifndef TSP_HISTORY_REMOVAL_H_
#define TSP_HISTORY_REMOVAL_H_


#include <vector>
#include "ALNS_inc.h"

class ISolution;
class ALNS_Iteration_Status;

class TSP_History_Removal: public ADestroyOperator, public IUpdatable {
public:
	TSP_History_Removal(std::string, int nbNodes);
	virtual ~TSP_History_Removal();
	void destroySolution(ISolution& sol);
	void update(ISolution& sol, ALNS_Iteration_Status& status);
	int rouletteWheel(std::vector<double>& sc);
private:
	double** scores;
	int nbN;
};

#endif /* TSP_HISTORY_REMOVAL_H_ */
