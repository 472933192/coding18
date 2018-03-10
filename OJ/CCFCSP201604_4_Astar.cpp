//��Ȼ·����Ψһ����ʹ��A*�㷨�ó����������һ�������������˹����������㷨��������ʡʱ
#include <iostream> 
#include <string>
#include <queue>
#include <cstring>
using namespace std;
struct State {
	int f, g, h; //A*�㷨
	int ary[9], pos;
	int hash;
	bool operator < (State tmp) const {
		return f == tmp.f ? g > tmp.g : f > tmp.f;
	} //����С����������������ȶ���
};
int fac[9] = { 1, 1, 2, 6, 24, 120, 720, 5040, 40320 };
int cantor(int ary[], int n) {
	int hash = 0;
	for (int i = 0; i < n; ++i) {
		int k = 0;
		for (int j = i + 1; j < n; ++j)
			if (ary[j] < ary[i]) ++k;
		hash += k * fac[n - 1 - i];
	}
	return hash; //����1��hashֵ��ΧΪ 0:n! - 1
}
const int N = 362880, des = 0;//123456789�Ŀ���չ��ֵ
const char op[5] = "udlr"; 
int dir[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
bool vis[N]; int pre[N]; char ch[N];
int get_h(int ary[]) { //״̬��ÿ�����ֵ���ȷλ�õ�ŷʽ�������Ϊ����ֵ
	int res = 0;
	for (int i = 0; i < 3; ++i) //��
		for (int j = 0; j < 3; ++j) //��
			res += abs((ary[i*3+j] - 1) / 3 - i) + abs((ary[i*3+j] - 1) % 3 - j);
	return res;
}
void print(int x) {
	if (pre[x] == -1) return;
	print(pre[x]);
	cout << ch[x];
}
void Astar(State st) {
	if (st.hash == des) { cout << endl; return; }
	memset(vis, 0, sizeof vis);
	priority_queue<State> pq;
	pq.push(st);
	vis[st.hash] = true;
	pre[st.hash] = -1;
	while (!pq.empty()) {
		st = pq.top(); pq.pop();
		int x = st.pos / 3, y = st.pos % 3;
		for (int i = 0; i < 4; ++i) {			
			int xx = x + dir[i][0], yy = y + dir[i][1];
			if (xx < 0 || xx > 2 || yy < 0 || yy > 2) continue;
			State tmp = st;
			tmp.pos = xx * 3 + yy;
			swap(tmp.ary[st.pos], tmp.ary[tmp.pos]);
			tmp.hash = cantor(tmp.ary, 9);
			if (vis[tmp.hash]) continue;
			pre[tmp.hash] = st.hash;
			ch[tmp.hash] = op[i];
			vis[tmp.hash] = true;
			if (tmp.hash == des) {
				print(0); cout << endl; return;
			}
			tmp.g++;
			tmp.h = get_h(tmp.ary);
			tmp.f = tmp.g + tmp.h;
			pq.push(tmp);
		}
	}
}
int main()
{
	ios::sync_with_stdio(false);
	char str[9];
	while (cin >> str[0]) {
		for (int i = 1; i < 9; ++i)
			cin >> str[i];
		State s;
		for (int i = 0; i < 9; ++i) {
			if (str[i] == 'x') {
				s.pos = i;
				s.ary[i] = 9;
			}
			else s.ary[i] = str[i] - '0';
		}
		s.g = 0; s.h = get_h(s.ary);
		s.f = s.g + s.h;
		s.hash = cantor(s.ary, 9);
		int k = 0; //ͨ������������ż�ж��Ƿ�ɽ�
		for (int i = 0; i < 9; ++i)
			for (int j = 0; j < i; ++j) //���i����ǰ�м�������ary[i]����
				if (s.ary[j] != 9 && s.ary[i] < s.ary[j])
					++k; //��ǿ������⣬�ƶ�һ�£��������ı�ż��ֵ
		if(k & 1) cout << "unsolvable" << endl;
		else Astar(s);
	}

	return 0;
}
