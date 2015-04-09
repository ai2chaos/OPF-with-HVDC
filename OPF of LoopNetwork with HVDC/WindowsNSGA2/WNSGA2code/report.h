/*This program subroutine is used to print the report*/

void report(int t,population *pop1_ptr, population *pop2_ptr,FILE *rep_ptr,FILE *gen_ptr, FILE *lastit);

void report(int t,population *pop1_ptr,population *pop2_ptr,FILE *rep_ptr,FILE *gen_ptr, FILE *lastit )
{
  int i,j,*be,*rptr,*rptr1; 

  float *ptr1,*ptr,*fptr,*fptr1, *ptr1_b, *ptr2_b;

  float *ptr2,*cons_ptr1,*cons_ptr2, *err2;
  
  int *gene_ptr1 ,*gene_ptr2 ;

  fprintf(rep_ptr,"\n\n---------------------------------------------------\n");
  fprintf(rep_ptr,"Generation No.     ->%d\n",t+1);
  fprintf(rep_ptr,"------------------------------------------------------\n");
  if(ncons == 0)
    fprintf(rep_ptr," variables (real %d binary %d)  fitness (%d)  rank cublen || variables  fitness rank cublen\n",nvar,nchrom,nfunc);
  else
    fprintf(rep_ptr," variables (real %d binary %d)  fitness (%d) constraint (%d) penalty rank cublen || variables  fitness constraint penalty rank cublen\n",nvar,nchrom,nfunc,ncons);
  
  pop1_ptr->ind_ptr = &(pop1_ptr->ind[0]);
  
  pop2_ptr->ind_ptr = &(pop2_ptr->ind[0]); // Deb 31/10/01


  for(i = 0;i < popsize;i++)
    {
      fprintf(rep_ptr,"\n------------------------------------------------\n"); 

      ptr1_b = &(pop1_ptr->ind_ptr->xbin[0]);
      ptr2_b = &(pop2_ptr->ind_ptr->xbin[0]);

      ptr1 = &(pop1_ptr->ind_ptr->xreal[0]);
      ptr2 = &(pop2_ptr->ind_ptr->xreal[0]);  // Deb 31/10/01
      
      fptr = &(pop1_ptr->ind_ptr->fitness[0]);
      fptr1 = &(pop2_ptr->ind_ptr->fitness[0]);
      
      rptr = &(pop1_ptr->ind_ptr->rank);
      rptr1 = &(pop2_ptr->ind_ptr->rank);
      
      cons_ptr1 = &(pop1_ptr->ind_ptr->constr[0]);
      cons_ptr2 = &(pop2_ptr->ind_ptr->constr[0]);
      
      err2 = &(pop2_ptr->ind_ptr->error);

      for(j = 0;j < nvar;j++)
	fprintf(rep_ptr,"%f ",*ptr1++);

      for(j = 0;j < nchrom; j++)
	fprintf(rep_ptr,"%f ",*ptr1_b++);
      if (t == gener-1)
	{
	  for(j = 0;j < nfunc;j++)
	    {   
	      if ((*err2 <= 0.0) && (*rptr1 == 1))
		fprintf(lastit,"%f\t",*fptr1++);
	      else *fptr1++;
	    }
	  if ((*err2 <= 0.0) && (*rptr1 == 1))
	    fprintf(lastit,"\n");
	}
      fptr =  &(pop1_ptr->ind_ptr->fitness[0]);
      fptr1 = &(pop2_ptr->ind_ptr->fitness[0]);
      
      for(j = 0;j < nfunc;j++)
	fprintf(rep_ptr,"  %.4f",*fptr++);
      
      if(ncons != 0)
	{
	  for(j = 0;j < ncons;j++)
	    fprintf(rep_ptr,"  %.2e",*cons_ptr1++);
	  fprintf(rep_ptr," %.2e",pop1_ptr->ind_ptr->error);
	}
      
      fprintf(rep_ptr," %d ",*rptr);
      
      fprintf(rep_ptr,"%f ",pop1_ptr->ind_ptr->cub_len);
      fprintf(rep_ptr,"|**|");

      for(j = 0;j < nvar;j++)
	{
	  fprintf(rep_ptr," %f ",*ptr2);
	  fprintf(gen_ptr," %f ",*ptr2++);
	}
      for(j = 0;j < nchrom; j++)
	{
	  fprintf(rep_ptr,"%f ",*ptr2_b); 
	  fprintf(gen_ptr,"%f ",*ptr2_b++);
	}
      for(j = 0;j < nfunc;j++)
	{	
	  fprintf(rep_ptr,"  %f",*fptr1);
	  fprintf(gen_ptr,"  %f",*fptr1++);
	}
      fprintf(rep_ptr," %d ",*rptr1);
      
      if(ncons != 0)
	{
	  for(j = 0;j < ncons;j++)
	    {
	      fprintf(rep_ptr,"  %.2e",*cons_ptr2);
	      fprintf(gen_ptr,"  %.2e",*cons_ptr2++);
	    }
	  fprintf(rep_ptr," %.2e",pop2_ptr->ind_ptr->error);
	  fprintf(gen_ptr," %.2e",pop2_ptr->ind_ptr->error);
	}
      
      fprintf(rep_ptr," %f ",pop2_ptr->ind_ptr->cub_len);
      
      pop1_ptr->ind_ptr = &(pop1_ptr->ind[i+1]);
      pop2_ptr->ind_ptr = &(pop2_ptr->ind[i+1]);
      
      fprintf(gen_ptr,"\n");
    }
  
  fprintf(rep_ptr,"\n--------------------------------------------------\n\n"); 
  fprintf(rep_ptr,"-------------------------------------------------------\n");
  fprintf(gen_ptr,"\n--------------------------------------------------\n\n");
  return;
}






