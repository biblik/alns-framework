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

#ifndef TSP_BEST_INSERT_H_
#define TSP_BEST_INSERT_H_

#include "ALNS_inc.h"

class TSP_Best_Insert: public ARepairOperator {
public:
	TSP_Best_Insert(std::string s);
	virtual ~TSP_Best_Insert();
	void repairSolution(ISolution& sol);
};

#endif /* TSP_BEST_INSERT_H_ */
