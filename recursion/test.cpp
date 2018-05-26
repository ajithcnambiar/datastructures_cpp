#include <iostream>
#include <vector>
using namespace std;

void show(vector<int>& v)
{
  auto itr = v.begin();
  while(itr != v.end())
  {
    cout << *itr << " ";
    itr++;
  }
  cout << endl;
}

class QuickSort
{
  void exch (vector<int>& a, int i, int j)
  {
    int t = a[i];
    a[i] = a[j];
    a[j] = t;
  }
  bool less (vector<int>& a, int i, int j)
  {
    return a[i] < a[j];
  }
  int partition (vector<int>& a, int lo, int hi)
  {
    int i = lo;
    int j = hi+1;
    while(true)
    {
      while(less(a, ++i, lo)) if (i >= hi) break;
      while(less(a, lo, --j)) if (j <= lo) break;
      
      if (i >= j) break;
      
      exch(a, i, j);
      
    }
    exch (a, lo, j);
    return j;
  }
  void sort(vector<int>& a, int lo, int hi)
  {
      if(lo >= hi) return;
      int p = partition (a, lo, hi);
      sort (a, lo, p-1);
      sort(a, p+1, hi);
      
  }
  public:
   QuickSort(vector<int>& v)
   {
     sort(v, 0, v.size());
   }
};

// To execute C++, please define "int main()"
int main() {
  vector<int> a ({2, 1, 5, 0});
  QuickSort q(a);
  show(a);
 
}


/* 
Your previous Plain Text content is preserved below:

This is just a simple shared plaintext pad, with no execution capabilities.

When you know what language you'd like to use for your interview,
simply choose it from the dropdown in the top bar.

You can also change the default language your pads are created with
in your account settings: https://coderpad.io/settings

Enjoy your intervie
 */