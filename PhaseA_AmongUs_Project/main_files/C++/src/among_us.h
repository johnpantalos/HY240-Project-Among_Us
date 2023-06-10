/**************************************************
 *                                                *
 * file: among_us.h                               *
 *                                                *
 *                                                *
 * @Author  Antonios Peris                        *
 * @Version 20-10-2020                            *
 * @email   csdp1196@csd.uoc.gr                   *
 *                                                *
 * @brief   Header file for the needs of cs-240   *
 * project 2020, with the structures and function *
 * prototypes                                     * 
 *                                                *
 **************************************************
 */

#ifndef __AMONG_US_H_
#define __AMONG_US_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/**
 * Structure defining a node of the players double linked list
 * tree
 */
struct Players
{
    int pid;                      /*Player's identifier*/
    int is_alien;                 /*Alien flag*/
    int evidence;                 /*Amount of evidence*/
    struct Players *prev;         /*Pointer to the previous node*/
    struct Players *next;         /*Pointer to the next node*/
    struct Tasks *tasks_head;     /*Pointer to the head of player's task list*/
    struct Tasks *tasks_sentinel; /*Pointer to the sentinel of player's task list*/
};

/**
 * Structure defining a node of the tasks sorted linked list
 */
struct Tasks
{
    int tid;                      /*Task's identifier*/
    int difficulty;               /*Task's difficulty*/
    struct Tasks *next;           /*Pointer to the next node*/  
};

struct Head_GL
{
    int tasks_count[3];           /*Count of tasks*/
    struct Tasks *head;           /*Pointer to the head of general list*/
};

struct Head_Completed_Task_Stack
{
    int count;                    /*Count of completed tasks*/
    struct Tasks *head;           /*Pointer to the top element of the stack*/
};

/* Global variable, pointer to the head of the players list */
struct Players *players_head;

/* Global variable, pointer to the head of the tasks list */
struct Head_GL *tasks_head;

/* Global variable, pointer to the top of the completed task's stack */
struct Head_Completed_Task_Stack *tasks_stack;

/**
 * @brief Optional function to initialize data structures that 
 *        need initialization
 *
 * @return 1 on success
 *         0 on failure
 */
int initialize();


int Double_Linked_List_Insert(int pid, int is_alien);
Players *Double_Linked_List_Search(int pid);
int Double_Linked_List_Delete(int pid);
int AddTask(int tid, int difficulty);
int Distribute_Tasks_To_Players();
Tasks *Search_A_Task_From_Player(int difficulty, struct Players *cur_pl);
int Delete_A_Task_From_A_Player(struct Players *pl ,struct Tasks *del_task);
Tasks *Push(int tid, int difficulty, struct Tasks *S);
int IsEmptyStack(struct Tasks *S);
Tasks *Pop(struct Tasks *S);
Tasks *Top(struct Tasks *S);
Players *Search_Player_With_Less_Tasks(int pid);
int Distribute_Tasks_From_Ejected_Player_To_Other_Player(struct Players *eject_pl, struct Players *pl_WT_ls_TSKS);
int Remove_Tasks_From_Stack_And_Distribute_To_Players(int pid, int number_of_tasks);
Players *Finding_Player_with_biggest_evidence();
Players *Search_Player_With_Min_0_Or_Max_1_Tasks(int min_or_max);
int Distribute_Tasks_From_Max_Player_To_Min(struct Players *min, struct Players *max);
int print_double_list_with_evidence();

/**
 * @brief Register player
 *
 * @param pid The player's id
 *
 * @param is_alien The variable that decides if he is an alien or not
 * @return 1 on success
 *         0 on failure
 */
int register_player(int pid, int is_alien);

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
int insert_task(int tid, int difficulty);

/**
 * @brief Distribute tasks to the players
 * @return 1 on success
 *         0 on failure
 */
int distribute_tasks();

/**
 * @brief Implement Task
 *
 * @param pid The player's id
 *
 * @param difficulty The task's difficuly
 *
 * @return 1 on success
 *         0 on failure
 */
int implement_task(int pid, int difficulty);

/**
 * @brief Eject Player
 * 
 * @param pid The ejected player's id
 *
 * @return 1 on success
 *         0 on failure
 */
int eject_player(int pid);

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
int witness_eject(int pid, int pid_a, int number_of_witnesses);

/**
 * @brief Sabbotage
 *
 * @param pid The player's id
 *
 * @param number_of_tasks The number of tasks to be popped
 * 
 * @return 1 on success
 *         0 on failure
 */
int sabbotage(int pid, int number_of_tasks);

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
int vote(int pid, int vote_evidence);

/**
 * @brief Give Away Work
 *
 * @return 1 on success
 *         0 on failure
 */
int give_work();

/**
 * @brief Terminate
 *
 * @return 1 on success
 *         0 on failure
 */
int terminate();

/**
 * @brief Print Players
 *
 * @return 1 on success
 *         0 on failure
 */
int print_players();

/**
 * @brief Print Tasks
 *
 * @return 1 on success
 *         0 on failure
 */
int print_tasks();

/**
 * @brief Print Stack
 *
 * @return 1 on success
 *         0 on failure
 */
int print_stack();

/**
 * @brief Print Players & Task List
 *
 * @return 1 on success
 *         0 on failure
 */
int print_double_list();

/**
 * @brief Free resources
 *
 * @return 1 on success
 *         0 on failure
 */

int free_all(void);

#endif /* __AMONG_US_H_ */
