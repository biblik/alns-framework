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

#include <stdlib.h>
#include <time.h>
#include "TSP_Random_Removal.h"
#include "ALNS_inc.h"
#include "TSPSolution.h"

TSP_Random_Removal::TSP_Random_Removal(std::string s): ADestroyOperator(10,20,s) {
	// TODO Auto-generated constructor stub

}

TSP_Random_Removal::~TSP_Random_Removal() {
	// TODO Auto-generated destructor stub
}

void TSP_Random_Removal::destroySolution(ISolution& sol)
{
	TSPSolution& tspsol = dynamic_cast<TSPSolution&>(sol);
	int randomDest = (rand() % static_cast<int>(0.1 * static_cast<double>(tspsol.getCustomerSequence().size()))) + static_cast<int>(0.1 * static_cast<double>(tspsol.getCustomerSequence().size()));
	for(int i = 0; i < randomDest; i++)
	{
		int pos = rand() % tspsol.getCustomerSequence().size();
		tspsol.remove(pos);
	}
}
