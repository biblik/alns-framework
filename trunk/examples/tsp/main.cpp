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
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "TSPSolution.h"
#include "TSP_Best_Insert.h"
#include "TSP_Random_Insert.h"
#include "TSP_Random_Removal.h"
#include "TSP_Worst_Removal.h"
#include "TSP_History_Removal.h"
#include "TSP_LS.h"
#include "ALNS_inc.h"

using namespace std;


int main(int argc, char* argv[])
{
	double* x = new double[100];
	double* y = new double[100];
	for(int i = 0; i < 100; i++)
	{
		x[i] = 100*(static_cast<double>(rand()) / RAND_MAX);
		y[i] = 100*(static_cast<double>(rand()) / RAND_MAX);
	}
	double** distances = new double*[100];
	for(int i = 0; i < 100; i++)
	{
		distances[i] = new double[100];
		for(int j = 0; j < 100; j++)
		{
			distances[i][j] = sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
		}
	}
	TSPSolution initialSol(distances,100);
	TSP_Best_Insert bestI("Best Insertion");
	TSP_Random_Insert randomI("Random Insertion");
	TSP_Random_Removal randomR("Random Removal");
	TSP_Worst_Removal worstR("Worst Removal");
	TSP_History_Removal historyR("History Removal",100);

	randomI.repairSolution(dynamic_cast<ISolution&>(initialSol));


	ALNS_Parameters alnsParam;
	alnsParam.loadXMLParameters("./param.xml");

	CoolingSchedule_Parameters csParam(alnsParam);
	csParam.loadXMLParameters("./param.xml");
	ICoolingSchedule* cs = CoolingScheduleFactory::makeCoolingSchedule(dynamic_cast<ISolution&>(initialSol),csParam);
	SimulatedAnnealing sa(*cs);



	OperatorManager opMan(alnsParam);
	opMan.addDestroyOperator(dynamic_cast<ADestroyOperator&>(randomR));
	opMan.addDestroyOperator(dynamic_cast<ADestroyOperator&>(worstR));
	opMan.addDestroyOperator(dynamic_cast<ADestroyOperator&>(historyR));
	opMan.addRepairOperator(dynamic_cast<ARepairOperator&>(bestI));
	opMan.addRepairOperator(dynamic_cast<ARepairOperator&>(randomI));

	SimpleBestSolutionManager bestSM(alnsParam);
	SimpleLocalSearchManager simpleLsManager(alnsParam);

	TSP_LS ls("My LS");
	TSP_LS lsB("LS FD");

	simpleLsManager.addLocalSearchOperator(dynamic_cast<ILocalSearch&>(ls));
	simpleLsManager.addLocalSearchOperator(dynamic_cast<ILocalSearch&>(lsB));

	ALNS alns("tspExample",dynamic_cast<ISolution&>(initialSol),dynamic_cast<IAcceptanceModule&>(sa),alnsParam,dynamic_cast<AOperatorManager&>(opMan),dynamic_cast<IBestSolutionManager&>(bestSM),dynamic_cast<ILocalSearchManager&>(simpleLsManager));

	alns.addUpdatable(dynamic_cast<IUpdatable&>(historyR));

	alns.solve();

	for(int i = 0; i < 100; i++)
	{
		delete[] distances[i];
	}
	delete[] distances;
	delete[] x;
	delete[] y;
	delete cs;

	return 0;
}
