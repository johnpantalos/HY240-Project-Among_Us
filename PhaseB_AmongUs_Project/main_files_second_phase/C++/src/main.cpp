/***************************************************************
 *                                                             *
 * file: main.cpp                                              *
 *                                                             *
 * @Author  Skerdi Basha                         		   	   *
 * @Version 1-12-2020                             			   *
 * @email   sbash@csd.uoc.gr                                   *
 *                                                             *
 * @brief   Main function and implemetantion of among_us.h     *
 *          for the needs of CS-240 project 2020               *
 *                                                             *
 ***************************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <stack>
#include <stack>
#include <iostream>
using namespace std;

#include "among_us.h"

unsigned int primes_g[650] = { 
                                 179,    181,    191,    193,    197,    199,    211,    223,    227,    229, 
                                 233,    239,    241,    251,    257,    263,    269,    271,    277,    281, 
                                 283,    293,    307,    311,    313,    317,    331,    337,    347,    349, 
                                 353,    359,    367,    373,    379,    383,    389,    397,    401,    409, 
                                 419,    421,    431,    433,    439,    443,    449,    457,    461,    463, 
                                 467,    479,    487,    491,    499,    503,    509,    521,    523,    541, 
                                 547,    557,    563,    569,    571,    577,    587,    593,    599,    601, 
                                 607,    613,    617,    619,    631,    641,    643,    647,    653,    659, 
                                 661,    673,    677,    683,    691,    701,    709,    719,    727,    733, 
                                 739,    743,    751,    757,    761,    769,    773,    787,    797,    809, 
                                 811,    821,    823,    827,    829,    839,    853,    857,    859,    863, 
                                 877,    881,    883,    887,    907,    911,    919,    929,    937,    941, 
                                 947,    953,    967,    971,    977,    983,    991,    997,   1009,   1013, 
                                1019,   1021,   1031,   1033,   1039,   1049,   1051,   1061,   1063,   1069, 
                                1087,   1091,   1093,   1097,   1103,   1109,   1117,   1123,   1129,   1151, 
                                1153,   1163,   1171,   1181,   1187,   1193,   1201,   1213,   1217,   1223, 
                                1229,   1231,   1237,   1249,   1259,   1277,   1279,   1283,   1289,   1291, 
                                1297,   1301,   1303,   1307,   1319,   1321,   1327,   1361,   1367,   1373, 
                                1381,   1399,   1409,   1423,   1427,   1429,   1433,   1439,   1447,   1451, 
                                1453,   1459,   1471,   1481,   1483,   1487,   1489,   1493,   1499,   1511, 
                                1523,   1531,   1543,   1549,   1553,   1559,   1567,   1571,   1579,   1583, 
                                1597,   1601,   1607,   1609,   1613,   1619,   1621,   1627,   1637,   1657, 
                                1663,   1667,   1669,   1693,   1697,   1699,   1709,   1721,   1723,   1733, 
                                1741,   1747,   1753,   1759,   1777,   1783,   1787,   1789,   1801,   1811, 
                                1823,   1831,   1847,   1861,   1867,   1871,   1873,   1877,   1879,   1889, 
                                1901,   1907,   1913,   1931,   1933,   1949,   1951,   1973,   1979,   1987, 
                                1993,   1997,   1999,   2003,   2011,   2017,   2027,   2029,   2039,   2053, 
                                2063,   2069,   2081,   2083,   2087,   2089,   2099,   2111,   2113,   2129, 
                                2131,   2137,   2141,   2143,   2153,   2161,   2179,   2203,   2207,   2213, 
                                2221,   2237,   2239,   2243,   2251,   2267,   2269,   2273,   2281,   2287, 
                                2293,   2297,   2309,   2311,   2333,   2339,   2341,   2347,   2351,   2357, 
                                2371,   2377,   2381,   2383,   2389,   2393,   2399,   2411,   2417,   2423, 
                                2437,   2441,   2447,   2459,   2467,   2473,   2477,   2503,   2521,   2531, 
                                2539,   2543,   2549,   2551,   2557,   2579,   2591,   2593,   2609,   2617, 
                                2621,   2633,   2647,   2657,   2659,   2663,   2671,   2677,   2683,   2687, 
                                2689,   2693,   2699,   2707,   2711,   2713,   2719,   2729,   2731,   2741, 
                                2749,   2753,   2767,   2777,   2789,   2791,   2797,   2801,   2803,   2819, 
                                2833,   2837,   2843,   2851,   2857,   2861,   2879,   2887,   2897,   2903, 
                                2909,   2917,   2927,   2939,   2953,   2957,   2963,   2969,   2971,   2999, 
                                3001,   3011,   3019,   3023,   3037,   3041,   3049,   3061,   3067,   3079, 
                                3083,   3089,   3109,   3119,   3121,   3137,   3163,   3167,   3169,   3181, 
                                3187,   3191,   3203,   3209,   3217,   3221,   3229,   3251,   3253,   3257, 
                                3259,   3271,   3299,   3301,   3307,   3313,   3319,   3323,   3329,   3331, 
                                3343,   3347,   3359,   3361,   3371,   3373,   3389,   3391,   3407,   3413, 
                                3433,   3449,   3457,   3461,   3463,   3467,   3469,   3491,   3499,   3511, 
                                3517,   3527,   3529,   3533,   3539,   3541,   3547,   3557,   3559,   3571, 
                                3581,   3583,   3593,   3607,   3613,   3617,   3623,   3631,   3637,   3643, 
                                3659,   3671,   3673,   3677,   3691,   3697,   3701,   3709,   3719,   3727, 
                                3733,   3739,   3761,   3767,   3769,   3779,   3793,   3797,   3803,   3821, 
                                3823,   3833,   3847,   3851,   3853,   3863,   3877,   3881,   3889,   3907, 
                                3911,   3917,   3919,   3923,   3929,   3931,   3943,   3947,   3967,   3989, 
                                4001,   4003,   4007,   4013,   4019,   4021,   4027,   4049,   4051,   4057, 
                                4073,   4079,   4091,   4093,   4099,   4111,   4127,   4129,   4133,   4139, 
                                4153,   4157,   4159,   4177,   4201,   4211,   4217,   4219,   4229,   4231, 
                                4241,   4243,   4253,   4259,   4261,   4271,   4273,   4283,   4289,   4297, 
                                4327,   4337,   4339,   4349,   4357,   4363,   4373,   4391,   4397,   4409, 
                                4421,   4423,   4441,   4447,   4451,   4457,   4463,   4481,   4483,   4493, 
                                4507,   4513,   4517,   4519,   4523,   4547,   4549,   4561,   4567,   4583, 
                                4591,   4597,   4603,   4621,   4637,   4639,   4643,   4649,   4651,   4657, 
                                4663,   4673,   4679,   4691,   4703,   4721,   4723,   4729,   4733,   4751, 
                                4759,   4783,   4787,   4789,   4793,   4799,   4801,   4813,   4817,   4831, 
                                4861,   4871,   4877,   4889,   4903,   4909,   4919,   4931,   4933,   4937, 
                                4943,   4951,   4957,   4967,   4969,   4973,   4987,   4993,   4999,   5003, 
                                5009,   5011,   5021,   5023,   5039,   5051,   5059,   5077,   5081,   5087, 
                                5099,   5101,   5107,   5113,   5119,   5147,   5153,   5167,   5171,   5179, 
                            };

static size_t a, b, p;
static int hash_function(int tid);
stack <Player*> v;
stack <Task*> vT;

// for eject
Player *root;

/**
 * @brief Optional function to initialize data structures that 
 *        need initialization
 *
 * @return 1 on success
 *         0 on failure
 */
int initialize() {
	
	GuardNode = new Player;
	GuardNode->pid = -1;
	GuardNode->is_alien = 0;
	GuardNode->evidence = 0;
	GuardNode->tasks = NULL;
	GuardNode->parrent = NULL;
	GuardNode->lc = NULL;
	GuardNode->rc = NULL;
	players_tree = GuardNode;

	root = GuardNode;
	
	srand(time(NULL));

	general_tasks_ht.tasks = (struct HT_Task **) malloc (sizeof(struct HT_Task*)*max_tasks_g);
	for(int j = 0; j < max_tasks_g; j++){general_tasks_ht.tasks[j] = NULL;}
	general_tasks_ht.count = 0;

	int x = 0;
	while(x <= 649 && (p = primes_g[x]) <= max_tasks_g){
		x++;
	}
	a = rand() % (p - 1) + 1;
	b = rand() % p;

	completed_tasks_pq.tasks = (struct HT_Task *) calloc (max_tasks_g, sizeof(struct HT_Task));
	completed_tasks_pq.size = 0;
    return 1;
}

int push(int tid, int difficulty){
	int in;
	in = completed_tasks_pq.size;
	if(in == max_tasks_g) return 0;

	while(difficulty > completed_tasks_pq.tasks[(in - 1)/2].difficulty && in > 0){
		completed_tasks_pq.tasks[in].tid = completed_tasks_pq.tasks[(in - 1)/2].tid;
		completed_tasks_pq.tasks[in].difficulty = completed_tasks_pq.tasks[(in - 1)/2].difficulty;
		in = (in - 1)/2;
	}
	completed_tasks_pq.tasks[in].tid = tid;
	completed_tasks_pq.tasks[in].difficulty = difficulty;
	completed_tasks_pq.size++;
	return 1;
}

Task pop(){
	Task newtask;
	int in = 0, p;
	
	if(completed_tasks_pq.size == 0) return newtask;
	newtask.tid = completed_tasks_pq.tasks[0].tid;
	newtask.difficulty = completed_tasks_pq.tasks[0].difficulty;
	int difficulty;
	difficulty = completed_tasks_pq.tasks[completed_tasks_pq.size - 1].difficulty;
	completed_tasks_pq.size--;

	if(completed_tasks_pq.size == 1){
		completed_tasks_pq.tasks[0].tid = completed_tasks_pq.tasks[1].tid;
		completed_tasks_pq.tasks[0].difficulty = completed_tasks_pq.tasks[1].difficulty;
		return newtask;
	} 
	in = 0;
	
	while (((2*in + 1) < completed_tasks_pq.size && difficulty < completed_tasks_pq.tasks[2*in + 1].difficulty) || 
	((2*in + 2) < completed_tasks_pq.size && difficulty < completed_tasks_pq.tasks[2*in + 2].difficulty))
	{
		if(2*in + 2 < completed_tasks_pq.size){
			if(completed_tasks_pq.tasks[2*in + 1].difficulty < completed_tasks_pq.tasks[2*in + 2].difficulty){
				p = 2*in + 1;
			}
			else
			{
				p = 2*in + 2;
			}
		}
		else
		{
			p = completed_tasks_pq.size - 1;
		}
		completed_tasks_pq.tasks[in].difficulty = completed_tasks_pq.tasks[p].difficulty;
		completed_tasks_pq.tasks[in].tid = completed_tasks_pq.tasks[p].tid;
		in = p;
	}
	
	completed_tasks_pq.tasks[in].difficulty = difficulty;
	completed_tasks_pq.tasks[in].tid = completed_tasks_pq.tasks[completed_tasks_pq.size].tid;

	return newtask;
}

void Visit(struct Player *p)
{
	if(p->pid == -1) return;
	cout << "<" << p->pid << "," << p->is_alien << "> ";
}

void InOrder(struct Player *p)
{
	if(p == NULL) return;
	InOrder(p->lc);
	Visit(p);
	InOrder(p->rc);
}

Player *InsertPlayer(int pid, int is_alien){

	Player *newPlayer = new Player;
	Player *P;
	Player *prev = NULL;

	newPlayer->pid = pid;
	newPlayer->is_alien = is_alien;
	newPlayer->evidence = 0;
	newPlayer->lc = GuardNode;
	newPlayer->rc = GuardNode;

	if(players_tree->lc == NULL || players_tree->rc == NULL){
		players_tree = newPlayer;
		newPlayer->parrent = NULL;
		newPlayer->lc = GuardNode;
		newPlayer->rc = GuardNode;
		return players_tree;
	}

	P = players_tree;

	while(P != GuardNode)
	{
		if(P->pid == pid)
		{
			P->is_alien = is_alien;
			P->evidence = 0;
			return players_tree;
		}
		prev = P;
		if(pid < P->pid)
		{
			P = P->lc;
		}
		else
		{
			P = P->rc;
		}	
	}

	if(prev == NULL)
	{
		return newPlayer;
	} 
	else if(pid < prev->pid)
	{
		prev->lc = newPlayer;
		newPlayer->parrent = prev;
	}
	else
	{
		prev->rc = newPlayer;
		newPlayer->parrent = prev;
	}
	return players_tree;
}

Player *Search_Player(int pid){
	Player *P = players_tree;
	while(P != GuardNode)
	{
		if(P->pid == pid)
		{
			return P;
		}
		if(pid < P->pid)
		{
			P = P->lc;
		}
		else
		{
			P = P->rc;
		}
	}
	return P;
}

static int hash_function(int tid)
{
	return (((a*tid + b)% p )% max_tasks_g);
} 

int General_Task_Insert(int tid, int difficulty)
{
	HT_Task *tmp;
	tmp = general_tasks_ht.tasks[hash_function(tid)];

	HT_Task * NewTask = new HT_Task;
	NewTask->tid = tid;
	NewTask->difficulty = difficulty;
	general_tasks_ht.count++;

	if(tmp == NULL)
	{
		general_tasks_ht.tasks[hash_function(tid)] = NewTask;
		NewTask->next = NULL;
	}
	else
	{
		while(tmp->next != NULL)tmp = tmp->next;
		tmp->next = NewTask;
		NewTask->next = NULL;
	}
	return 1;
}

int lcn = 0;
void IOR(struct Task *p)
{
	if(p == NULL) return;
	IOR(p->lc);
	lcn++;
	IOR(p->rc);
}

HT_Task *tmp_task;
static int count = 0; 
static int q = 0;
static int flag = 0;
void Insert_Task_To_Player(struct Player *p)
{
	if(general_tasks_ht.count > count){
		
		while(general_tasks_ht.tasks[q] == NULL) q++;
		tmp_task = general_tasks_ht.tasks[q];

		for(int i = flag; i > 0; i--) tmp_task = tmp_task->next;

		Task *P;
		Task *prev = NULL;
		Task *NewTask = new Task;
		NewTask->tid = tmp_task->tid;
		NewTask->difficulty = tmp_task->difficulty;
		NewTask->lcnt = 0;
		count++;

		if(p->tasks == NULL){
			p->tasks = NewTask;
			NewTask->lc = NULL;
			NewTask->rc = NULL;
			if(tmp_task->next != NULL)
			{
				flag++;
			}
			else
			{
				flag = 0;
				q++;
				while(general_tasks_ht.tasks[q] == NULL) q++;
			}
			return;
		}

		P = p->tasks;

		while(P != NULL)
		{
			prev = P;
			if(tmp_task->tid < P->tid)
			{
				P = P->lc;
			}
			else
			{
				P = P->rc;
			}	
		}

		if(prev == NULL)
		{
			return;
		} 
		else if(tmp_task->tid < prev->tid)
		{
			prev->lc = NewTask;
		}
		else
		{
			prev->rc = NewTask;
		}

		if(tmp_task->next != NULL)
		{
			flag++;
		}
		else
		{
			flag = 0;
			q++;
			while(general_tasks_ht.tasks[q] == NULL) q++;
		}
		IOR(NewTask->lc);
		NewTask->lcnt = lcn;
		lcn = 0;
	}
}

void Distribute_Tasks_To_Players(struct Player *p)
{
	if(p == NULL) return;
	Distribute_Tasks_To_Players(p->lc);

	if(p->is_alien == 0 && p->pid != -1) Insert_Task_To_Player(p);

	Distribute_Tasks_To_Players(p->rc);
}


// for eject : 													begin

void InOrderVector(struct Player *p, int pid)
{
	if(p == NULL) return;
	InOrderVector(p->lc, pid);
	if(p->pid != pid && p != GuardNode)
	{
		p->parrent = NULL;
		v.push(p);
	}
	InOrderVector(p->rc, pid);
}

int Delete_Player(int pid_1) {

	int child = 0;
    Player* parent = NULL;
    Player* curr;
	curr = Search_Player(pid_1);
	root = curr;

	Player *P1 = Search_Player(pid_1);
	Task *eject_Tasks = P1->tasks;

    if (curr == NULL || curr == GuardNode)
        return 0;

    if (curr->lc == GuardNode && curr->rc == GuardNode)
    {
        if (curr != root)
        {
            if (curr->parrent->lc == curr)
                curr->parrent->lc = GuardNode;
            else if(curr->parrent->rc == curr)
                curr->parrent->rc = GuardNode;
        }
        else
		{
            root = GuardNode;
			if (curr->parrent->lc == curr)
                curr->parrent->lc = GuardNode;
            else if(curr->parrent->rc == curr)
                curr->parrent->rc = GuardNode;
		}
    }
	else
	{
		Player *par = P1->parrent;
		InOrderVector(P1, pid_1);
	
		if(P1 != players_tree && P1 != GuardNode)
		{
			if(P1->parrent->lc == P1)
			{
				par->lc = GuardNode;
				child = -1;
			}
			else if (P1->parrent->rc == P1)
			{
				par->rc = GuardNode;
				child = 1;
			}
		}
	
		P1->parrent = NULL;
		P1->lc = GuardNode;
		P1->rc = GuardNode;
		P1->parrent = NULL;
		root = GuardNode;            
		Player *prev = NULL;
		Player *P;
		Player *NP;
		
		while(!v.empty())
		{
			prev = NULL;

			Player *NP = v.top();
			NP->lc = GuardNode;
			NP->rc = GuardNode;
			v.pop();

			if(root->lc == NULL && root->rc == NULL){
				root = NP;
				NP->lc = GuardNode;
				NP->rc = GuardNode;
				continue;
			}
			P = root;
			while(P != GuardNode)
			{
				if(P->pid == NP->pid)
				{
					P->is_alien = NP->is_alien;
					P->evidence = 0;
					return 0;
				}
				prev = P;
				if(NP->pid < P->pid)
				{
					P = P->lc;
				}
				else
				{
					P = P->rc;
				}	
			}

			if(prev == NULL)
			{
				return 1;
			} 
			else if(NP->pid < prev->pid)
			{
				prev->lc = NP;
				NP->parrent = prev;
			}
			else
			{
				prev->rc = NP;
				NP->parrent = prev;
			}
		}

		if(child == -1){
			par->lc = root;
		}
		else if(child == 1)
		{
			par->rc = root;
		}

		if(P1 != players_tree){
			root->parrent = par;
		}
		else
		{
			players_tree = root;
			players_tree->parrent = NULL;
		}
	}
return 1;
}

void InOrderVectorTasks(struct Task *p)
{
	if(p == NULL) return;
	InOrderVectorTasks(p->lc);
	vT.push(p);
	InOrderVectorTasks(p->rc);
}

int Distribute_Task_From_Ejected_Player(Task *eject_Tasks, int pid_2) {
	Player *P2 = Search_Player(pid_2);

	InOrderVectorTasks(eject_Tasks);
	InOrderVectorTasks(P2->tasks);

	P2->tasks = NULL;

		Task *prev;
		Task *P;
		Task *NP;
		
		while(!vT.empty())
		{
			prev = NULL;

			Task *NP = vT.top();
			NP->lc = NULL;
			NP->rc = NULL;
			vT.pop();

			if(P2->tasks == NULL){
				P2->tasks = NP;
				NP->lc = NULL;
				NP->rc = NULL;
				continue;
			}
			P = P2->tasks;

			while(P != NULL)
			{
				if(P->tid == NP->tid)
				{
					P->difficulty = NP->difficulty;
					return 0;
				}
				prev = P;
				if(NP->tid < P->tid)
				{
					P = P->lc;
				}
				else
				{
					P = P->rc;
				}	
			}

			if(prev == NULL)
			{
				return 1;
			} 
			else if(NP->tid < prev->tid)
			{
				prev->lc = NP;
			}
			else
			{
				prev->rc = NP;
			}
		}
return 1;
}
// for eject : 													end

//                         					 For implement  : begin

Task* minimumKey(struct Task* s)
{
    struct Task* cur = s;
 
    while (cur && cur->lc != NULL)
        cur = cur->lc;
 
    return cur;
}

void deleteNode(Task*& root, int key)
{
    Task* parent = NULL;
    Task* curr = root;
 
	while (curr != NULL && curr->tid != key)
    {
        parent = curr;
        if (key < curr->tid)
		{
            curr = curr->lc;
		}
        else
		{
            curr = curr->rc;
		}
    }
    if (curr == NULL)
        return;
 
	push(curr->tid, curr->difficulty);

    if (curr->lc == NULL && curr->rc == NULL)
    {
        if (curr != root)
        {
            if (parent->lc == curr)
			{
                parent->lc = NULL;
			}
            else
			{
                parent->rc = NULL;
			}
        }
        else
		{
            root = NULL;
		}
 
        free(curr);
    }
    else if (curr->lc && curr->rc)
    {
        Task* successor  = minimumKey(curr->rc);
        int val = successor->tid;
        deleteNode(root, successor->tid);
        curr->tid = val;
    }
    else
    {
        Task* child = (curr->lc)? curr->lc: curr->rc;
        if (curr != root)
        {
            if (curr == parent->lc)
                parent->lc = child;
            else
                parent->rc = child;
        }
        else
		{
            root = child;
		}
        free(curr);
    }
}
//                         					 For implement  : end


// for vote : 										begin
static int max_int = 0;
void Find_Player_With_Max_Evidence(struct Player *p)
{
	if(p == NULL) return;
	Find_Player_With_Max_Evidence(p->lc);
	if(max_int < p->evidence && p != GuardNode) max_int = p->evidence;
	Find_Player_With_Max_Evidence(p->rc);
}

static int pid_Evid = 1000;
void Find_Player_With_Max_Evidence_2(struct Player *p)
{
	if(p == NULL) return;
	Find_Player_With_Max_Evidence_2(p->lc);
	if(max_int == p->evidence && p != GuardNode) pid_Evid = p->pid;
	Find_Player_With_Max_Evidence_2(p->rc);
}
// for vote : 										end

void InOrderTask(struct Task *p);
void PrintPlayerWithEvidence(struct Player *p)
{
	if(p == NULL) return;
	PrintPlayerWithEvidence(p->lc);

	if(p->pid != -1 && p->pid != 1)
	{
		cout << "<Player" << p->pid << ", " << p->evidence << "> =";
		InOrderTask(p->tasks);
		cout << "\n";
	}
	PrintPlayerWithEvidence(p->rc);
}



// 									For Sabotage  :  begin
Player *PreDeccesor(int pid){
	Player *tmp = Search_Player(pid);
	if(tmp->lc != GuardNode){
		tmp = tmp->lc;
		while (tmp->rc != GuardNode) tmp = tmp->rc;
		return tmp;
	} 

	while(tmp->parrent != NULL && tmp->parrent->lc == tmp){
		tmp = tmp->parrent;
	}
	if(tmp->parrent == NULL) return NULL;

	return tmp->parrent;
}

Player *TreeSuccesor(int pid){
	Player *tmp = Search_Player(pid);

	if(tmp->rc != GuardNode){
		tmp = tmp->rc;
		while (tmp->lc != GuardNode) tmp = tmp->lc;
		return tmp;
	}

	while(tmp->parrent != NULL && tmp->parrent->rc == tmp){
		tmp = tmp->parrent;
	}
	if(tmp->parrent == NULL) return NULL;
	
	return tmp->parrent;
}

Player *TreeMax(){
	Player * tmp = players_tree;
	if(players_tree == GuardNode) return NULL;
	while (tmp->rc != GuardNode) tmp = tmp->rc;
	return tmp;
}

Player *TreeMin(){
	Player * tmp = players_tree;
	if(players_tree == GuardNode) return NULL;
	while (tmp->lc != GuardNode) tmp = tmp->lc;
	return tmp;
}

void InsertTaskToPlayer(int tid, int difficulty, int lcnt, Player *P2){

		Task *prev = NULL;
		Task *P;

		Task *NP = new Task;
		NP->tid = tid;
		NP->difficulty = difficulty;
		NP->lcnt = lcnt;

		if(P2->tasks == NULL){
			P2->tasks = NP;
			NP->lc = NULL;
			NP->rc = NULL;
			return;
		}
		P = P2->tasks;

		while(P != NULL)
		{
			if(P->tid == NP->tid)
			{
				P->difficulty = NP->difficulty;
				return;
			}
			prev = P;
			if(NP->tid < P->tid)
			{
				P = P->lc;
			}
			else
			{
				P = P->rc;
			}	
		}

		if(prev == NULL)
		{
			return;
		} 
		else if(NP->tid < prev->tid)
		{
			prev->lc = NP;
		}
		else
		{
			prev->rc = NP;
		}
}
// 									For Sabotage  :  end


// 									For print double tree : begin
void VisitTask(struct Task *p)
{
	cout << "<" << p->tid << "," << p->difficulty << "> ";
}
void InOrderTask(struct Task *p)
{
	if(p == NULL) return;
	InOrderTask(p->lc);
	VisitTask(p);
	InOrderTask(p->rc);
}
void InOrderPlayer(struct Player *p)
{
	if(p == NULL) return;
	InOrderPlayer(p->lc);

	if(p->pid != -1 && p->pid != 1)
	{
		cout << "Player" << p->pid << " = ";
		InOrderTask(p->tasks);
		cout << "\n";
	}

	InOrderPlayer(p->rc);
}
// 									For print double tree : end

/**
 * @brief Register Player
 *
 * @param pid The player's id
 *
 * @param is_alien The variable that decides if he is an alien or not
 * @return 1 on success
 *         0 on failure
 */
int register_player(int pid, int is_alien) {
	InsertPlayer(pid, is_alien);
	print_players();
    return 1;
}

/**
 * @brief Insert Task in the general task hash table
 *
 * @param tid The task id
 * 
 * @param difficulty The difficulty of the task
 *
 * @return 1 on success
 *         0 on failure
 */
int insert_task(int tid, int difficulty) {
	General_Task_Insert(tid, difficulty);
	print_tasks();
    return 1;
}

/**
 * @brief Distribute Tasks to the players
 * @return 1 on success
 *         0 on failure
 */
int distribute_tasks() {
	while(general_tasks_ht.count > count){
		Distribute_Tasks_To_Players(players_tree);
	}
	print_double_tree();
    return 1;
}

/**
 * @brief Implement Task
 *
 * @param pid The player's id
 *
 * @param tid The task's tid
 *
 * @return 1 on success
 *         0 on failure
 */
int implement_task(int pid, int tid) {
	Player *pl;
	pl = Search_Player(pid);
	deleteNode(pl->tasks, tid);
	print_double_tree();
    return 1;
}

/**
 * @brief Eject Player
 * 
 * @param pid_1 The ejected player's id
 *
 * @param pid_2 The crewmates id
 *
 * @return 1 on success
 *         0 on failure
 */
int eject_player(int pid_1, int pid_2) {

	Player *ej_pl = Search_Player(pid_1);
	Task *eject_Tasks = ej_pl->tasks;

	Delete_Player(pid_1);
	if(ej_pl->is_alien != 1) Distribute_Task_From_Ejected_Player(eject_Tasks, pid_2);

	print_double_tree();
    return 1;
}

/**
 * @brief Witness Eject Player
 *
 * @param pid_1 The ejected player's id
 * 
 * @param pid_2 The crewmate's pid
 *
 * @param pid_a The alien's pid
 * 
 * @param number_of_witnesses The number of witnesses
 *
 * @return 1 on success
 *         0 on failure
 */
int witness_eject(int pid_1, int pid_2, int pid_a, int number_of_witnesses){

	Player *ej_pl = Search_Player(pid_1);
	Task *eject_Tasks = ej_pl->tasks;

	Delete_Player(pid_1);
	if(ej_pl->is_alien != 1) Distribute_Task_From_Ejected_Player(eject_Tasks, pid_2);
	(Search_Player(pid_a)->evidence) += number_of_witnesses;
	PrintPlayerWithEvidence(players_tree);
    return 1;
}

/**
 * @brief Sabotage
 *
 * @param number_of_tasks The number of tasks to be sabotaged
 *
 * @param pid The player's id
 * 
 * @return 1 on success
 *         0 on failure
 */
int sabotage(int number_of_tasks, int pid) {

	Player *pl = Search_Player(pid);
	int i;

	for(i = number_of_tasks/2; i > 0 ; i--)
	{
		pl = PreDeccesor(pl->pid);
		if(pl == NULL) pl = TreeMax();
	}
	Task tmpts;
	
	for(i = 0; i < number_of_tasks && completed_tasks_pq.size != 0;)
	{
		if(pl->is_alien != 1)
		{
			tmpts = pop();
			InsertTaskToPlayer(tmpts.tid, tmpts.difficulty, tmpts.lcnt, pl);
			i++;
		}

		pl = TreeSuccesor(pl->pid);
		if(pl == NULL) pl = TreeMin();
	}
	print_double_tree();
    return 1;
}

/**
 * @brief Vote
 *
 * @param pid_1 The suspicious player's id
 *
 * @param pid_2 The crewmate's pid
 * 
 * @param vote_evidence The vote's evidence
 *
 * @return 1 on success
 *         0 on failure
 */
int vote(int pid_1, int pid_2, int vote_evidence) {
	(Search_Player(pid_1)->evidence) += vote_evidence;
	Find_Player_With_Max_Evidence(players_tree);
	Find_Player_With_Max_Evidence_2(players_tree);

	Player *ej_pl = Search_Player(pid_Evid);
	Task *eject_Tasks = ej_pl->tasks;

	Delete_Player(pid_Evid);

	if(ej_pl->is_alien != 1) Distribute_Task_From_Ejected_Player(eject_Tasks, pid_2);
	PrintPlayerWithEvidence(players_tree);
	return 1;
}

/**
 * @brief Give Away Work
 *
 * @param pid_1 The existing crewmate's id
 *
 * @param pid_2 The new crewmate's pid
 *
 * @return 1 on success
 *         0 on failure
 */
int give_work(int pid_1, int pid_2) {
    return 1;
}

static int aliens=0, crewmates=0;
void InOrderr(struct Player *p)
{
	if(p == NULL) return;
	InOrderr(p->lc);
	if(p->is_alien == 1){aliens++;}else if(p->is_alien == 0 && p != GuardNode){crewmates++;}
	InOrderr(p->rc);
}
/**
 * @brief Terminate
 *
 * @return 1 on success
 *         0 on failure
 */
int Terminate() {
	InOrderr(players_tree);
	if(aliens > crewmates){
		cout << "  Aliens win.\nDONE\n";
		return 1;
	}
	if(general_tasks_ht.count == completed_tasks_pq.size || aliens == 0){
		cout << "  Crewmates win.\nDONE\n";
		return 1;
	}
    return 1;
}

/**
 * @brief Print Players
 *
 * @return 1 on success
 *         0 on failure
 */
int print_players() {
	cout << "Players = ";
	InOrder(players_tree);
	cout << "\nDONE\n";
    return 1;
}

/**
 * @brief Print Tasks
 *
 * @return 1 on success
 *         0 on failure
 */
int print_tasks(){

	for(int k = 0; k < max_tasks_g; k++)
	{
		cout << "Chain " << k << ": ";
		HT_Task *tmp = general_tasks_ht.tasks[k];
		for(; tmp != NULL; tmp = tmp->next)
		{
			if(tmp != NULL) cout << "<" << tmp->tid << "," << tmp->difficulty << ">";
			if(tmp->next != NULL) cout << ", ";
		}
		cout << "\n";
	}
	cout << "DONE\n";
    return 1;
}

/**
 * @brief Print Priority Queue
 *
 * @return 1 on success
 *         0 on failure
 */
int print_pq() {
	cout << "Completed Tasks = ";
	int i = completed_tasks_pq.size - 1;
	while(i >= 0) {
        cout << "<" << completed_tasks_pq.tasks[i].tid << "," << completed_tasks_pq.tasks[i].difficulty << "> ";
		i--;
		if(i != -1) cout << ", ";
    }
    cout << "\nDONE\n";
    return 1;
}

/**
 * @brief Print Players & Task tree
 *
 * @return 1 on success
 *         0 on failure
 */
int print_double_tree() {
	InOrderPlayer(players_tree);
	cout << "\nDONE\n";
    return 1;
}

/**
 * @brief Free resources
 *
 * @return 1 on success
 *         0 on failure
 */

int free_all(void) {
    return 1;
}

#define BUFFER_SIZE 1024 /* Maximum length of a line in input file */

/* Uncomment the following line to enable debugging prints 
 * or comment to disable it */
#define DEBUG
#ifdef DEBUG
#define DPRINT(...) fprintf(stderr, __VA_ARGS__);
#else /* DEBUG */
#define DPRINT(...)
#endif /* DEBUG */

/**
 * @brief The main function
 *
 * @param argc Number of arguments
 * @param argv Argument vector
 *
 * @return 0 on success
 *         1 on failure
 */
int main(int argc, char **argv)
{
	FILE *fin = NULL;
	char buff[BUFFER_SIZE], event='\0';

	/* Check command buff arguments */
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <input_file> <>\n", argv[0]);
		return EXIT_FAILURE;
	}

	/* Open input file */
	if ((fin = fopen(argv[1], "r")) == NULL)
	{
		fprintf(stderr, "\n Could not open file: %s\n", argv[1]);
		perror("Opening test file\n");
		return EXIT_FAILURE;
	}

	// Read max enemy soldiers' number
	fgets(buff, BUFFER_SIZE, fin);
	sscanf(buff, "%d", &max_tasks_g);
	DPRINT("Max number of tasks: %d\n", max_tasks_g)

	// Read max enemy soldiers' ID
	fgets(buff, BUFFER_SIZE, fin);
	sscanf(buff, "%d", &max_tid_g);
	DPRINT("Max task tid: %d\n", max_tid_g)

	/* Initializations */
	initialize();

	/* Read input file buff-by-buff and handle the events */
	while (fgets(buff, BUFFER_SIZE, fin))
	{

		DPRINT("\n>>> Event: %s", buff);

		switch (buff[0])
		{

		/* Comment */
		case '#':
			break;

		/* Register Player
		 * P <pid> <is_alien> */
		case 'P':
		{
			int pid;
			int is_alien;
			sscanf(buff, "%c %d %d", &event, &pid, &is_alien);
			DPRINT("%c %d %d\n", event, pid, is_alien);

			if (register_player(pid, is_alien))
			{
				DPRINT("P %d %d succeeded\n", pid, is_alien);
			}
			else
			{
				fprintf(stderr, "P %d %d failed\n", pid, is_alien);
			}

			break;
		}

		/* Insert Task
		 * T <tid> <difficulty>  */
		case 'T':
		{
			int tid, difficulty;

			sscanf(buff, "%c %d %d", &event, &tid, &difficulty);
			DPRINT("%c %d %d\n", event, tid, difficulty);

			if (insert_task(tid, difficulty))
			{
				DPRINT("%c %d %d succeded\n", event, tid, difficulty);
			}
			else
			{
				fprintf(stderr, "%c %d %d failed\n", event, tid, difficulty);
			}

			break;
		}

		/* Distribute Tasks
		 * D */
		case 'D':
		{
			sscanf(buff, "%c", &event);
			DPRINT("%c\n", event);

			if (distribute_tasks())
			{
				DPRINT("%c succeeded\n", event);
			}
			else
			{
				fprintf(stderr, "%c failed\n", event);
			}

			break;
		}

		/* Implement Task
		 * I <pid> <tid> */
		case 'I':
		{
			int pid, tid;

			sscanf(buff, "%c %d %d", &event, &pid, &tid);
			DPRINT("%c %d %d \n", event, pid, tid);

			if (implement_task(pid, tid))
			{
				DPRINT("%c %d %d succeeded\n", event, pid, tid);
			}
			else
			{
				fprintf(stderr, "%c %d %d failed\n", event, pid, tid);
			}

			break;
		}

		/* Eject Player
		 * E <pid_1> <pid_2>*/
		case 'E':
		{
			int pid_1, pid_2;

			sscanf(buff, "%c %d %d", &event, &pid_1, &pid_2);
			DPRINT("%c %d %d\n", event, pid_1, pid_2);

			if (eject_player(pid_1, pid_2))
			{
				DPRINT("%c %d %d succeeded\n", event, pid_1, pid_2);
			}
			else
			{
				fprintf(stderr, "%c %d %d failed\n", event, pid_1, pid_2);
			}

			break;
		}

		/* Witness Ejection
		 * W <pid> <pid_a> <number_of_witnesses>
		 */
		case 'W':
		{
			int pid_1, pid_2 ,pid_a ,number_of_witnesses;

			sscanf(buff, "%c %d %d %d %d", &event, &pid_1, &pid_2, &pid_a, &number_of_witnesses);
			DPRINT("%c %d %d %d %d\n", event, pid_1, pid_2, pid_a, number_of_witnesses);

			if (witness_eject(pid_1, pid_2, pid_a, number_of_witnesses))
			{
				DPRINT("%c %d %d %d %d succeded\n", event, pid_1, pid_2, pid_a, number_of_witnesses);
			}
			else
			{
				fprintf(stderr, "%c %d %d %d %d failed\n", event, pid_1, pid_2, pid_a, number_of_witnesses);
			}

			break;
		}

		/* Sabotage
		 * S <number_of_tasks> <pid> */
		case 'S':
		{
			int number_of_tasks, pid;

			sscanf(buff, "%c %d %d\n", &event, &number_of_tasks, &pid);
			DPRINT("%c %d %d\n", event, number_of_tasks, pid);

			if (sabotage(number_of_tasks, pid))
			{
				DPRINT("%c %d %d succeeded\n", event, number_of_tasks, pid);
			}
			else
			{
				fprintf(stderr, "%c %d %d failed\n", event, number_of_tasks, pid);
			}

			break;
		}

		/* Vote
		 * V <pid_1> <pid_2> <vote_evidence> */
		case 'V':
		{
			int pid_1, pid_2, vote_evidence;

			sscanf(buff, "%c %d %d %d\n", &event, &pid_1, &pid_2, &vote_evidence);
			DPRINT("%c %d %d %d\n", event, pid_1, pid_2, vote_evidence);

			if (vote(pid_1, pid_2, vote_evidence))
			{
				DPRINT("%c %d %d %d succeeded\n", event, pid_1, pid_2, vote_evidence);
			}
			else
			{
				fprintf(stderr, "%c %d %d %d failed\n", event, pid_1, pid_2, vote_evidence);
			}

			break;
		}

		/* Give Away Work
		 * G <pid_1> <pid_2> */
		case 'G':
		{
			int pid_1, pid_2;

			sscanf(buff, "%c %d %d", &event, &pid_1, &pid_2);
			DPRINT("%c %d %d\n", event, pid_1, pid_2);

			if (give_work(pid_1, pid_2))
			{
				DPRINT("%c %d %d succeeded\n", event, pid_1, pid_2);
			}
			else
			{
				fprintf(stderr, "%c %d %d failed\n", event, pid_1, pid_2);
			}

			break;
		}

		/* Terminate
		 * F */
		case 'F':
		{
			sscanf(buff, "%c", &event);
			DPRINT("%c\n", event);

			if (Terminate())
			{
				DPRINT("%c succeeded\n", event);
			}
			else
			{
				fprintf(stderr, "%c failed\n", event);
			}

			break;
		}

		/* Print Players
		 * X */
		case 'X':
		{
			sscanf(buff, "%c", &event);
			DPRINT("%c\n", event);

			if (print_players())
			{
				DPRINT("%c succeeded\n", event);
			}
			else
			{
				fprintf(stderr, "%c failed\n", event);
			}

			break;
		}

		/* Print Tasks
		 * Y */
		case 'Y':
		{
			sscanf(buff, "%c", &event);
			DPRINT("%c\n", event);

			if (print_tasks())
			{
				DPRINT("%c succeeded\n", event);
			}
			else
			{
				fprintf(stderr, "%c failed\n", event);
			}

			break;
		}

		/* Print Priority Queue
		 * Z */
		case 'Z':
		{
			sscanf(buff, "%c", &event);
			DPRINT("%c\n", event);

			if (print_pq())
			{
				DPRINT("%c succeeded\n", event);
			}
			else
			{
				fprintf(stderr, "%c failed\n", event);
			}

			break;
		}

		/* Print Players & Tasks tree
		 * F */
		case 'U':
		{
			sscanf(buff, "%c", &event);
			DPRINT("%c\n", event);

			if (print_double_tree())
			{
				DPRINT("%c succeeded\n", event);
			}
			else
			{
				fprintf(stderr, "%c failed\n", event);
			}

			break;
		}

		/* Empty line */
		case '\n':
			break;

		/* Ignore everything else */
		default:
			DPRINT("Ignoring buff: %s \n", buff);

			break;
		}
	}

	free_all();
	return (EXIT_SUCCESS);
}
