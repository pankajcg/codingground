#include <iostream>
#include <unordered_map>

using namespace std;

int main()
{
   int arr[10] = {99,1,95,5,97,3,96,4,5,95};
   int sum = 100;
   
   unordered_map<int, bool> uMap;
   
   for(int i = 0; i < 10; i++)
   {
       unordered_map<int, bool>::const_iterator it = uMap.find(sum-arr[i]);
       if(it != uMap.end())
       {
           uMap[arr[i]] = true;
           if((sum-arr[i]) < arr[i])
           {
                cout << sum-arr[i] << ", " << arr[i] << endl;
                break;
           }
       }
        else
            uMap[arr[i]] = true;
   }
   
   return 0;
}

