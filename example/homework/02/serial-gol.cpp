using namespace std;
#include <iostream>
#include <assert.h>

// forward declarations:
void zero_domain(char *domain, int M, int N);
void print_domain(char *domain, int M, int N);
void update_domain(char *new_domain, char *old_domain, int M, int N);

int main(int argc, char **argv)
{

  //initialize mpi
  char *even_domain = nullptr;
  char *odd_domain = nullptr;

  int M, N;
  int iterations;

  if(argc < 4)
  {
    cout << "usage: " << argv[0] << " M N iterations" << endl;
    exit(0);
  }
  
  M = atoi(argv[1]); N = atoi(argv[2]); iterations = atoi(argv[3]);
  
  even_domain = new char[M*N];
  odd_domain = new char[M*N];

  zero_domain(even_domain, M, N);
  zero_domain(odd_domain, M, N);

  // fill in even_domain with something meaningful (initial state)
  // this requires min size for default values to fit:
  if((N >= 8) && (M >= 10))
  {
    even_domain[0*N+(N-1)] = 1;
    even_domain[0*N+0] = 1;
    even_domain[0*N+1] = 1;
    
    even_domain[3*N+5] = 1;
    even_domain[3*N+6] = 1;
    even_domain[3*N+7] = 1;

    even_domain[6*N+7] = 1;
    even_domain[7*N+7] = 1;
    even_domain[8*N+7] = 1;
    even_domain[9*N+7] = 1;
  }

  // here is where I might print out my picture of the initial domain
  cout << "Initial:"<<endl; print_domain(even_domain, M, N);

  for(int i = 0; i < iterations; ++i)
  {
    char *temp;
    update_domain(odd_domain, even_domain, M, N);
    // here is where I might print out my picture of the updated domain
    cout << "Iteration #" << i << endl; print_domain(odd_domain, M, N);

    // swap pointers:
    temp        = odd_domain;
    odd_domain  = even_domain;
    even_domain = temp;
  }

  // free dynamic memory:
  delete[] even_domain;
  delete[] odd_domain;

  return 0;
}

void zero_domain(char *domain, int M, int N)
{
  for(int i = 0; i < M; ++i)
    for(int j = 0; j < N; ++j)
      domain[i*N+j] = 0;
}

void print_domain(char *domain, int M, int N)
{
  // this is naive; it doesn't understand big domains at all 
  for(int i = 0; i < M; ++i)
  {
    for(int j = 0; j < N; ++j)
      cout << ((domain[i*N+j]) ? "*" : " ");
    cout << endl;
  }
}

void update_domain(char *new_domain, char *old_domain, int M, int N)
{
  int neighbor_count;
  
  for(int i = 0; i < M; ++i)
  {
    for(int j = 0; j < N; ++j)
    {
      neighbor_count = 0;
      for(int delta_i = -1; delta_i <= 1; delta_i++)
      {
	for(int delta_j = -1; delta_j <= 1; delta_j++)
	{
	  if(delta_i == 0 && delta_j == 0) //skip self
	    continue;

	  // this first implementation is sequental and wraps the vertical
	  // and horizontal dimensions without dealing with halos (ghost cells)
	  if(old_domain[((i+delta_i+M)%M)*N+((j+delta_j+N)%N)])
	     ++neighbor_count;
	    
	}
      }
      char mycell = old_domain[i*N + j];
      char newcell = 0;
      if(mycell == 0)
	newcell = (neighbor_count == 3) ? 1 : 0;
      else
	newcell = ((neighbor_count == 2)||(neighbor_count == 3)) ? 1 : 0;
      
      new_domain[i*N + j] = newcell;
    } // int j
  } // int i
}


