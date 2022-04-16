struct Kmeans {
	Int nn, mm, kk, nchg;
	MatDoub data, means;
	VecInt assign, count;

	Kmeans(MatDoub &ddata, MatDoub &mmeans) : nn(ddata.nrows()), mm(ddata.ncols()),
	kk(mmeans.nrows()), data(ddata), means(mmeans), assign(nn), count(kk) {
		ofstream outstream;
		outstream.open("kmeans_init_values.log");
		
        cout << "Running K-Means Clustering..." << endl << endl;
        outstream << "Running K-Means Clustering..." << endl << endl;
        
		estep();
		mstep();
		
		cout << "ddata.ncols = " << ddata.ncols() << endl;
		outstream << "ddata.ncols = " << ddata.ncols() << endl;
		cout << "mm(ddata.ncols) = mm(" << ddata.ncols() << ")" << endl;
		outstream << "mm(ddata.ncols) = mm(" << ddata.ncols() << ")" << endl;
		cout << "ddata.nrows() = " << ddata.nrows() << endl;
		outstream << "ddata.nrows() = " << ddata.nrows() << endl;
		cout << "nn(ddata.nrows()) = nn(" << ddata.nrows() << ")" << endl;
		outstream << "nn(ddata.nrows()) = nn(" << ddata.nrows() << ")" << endl;
		cout << "mmeans.nrows() = " << mmeans.nrows() << endl;
		outstream << "mmeans.nrows() = " << mmeans.nrows() << endl;
		cout << "kk(mmeans.nrows()) = kk(" << mmeans.nrows() << ")" << endl;
		outstream << "kk(mmeans.nrows()) = kk(" << mmeans.nrows() << ")" << endl;
		//assign(nn), count(kk)
		cout << "assign(nn) = assign(" << nn << ")" << endl;
		outstream << "assign(nn) = assign(" << nn << ")" << endl;
		cout << "count(kk) = count(" << kk << ")" << endl;
		outstream << "count(kk) = count(" << kk << ")" << endl;
	}
	Int estep() {
		Int k,m,n,kmin;
		Doub dmin,d, sum_dmin;
		nchg = 0;

		ofstream outstream;
		outstream.open("kmeans_estep.log");
		cout << "===== KMeans E-step (Euclidian points assignment into the clusters) =====" << endl;
		outstream << "===== KMeans E-step (Euclidian points assignement into clusters) =====" << endl;

		for (k=0;k<kk;k++) count[k] = 0;
		for (n=0;n<nn;n++) {
			dmin = 9.99e99;
			//dmin = 3;
			for (k=0;k<kk;k++) {
				for (d=0.,m=0; m<mm; m++) {
                    d += SQR(data[n][m]-means[k][m]);
                    cout << "Square Distance (d) = " << d /*SQR(data[n][m]-means[k][m])*/ << endl;
                    outstream << "Square Distance (d) = " << d /*SQR(data[n][m]-means[k][m])*/ << endl;
                }
                //Ajouté le 26/06/2020 Par Anselme R. Affane M.
                Doub edist = sqrt(d);
                cout << "Euclidian Distance = " << edist << endl;
                outstream << "Euclidian Distance = " << edist << endl;
                cout << endl;
                outstream << endl;
                if (edist < dmin) {dmin = edist; kmin = k;}
				//if (d < dmin) {dmin = d; kmin = k;}
			}
			//Ajout
			sum_dmin += dmin;
			if (kmin != assign[n]) nchg++;
			assign[n] = kmin;
			count[kmin]++;
			cout << "Affectation : " << endl;
			outstream << "Affectation : " << endl;
			cout << "The element (P" << (1+n) << "), is assign to the cluster (C" << (1+assign[n]) << ")" << endl << endl;
			outstream << "The element (P" << (1+n) << "), is assign to the cluster (C" << (1+assign[n]) << ")" << endl << endl;
		}
		cout << "Sum of dmin = " << sum_dmin << endl;
		outstream << "Sum of dmin = " << sum_dmin << endl;

		cout << "The converge(nchg) value is = " << nchg << endl;
		outstream << "The converge(nchg) value is = " << nchg << endl;

		return nchg;
	}
	void mstep() {
		Int n,k,m;

		ofstream outstream;
		outstream.open("kmeans_mstep.log");
		cout << "===== KMeans M-step (re-estimate the means) =====" << endl;
		outstream << "===== KMeans M-step (re-estimate the means) =====" << endl;

		for (k=0;k<kk;k++) for (m=0;m<mm;m++) means[k][m] = 0.;
		for (n=0;n<nn;n++)
			for (m=0;m<mm;m++) {
				cout << "n = " << n << ", assign[n] = " << assign[n] << ", m = " << m << endl;
				outstream << "n = " << n << ", assign[n] = " << assign[n] << ", m = " << m << endl;
				Doub sum_means = means[assign[n]][m] += data[n][m];
                cout << "means[" << assign[n] << "][" << m << "] => " << sum_means /*(means[assign[n]][m] += data[n][m])*/ << endl << endl;
                outstream << "means[" << assign[n] << "][" << m << "] => " << sum_means /*(means[assign[n]][m] += data[n][m])*/ << endl << endl;
                //cout << means[assign[n]][m] << endl;
				//outstream << means[assign[n]][m] << endl;
		}
		for (k=0;k<kk;k++) {
			if (count[k] > 0) {
				cout << "Nbr points in C(" << (k+1) << ") = " << count[k] << endl;
				outstream << "Nbr points in C(" << (k+1) << ") = " << count[k] << endl;
				for (m=0;m<mm;m++) {
                    Doub new_means = means[k][m] /= count[k];
                    cout << "New_means[" << k << "][" << m << "] => (" << means[k][m] << "/" << count[k] << ") = " << new_means /*(means[k][m] /= count[k])*/ << endl;
                    outstream << "New_means[" << k << "][" << m << "] => (" << means[k][m] << "/" << count[k] << ") = " << new_means /*(means[k][m] /= count[k])*/ << endl;
				}
            }
		}
	}
};
