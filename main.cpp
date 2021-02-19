#include <iostream>
#include <cmath>
#include <random>
#include <iostream>
#include<iomanip>

#include "simulation.cpp"

#include "mathAnalysis.cpp"

using namespace std;

double rounding(double, int);

class result_set {
public:
	string name;
	vector<double> Ly;		//  
	vector<double> Wy;		// 整個系統的waiting time 
	vector<double> QLy;
	vector<double> QWy;		// queue的waiting time 
	// vector<double> dropy;
	
	result_set(string name) {
		this->name = name;
	}
	
	void add_L_W_QL_QW(double L, double W, double QL, double QW) {
		this->Ly.emplace_back(L);
		this->QLy.emplace_back(QL);
		this->Wy.emplace_back(W);
		this->QWy.emplace_back(QW);
	}
	
	void print_result() {
		
		cout << name << "_L\t[" << setiosflags(ios::fixed) << setprecision(4) <<  rounding(Ly[0], 4);
		for (int i=1; i<Ly.size(); i++) {
			cout << ", " << setiosflags(ios::fixed) << setprecision(4) <<  rounding(Ly[i], 4);
		}
		cout << "]" << endl << name << "_QL\t[" << setiosflags(ios::fixed) << setprecision(4) << rounding(QLy[0],4);
		for (int i=1; i<QLy.size(); i++) {
			cout << ", " << setiosflags(ios::fixed) << setprecision(4) <<  rounding(QLy[i], 4);
		}
		cout << "]" << endl << name << "_W\t[" << setiosflags(ios::fixed) << setprecision(4) <<  rounding(Wy[0],4);
		for (int i=1; i<Wy.size(); i++) {
			cout << ", " << setiosflags(ios::fixed) << setprecision(4) <<  rounding(Wy[i], 4);
		}
		cout << "]" << endl << name << "_QW\t[" << setiosflags(ios::fixed) << setprecision(4) <<  rounding(QWy[0],4);
		for (int i=1; i<QWy.size(); i++) {
			cout << ", " << setiosflags(ios::fixed) << setprecision(4) <<  rounding(QWy[i], 4);
		}
		cout << "]" << endl << endl;
		
		
		/*
		 << name << "_drop\t[" << setiosflags(ios::fixed) << setprecision(4) <<  rounding(dropy[0],4);
		for (int i=1; i<dropy.size(); i++) {
			cout << ",\t" << setiosflags(ios::fixed) << setprecision(4) <<  rounding(dropy[i], 4);
		}
		cout << "]" << endl << endl;
		*/
	}
	
	void print_result_forPY() {
		
		cout << name << "_L = [" << setiosflags(ios::fixed) << setprecision(4) <<  rounding(Ly[0], 4);
		for (int i=1; i<Ly.size(); i++) {
			cout << ", " << setiosflags(ios::fixed) << setprecision(4) <<  rounding(Ly[i], 4);
		}
		cout << "]" << endl << name << "_QL = [" << setiosflags(ios::fixed) << setprecision(4) << rounding(QLy[0],4);
		for (int i=1; i<QLy.size(); i++) {
			cout << ", " << setiosflags(ios::fixed) << setprecision(4) <<  rounding(QLy[i], 4);
		}
		cout << "]" << endl << name << "_W = [" << setiosflags(ios::fixed) << setprecision(4) <<  rounding(Wy[0],4);
		for (int i=1; i<Wy.size(); i++) {
			cout << ", " << setiosflags(ios::fixed) << setprecision(4) <<  rounding(Wy[i], 4);
		}
		cout << "]" << endl << name << "_QW = [" << setiosflags(ios::fixed) << setprecision(4) <<  rounding(QWy[0],4);
		for (int i=1; i<QWy.size(); i++) {
			cout << ", " << setiosflags(ios::fixed) << setprecision(4) <<  rounding(QWy[i], 4);
		}
		cout << "]" << endl << endl;
		
		
		/*
		 << name << "_drop\t[" << setiosflags(ios::fixed) << setprecision(4) <<  rounding(dropy[0],4);
		for (int i=1; i<dropy.size(); i++) {
			cout << ",\t" << setiosflags(ios::fixed) << setprecision(4) <<  rounding(dropy[i], 4);
		}
		cout << "]" << endl << endl;
		*/
	}
	
	void result_clear() {
		Ly.clear();
		Wy.clear();
		QLy.clear();
		QWy.clear();
	}
};

int main() {
	const int cusNum = 50000;
	
	const double lam = 2.0;
	const double mu = 8.0;
	const int s = 1;
	const int k = 200000;
	vector<double> x;
	
	result_set MMs_math_rst("MMs_MATH");
	result_set MG1_math_rst("MG1_MATH");
	result_set MMs_sim_rst("MMs_SIM");
	result_set MG1_sim_rst("MG1_SIM");
	
	result_set GMm_sim_rst("GMm_SIM");
	
	mathAnalysis mathAna;
	
	for (float i=1.5; i<6; i++) {
		x.emplace_back(i);
		//把lambda當成變數 
		simulation MMs_sim(i, mu, s, k, cusNum, "MMs");
		MMs_sim.run();
		MMs_sim_rst.add_L_W_QL_QW(MMs_sim.avgWaitLen,
								  MMs_sim.avgWaitTime,
								  MMs_sim.avgQWaitLen,
								  MMs_sim.avgQWaitTime);
		
		simulation MG1_sim(i, mu, s, k, cusNum, "MG1");
		MG1_sim.run();
		MG1_sim_rst.add_L_W_QL_QW(MG1_sim.avgWaitLen,
								  MG1_sim.avgWaitTime,
								  MG1_sim.avgQWaitLen,
								  MG1_sim.avgQWaitTime);
								  
		simulation GMm_sim(i, mu, s, k, cusNum, "GMm");
		GMm_sim.run();
		GMm_sim_rst.add_L_W_QL_QW(GMm_sim.avgWaitLen,
								  GMm_sim.avgWaitTime,
								  GMm_sim.avgQWaitLen,
								  GMm_sim.avgQWaitTime);
		
		MMs_math_rst.add_L_W_QL_QW(mathAna.L_(i, mu, s, k),
								   mathAna.W_(i, mu, s, k),
								   mathAna.Lq(i, mu, s, k),
								   mathAna.Wq(i, mu, s, k));
									
		MG1_math_rst.add_L_W_QL_QW(mathAna.MG1_L(i, mu, s, k),
								   mathAna.MG1_W(i, mu, s, k),
								   mathAna.MG1_Lq(i, mu, s, k),
								   mathAna.MG1_Wq(i, mu, s, k));
	}
	
	
	cout << "Env. " << endl << "mu = 6.0, s = 1, k = inf." << endl;
	
	cout << "lambda = \t[" << setiosflags(ios::fixed) << setprecision(4) <<  rounding(x[0], 4);
	for (int i=1; i<x.size(); i++) {
		cout << ", " << setiosflags(ios::fixed) << setprecision(4) <<  rounding(x[i], 4);
	}
	cout << "]" << endl << endl;
	
	MMs_sim_rst.print_result_forPY();
	MMs_math_rst.print_result_forPY();
	MG1_sim_rst.print_result_forPY();
	MG1_math_rst.print_result_forPY();
	GMm_sim_rst.print_result_forPY();
	
	// Reset the rst_lists
	x.clear();
	MMs_sim_rst.result_clear();
	MMs_math_rst.result_clear();
	MG1_sim_rst.result_clear();
	MG1_math_rst.result_clear();
	GMm_sim_rst.result_clear();
	
	for (float i=2.5; i<7; i++) {
		x.emplace_back(i);
		//把mu當成變數 
		simulation MMs_sim(lam, i, s, k, cusNum, "MMs");
		MMs_sim.run();
		MMs_sim_rst.add_L_W_QL_QW(MMs_sim.avgWaitLen,
								  MMs_sim.avgWaitTime,
								  MMs_sim.avgQWaitLen,
								  MMs_sim.avgQWaitTime);
		
		simulation MG1_sim(lam, i, s, k, cusNum, "MG1");
		MG1_sim.run();
		MG1_sim_rst.add_L_W_QL_QW(MG1_sim.avgWaitLen,
								  MG1_sim.avgWaitTime,
								  MG1_sim.avgQWaitLen,
								  MG1_sim.avgQWaitTime);
								  
		simulation GMm_sim(lam, i, s, k, cusNum, "GMm");
		GMm_sim.run();
		GMm_sim_rst.add_L_W_QL_QW(GMm_sim.avgWaitLen,
								  GMm_sim.avgWaitTime,
								  GMm_sim.avgQWaitLen,
								  GMm_sim.avgQWaitTime);
		
		MMs_math_rst.add_L_W_QL_QW(mathAna.L_(lam, i, s, k),
								   mathAna.W_(lam, i, s, k),
								   mathAna.Lq(lam, i, s, k),
								   mathAna.Wq(lam, i, s, k));
									
		MG1_math_rst.add_L_W_QL_QW(mathAna.MG1_L(lam, i, s, k),
								   mathAna.MG1_W(lam, i, s, k),
								   mathAna.MG1_Lq(lam, i, s, k),
								   mathAna.MG1_Wq(lam, i, s, k));
	}
	
	cout << "Env. " << endl << "lam = 2.0, s = 1, k = inf." << endl;
	
	cout << "mu = \t[" << setiosflags(ios::fixed) << setprecision(4) <<  rounding(x[0], 4);
	for (int i=1; i<x.size(); i++) {
		cout << ", " << setiosflags(ios::fixed) << setprecision(4) <<  rounding(x[i], 4);
	}
	cout << "]" << endl << endl;
	
	MMs_sim_rst.print_result_forPY();
	MMs_math_rst.print_result_forPY();
	MG1_sim_rst.print_result_forPY();
	MG1_math_rst.print_result_forPY();
	GMm_sim_rst.print_result_forPY();

	// Reset the rst_lists
	x.clear();
	MMs_sim_rst.result_clear();
	MMs_math_rst.result_clear();
	MG1_sim_rst.result_clear();
	MG1_math_rst.result_clear();
	GMm_sim_rst.result_clear();
	
	for (int i=1; i<6; i++) {
		x.emplace_back(i);
		//把s當成變數 
		simulation MMs_sim(4.0, mu, i, k, cusNum, "MMs");
		MMs_sim.run();
		MMs_sim_rst.add_L_W_QL_QW(MMs_sim.avgWaitLen,
								  MMs_sim.avgWaitTime,
								  MMs_sim.avgQWaitLen,
								  MMs_sim.avgQWaitTime);
								  
		simulation GMm_sim(4.0, mu, i, k, cusNum, "GMm");
		GMm_sim.run();
		GMm_sim_rst.add_L_W_QL_QW(GMm_sim.avgWaitLen,
								  GMm_sim.avgWaitTime,
								  GMm_sim.avgQWaitLen,
								  GMm_sim.avgQWaitTime);
		
		MMs_math_rst.add_L_W_QL_QW(mathAna.L_(4.0, mu, i, k),
								   mathAna.W_(4.0, mu, i, k),
								   mathAna.Lq(4.0, mu, i, k),
								   mathAna.Wq(4.0, mu, i, k));
	}
	cout << "Env. " << endl << "lam = 4.0, mu = 6.0, k = inf." << endl;
	
	cout << "s = \t[" << setiosflags(ios::fixed) << setprecision(4) <<  rounding(x[0], 4);
	for (int i=1; i<x.size(); i++) {
		cout << ", " << setiosflags(ios::fixed) << setprecision(4) <<  rounding(x[i], 4);
	}
	cout << "]" << endl << endl;
	
	MMs_sim_rst.print_result_forPY();
	MMs_math_rst.print_result_forPY();
	GMm_sim_rst.print_result_forPY();
	
	// Reset the rst_lists
	x.clear();
	MMs_sim_rst.result_clear();
	MMs_math_rst.result_clear();
	GMm_sim_rst.result_clear();


	for (int i=2; i<7; i++) {
		x.emplace_back(i);
		//把k當成變數 
		simulation MMs_sim(4.0, mu, 2, i, cusNum, "MMs");
		MMs_sim.run();
		MMs_sim_rst.add_L_W_QL_QW(MMs_sim.avgWaitLen,
								  MMs_sim.avgWaitTime,
								  MMs_sim.avgQWaitLen,
								  MMs_sim.avgQWaitTime);
								  
		simulation GMm_sim(4.0, mu, 2, i, cusNum, "GMm");
		GMm_sim.run();
		GMm_sim_rst.add_L_W_QL_QW(GMm_sim.avgWaitLen,
								  GMm_sim.avgWaitTime,
								  GMm_sim.avgQWaitLen,
								  GMm_sim.avgQWaitTime);
		
		MMs_math_rst.add_L_W_QL_QW(mathAna.L_(4.0, mu, 2, i),
								   mathAna.W_(4.0, mu, 2, i),
								   mathAna.Lq(4.0, mu, 2, i),
								   mathAna.Wq(4.0, mu, 2, i));
	}
	cout << "Env. " << endl << "lam = 4.0, mu = 6.0, s = 2" << endl;
	
	cout << "k = \t[" << setiosflags(ios::fixed) << setprecision(4) <<  rounding(x[0], 4);
	for (int i=1; i<x.size(); i++) {
		cout << ", " << setiosflags(ios::fixed) << setprecision(4) <<  rounding(x[i], 4);
	}
	cout << "]" << endl << endl;
	
	MMs_sim_rst.print_result_forPY();
	MMs_math_rst.print_result_forPY();
	GMm_sim_rst.print_result_forPY();
	
	// Reset the rst_lists
	x.clear();
	MMs_sim_rst.result_clear();
	MMs_math_rst.result_clear();
	GMm_sim_rst.result_clear();

	return 0;
} 

double rounding(double num, int index)
{
    bool isNegative = false; // whether is negative number or not
	
    if(num < 0) // if this number is negative, then convert to positive number
    {
        isNegative = true;	
        num = -num;
    }
	
    if(index >= 0)
    {
        int multiplier;
        multiplier = pow(10, index);
        num = (int)(num * multiplier + 0.5) / (multiplier * 1.0);
    }
	
    if(isNegative) // if this number is negative, then convert to negative number
    {
        num = -num;
    }
	
    return num;
}
