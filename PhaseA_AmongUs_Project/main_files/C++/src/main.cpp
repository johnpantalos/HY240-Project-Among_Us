/***************************************************************
 *                                                             *
 * file: main.cpp                                                *
 *                                                             *
 * @Author  Antonios Peris                         		   	   *
 * @Version 20-10-2020                             			   *
 * @email   csdp1196@csd.uoc.gr                                *
 *                                                             *
 * @brief   Main function for the needs of cs-240 project 2020 *
 *                                                             *
 ***************************************************************
 */

#include "among_us.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <iostream>
using namespace std;

/***************************************************
 *                                                 *
 * file: among_us.cpp                              *
 *                                                 *
 * @Author  Antonios Peris                         *
 * @Version 20-10-2020                             *
 * @email   csdp1196@csd.uoc.gr                    *
 *                                                 *
 * @brief   Implementation of among_us.h           *
 *                                                 *
 ***************************************************
 */

/**
 * @brief Optional function to initialize data structures that 
 *        need initialization
 *
 * @return 1 on success
 *         0 on failure
 */
int initialize()
{
	players_head = new Players;
	players_head->pid = -1;
	players_head->is_alien = -2;
	players_head->evidence = -1;
	players_head->prev = NULL;
	players_head->next = NULL;

	tasks_head = new Head_GL;
	tasks_head->tasks_count[0] = 0;
	tasks_head->tasks_count[1] = 0;
	tasks_head->tasks_count[2] = 0;
	tasks_head->head = NULL;

	tasks_stack = new Head_Completed_Task_Stack;
	tasks_stack->count = 0;
	tasks_stack->head = NULL;
	return 1;
}

int Double_Linked_List_Insert(int pid, int is_alien){

	Players *pl = new Players;
    pl->pid = pid;
    pl->is_alien = is_alien;
	pl->evidence = 0;
    
    if(players_head->next == NULL && players_head->prev == NULL)
    {
        players_head->next = pl;
        players_head->prev = pl;
        pl->prev = players_head;
        pl->next = players_head;
    }
    else
    {
		pl->next = players_head;			//		τοποθετω στο τελος
		pl->prev = players_head->prev;
		(players_head->prev)->next = pl;
        players_head->prev = pl;
	}

//  Creation of Guard node
	Tasks *ts = new Tasks;
	ts->tid = -1;
	ts->difficulty = 0;
	ts->next = NULL;
	pl->tasks_head = ts;
	pl->tasks_sentinel = ts;

    return 1;
}

Players *Double_Linked_List_Search(int pid)
{
    Players *cur_pl = players_head;
    while(cur_pl->pid != pid && cur_pl->next != players_head) cur_pl = cur_pl->next; 
    
	if(cur_pl->next == players_head && cur_pl->pid != pid){
		return players_head;
	}
	return cur_pl;
}

int Double_Linked_List_Delete(int pid){
    Players *tmp_pl;
    tmp_pl = Double_Linked_List_Search(pid);

	if(tmp_pl != players_head){
    	tmp_pl->prev->next = tmp_pl->next;
    	tmp_pl->next->prev = tmp_pl->prev;
    	free(tmp_pl);
	}
    return 1;
}

int AddTask(int tid, int difficulty){					//    Προσθηκη task στη General List

    if(tasks_head->head == NULL){		//  αν : Αδεια λιστα
		Tasks *newtask = new Tasks;
		newtask->tid = tid;
		newtask->difficulty = difficulty;
		newtask->next = NULL;
		tasks_head->head = newtask;
		(tasks_head->tasks_count[difficulty-1])++; 
	}
	else
	{
		Tasks *newtask = new Tasks;
		newtask->tid = tid;
		newtask->difficulty = difficulty;
		(tasks_head->tasks_count[difficulty-1])++;

		if((tasks_head->head->difficulty) >= (newtask->difficulty)){
			newtask->next = tasks_head->head;
			tasks_head->head = newtask;
		}else{
			Tasks *tmp = tasks_head->head;
			
			while(tmp->next != NULL && ((tmp->next->difficulty) < (newtask->difficulty))){
				tmp = tmp->next;
			}
			if(tmp->next == NULL){
				tmp->next = newtask;
				newtask->next = NULL;
			}else{
				newtask->next = tmp->next;
				tmp->next = newtask;
			}
		}
	}
	return 1;
}

int Distribute_Tasks_To_Players(){
	Players *tmp_pl = players_head->next;
	Tasks *tmp_ts = tasks_head->head; //   first element of tasks list
	
	while(tmp_ts != NULL){

		while(tmp_pl->is_alien == 1 || tmp_pl == players_head)tmp_pl = tmp_pl->next;

		Tasks *nt = new Tasks;
		nt->tid = tmp_ts->tid;
		nt->difficulty = tmp_ts->difficulty;

		if(tmp_pl->tasks_head->tid != -1){			//   αν  η λιστα των τασκ του συγκεκριμενου player ειναι κενη (εχει μονο τον task sentinel)
			nt->next = tmp_pl->tasks_sentinel;
			tmp_pl->tasks_sentinel->next->next = nt;
			tmp_pl->tasks_sentinel->next = nt;
		}
		else
		{
			nt->next = tmp_pl->tasks_sentinel;
			tmp_pl->tasks_head = nt;
			tmp_pl->tasks_sentinel->next = nt;
		}
		tmp_pl = tmp_pl->next;
		tmp_ts = tmp_ts->next; 
	}
	if(tasks_head->head == NULL){return 0;}		//	αυτο συμβαινει αν η general list ειναι αδεια
	return 1;
}


Tasks *Search_A_Task_From_Player(int difficulty, struct Players *cur_pl){ 

	Tasks *cur_ts = cur_pl->tasks_head;

    if(cur_pl->tasks_head->difficulty == difficulty){
        return cur_pl->tasks_head;
    }else{
        for(; cur_ts->difficulty != difficulty; cur_ts = cur_ts->next){
            if(cur_ts->next->difficulty == 0){		//					αν δεν βρει το συγκεκριμενο task και φτασει στον sentinel
                cur_ts = cur_pl->tasks_sentinel;
                return cur_ts;
            }
        }
        return cur_ts;
    }
}

int Delete_A_Task_From_A_Player(struct Players *pl ,struct Tasks *del_task){
    
    if(pl->tasks_head->difficulty == 0){			//			αν δεν υπαρχει κανενα task σε αυτον τον player και ειναι μονο ο sentinel
		return 0;
	}else{
		if(del_task == pl->tasks_head){
			pl->tasks_head = pl->tasks_head->next;
			return 1;
		}

		Tasks *del_task_prev;
		for(del_task_prev = pl->tasks_head; del_task_prev->next != del_task; del_task_prev = del_task_prev->next){} //		αυτο χρειαζεται για να σβησουμε ενα στοιχειο μιας απλα συνδεδεμενης λιστας


		if(del_task_prev->next->next->difficulty == 0)	//	το ελεγχω για να φτιαξω και τον δεικτη : task_sentinel->next (πρπ)
		{
			del_task_prev->next = pl->tasks_sentinel;
			pl->tasks_sentinel->next = del_task_prev;
		}
		else
		{
			del_task_prev->next = del_task_prev->next->next;
		}
	}
    return 1;
}

Tasks *Push(int tid, int difficulty, struct Tasks *S){		//		η γνωστη για stack σαν απλα συνδεδεμενη λιστα
    Tasks *P = new Tasks;
    P->tid = tid;
    P->difficulty = difficulty;
    P->next = S;
    tasks_stack->head = P;
    (tasks_stack->count)++;
    return tasks_stack->head;
}

int IsEmptyStack(struct Tasks *S){		//		η γνωστη για stack σαν απλα συνδεδεμενη λιστα
    if(S == NULL){
        return 1;
    }else{
        return 0;
    }
}

Tasks *Pop(struct Tasks *S){		//		η γνωστη για stack σαν απλα συνδεδεμενη λιστα

    Tasks *P = tasks_stack->head;

    if(IsEmptyStack(S)){
		tasks_stack->head = NULL;
        return NULL;
    }else{
        tasks_stack->head = tasks_stack->head->next;
		(tasks_stack->count)--;
    }
    return P;
}

Tasks *Top(struct Tasks *S){		//		η γνωστη για stack σαν απλα συνδεδεμενη λιστα
    if(IsEmptyStack(S) == false){
        return tasks_stack->head;
    }
    else
    {
        return NULL;
    }
    return NULL;
}

Players *Search_Player_With_Less_Tasks(int pid) 
{
    Players *current_pl = players_head->next;
    Tasks *current_task = current_pl->tasks_head;
    int min = 10000, tmp;

	for(;current_pl != players_head; current_pl = current_pl->next){
        tmp = 0;
        while(current_pl->pid == pid || current_pl->is_alien == 1) // "current_pl->pid == pid"  =>  o player me pid den tha prepei na elegxetai gia to posa tasks exei
        {
            if (current_pl->next != players_head) 	//		αν ο παικτης με τα λιγοτερα tasks δεν ειναι ο τελευταιος (αυτος πριν τον players_head)
            {
                current_pl = current_pl->next;
            }
            else		//		σε περιπτωση που ο παικτης με τα λιγοτερα tasks ειναι ο τελευταιος πριν τον players_head
            {
                break;
            }
        }
		if(current_pl->is_alien != 1 && current_pl->pid != pid)
		{
			current_task = current_pl->tasks_head;
			while(current_task->difficulty != 0){	//		διαδικασια για να μετραμε ποσα tasks εχει ο καθε παικτης
				tmp++;
				current_task = current_task->next;
			}
			if(min >= tmp){
				min = tmp;
			}
		}
    } // exoume to min

    for(current_pl = players_head->next; current_pl != players_head; current_pl = current_pl->next){ //		ιδια διαδικασια για να βρουμε τον παικτη με (=min) tasks
        tmp = 0;
        while(current_pl->pid == pid || current_pl->is_alien == 1) 
        {
            if (current_pl->next != players_head)
            {
                current_pl = current_pl->next;
            }
            else
            {
                break;
            }
        }

		if(current_pl->is_alien != 1 && current_pl->pid != pid){

			current_task = current_pl->tasks_head;
			while(current_task->difficulty != 0){
				tmp++;
				current_task = current_task->next;
			}
			if(tmp == min){
				return current_pl;	// επιστρεφει τον παικτη με τα λιγοτερα tasks (tasks = min)
			}
		}
    }
    return current_pl;
}

int Distribute_Tasks_From_Ejected_Player_To_Other_Player(struct Players *eject_pl, struct Players *pl_WT_ls_TSKS){		//	για συγκεκριμενα events
	
    Tasks *ej_tasks = eject_pl->tasks_head;
    Tasks *less_tasks = pl_WT_ls_TSKS->tasks_head;
    
    for(;ej_tasks->difficulty != 0; ej_tasks = ej_tasks->next){
        less_tasks = pl_WT_ls_TSKS->tasks_head;
        Tasks *newTask = new Tasks;
        newTask->tid = ej_tasks->tid;
        newTask->difficulty = ej_tasks->difficulty;

		
		//		Για την ταξινομηση των tasks σε καθε παικτη                            θα μπορουσα να φτιαξω μια sort

        if(ej_tasks->difficulty <= less_tasks->difficulty){		//		για να φτιαξω δεικτες μονο για tasks_head
            newTask->next = pl_WT_ls_TSKS->tasks_head;
            pl_WT_ls_TSKS->tasks_head = newTask;
        }
        else if(pl_WT_ls_TSKS->tasks_head == pl_WT_ls_TSKS->tasks_sentinel){	//		για να φτιαξω δεικτες για tasks_head και tasks_sentinel
			newTask->next = pl_WT_ls_TSKS->tasks_sentinel;
		 	pl_WT_ls_TSKS->tasks_head = newTask;
			pl_WT_ls_TSKS->tasks_sentinel->next = newTask;
		}
		else
        {
            Tasks *less_tasks = pl_WT_ls_TSKS->tasks_head;

			while(less_tasks->next != pl_WT_ls_TSKS->tasks_sentinel && ((less_tasks->next->difficulty) < (newTask->difficulty))){	//	βοηθαει στην ταξινομηση (δηλαδη για το που θα μπει το συγκεκριμενο task που φτιαξαμε ετσι ωστε να παραμεινει ταξινομημενη η λιστα)
				less_tasks = less_tasks->next;
			}
			if(less_tasks->next == pl_WT_ls_TSKS->tasks_sentinel){
			
				newTask->next = pl_WT_ls_TSKS->tasks_sentinel;
				less_tasks->next = newTask;
				pl_WT_ls_TSKS->tasks_sentinel->next = newTask;
			}else{
				newTask->next = less_tasks->next;
				less_tasks->next = newTask;
			}
        }
    }
    return 1;
}

int Remove_Tasks_From_Stack_And_Distribute_To_Players(int pid, int number_of_tasks){		// για το event Sabbotage

	Players *cur_pl = players_head->next;
	Tasks *pl_cur_tasks;
	cur_pl = Double_Linked_List_Search(pid);

	if(number_of_tasks > tasks_stack->count){ return 0; }		//		number_of_tasks == ποσα τασκ θελεις να βγαλεις απο το stack και να τα μοιρασεις πισω στους παικτες

	if(cur_pl != players_head){		//		αν δεν ειναι αδεια η λιστα των παικτων

		double fl = number_of_tasks/2;
		for(int num = (int)fl; num > 0; num--)cur_pl = cur_pl->prev;	//	θα παει φορες πισω για να βρει τον παικτη που θα του ανατεθει η πρωτη εργασια απο αυτες (συμφωνα με την εκφωνηση)

		Tasks *task;
		for(int i = 0; i < number_of_tasks; i++){		//	θα εκτελεστει (number_of_tasks) φορες

			while(cur_pl == players_head || cur_pl->is_alien == 1) cur_pl = cur_pl->next;
			
			pl_cur_tasks = cur_pl->tasks_head;
			task = Pop(tasks_stack->head);

			if(task->difficulty <= pl_cur_tasks->difficulty || pl_cur_tasks->difficulty == 0){
				task->next = cur_pl->tasks_head;
				cur_pl->tasks_head = task;
			}
			else if(cur_pl->tasks_head == cur_pl->tasks_sentinel){
				task->next = cur_pl->tasks_sentinel;
				cur_pl->tasks_head = task;
				cur_pl->tasks_sentinel->next = task;
			}
			else
			{	
				while(pl_cur_tasks->next != cur_pl->tasks_sentinel && ((pl_cur_tasks->next->difficulty) < (task->difficulty))){
					pl_cur_tasks = pl_cur_tasks->next;
				}
				if(pl_cur_tasks->next == cur_pl->tasks_sentinel){

					task->next = cur_pl->tasks_sentinel;
					pl_cur_tasks->next = task;
					cur_pl->tasks_sentinel->next = task;

				}else{
					task->next = pl_cur_tasks->next;
					pl_cur_tasks->next = task;
				}
			}
		cur_pl = cur_pl->next;
		}
	return 1;
	}
	//epeidi den vrike ton player me pid 
	return 0;
}

Players *Finding_Player_with_biggest_evidence(){
	Players *cur = players_head->next;
	int max = 0;
	for(; cur != players_head; cur = cur->next){
		if(cur->evidence >= max) max = cur->evidence;
	}//max defined
	for(cur = players_head->next; cur->evidence != max; cur = cur->next){}
	return cur;
}

Players *Search_Player_With_Min_0_Or_Max_1_Tasks(int min_or_max){		//	εφτιαξα αυτη τη συναρτηση ετσι ωστε αν θελω να βρω τον παικτη με min tasks θα βαλω ως παραμετρο το 0 και αν θελω να βρω τον παικτη με max tasks θα βαλω ως παραμετρο το 1
    Players *current_pl = players_head->next;
    Tasks *current_task = current_pl->tasks_head;
    int min = 1000, tmp, max = 0;

	for(;current_pl != players_head; current_pl = current_pl->next){
        tmp = 0;
        while(current_pl->is_alien == 1) 
        {
            if (current_pl->next != players_head)
            {
                current_pl = current_pl->next;
            }
            else
            {
                break;
            }
        }
		if(current_pl->is_alien != 1)
		{
			current_task = current_pl->tasks_head;
			while(current_task->difficulty != 0){
				tmp++;
				current_task = current_task->next;
			}
			if(min >= tmp) min = tmp;
			if(tmp > max) max = tmp;
		}
    } // exoume to min kai to max

	current_task = current_pl->tasks_head;
    for(current_pl = players_head->next; current_pl != players_head; current_pl = current_pl->next){
        tmp = 0;
        while(current_pl->is_alien == 1)
        {
            if (current_pl->next != players_head)
            {
                current_pl = current_pl->next;
            }
            else
            {
                break;
            }
        }

        current_task = current_pl->tasks_head;
        while(current_task->difficulty != 0){
            tmp++;
            current_task = current_task->next;
        }
		if(min_or_max == 0  && current_pl->is_alien != 1){ 
			if(tmp == min) return current_pl;
		}
		else if(min_or_max == 1 && current_pl->is_alien != 1){
			if(tmp == max) return current_pl;
		}
    }
	return current_pl;
}

int Distribute_Tasks_From_Max_Player_To_Min(struct Players *min, struct Players *max){		//	για το event => give work

	Tasks *min_ts = min->tasks_head;
	Tasks *max_ts = max->tasks_head;
	int ts=0;

	for(; max_ts != max->tasks_sentinel; max_ts = max_ts->next)ts++;
	ts = ts/2;

	for(; ts > 0; ts--){	// θα εκτελεστει τοσες φορες οσες τα μισά tasks το player με τα περισσοτερα tasks
		max_ts = max->tasks_head;

		Tasks *newTask = new Tasks;
        newTask->tid = max_ts->tid;
        newTask->difficulty = max_ts->difficulty;


		if(max_ts->difficulty <= min_ts->difficulty){
			newTask->next = min->tasks_head;
			min->tasks_head = newTask;
		}
		else if(min->tasks_head == min->tasks_sentinel){
			
		
			newTask->next = min->tasks_sentinel;
		 	min->tasks_head = newTask;
			min->tasks_sentinel->next = newTask;
		}
		else
        {
			while(min_ts->next != min->tasks_sentinel && ((min_ts->next->difficulty) < (newTask->difficulty))){	//	βοηθαει στην παραμονη της ταξινομημενης λιστας
				min_ts = min_ts->next;
			}
			if(min_ts->next == min->tasks_sentinel){
			
				newTask->next = min->tasks_sentinel;
				min_ts->next = newTask;
				min->tasks_sentinel->next = newTask;
			}else{
				newTask->next = min_ts->next;
				min_ts->next = newTask;
			}
        }

		max->tasks_head = max->tasks_head->next;
	}
	return 1;
}

int print_double_list_with_evidence(){
	Players *cur_pl = players_head->next;
	Tasks *cur_ts = cur_pl->tasks_head;
	Tasks *tmp_ts = tasks_head->head;

	for(; cur_pl != players_head; cur_pl = cur_pl->next){

	//while(cur_pl->is_alien == 1 && cur_pl->next != players_head)cur_pl = cur_pl->next;
	
	/* if(cur_pl->is_alien != 1) */cout << "<Player"<< cur_pl->pid << "," << cur_pl->evidence << "> = ";

	for(cur_ts = cur_pl->tasks_head; cur_ts->tid != -1 && cur_pl != players_head; cur_ts = cur_ts->next){
		cout << "<" << cur_ts->tid << "," << cur_ts->difficulty << ">";
	}
	cout << "\n";
	}
	cout << "DONE\n";
	return 1;
}

/**
 * @brief Register player
 *
 * @param pid The player's id
 *
 * @param is_alien The variable that decides if he is an alien or not
 * @return 1 on success
 *         0 on failure
 */
int register_player(int pid, int is_alien)
{
    Double_Linked_List_Insert(pid, is_alien);
	print_players();
	return 1;
}

/**
 * @brief Insert task in the general task list
 *
 * @param tid The task id
 * 
 * @param difficulty The difficulty of the task
 *
 * @return 1 on success
 *         0 on failure
 */
int insert_task(int tid, int difficulty)
{
	AddTask(tid, difficulty);
	print_tasks();
	return 1;
}

/**
 * @brief Distribute tasks to the players
 * @return 1 on success
 *         0 on failure
 */
int distribute_tasks(){
	if(Distribute_Tasks_To_Players()){
		print_double_list();
		return 1;
	}else{
		print_double_list();
		return 0;
	}
}

/* 
 * @brief Implement Task
 *
 * @param pid The player's id
 *
 * @param difficulty The task's difficuly
 *
 * @return 1 on success
 *         0 on failure
 */
int implement_task(int pid, int difficulty)
{
	Players *cur_pl;
	cur_pl = Double_Linked_List_Search(pid);

	if(cur_pl != players_head){
		Tasks *tmp_task;
		tmp_task = Search_A_Task_From_Player(difficulty, cur_pl);

		if(tmp_task != cur_pl->tasks_sentinel){
			if(Delete_A_Task_From_A_Player(cur_pl, tmp_task) == 1) Push(tmp_task->tid, tmp_task->difficulty, tasks_stack->head);
			print_double_list();
			return 1;
		}else{
			print_double_list();
			return 0;
		}
	}
	print_double_list();
	return 0;
}

/**
 * @brief Eject Player
 * 
 * @param pid The ejected player's id
 *
 * @return 1 on success
 *         0 on failure
 */
int eject_player(int pid)
{
    Players *eject_pl;
    eject_pl = Double_Linked_List_Search(pid);
    Players *pl_WT_ls_TSKS;
    pl_WT_ls_TSKS = Search_Player_With_Less_Tasks(pid);

    if(eject_pl != players_head && pl_WT_ls_TSKS != players_head){
    	Distribute_Tasks_From_Ejected_Player_To_Other_Player(eject_pl, pl_WT_ls_TSKS);
    	Double_Linked_List_Delete(pid);
		print_double_list();
		return 1;
	}
	else
	{
		print_double_list();
		return 0;
	}
}

/**
 * @brief Witness Eject Player
 *
 * @param pid_a The alien's pid
 * 
 * @param pid The crewmate's pid
 * 
 * @param number_of_witnesses The number of witnesses
 *
 * @return 1 on success
 *         0 on failure
 */
int witness_eject(int pid, int pid_a, int number_of_witnesses)
{
	Players *eject_pl;
    eject_pl = Double_Linked_List_Search(pid);
    Players *pl_WT_ls_TSKS;
    pl_WT_ls_TSKS = Search_Player_With_Less_Tasks(pid);
    
	if(eject_pl != players_head && pl_WT_ls_TSKS != players_head){
    	Distribute_Tasks_From_Ejected_Player_To_Other_Player(eject_pl, pl_WT_ls_TSKS);
		Double_Linked_List_Delete(pid);
		Players *alien_evid;
		alien_evid = Double_Linked_List_Search(pid_a);
		
		if(alien_evid != players_head) {
			alien_evid->evidence += number_of_witnesses;
		}else{
			print_double_list_with_evidence();
			return 0;
		}
		print_double_list_with_evidence();
		return 1;
	}

	print_double_list_with_evidence();
	return 0;
}

/**
 * @brief Sabbotage
 *
 * @param pid The player's id
 *
 * @param number_of_tasks The number of tasks to be popped
 * 
 * @return 1 on success
 *         0 on failureDONE\n
 */
int sabbotage(int pid, int number_of_tasks)
{
	if(Remove_Tasks_From_Stack_And_Distribute_To_Players(pid, number_of_tasks)){
		print_double_list();
		return 1;
	}else{
		print_double_list();
		return 0;
	}
}

/**
 * @brief Vote
 *
 * @param pid The player's id
 * 
 * @param vote_evidence The vote's evidence
 *
 * @return 1 on success
 *         0 on failure
 */
int vote(int pid, int vote_evidence)
{
	Players *evid_pl;
	evid_pl = Double_Linked_List_Search(pid);

	if(evid_pl != players_head){
		evid_pl->evidence += vote_evidence;
		Players *pl_WT_ls_TSKS;
    	pl_WT_ls_TSKS = Search_Player_With_Less_Tasks(pid);
		if (pl_WT_ls_TSKS == players_head)return 0;
		Distribute_Tasks_From_Ejected_Player_To_Other_Player(Finding_Player_with_biggest_evidence(), pl_WT_ls_TSKS);
    	Double_Linked_List_Delete(Finding_Player_with_biggest_evidence()->pid);
		print_double_list_with_evidence();
		return 1;
	}
	print_double_list_with_evidence();
	return 0;
}

/**
 * @brief Give Away Work
 *
 * @return 1 on success
 *         0 on failure
 */
int give_work()
{
	Players *min_pl;
	Players *max_pl;
	min_pl = Search_Player_With_Min_0_Or_Max_1_Tasks(0);
	max_pl = Search_Player_With_Min_0_Or_Max_1_Tasks(1);
	if(min_pl != players_head && max_pl != players_head){
		Distribute_Tasks_From_Max_Player_To_Min(min_pl, max_pl);
		print_double_list();
		return 1;
	}
	else{
		print_double_list();
		return 0;
	}
}

/**
 * @brief Terminate
 *
 * @return 1 on success
 *         0 on failure
 */
int Terminate()
{
	Players *cur = players_head->next;
	int aliens=0, crewmates=0;
	for(; cur != players_head; cur = cur->next){ if(cur->is_alien == 1){aliens++;}else{crewmates++;} }
	if(aliens > crewmates){
		cout << "  Aliens win.\nDONE\n";
		return 1;
	}
	int total_tasks = tasks_head->tasks_count[0] + tasks_head->tasks_count[1] + tasks_head->tasks_count[2];
	if(tasks_stack->count == total_tasks || aliens == 0){
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
int print_players()
{
	Players *cur = players_head->next;
	cout << "Players = ";
	for(; cur != players_head; cur = cur->next){ cout << "<" << cur->pid << ":" << cur->is_alien << ">"; }
	cout << "\n";
	cout << "DONE";
	cout << "\n";
	return 1;
}

/**
 * @brief Print Tasks
 *
 * @return 1 on success
 *         0 on failure
 */
int print_tasks()
{
	Tasks *cur = tasks_head->head;
	cout << "Tasks = ";
	for(; cur->next != NULL; cur = cur->next){
		cout << "<" << cur->tid << "," << cur->difficulty << ">";
	}
	if(cur->next == NULL) cout << "<" << cur->tid << "," << cur->difficulty << ">";
	cout << "\nDONE\n";
	return 1;
}

/**
 * @brief Print Stack
 *
 * @return 1 on success
 *         0 on failure
 */
int print_stack()
{
    Tasks *s = tasks_stack->head;
    cout << "Stack_Tasks = ";
	while(!IsEmptyStack(s) && tasks_stack->head != NULL){
        cout << "<" << Top(s)->tid << "," << Top(s)->difficulty << ">";
		Pop(s);
    }
    cout << "\nDONE\n";
	return 1;
}

/**
 * @brief Print Players & Task List
 *
 * @return 1 on success
 *         0 on failure
 */
int print_double_list()
{
	Players *cur_pl = players_head->next;
	Tasks *cur_ts = cur_pl->tasks_head;
	Tasks *tmp_ts = tasks_head->head;

	for(; cur_pl != players_head; cur_pl = cur_pl->next){

	cout << "<Player"<< cur_pl->pid << " = ";

	for(cur_ts = cur_pl->tasks_head; cur_ts->tid != -1; cur_ts = cur_ts->next){
		cout << "<" << cur_ts->tid << "," << cur_ts->difficulty << ">";
	}
	cout << "\n";
	}
	cout << "DONE\n";
	return 1;
}

/**
 * @brief Free resources
 *
 * @return 1 on success
 *         0 on failure
 */
int free_all(void)
{
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
	char buff[BUFFER_SIZE], event = '\0';

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

		/* Register player
			 * P <pid><is_alien> */
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

		/* Insert task
			 * T <tid><difficulty>  */
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
			 * I <pid> <difficulty> */
		case 'I':
		{
			int pid, difficulty;

			sscanf(buff, "%c %d %d", &event, &pid, &difficulty);
			DPRINT("%c %d %d \n", event, pid, difficulty);

			if (implement_task(pid, difficulty))
			{
				DPRINT("%c %d %d succeeded\n", event, pid, difficulty);
			}
			else
			{
				fprintf(stderr, "%c %d %d failed\n", event, pid, difficulty);
			}

			break;
		}

		/* Eject Player
			 * E <pid>*/
		case 'E':
		{
			int pid;

			sscanf(buff, "%c %d", &event, &pid);
			DPRINT("%c %d\n", event, pid);

			if (eject_player(pid))
			{
				DPRINT("%c %d succeeded\n", event, pid);
			}
			else
			{
				fprintf(stderr, "%c %d failed\n", event, pid);
			}

			break;
		}

			/* Witness Ejection
                 * W <pid> <pid_a> <number_of_witnesses>
                 */
		case 'W':
		{
			int pid, pid_a, number_of_witnesses;

			sscanf(buff, "%c %d %d %d", &event, &pid, &pid_a, &number_of_witnesses);
			DPRINT("%c %d %d %d\n", event, pid, pid_a, number_of_witnesses);

			if (witness_eject(pid, pid_a, number_of_witnesses))
			{
				DPRINT("%c %d %d %d succeded\n", event, pid, pid_a, number_of_witnesses);
			}
			else
			{
				fprintf(stderr, "%c %d %d %d failed\n", event, pid, pid_a, number_of_witnesses);
			}

			break;
		}

		/* Sabbotage
			 * S <number_of_tasks><pid> */
		case 'S':
		{
			int pid, number_of_tasks;

			sscanf(buff, "%c %d %d\n", &event, &number_of_tasks, &pid);
			DPRINT("%c %d %d\n", event, number_of_tasks, pid);

			if (sabbotage(pid, number_of_tasks))
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
			 * V <pid> <vote_evidence> */
		case 'V':
		{
			int pid, vote_evidence;

			sscanf(buff, "%c %d %d\n", &event, &pid, &vote_evidence);
			DPRINT("%c %d %d\n", event, pid, vote_evidence);

			if (vote(pid, vote_evidence))
			{
				DPRINT("%c %d %d succeeded\n", event, pid, vote_evidence);
			}
			else
			{
				fprintf(stderr, "%c %d %d failed\n", event, pid, vote_evidence);
			}

			break;
		}

		/* Give Away Work
			 * G */
		case 'G':
		{
			sscanf(buff, "%c", &event);
			DPRINT("%c\n", event);

			if (give_work())
			{
				DPRINT("%c succeeded\n", event);
			}
			else
			{
				fprintf(stderr, "%c failed\n", event);
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
		/* Print Stack
			 * Z */
		case 'Z':
		{
			sscanf(buff, "%c", &event);
			DPRINT("%c\n", event);

			if (print_stack())
			{
				DPRINT("%c succeeded\n", event);
			}
			else
			{
				fprintf(stderr, "%c failed\n", event);
			}

			break;
		}
		/* Print Players & Tasks list
			 * F */
		case 'U':
		{
			sscanf(buff, "%c", &event);
			DPRINT("%c\n", event);

			if (print_double_list())
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