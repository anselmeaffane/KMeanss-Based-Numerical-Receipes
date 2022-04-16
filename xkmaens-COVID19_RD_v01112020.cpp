#include <iostream>
#include <fstream>
#include "nr3.h"
#include "kmeans_v01112020.h"

using namespace std;

int main(){
	Int n, nn(100);
    MatDoub ddata(nn,2);
    MatDoub mmeans(3,2);
    Doub first, second;//Variables to select data into the dataset object

    // Upload 2 dimensional Gaussian data point from a file

	ifstream instream;
    //instream.open("xdatafile_new.txt");//Radom 600 2d gaussians values with Python
    //instream.open("r_dataset-v29072020.txt");//Radom 100 2d gaussians values with R
    instream.open("dataRecovered-Death.txt");// 200 COVID-19 data points of mixture of 3 gaussians values

    for (n=0;n<nn;n++) {
    //select 1st column with "first" variable and selest the 2nd colums with "second" variable
    instream >> first >> second;
        /*ddata[n][0] = float(first);
		ddata[n][1] = float(second);*/
		ddata.add(n, 0, first);
        ddata.add(n, 1, second);
    }

   //Manual 2 dimensional means definition values
	//mu1 (x,y)
	/*mmeans[0][0] = 2.1507589;
	mmeans[0][1] = 0.7436146;
	//mu2 (x,y)
	mmeans[1][0] = 0.06903436;
	mmeans[1][1] = -2.9340691;
	//mu3 (x,y)
	mmeans[2][0] = 5.93928624;
	mmeans[2][1] = -1.5595787;*/
	//mu1 (x,y)
	mmeans[0][0] = 30.56;
	mmeans[0][1] = 2.79;
	//mu2 (x,y)
	mmeans[1][0] = 154.34;
	mmeans[1][1] = 1.00;
	//mu3 (x,y)
	mmeans[2][0] = 942.22;
	mmeans[2][1] = 21.95;

	struct Kmeans myKmeans(ddata, mmeans);
	
	//Repeat K-Means Iter times
	/*for (Int iter=1, i=1;i<iter;i++) {
		myKmeans.estep(i);
		myKmeans.mstep();
	}*/

	/*cout << endl << " Print DDATA : " << endl;
    ddata.print();

    cout << endl << " Print MMEANS : " << endl;
    mmeans.print();*/

	return 0;
}
