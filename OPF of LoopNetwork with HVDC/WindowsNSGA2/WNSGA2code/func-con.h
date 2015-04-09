/*This is the program used to evaluate the value of the function & errors
************************************************************************/

void func(population *pop_ptr);

void func(population *pop_ptr)
{
  /*File ptr to the file to store the value of the g for last iteration
    g is the parameter required for a particular problem
    Every problem is not required*/
 
  float *realx_ptr, /*Pointer to the array of x values*/
    *binx_ptr,      /* Pointer to the binary variables */
    *fitn_ptr,      /*Pointer to the array of fitness function*/
    x[2*maxvar],     /* problem variables */
    f[maxfun],     /*array of fitness values*/
    *err_ptr,      /*Pointer to the error */
    cstr[maxcons];

  int i,j,k; 
  float error, cc;

  pop_ptr->ind_ptr= &(pop_ptr->ind[0]);

  /*Initializing the max rank to zero*/
  pop_ptr->maxrank = 0;
  for(i = 0;i < popsize;i++)
    {
      pop_ptr->ind_ptr = &(pop_ptr->ind[i]);
      realx_ptr = &(pop_ptr->ind_ptr->xreal[0]);
      binx_ptr = &(pop_ptr->ind_ptr->xbin[0]);
      
      for(j = 0; j < nvar; j++)
	{ // Real-coded variables 
	  x[j] = *realx_ptr++;
	}

      for(j = 0; j < nchrom; j++)
	{ // Binary-codced variables
	  x[nvar+j] = *binx_ptr++;
	}
      
      fitn_ptr = &(pop_ptr->ind_ptr->fitness[0]);
      err_ptr = &(pop_ptr->ind_ptr->error);



      /*   DO NOT CHANGE ANYTHING ABOVE   */
      /*----------------------CODE YOUR OBJECTIVE FUNCTIONS HERE------------*/
      /*All functions must be of minimization type, negate maximization
            functions */
      /*============Start Coding Your Function From This Point=============*/
      // First fitness function
      f[0] = x[0];
      // Second Fitness Function
      f[1] = x[1];
      /*=========End Your Coding Upto This Point===============*/

      /******************************************************************/
      /*              Put The Constraints Here                          */
      /******************************************************************/
      // g(x) >= 0 type (normalize g(x) as in the cstr[1] below)
      /*===========Start Coding Here=============*/
      
      cstr[0] = x[0]*x[0]+x[1]*x[1]-1.0-0.1*cos(16.0*atan(x[0]/x[1]));
      cstr[1] = (-square(x[0]-0.5) - square(x[1]-0.5) + 0.5)/0.5;
      
      /*===========Constraints Are Coded Upto Here=============*/
      /*   DO NOT CHANGE ANYTHING BELOW  */



      for(k = 0 ; k < nfunc ;k++)
	{
	  *fitn_ptr++  = f[k];
	}
      
      for (k = 0;k < ncons; k++)
	{
	  pop_ptr->ind_ptr->constr[k] = cstr[k];
	}
      error = 0.0;
      for (k = 0;k < ncons;k++)
	{
	  cc = cstr[k];
	  if(cc < 0.0)
	    error = error - cc;
	}
      *err_ptr = error;
    }
  
  /*---------------------------* RANKING *------------------------------*/
  
  if(ncons == 0)
    ranking(pop_ptr);
  else
    rankcon(pop_ptr);

  return;
}






