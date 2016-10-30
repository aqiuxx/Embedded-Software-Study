#include "linkqueue.h"
#include "seqstack.h"

int check_linkqueue(linkqueue_t *lq)
{
	linknode_t *temp = lq->front->next;

	while(temp->next != NULL)
	{
		if(temp->data < temp->next->data)
		{
			temp = temp->next;
		}
		else
		{
			return 0;
		}
	}

	return 1;
}

int ball_time()
{
	linkqueue_t *lq = linkqueue_create();
	seqstack_t *s_min = seqstack_create();
	seqstack_t *s_five = seqstack_create();
	seqstack_t *s_hour = seqstack_create();

	int count = 0;

	//将数据放在队列里面
	int i = 0;

	for(i = 1; i <= 27; i++)
	{
		linkqueue_input(lq, i);
	}

	while(1)
	{
		i = linkqueue_output_del(lq);

		count++;

		if(s_min->top < 3)
		{
			seqstack_push(s_min, i);
		}
		else
		{
			while(!seqstack_empty(s_min))
			{
				linkqueue_input(lq, seqstack_pop(s_min));
			}

			if(s_five->top < 10)
			{
				seqstack_push(s_five, i);
			}
			else
			{
				while(!seqstack_empty(s_five))
				{
					linkqueue_input(lq, seqstack_pop(s_five));
				}

				if(s_hour->top < 10)
				{
					seqstack_push(s_hour, i);
				}
				else
				{
					while(!seqstack_empty(s_hour))
					{
						linkqueue_input(lq, seqstack_pop(s_hour));
					}

					linkqueue_input(lq, i);

					if(check_linkqueue(lq) == 1)
					{
						break;
					}
				}
			}
		}
	}

	return count;
}

int main(int argc, const char *argv[])
{
	int count = 0;
	count = ball_time();

	printf("%d min ---> %d hour ---> %d day\n", count, count/60, count/60/24);

	return 0;
}
