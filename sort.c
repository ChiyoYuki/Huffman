#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

struct NODE
{
    long long data;
    struct NODE *pre;
    struct NODE *next;
};

typedef long long ll;
typedef struct NODE node;

void merge_sort(node *head);
void quick_sort(node *head);
void selection_sort(node *head);
void insertion_sort(node *head);
void stalin_sort(node *head);

int main()
{
    int mode;
    printf("归并排序请按1\n");
    printf("快速排序请按2\n");
    printf("选择排序请按3\n");
    printf("插入排序请按4\n");
    printf("斯大林排序请按5\n");
    // 有关于斯大林排序，请查看：https://codeforces.com/contest/2027/problem/B
    scanf("%d", &mode);

    freopen("input.txt", "r", stdin);
    int i, j;
    int n;
    scanf("%d", &n);
    node *head = (node *)malloc(sizeof(node));
    head->data = n;
    head->pre = head;
    head->next = head;
    node *tail;
    for (i = 0; i < n; i++)
    {
        tail = (node *)malloc(sizeof(node));
        tail->pre = head->pre;
        tail->next = head;
        tail->next->pre = tail;
        tail->pre->next = tail;
        scanf("%lld", &(tail->data));
    }

    struct timeval begin, end;
    gettimeofday(&begin, 0);
    switch (mode)
    {
    case 1:
        merge_sort(head);
        break;
    case 2:
        quick_sort(head);
        break;
    case 3:
        selection_sort(head);
        break;
    case 4:
        insertion_sort(head);
        break;
    case 5:
        stalin_sort(head);
        break;
    default:
        break;
    }
    gettimeofday(&end, 0);

    printf("本次排序结束，用时%d.%06d秒\n",end.tv_sec-begin.tv_sec,end.tv_usec-begin.tv_usec);
    freopen("test.out", "w", stdout);
    printf("本次排序结束，用时%d.%06d秒\n",end.tv_sec-begin.tv_sec,end.tv_usec-begin.tv_usec);
    printf("%d\n", n);
    for (tail = head->next; tail != head; tail = tail->next)
        printf("%d ", tail->data);

    return 0;
}

void merge_sort(node *head)
{
    if (head->data <= 1)
        return;

    node *head0 = (node *)malloc(sizeof(node));
    head0->data = head->data / 2;
    head0->next = head->next;
    head0->pre = head0;

    node *head1 = (node *)malloc(sizeof(node));
    head1->data = head->data - head0->data;
    head1->pre = head->pre;
    head1->next = head1;

    int i, j;
    node *now = head;
    for (i = 0; i < head0->data; i++)
        now = now->next;

    now->next->pre = head1;
    head1->next = now->next;
    head1->pre->next = head1;

    now->next = head0;
    head0->pre = now;
    head0->next->pre = head0;

    merge_sort(head0);
    merge_sort(head1);

    now = head;
    while (head0->data != 0 && head1->data != 0)
    {
        if (head0->next->data < head1->next->data)
        {
            now->next = head0->next;
            head0->next = head0->next->next;
            head0->next->pre = head0;
            head0->data--;
        }
        else
        {
            now->next = head1->next;
            head1->next = head1->next->next;
            head1->next->pre = head1;
            head1->data--;
        }
        now->next->pre = now;
        now->next->next = head;
        now = now->next;
    }

    if (head0->data == 0)
    {
        head->pre = head1->pre;
        now->next = head1->next;
    }
    else
    {
        head->pre = head0->pre;
        now->next = head0->next;
    }

    now->next->pre = now;
    head->pre->next = head;

    free(head0);
    free(head1);
    return;
}

void quick_sort(node *head)
{
    if (head->data <= 1)
        return;

    node *head0 = (node *)malloc(sizeof(node));
    head0->data = 0;
    head0->pre = head0;
    head0->next = head0;
    node *head1 = (node *)malloc(sizeof(node));
    head1->data = 0;
    head1->pre = head1;
    head1->next = head1;
    node *mid = head->next;
    head->next = head->next->next;
    head->next->pre = head;

    node *now;
    while (head->next != head)
    {
        now = head->next;
        head->next = head->next->next;
        head->next->pre = head;

        if (now->data < mid->data)
        {
            now->pre = head0->pre;
            now->next = head0;
            head0->data++;
        }
        else
        {
            now->pre = head1->pre;
            now->next = head1;
            head1->data++;
        }

        now->pre->next = now;
        now->next->pre = now;
    }

    quick_sort(head0);
    quick_sort(head1);

    if (head0->data != 0)
    {
        head->next = head0->next;
        head->next->pre = head;
        mid->pre = head0->pre;
        mid->pre->next = mid;
    }
    else
    {
        mid->pre = head;
        head->next = mid;
    }

    if (head1->data != 0)
    {
        head->pre = head1->pre;
        head->pre->next = head;
        mid->next = head1->next;
        mid->next->pre = mid;
    }
    else
    {
        mid->next = head;
        head->pre = mid;
    }

    free(head0);
    free(head1);

    return;
}

void selection_sort(node *head)
{
    node *fin = head->next, *now = fin, *mi = fin;
    while (fin != head)
    {
        mi = fin;
        for (now = fin; now != head; now = now->next)
            if (now->data < mi->data)
                mi = now;

        if (mi != fin)
        {
            fin->data ^= mi->data;
            mi->data ^= fin->data;
            fin->data ^= mi->data;
        }

        fin = fin->next;
    }

    return;
}

void insertion_sort(node *head)
{
    if (head->data <= 1)
        return;

    node *new_head = (node *)malloc(sizeof(node));
    new_head->pre = new_head;
    new_head->next = new_head;

    new_head->next = head->next;
    new_head->pre = head->next;
    head->next = head->next->next;
    head->next->pre = head;
    new_head->pre->next = new_head;
    new_head->next->pre = new_head;

    node *now, *pos;
    while (head->next != head)
    {
        now = head->next;
        head->next = now->next;
        head->next->pre = head;

        if (now->data <= new_head->next->data)
        {
            now->pre = new_head;
            now->next = new_head->next;
            now->pre->next = now;
            now->next->pre = now;
            continue;
        }

        if (now->data >= new_head->pre->data)
        {
            now->next = new_head;
            now->pre = new_head->pre;
            now->pre->next = now;
            now->next->pre = now;
            continue;
        }

        for (pos = new_head->next; pos != new_head->pre; pos = pos->next)
        {
            if (pos->data <= now->data && pos->next->data >= now->data)
            {
                now->pre = pos;
                now->next = pos->next;
                now->pre->next = now;
                now->next->pre = now;
                break;
            }
        }
    }

    head->next = new_head->next;
    free(new_head);

    return;
}

void stalin_sort(node *head)
{
    if (head->data <= 1)
        return;
    node *now = head->next->next;
    node *del = NULL;
    while (now != head)
    {
        if (now->data < now->pre->data)
        {
            del = now;
            now = now->next;
            del->pre->next = del->next;
            del->next->pre = del->pre;
            free(del);
        }
        else
            now = now->next;
    }
    return;
}
