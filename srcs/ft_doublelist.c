#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"

//typedef struct s_tlist
//{
//    char content;
//    struct s_tlist *next;
//    struct s_tlist *prev;
//}               t_tlist;

void    ft_init(t_tlist **head, t_tlist **tail, char *str, t_com *com)
{
    t_tlist *new;
    new = malloc(sizeof(t_tlist));
    if (new == NULL)
    {
        exit(2);
        return ;
    }
    new->content = ft_strdup(str);
    new->next = NULL;
    new->prev = NULL;
    *head = new;
    *tail = new;
    com->inited = 1;
}

void    insert_end(t_tlist **tail, char *str)
{
    t_tlist *new;
    // t_tlist *curr;

    new = malloc(sizeof(t_tlist));
    if (new == NULL)
    {
        exit(1);
        return ;
    }
    new->content = ft_strdup(str);
    new->next = NULL;
    
    new->prev = *tail;
    if (*tail != NULL)
    {
        // (*head)->next = NULL;
        (*tail)->next = new;
    }
    // else
    // {
    //     *head
    // }
    *tail = new;

}

void    insert_beginning(t_tlist **head, char *str)
{
    t_tlist *new;
    new = malloc(sizeof(t_tlist));
    if (new == NULL)
    {
        exit(1);
        return ;
    }
    new->content = ft_strdup(str);
    new->next = *head;
    new->prev = NULL;
    if (*head != NULL)
    {
        // (*head)->next = NULL;
        (*head)->prev = new;
    }
    // else
    // {
    //     *head
    // }
    *head = new;


}

//int main(int argc, char **argv)
//{
//    t_tlist *head = NULL;
//    t_tlist *tail = NULL;
//
//    t_tlist *curr;
//
//    init(&head, &tail, 'a');
//    insert_beginning(&head, 'b');
//    insert_beginning(&head, 'c');
//    insert_beginning(&head, 'd');
//    insert_beginning(&head, 'e');
//    insert_beginning(&head, 'f');
//    insert_beginning(&head, 'g');
//    insert_end(&tail, 'z');
//    curr = tail;
//    while(curr)
//    {
//        // curr = tail;
//        printf("%c\n", curr->content);
//        curr = curr->prev;
//    }
//
//    return (0);
//}