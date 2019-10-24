#include <bits/stdc++.h>

using namespace std;

using ll =  long long;
using Pll = pair<ll, ll>;
using Pii = pair<int, int>;

constexpr int N = 100;
constexpr int Q = 1000;
constexpr int A_MAX = 100000;

// 乱数
random_device rnd;
mt19937 mt(rnd());
uniform_int_distribution<> randN(0, N-1);

// 時間計測
chrono::system_clock::time_point start_time, end_time; 
unsigned int duration;

// 盤面
int a[N][N] = {};
int b[N][N] = {};

vector<tuple<int, int, int>> ans; // y, x, h;

inline void input() {
    for(int i=0;i<N;++i) for(int j=0;j<N;++j) cin >> a[i][j];
}

inline bool check_range(int y, int x) {
    return 0 <= y && y < N && 0 <= x && x < N;
}

inline ll calc_diff() {
    ll diff = 0LL;
    for(int i=0;i<N;++i) for(int j=0;j<N;++j) diff = abs(b[i][j] - a[i][j]);
    return diff;
}

inline void solve() {
    start_time = chrono::system_clock::now();
    end_time = chrono::system_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end_time-start_time).count();

    ll min_diff = 1LL << 60;

    while(duration < 5800) {
        vector<tuple<int, int, int>> tmpans;
        for(int qi=0;qi<Q;++qi) {
            int y = randN(mt), x = randN(mt), h = randN(mt)+1;
            for(int dy=0;dy<=h;++dy) {
                for(int dx=0;dx<=h-dy;++dx) {
                    int hh = h - (dx+dy);
                    if(check_range(y+dy, x+dx)) b[y+dy][x+dx] += hh;
                    if(check_range(y-dy, x+dx)) b[y-dy][x+dx] += hh;
                    if(check_range(y+dy, x-dx)) b[y+dy][x-dx] += hh;
                    if(check_range(y-dy, x-dx)) b[y-dy][x-dx] += hh;
                }
            }
            tmpans.emplace_back(y, x, h);
        }

        ll diff = calc_diff();
        if(diff < min_diff) {
            min_diff = diff;
            ans.clear();
            copy(tmpans.begin(), tmpans.end(), back_inserter(ans));
        }

        fill_n(b[0], N*N, 0);

        end_time = chrono::system_clock::now();
        duration = chrono::duration_cast<chrono::milliseconds>(end_time-start_time).count();
    }
}

inline void output() {
    cout << ans.size() << endl;
    for(tuple<int, int, int> t: ans) {
        cout << get<0>(t) << " " << get<1>(t) << " " << get<2>(t) << endl;
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    input();
    solve();
    output();
}
