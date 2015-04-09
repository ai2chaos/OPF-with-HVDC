/* This is the selection operator for the roulette wheel selection */

void roulette(population *old_pop_ptr,population *mate_pop_ptr);


void roulette(population *old_pop_ptr,population *mate_pop_ptr)
{
  int i,j,k,r,*gene1,*gene2,maxrank;
  float sum,c,cumprob[maxpop],rnd,*fit; 

  /*Find Sum of the fitness*/
  sum = 0;
  
  for (i = 0;i < popsize;i++)
    { 
      old_pop_ptr->ind_ptr = &(old_pop_ptr->ind[i]);
      fit = &(old_pop_ptr->ind_ptr->dumfit);
      r = old_pop_ptr->ind_ptr->rank;
      sum = sum +  *fit*1000*(popsize-r);
    }

  c = 0;

  /*Finding the cumulative probability for the different individuals*/
  for(i = 0;i < popsize;i++)
    {
      old_pop_ptr->ind_ptr = &(old_pop_ptr->ind[i]);
      
      fit = &(old_pop_ptr->ind_ptr->dumfit);
      
      r = old_pop_ptr->ind_ptr->rank;
      
      c = c +  *fit*1000*(popsize-r) ;
      
      cumprob[i] = c/sum ;
      
    }
  
  for(i = 0;i < popsize;i++)
   {
     rnd = randomperc();
     j = 0;
     
     /*Generate a Random No to find which individual to select*/
     
     while(rnd > cumprob[j])
       {
	 j++;
       }
     
     old_pop_ptr->ind_ptr = &(old_pop_ptr->ind[j]);
     mate_pop_ptr->ind_ptr = &(mate_pop_ptr->ind[i]);
     
     if(optype != 3)
       {
	 gene1 = &(old_pop_ptr->ind_ptr->genes[0]);
	 
	 gene2 = &(mate_pop_ptr->ind_ptr->genes[0]);
	 
	 for(k = 0;k < chrom;k++)
	   *gene2++ = *gene1++;
	 
       }
     else
       {
	 for(k = 0;k < chrom;k++)
	   mate_pop_ptr->ind_ptr->gener[k] = old_pop_ptr->ind_ptr->gener[k];
       }
     for(k = 0;k < nvar;k++)
       mate_pop_ptr->ind_ptr->xreal[k] = old_pop_ptr->ind_ptr->xreal[k];
   }
  return;
}


