 struct Name
{
    int next;
	char s[maxs];
	int num;       //�ַ����ĸ���
}m[maxh+maxe];   //������ // maxe�Ƕ����
int BKDR(char *str)
{
	unsigned int hash=0;
	int seed =131;
	for(int i=0;str[i];i++)
		hash=hash*seed+str[i];
	return hash&0x7fffffff;
}
int Hash(char *str)
{
	int mm=BKDR(str)%maxh;
	if(m[mm].next==-1)    //0-maxh��ʼ��Ϊ-1
	{
		strcpy(m[mm].s,str);
		m[mm].next=mm;
	}
	else
	{
		while(m[mm].next!=mm&&strcmp(m[mm].s,str)!=0)
		{
			mm=m[mm].next;
		}
		if(m[mm].next==mm)
		{
			strcpy(m[cur].s,str);
			m[mm].next=cur++;
		}
	}
	return mm;
}