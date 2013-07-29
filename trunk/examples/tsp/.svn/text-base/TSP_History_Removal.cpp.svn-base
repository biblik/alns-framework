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
#include <time.h>
#include <stdlib.h>
#include "TSP_History_Removal.h"
#include "TSPSolution.h"
#include "ALNS_inc.h"

using namespace std;

TSP_History_Removal::TSP_History_Removal(std::string s, int nbNodes): ADestroyOperator(10,20,s) {
	nbN = nbNodes;
	scores = new double*[nbNodes];
	for(int i = 0; i < nbNodes; i++)
	{
		scores[i] = new double[nbNodes];
		for(int j = 0; j < nbNodes; j++)
		{
			scores[i][j] = 100000;
		}
	}

}

TSP_History_Removal::~TSP_History_Removal() {
	for(int i = 0 ; i < nbN ; i++)
	{
		delete[] scores[i];
	}
	delete[] scores;
}

void TSP_History_Removal::destroySolution(ISolution& sol)
{
	TSPSolution& tspsol = dynamic_cast<TSPSolution&>(sol);
	int randomDest = (rand() % static_cast<int>(0.1 * static_cast<double>(tspsol.getCustomerSequence().size()))) + static_cast<int>(0.1 * static_cast<double>(tspsol.getCustomerSequence().size()));
	for(int i = 0; i < randomDest; i++)
	{
		vector<double> sc;
		sc.push_back(0);
		vector<int> custSeq = tspsol.getCustomerSequence();
		for(size_t i = 0; i < custSeq.size()-1; i++)
		{
			sc.push_back(scores[custSeq[i]][custSeq[i+1]]);
		}

		tspsol.remove(rouletteWheel(sc));
	}
}

int TSP_History_Removal::rouletteWheel(std::vector<double>& sc)
{
	double sum = 0;
	for(vector<double>::iterator it = sc.begin(); it != sc.end(); it++)
	{
		sum += *it;
	}
	double random = static_cast<double>(rand())/RAND_MAX;
	random *= sum;
	double cumul = 0;
	for(size_t i = 0; i < sc.size(); i++)
	{
		if(cumul + sc[i] > random)
		{
			return i;
		}
		else
		{
			cumul += sc[i];
		}
	}
	return (sc.size()-1);
}

void TSP_History_Removal::update(ISolution& sol, ALNS_Iteration_Status& status)
{
	TSPSolution& tspsol = dynamic_cast<TSPSolution&>(sol);
	vector<int> custSeq = tspsol.getCustomerSequence();
	for(size_t i = 0; i < custSeq.size()-1; i++)
	{
		if(scores[custSeq[i]][custSeq[i+1]] > tspsol.getObjectiveValue())
		{
			scores[custSeq[i]][custSeq[i+1]] = tspsol.getObjectiveValue();
		}
	}
}


