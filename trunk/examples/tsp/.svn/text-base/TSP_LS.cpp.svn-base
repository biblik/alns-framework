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

#include "TSP_LS.h"
#include "TSPSolution.h"
#include <iostream>
#include "ALNS_inc.h"

TSP_LS::TSP_LS(std::string n) {
	name = n;

}

TSP_LS::~TSP_LS() {
	// Nothing to do.
}

bool TSP_LS::performLocalSearch(ISolution& sol)
{
	TSPSolution& tspsol = dynamic_cast<TSPSolution&>(sol);
	bool ok = false;
	bool toReturn = false;
	do
	{
		ok = false;
		for(int cust = 0; cust < tspsol.getCustomerSequence().size(); cust++)
		{
			double prevCost = tspsol.getObjectiveValue();
			int prevPos = 0;
			for(int pos = 0; pos < tspsol.getCustomerSequence().size(); pos++)
			{
				if(tspsol.getCustomerSequence()[pos] == cust)
				{
					tspsol.remove(pos);
					prevPos = pos;
					break;
				}
			}
			for(int pos = 0; pos < tspsol.getCustomerSequence().size(); pos++)
			{
				if(tspsol.evaluateInsert(cust,pos)+tspsol.getObjectiveValue()<prevCost-0.01)
				{
					tspsol.insert(cust,pos);
					prevPos = -1;
					ok = true;
					toReturn = true;
					break;
				}
			}
			if(prevPos != -1)
			{
				tspsol.insert(cust,prevPos);
			}
		}
	}while(ok);
	return toReturn;

}
