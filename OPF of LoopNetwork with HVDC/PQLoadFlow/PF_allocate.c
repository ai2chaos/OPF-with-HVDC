/* Memory allocation and deallocation routines */

#include <malloc.h>
#include "PowerFlow.h"


/* Function to allocate memory to a population */
void allocate_memory_rawdata (RawData_Type * RawData)
{
	int i, j;
	RawData->BusData = (Bus_Type *)malloc (Nbus * sizeof (Bus_Type));
	RawData->BranchData = (Branch_Type *)malloc (Nbranch * sizeof (Branch_Type));
    for ( i = 0; i < Nbus; i++)
    {
        allocate_memory_bus (&(RawData->BusData[i]));
    }
	for ( j = 0; j < Nbranch; j++ )
	{
		allocate_memory_branch (&(RawData->BranchData[j]));
	}
    return;
}

/*为Bus数据分配内存地址*/
void allocate_memory_bus (Bus_Type * bus)
{
	bus->BusNum = (int *)malloc (sizeof(int));
	bus->Name = (char *)malloc (13*sizeof(char));
	bus->LFarea = (int *)malloc (sizeof(int));
	bus->LossZone = (int *)malloc (sizeof(int));
	bus->Type = (int *)malloc (sizeof(int));
	bus->Vol = (float *)malloc (sizeof(float));
	bus->Deg = (float *)malloc (sizeof(float));
	bus->PL = (float *)malloc (sizeof(float));
	bus->PG = (float *)malloc (sizeof(float));
	bus->QL = (float *)malloc (sizeof(float));
	bus->QG = (float *)malloc (sizeof(float));
	bus->BaseVol = (float *)malloc (sizeof(float));
	bus->DesiredVol = (float *)malloc (sizeof(float));
	bus->MaxVol = (float *)malloc (sizeof(float));
	bus->MinVol = (float *)malloc (sizeof(float));
	bus->ShuntB = (float *)malloc (sizeof(float));
	bus->ShuntG = (float *)malloc (sizeof(float));
	bus->RemoteCtrlBus = (int *)malloc (sizeof(int));
    return;
}

/*为Branch数据分配内存地址*/
void allocate_memory_branch (Branch_Type * branch)
{
	branch->i = (int *)malloc (sizeof(int));
	branch->j = (int *)malloc (sizeof(int));
	branch->LFarea = (int *)malloc (sizeof(int));
	branch->LossZone = (int *)malloc (sizeof(int));
	branch->Circuit = (int *)malloc (sizeof(int));
	branch->Type = (int *)malloc (sizeof(int));
	branch->R = (float *)malloc (sizeof(float));
	branch->X = (float *)malloc (sizeof(float));
	branch->B = (float *)malloc (sizeof(float));
	branch->LineRate1 = (int *)malloc (sizeof(int));
	branch->LineRate2 = (int *)malloc (sizeof(int));
	branch->LineRate3 = (int *)malloc (sizeof(int));
	branch->CtrlBusNum = (int *)malloc (sizeof(int));
	branch->CtrlBusSide = (int *)malloc (sizeof(int));
	branch->K = (float *)malloc (sizeof(float));
	branch->PhaseShifterDeg = (float *)malloc (sizeof(float));
	branch->MinTap = (float *)malloc (sizeof(float));
	branch->MaxTap = (float *)malloc (sizeof(float));
	branch->StepSize = (float *)malloc (sizeof(float));
	branch->MinSorVol = (float *)malloc (sizeof(float));
	branch->MaxSorVol = (float *)malloc (sizeof(float));
	return;
}
/*
void deallocate_memory_pop (population *pop, int size)
{
    int i;
    for (i=0; i<size; i++)
    {
        deallocate_memory_ind (&(pop->ind[i]));
    }
    free (pop->ind);
    return;
}

void deallocate_memory_ind (individual *ind)
{
    int j;
    if (nreal != 0)
    {
        free(ind->xreal);
    }
    if (nbin != 0)
    {
        for (j=0; j<nbin; j++)
        {
            free(ind->gene[j]);
        }
        free(ind->xbin);
        free(ind->gene);
    }
    free(ind->obj);
    if (ncon != 0)
    {
        free(ind->constr);
    }
    return;
}
*/