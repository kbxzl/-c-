#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
struct list * findmoive(struct  list *li,int id,FILE *m);
struct list{
	int like_num; 
	char name[30];//类别的名称 
	struct list *nextl;
};
struct user{
	int id;
	struct list *like;//指向喜欢的影片的链表 
	struct user *nextu;
};
void output(struct user *p)
{
	FILE *f;
	f=fopen("./outp.csv","w");
	char temp[10];
	struct list *li;
	while(p!=NULL)
	{
		li=p->like;
		itoa(p->id,temp,10);
		fputs(temp,f);
		fputs(":",f);
		while(li->nextl!=NULL)
		{
			fputs(li->name,f);
			fputs(" ",f);
			itoa(li->like_num,temp,10);
			fputs(temp,f);
			fputs(" |",f);
			li=li->nextl;
		}
		fputs(li->name,f);
		fputs(" ",f);
		itoa(li->like_num,temp,10);
		fputs(temp,f);
		fputs(" \n",f);
		p=p->nextu;
	}
} 
struct user *findmain(FILE *m,FILE *r)
{
	struct user *p,*temp,*head;
	p=(struct user *)malloc(sizeof(struct user));
	head = p;
	int movieid,num,i=0,id1;
	float rate;
	p->id=1;
	p->like =NULL;
	p->nextu=NULL;
	char namem[200],tempc[200];
	while(r != NULL)
	{
		if(fscanf(r,"%d",&id1)==EOF)
		{
			break;
		}
		fscanf(r,",%d,%f",&movieid,&rate);
		if(p->id == id1)
		{
			if(fabs(rate-3)<10e-6 || rate>=3)
			{
				rewind(m);
				fgets(namem,200,m);
				p->like = findmoive(p->like,movieid,m);
			}
		}
		else if(abs(rate-3)<10e-6 || rate>=3 )
		{
			printf("\n\n\n%d",id1);
			p->nextu = (struct user *)malloc(sizeof(struct user));
			p=p->nextu;
			p->id=id1;
			p->like = NULL;
			p->nextu=NULL;
			rewind(m);
			fgets(namem,200,m);
			p->like = findmoive(p->like,movieid,m);
		}
		fgets(tempc,200,r);	
	} 
	return head;
}
struct list * findmoive(struct list *li,int id,FILE *m)
{
	int num,i=0,sign=0;
	char *c,d[200],line[200],*p,line1[200],*line2,temp[200];
	struct list *head;
	head = li;//li应被初始化为NULL 
	fscanf(m,"%d",&num);
	while(id != num)
	{
		fgets(d,200,m);
		fscanf(m,"%d",&num);
	}
	fgets(line,200,m);
	strcpy(line1,line);
	while(line[i] != '\n')
	{
		if(line[i] == ',')
		{
			p=&line[i];//找到最后一个 ',' 
		}
		i++;
	}
	p=p+1;
	c=p;
	while(1)
	{
		if(*c=='\n')
		{
			break;
		}
		i=0;
		while(*c!='\n' && *c!='|')
		{
			temp[i]=*c;
			i++;
			c++;
		}
		temp[i]='\0';
		if(li==NULL)//第一次，初始化 
		{
			li=(struct list *)malloc(sizeof(struct list));
			head=li; 
			strcpy(li->name,temp);
			li->like_num=1;
			li->nextl=NULL;
		}
		else//非第一次 
		{
			sign = 1;
			li=head;
			while(li->nextl!=NULL)
			{
				if(strcmp(temp,li->name)==0)
				{
					li->like_num++;
					sign = 0;
					li=head;
					li=li->nextl;
					break;
				}
				li=li->nextl;
			} 
			if(strcmp(temp,li->name)==0 && sign==1)
			{
				li->like_num++;
				sign = 0;
				li=head;
			}
			if(sign)//新类型 
			{
				li->nextl = (struct list *)malloc(sizeof(struct list));
				li->nextl->nextl = NULL; 
				li->nextl->like_num = 1;
				strcpy(li->nextl->name,temp);
				li = head;
			}
		}
		if(*c == '\n')
		{
			break;
		}
		c++;
	}
	li = head;
	return head;
}
int main()
{
	FILE *m,*r;
	char c[1000];
	struct user *p;
	p=(struct user *)malloc(sizeof(struct user));
	m=fopen("./movies.csv","r");
	r=fopen("./ratings.csv","r");
	fgets(c,100,m);
	fgets(c,100,r);
	p=findmain(m,r);
	output(p);
} 
