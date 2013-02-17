/*
 * =====================================================================================
 *
 *       Filename:  te.cpp
 *
 *    Description:  i
 *
 *        Version:  1.0
 *        Created:  2013年02月15日 10时33分34秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  金鹏 (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include  <algorithm>
#include <iostream>
#include  <vector>

using namespace std;

void f(vector< pair<int,int> >& v ){

	#define kpart  make_pair<int,int>  
	for( int i = 0 ; i < 10  ; i++ )
	{
		v.push_back(kpart(i,i)) ;
	}
}

void p(pair<int,int>& elem)
{
	cout << elem.first <<elem.second<< endl ;
}

int main(int argc, char *argv[])
{
	vector<pair<int,int> > v ;
	f(v);
	for_each(v.begin() , v.end() , p) ;
}
