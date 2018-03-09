#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int maxn = 65537;
bool vis[maxn];
int ronud = 0;
int dir[5] = { 4, -4, 1, -1, 0 };//���������� 
int rd[maxn]; //rd[i]����״̬iʱ���ƶ��Ĵ��� 
int myFlip(int bit, int state) { //��ת��bitλ�����ܱߵ����� 
	for (int i = 0; i < 5; ++i) {
		int bt = bit + dir[i];
		if (dir[i] == 1 && bt % 4 == 0 || dir[i] == -1 && bt % 4 == 3)
			continue;
		if (-1 < bt && bt < 16) { //��֤ ������ ��ת������û��Խ�� 
			if ((state >> bt) & 1)
				state -= (1 << bt);
			else state += (1 << bt);
		}
	}
	return state;
}
int BFS(int state) {
	if (state == 0 || state == (1 << 16) - 1) {
		return 0;//��ʼ��״̬��������Ҫ�� 
	}
	int round = 0;	//�����ַ�ת����Գ���״̬0 or (1<<16)-1
	queue<int> que;
	que.push(state);
	memset(vis, 0, sizeof(bool) * maxn);//vis[i]Ϊ1����ʾ״̬i�Ѵ���
	vis[state] = true;
	rd[state] = 0;
	while (!que.empty()) {
		state = que.front(); //��ǰ��ڵ� 
		que.pop();
		for (int bit = 15; bit >= 0; --bit) {
			int st = myFlip(bit, state);
			if (!vis[st]) {
				rd[st] = rd[state] + 1; //��ڵ�state��չ�õ��Ľڵ�st
				vis[st] = true;
				if (st == 0 || st == (1 << 16) - 1)
					return rd[st];
				que.push(st);
			}
		}
	}
	return -1; //������������� 
}
int main()
{
	//freopen("data.in", "r", stdin);
	char ch;
	int state0 = 0;
	for (int i = 15; i >= 0; --i) {
		scanf(" %c", &ch);
		if (ch == 'b') {
			state0 += (1 << i);
		}
	} //����16�����ӣ�״̬ѹ��������1<<16��״̬��ɫΪ1�� 
	int round = BFS(state0);
	if (round == -1) {
		puts("Impossible");
	}
	else {
		printf("%d\n", round);
	}
	
	return 0;
}
