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
#include <iostream>
#include <vector>
#include "TSPSolution.h"

using namespace std;

TSPSolution::TSPSolution(double** dist, int nbNodes) {
	this->distanceMatrix = dist;
	this->nbNodes = nbNodes;
	cost = 0;
	for(int i = 0; i < nbNodes; i++)
	{
		nonInserted.push_back(i);
	}

}

TSPSolution::~TSPSolution() {
	customerSequence.clear();
	nonInserted.clear();
}

double TSPSolution::getObjectiveValue()
{
	return cost;
}

double TSPSolution::getPenalizedObjectiveValue()
{
	return (cost + (100*((customerSequence).size()-nbNodes)));
}

bool TSPSolution::isFeasible()
{
	return (customerSequence.size()-nbNodes) == 0;
}

bool TSPSolution::operator<(ISolution& s)
{
	if((isFeasible() && s.isFeasible()) || (!isFeasible() && !s.isFeasible()))
	{
		return static_cast<long long>(1000*getObjectiveValue()) < static_cast<long long>(1000*s.getObjectiveValue());
	}
	else
	{
		return isFeasible();
	}
}

int TSPSolution::distance(ISolution&)
{
	return 0;
}

ISolution* TSPSolution::getCopy()
{
	TSPSolution* newSol = new TSPSolution(distanceMatrix,nbNodes);
	for(size_t i = 0; i < customerSequence.size(); i++)
	{
		newSol->getCustomerSequence().push_back(customerSequence[i]);
	}
	newSol->getNonInserted().clear();
	for(size_t i = 0; i < nonInserted.size(); i++)
	{
		newSol->getNonInserted().push_back(nonInserted[i]);
	}
	newSol->recomputeCost();
	return dynamic_cast<ISolution*>(newSol);
}

void TSPSolution::insert(int node, size_t pos)
{
	if(customerSequence.empty())
	{
		customerSequence.push_back(node);
	}
	else
	{
		if(pos < customerSequence.size())
		{
			if(pos > 0)
			{
				cost -= distanceMatrix[customerSequence[pos-1]][customerSequence[pos]];
				cost += distanceMatrix[customerSequence[pos-1]][node];
				cost += distanceMatrix[node][customerSequence[pos]];
				customerSequence.insert(customerSequence.begin()+pos,node);
			}
			else
			{
				cost+= distanceMatrix[node][customerSequence.front()];
				customerSequence.insert(customerSequence.begin(),node);
			}
		}
		else
		{
			cost+= distanceMatrix[customerSequence.back()][node];
			customerSequence.push_back(node);
		}
	}
	for(vector<int>::iterator it = nonInserted.begin(); it!=nonInserted.end(); it++)
	{
		if(*it == node)
		{
			nonInserted.erase(it);
			break;
		}
	}

}

void TSPSolution::remove(size_t pos)
{
	int node = customerSequence[pos];
	if(customerSequence.size() == 1)
	{
		customerSequence.pop_back();
	}
	else
	{
		if(pos == customerSequence.size() - 1)
		{
			cost -= distanceMatrix[customerSequence[pos-1]][customerSequence[pos]];
			customerSequence.pop_back();
		}
		else if(pos == 0)
		{
			cost -= distanceMatrix[customerSequence[0]][customerSequence[1]];
			customerSequence.erase(customerSequence.begin());
		}
		else
		{
			cost -= distanceMatrix[customerSequence[pos-1]][customerSequence[pos]];
			cost -= distanceMatrix[customerSequence[pos]][customerSequence[pos+1]];
			cost += distanceMatrix[customerSequence[pos-1]][customerSequence[pos+1]];
			customerSequence.erase(customerSequence.begin()+pos);
		}
	}
	nonInserted.push_back(node);
}

double TSPSolution::evaluateInsert(int node, size_t pos)
{
	if(customerSequence.empty())
	{
		return 0;
	}
	else
	{
		if(pos < customerSequence.size())
		{
			if(pos > 0)
			{
				double delta = 0;
				delta -= distanceMatrix[customerSequence[pos-1]][customerSequence[pos]];
				delta += distanceMatrix[customerSequence[pos-1]][node];
				delta += distanceMatrix[node][customerSequence[pos]];
				return delta;
			}
			else
			{
				return distanceMatrix[node][customerSequence.front()];
			}
		}
		else
		{
			return distanceMatrix[customerSequence.back()][node];
		}
	}
}

double TSPSolution::evaluateRemove(size_t pos)
{
	if(customerSequence.size() == 1)
	{
		return 0;
	}
	else
	{
		if(pos == customerSequence.size() - 1)
		{
			return distanceMatrix[customerSequence[pos-1]][customerSequence[pos]];
		}
		else if(pos == 0)
		{
			return distanceMatrix[customerSequence[0]][customerSequence[1]];
		}
		else
		{
			double delta = 0;
			delta += distanceMatrix[customerSequence[pos-1]][customerSequence[pos]];
			delta += distanceMatrix[customerSequence[pos]][customerSequence[pos+1]];
			delta -= distanceMatrix[customerSequence[pos-1]][customerSequence[pos+1]];
			return delta;
		}
	}
}

void TSPSolution::recomputeCost()
{
	cost = 0;
	for(size_t i = 0; i < customerSequence.size()-1; i++)
	{
		cost += distanceMatrix[customerSequence[i]][customerSequence[i+1]];
	}
}

long long TSPSolution::getHash()
{
	double hash = 0;
	for(size_t i = 0; i < customerSequence.size()-1; i++)
	{
		hash += distanceMatrix[customerSequence[i]][customerSequence[i+1]]*distanceMatrix[customerSequence[i]][customerSequence[i+1]];
	}
	return static_cast<long long>(100*hash);
}
