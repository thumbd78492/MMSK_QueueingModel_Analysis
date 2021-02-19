#include <cmath>

class mathAnalysis {
public:
	int lambdaN(float lam, int k, int n) {
		if (n < k)
			return lam;
		return 0;
	}
	float muN(float mu, int s, int n) {
		if (n < s)
			return n*mu;
		return s*mu;
	}
	
	int factorial(int n) {
		if ((n==0)||(n==1))
			return 1;
		else
			return n*factorial(n-1);
	}
	
	double P0(float lam, float mu, int s, int k) {
		double sum = 1.0;
		for (int i=1; i<s; i++)
			sum += (pow((lam/mu), i) / factorial(i));
		sum += ((pow((lam/mu), s) / factorial(s)) * ((1-pow((lam/(s*mu)), (k-s+1))) / (1-(lam/(s*mu)))));
		return 1/sum;
	}
	
	double Pn(float lam, float mu, int s, int k, int n) {
	    if (n<s)
	        return ((pow((lam/mu), n)) / factorial(n)) * P0(lam, mu, s, k);
	    return ((pow((lam/mu), n)) / (factorial(s) * pow(s, (n-s)))) * P0(lam, mu, s, k);
	}
	
	double Lq(float lam, float mu, int s, int k) {
	    double result = 0;
	    for (int i=s; i<k+1; i++)
	        result += ((i-s) * Pn(lam, mu, s, k, i));
	    return result;
	}
	
	double L_(float lam, float mu, int s, int k) {
	    double sum = 0;
	    double sum2 = 0;
	    for (int i=0; i<s; i++) {
	        double temp = Pn(lam, mu, s, k, i);
	        sum += i * temp;
	        sum2 += temp;
		}
	    sum2 = s * (1 - sum2);
	    return (Lq(lam, mu, s, k) + sum + sum2);
	} 
	double lambdaEff(float lam, float mu, int s, int k) 
	    {return lam * (1 - Pn(lam, mu, s, k, k));} 
	    
	double W_(float lam, float mu, int s, int k)
	    {return (L_(lam, mu, s, k) / lambdaEff(lam, mu, s, k));} 
	    
	double Wq(float lam, float mu, int s, int k)
	    {return (Lq(lam, mu, s, k) / lambdaEff(lam, mu, s, k));} 
	
	double dropRatio(float lam, float mu, int s, int k)
		{return Pn(lam, mu, s, k, k);}

	double MG1_Lq(float lam, float mu, int s, int k) {
		double var = pow( ((1/mu)*2), 2) / 12;
		// double var = pow(100/12.0, 2);
		double tmp = pow(lam, 2);
		
		return ((tmp*var)+pow(lam/mu, 2)) / (2*(1-lam/mu));
	}
	
	double MG1_L(float lam, float mu, int s, int k) {
		return MG1_Lq(lam,mu,s,k) + (lam/mu);
	}
	
	double MG1_Wq(float lam, float mu, int s, int k) {
		return MG1_Lq(lam,mu,s,k) / lam;
	}
	
	double MG1_W(float lam, float mu, int s, int k) {
		return MG1_Wq(lam,mu,s,k) + (1/mu);
	}
	
	double GMm_Wq(float lam, float mu, int s, int k) {
		// m ´N¬O s
		double sigT = pow( ((1/lam)*2), 2) / 12;
		double sigX = 1/pow(mu, 2);
		double fraction = lam * (sigT + sigX/double(s));
		double denominator = 2*(1-(lam/mu)/s);
		
		return fraction/denominator;
	}
};
