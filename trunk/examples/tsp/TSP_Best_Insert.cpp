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

#include <vector>
#include "TSP_Best_Insert.h"
#include "TSPSolution.h"
#include "ALNS_inc.h"

#include <time.h>



using namespace std;

TSP_Best_Insert::TSP_Best_Insert(std::string s): ARepairOperator(s)
{
	// TODO Auto-generated constructor stub

}

TSP_Best_Insert::~TSP_Best_Insert() {
	// TODO Auto-generated destructor stub
}

void TSP_Best_Insert::repairSolution(ISolution& sol)
{
	TSPSolution& tspsol = dynamic_cast<TSPSolution&>(sol);
	while(!tspsol.getNonInserted().empty())
	{
		int pos = 0;
		int node = 0;
		double best = 100000;
		for(vector<int>::iterator it = tspsol.getNonInserted().begin(); it != tspsol.getNonInserted().end(); it++)
		{
			for(size_t i = 0; i <= tspsol.getCustomerSequence().size(); i++)
			{
				double cost = tspsol.evaluateInsert(*it,i);
				if(cost < best)
				{
					best = cost;
					pos = i;
					node = *it;
				}
			}
		}
		tspsol.insert(node, pos);
	}
}
