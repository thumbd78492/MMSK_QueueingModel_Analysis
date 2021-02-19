#include <iostream>
#include <string>
#include <random>
#include <vector>
#include <queue>
#include <ctime>
#include <cmath>

using std::string;
using std::vector;
using std::queue;
using std::priority_queue;
using std::cout; using std::endl;

std::default_random_engine gen{static_cast<long unsigned int>(time(0))};

class simulation {
private:
	enum eventType {
		empty,
		arrive,
		serving,
		depart,
		drop
	};

	class Customer {
	public:
		int arrivalTime, serviceTime, departTime;
		eventType event;
		Customer(int arrivalTime, int serviceTime) {
			this->arrivalTime = arrivalTime;
			this->serviceTime = serviceTime;
			this->event = eventType::empty;
		}
		
		friend bool operator < (const Customer& a, const Customer& b)
		{	return a.departTime < b.departTime;	}
		
		friend bool operator > (const Customer& a, const Customer& b)
		{	return a.departTime > b.departTime;	}
	};
	
	class customerQueue {
	private:
		queue<Customer> cusList;	// ��queue�ӻs�@�A�۵M�|�Harrival time�ӱƧ� 
	public:
		void setCusQueue_MG1(float lam, float mu, int n) {
			std::uniform_int_distribution<> general_distribute_mu(0,(1/mu)*60*2);
			std::exponential_distribution<double> exp_distribute_lam(lam);
			
			Customer firstCus = Customer(0, general_distribute_mu(gen));
			this->cusList.push(firstCus);
			int preArrivalTime = 0, serviceTime, interarrivalTime;
			
			for (int i=1; i<n; i++) {
				serviceTime = general_distribute_mu(gen);
				interarrivalTime = std::round(exp_distribute_lam(gen) * 60);
				this->cusList.push(Customer(preArrivalTime + interarrivalTime, serviceTime));
				preArrivalTime = preArrivalTime + interarrivalTime;
			}
		}
		
		void setCusQueue_MMSK(float lam, float mu, int n) {
			std::exponential_distribution<double> exp_distribute_mu(mu);
			std::exponential_distribution<double> exp_distribute_lam(lam);
			
			Customer firstCus = Customer(0, std::round(exp_distribute_mu(gen) * 60));
			this->cusList.push(firstCus);
			int preArrivalTime = 0, serviceTime, interarrivalTime;
			
			for (int i=1; i<n; i++) {
				serviceTime = std::round(exp_distribute_mu(gen) * 60);
				interarrivalTime = std::round(exp_distribute_lam(gen) * 60);
				this->cusList.push(Customer(preArrivalTime + interarrivalTime, serviceTime));
				preArrivalTime = preArrivalTime + interarrivalTime;
			}
		}
		
		void setCusQueue_GMm(float lam, float mu, int n) {
			std::exponential_distribution<double> exp_distribute_mu(mu);
			std::uniform_int_distribution<> general_distribute_lam(0, (60/lam)*2);
			
			Customer firstCus = Customer(0, std::round(exp_distribute_mu(gen) * 60));
			this->cusList.push(firstCus);
			int preArrivalTime = 0, serviceTime, interarrivalTime;
			
			for (int i=1; i<n; i++) {
				serviceTime = std::round(exp_distribute_mu(gen) * 60);
				interarrivalTime = general_distribute_lam(gen);
				this->cusList.push(Customer(preArrivalTime + interarrivalTime, serviceTime));
				preArrivalTime = preArrivalTime + interarrivalTime;
			}
		}
		
		bool empty()
		{	return this->cusList.empty();	}
		
		void pop() {
			this->cusList.pop();
			return;
		}
		
		Customer front() {
			return this->cusList.front();
		}
	};
	
	
	float lam, mu;
	int idleServer, serverSize, queueSize, cusNum;
	
	customerQueue allCustomerQueue;
	queue<Customer> systemQueue;
	
	priority_queue<Customer, vector<Customer>, std::greater<Customer> > servingCustomers;
	//priority_queue<Customer> servingCustomers;

public:
	double avgWaitTime, avgQWaitTime, avgWaitLen, avgQWaitLen;
	int finishCusNum = 0, dropCusNum = 0, totalCusNum = 0;
	
	simulation(float lam, float mu, int s, int k, int n, string simType) {
		this->lam = lam;
		this->mu = mu;
		this->idleServer = s;
		this->serverSize = s;
		this->cusNum = n;
		this->queueSize = k-s;
		if (simType == "MG1")
			this->allCustomerQueue.setCusQueue_MG1(lam, mu, n);
		else if (simType == "GMm")
			this->allCustomerQueue.setCusQueue_GMm(lam, mu, n);
		else
			this->allCustomerQueue.setCusQueue_MMSK(lam, mu, n);

	}
	
	void run() {
		int nowTime = 0;

		int totalWaitTime = 0, totalQWaitTime = 0;
		int lastArr = 0;

		while (!this->allCustomerQueue.empty() || !this->servingCustomers.empty()) {
			// �q �ثe�Q�A�Ȫ�customer�̭������}�ɶ��@�M�@�N�Ө쪺customer�ݩ�F�ɶ�
			// ���Ӯɶ��֡A�N�O�U�@�ӵo�ͪ��ƥ� 
			int nextDepartTime = INT_MAX, nextArriveTime = INT_MAX;
			if (!this->allCustomerQueue.empty()) {
				nextArriveTime = this->allCustomerQueue.front().arrivalTime;
				// cout << "nextArriveTime: " << nextArriveTime << endl;
			}
			if (!this->servingCustomers.empty()) {
				nextDepartTime = this->servingCustomers.top().departTime;
				// cout << "nextDepartTime: " << nextDepartTime << endl;
			}
			
			if (nextDepartTime == INT_MAX && nextArriveTime == INT_MAX) {
				// �ƹ�W���i��|�]�i�� 
				cout << "DTime = MAX, ATime = MAX, Error.\n";
				return;
			}
			
			if (nextDepartTime <= nextArriveTime) {
				// �u���B�zdepart�ƥ�
				// �p��ɶ� 
				int timePass = nextDepartTime-nowTime;
				nowTime = nextDepartTime;
				totalWaitTime += (servingCustomers.size() + systemQueue.size())*timePass;
				totalQWaitTime += systemQueue.size() * timePass;
				
				// �B�z�ȤH 
				Customer tmp = servingCustomers.top();
				servingCustomers.pop();
				finishCusNum++;
				if (tmp.event != eventType::serving) { 
					// �ƹ�W���i��|�]�i�� 
					cout << "departing cus event is not serving, Error.\n";
					return;
				}
				tmp.event = eventType::depart;
				
				if (!systemQueue.empty()) {
					// ��queue�����U�@�ӫȤH�e�i�ӪA�� 
					Customer nextCus = systemQueue.front();
					nextCus.event = eventType::serving;
					nextCus.departTime = nowTime+nextCus.serviceTime;					
					systemQueue.pop();
					servingCustomers.push(nextCus);
				}	// �_�hservingCustomers.size()�|�p��serverSize 
			}
			else {
				// �B�zarrive�ƥ� 
				// �p��ɶ� 
				int timePass = nextArriveTime-nowTime;
				nowTime = nextArriveTime;
				totalWaitTime += (servingCustomers.size() + systemQueue.size())*timePass;
				totalQWaitTime += systemQueue.size() * timePass;
				
				lastArr = nowTime;
				
				// �B�z�ȤH 
				Customer newCus = allCustomerQueue.front();
				allCustomerQueue.pop();
				totalCusNum++;
				if (newCus.event != eventType::empty) {
					// �ƹ�W���i��|�]�i�� 
					cout << "arriving cus event is not empty, Error.\n";
					return;
				}
				if (servingCustomers.size() < serverSize) {
					// ������iserver�A��
					newCus.departTime = nowTime+newCus.serviceTime;
					newCus.event = eventType::serving;
					servingCustomers.push(newCus);
				}
				else if (systemQueue.size() < queueSize) {
					// ��i�ƶ���queue�̭�
					newCus.event = eventType::arrive;
					systemQueue.push(newCus);
				}
				else {
					// drop���o�ӫȤH
					newCus.event = eventType::drop; 
					dropCusNum++;
				}	
			}
		}
		
		/* Debug Message
		cout << "totalWaitTime: " << totalWaitTime << endl <<
			"totalQWaitTime: " << totalQWaitTime << endl;
			
		cout << "avgWaitTime: " << totalWaitTime / double(finishCusNum) << endl;
		cout << "avgQWaitTime: " << totalQWaitTime / double(finishCusNum) << endl;
		cout << "avgWaitLen: " << totalWaitTime / double(nowTime) << endl;
		cout << "avgQWaitLen: " << totalQWaitTime / double(nowTime) << endl;
		cout << "totalCusNum: " << totalCusNum << endl;
		cout << "finishCusNum: " << finishCusNum << endl;
		cout << "drop customers: " << dropCusNum << endl;
		cout << "drop ratio: " << dropCusNum / double(totalCusNum) << endl;
		cout << "last arr: " << lastArr << endl;
		cout << "arrival rate: " << totalCusNum / double(lastArr) << endl; 
		
		cout << "SIM END." << endl;
		Debug Message End */

		avgWaitTime = ( totalWaitTime / double(finishCusNum) ) / 60;
		avgQWaitTime = ( totalQWaitTime / double(finishCusNum) ) / 60;
		avgWaitLen = totalWaitTime / double(nowTime);
		avgQWaitLen = totalQWaitTime / double(nowTime);
	}
};

